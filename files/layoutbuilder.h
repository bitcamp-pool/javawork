#ifndef OASIS_LAYOUTBUILDER_H
#define OASIS_LAYOUTBUILDER_H

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include "port/hash-table.h"
#include "misc/utils.h"
#include "builder.h"
#include "modal-vars.h"
#include "names.h"
#include "oasis.h"
#include "rectypes.h"
#include "writer.h"

#include <math.h> // 각도 변환을 위해 필요

namespace Oasis {

using std::unique_ptr;
using std::string;
using SoftJin::Uint;
using SoftJin::Ulong;
using SoftJin::HashMap;
using SoftJin::HashPointer;


namespace JLayout {


// 행렬 구조체: 2D 변환을 위한 2x2 행렬
struct Matrix2D {
    double m[2][2];  // 2x2 행렬

    // 좌표에 행렬 곱을 적용하는 함수
    std::pair<long, long> multiply(long x, long y) const {
        long new_x = static_cast<long>(m[0][0] * x + m[0][1] * y);
        long new_y = static_cast<long>(m[1][0] * x + m[1][1] * y);
        return {new_x, new_y};
    }
};

// 회전 변환을 위한 행렬 생성 함수 (각도는 라디안 값으로 입력)
Matrix2D rotationMatrix(double angle);

// BBox 구조체: 도형이나 셀의 경계 영역을 정의합니다.
// 각 좌표는 경계의 최소(min)와 최대(max) 값을 저장합니다.
struct BBox {
    long x_min, y_min, x_max, y_max;

    // 기본 생성자: 최댓값과 최솟값으로 초기화
    BBox() : x_min(LONG_MAX), y_min(LONG_MAX), x_max(LONG_MIN), y_max(LONG_MIN) {}

    // 인자를 받는 생성자
    BBox(long x_min, long y_min, long x_max, long y_max)
        : x_min(x_min), y_min(y_min), x_max(x_max), y_max(y_max) {}

    // 두 BBox 간의 병합 함수: 두 BBox를 합쳐서 더 큰 영역을 커버하는 BBox 생성
    void merge(const BBox& other) {
        x_min = std::min(x_min, other.x_min);
        y_min = std::min(y_min, other.y_min);
        x_max = std::max(x_max, other.x_max);
        y_max = std::max(y_max, other.y_max);
    }

    // 좌표 변환을 적용하여 새로운 BBox를 계산하는 함수
    BBox transform(const Matrix2D& matrix) const {
        auto [x1, y1] = matrix.multiply(x_min, y_min);
        auto [x2, y2] = matrix.multiply(x_max, y_min);
        auto [x3, y3] = matrix.multiply(x_min, y_max);
        auto [x4, y4] = matrix.multiply(x_max, y_max);

        long new_x_min = std::min({x1, x2, x3, x4});
        long new_y_min = std::min({y1, y2, y3, y4});
        long new_x_max = std::max({x1, x2, x3, x4});
        long new_y_max = std::max({y1, y2, y3, y4});

        return {new_x_min, new_y_min, new_x_max, new_y_max};
    }
};





enum Type { Rectangle, Square, Polygon, Path, Trapezoid, Circle, Text };

class Layer {
public:
    Ulong layer;
    Ulong datatype;

    Layer(Ulong lay, Ulong dtype) : layer(lay), datatype(dtype) {}

    bool operator==(const Layer& other) const {
        return layer == other.layer && datatype == other.datatype;
    }

    // 해시 함수 정의
    struct HashFunction {
        size_t operator()(const Layer& l) const {
            return std::hash<Ulong>()(l.layer) ^ (std::hash<Ulong>()(l.datatype) << 1);
        }
    };
};


// Repetition 처리 함수
void unpackRepetition(long x, long y, const Repetition* rep, std::vector<std::pair<long, long>>& positions);

}  // namespace JLayout





// Shape 정의
class JShape {
public:
    virtual JLayout::BBox getBBox() const = 0;
    virtual void generateBinary(OasisBuilder& builder, Ulong layer, Ulong datatype) const = 0;
    virtual std::vector<std::pair<long, long>> getRepeatedPositions() const = 0;
    virtual ~JShape() = default;

    JLayout::Type getShapeType() const { return shapeType; }

protected:
    JLayout::Type shapeType;

    JShape(JLayout::Type type) : shapeType(type) {}
};

class JRectangle : public JShape {
public:
    JRectangle(long x, long y, long width, long height, const Repetition* rep)
        : JShape(JLayout::Rectangle), x(x), y(y), width(width), height(height), rep(rep) {
        // Repetition 처리하여 repeatedPositions에 저장
        JLayout::unpackRepetition(x, y, rep, repeatedPositions);
    }

    JLayout::BBox getBBox() const override;
    void generateBinary(OasisBuilder& builder, Ulong layer, Ulong datatype) const override;

    std::vector<std::pair<long, long> > getRepeatedPositions() const override;

private:
    long x, y, width, height;
    const Repetition* rep;
    std::vector<std::pair<long, long>> repeatedPositions;  // 반복된 위치들
};

class JSquare : public JShape {
public:
    JSquare(long x, long y, long width, const Repetition* rep)
        : JShape(JLayout::Square), x(x), y(y), width(width), rep(rep) {
        JLayout::unpackRepetition(x, y, rep, repeatedPositions);
    }

    JLayout::BBox getBBox() const override;
    void generateBinary(OasisBuilder& builder, Ulong layer, Ulong datatype) const override;

    std::vector<std::pair<long, long> > getRepeatedPositions() const override;

private:
    long x, y, width;
    const Repetition* rep;
    std::vector<std::pair<long, long>> repeatedPositions;  // 반복된 위치들
};

class JPolygon : public JShape {
public:
    JPolygon(long x, long y, const PointList& points, const Repetition* rep)
        : JShape(JLayout::Polygon), x(x), y(y), points(points), rep(rep) {
        JLayout::unpackRepetition(x, y, rep, repeatedPositions);
    }

    JLayout::BBox getBBox() const override;
    void generateBinary(OasisBuilder& builder, Ulong layer, Ulong datatype) const override;

    std::vector<std::pair<long, long> > getRepeatedPositions() const override;

private:
    long x, y;
    PointList points;
    const Repetition* rep;
    std::vector<std::pair<long, long>> repeatedPositions;  // 반복된 위치들
};

// Path 도형 정의
class JPath : public JShape {
public:
    JPath(long x, long y, long halfwidth, long startExtn, long endExtn, const PointList& points, const Repetition* rep)
        : JShape(JLayout::Path), x(x), y(y), halfwidth(halfwidth), startExtn(startExtn), endExtn(endExtn), points(points), rep(rep) {
        JLayout::unpackRepetition(x, y, rep, repeatedPositions);
    }

    JLayout::BBox getBBox() const override;
    void generateBinary(OasisBuilder& builder, Ulong layer, Ulong datatype) const override;

    std::vector<std::pair<long, long> > getRepeatedPositions() const override;

private:
    long x, y;
    long halfwidth, startExtn, endExtn;
    PointList points;
    const Repetition* rep;
    std::vector<std::pair<long, long>> repeatedPositions;  // 반복된 위치들
};

// Trapezoid 도형 정의
class JTrapezoid : public JShape {
public:
    // 트랩레조이드의 좌표와 기하학적 속성을 멤버로 정의
    JTrapezoid(long x, long y, const class Trapezoid& trapezoid, const Repetition* rep)
        : JShape(JLayout::Trapezoid), x(x), y(y), trapezoid(trapezoid), rep(rep) {
        JLayout::unpackRepetition(x, y, rep, repeatedPositions);
    }

    JLayout::BBox getBBox() const override;
    void generateBinary(OasisBuilder& builder, Ulong layer, Ulong datatype) const override;

    std::vector<std::pair<long, long> > getRepeatedPositions() const override;

private:
    long x, y;
    class Trapezoid trapezoid;  // Trapezoid는 구조체로 정의된 도형의 속성 (예: 두 변의 길이, 높이)
    const Repetition* rep;
    std::vector<std::pair<long, long>> repeatedPositions;  // 반복된 위치들
};


// Circle 도형 정의
class JCircle : public JShape {
public:
    JCircle(long x, long y, long radius, const Repetition* rep)
        : JShape(JLayout::Circle), x(x), y(y), radius(radius), rep(rep) {
        JLayout::unpackRepetition(x, y, rep, repeatedPositions);
    }

    JLayout::BBox getBBox() const override;
    void generateBinary(OasisBuilder& builder, Ulong layer, Ulong datatype) const override;

    std::vector<std::pair<long, long> > getRepeatedPositions() const override;

private:
    long x, y, radius;
    const Repetition* rep;
    std::vector<std::pair<long, long>> repeatedPositions;  // 반복된 위치들
};

// Text 도형 정의
class JText : public JShape {
public:
    JText(long x, long y, TextString* text, const Repetition* rep)
        : JShape(JLayout::Text), x(x), y(y), text(text), rep(rep) {
        JLayout::unpackRepetition(x, y, rep, repeatedPositions);
    }

    JLayout::BBox getBBox() const override;
    void generateBinary(OasisBuilder& builder, Ulong layer, Ulong datatype) const override;

    std::vector<std::pair<long, long> > getRepeatedPositions() const override;

private:
    long x, y;
    TextString* text;
    const Repetition* rep;
    std::vector<std::pair<long, long>> repeatedPositions;  // 반복된 위치들
};

// Placement 정의
class JPlacement {
public:
    JPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep);
    void generateBinary(OasisBuilder& builder) const;

    std::vector<std::pair<long, long>> getRepeatedPositions() const;

    CellName* getName() const;

    long getX() const;
    long getY() const;
    Oreal getMag() const;
    Oreal getAngle() const;
    bool getFlip() const;

private:
    CellName* cellName;
    long x, y;
    Oreal mag, angle;
    bool flip;
    const Repetition* rep;
    std::vector<std::pair<long, long>> repeatedPositions;  // 반복된 위치 저장
};



// Cell 정의
class JCell {
public:
    explicit JCell(CellName* name);

    void addShape(const JLayout::Layer& layerKey, std::unique_ptr<JShape> shape);
    void addPlacement(std::unique_ptr<JPlacement> placement);
    void addParent(JCell* parent);
    void addChild(JCell* child);
    CellName* getName() const;
    void generateBinary(OasisBuilder& builder) const;

    JCell* parent = nullptr;

    // shapesByLayer의 getter 함수 (const 참조로 반환)
    const std::unordered_map<JLayout::Layer, std::vector<std::unique_ptr<JShape>>, JLayout::Layer::HashFunction>& getShapesByLayer() const {
        return shapesByLayer;
    }
    // placements 벡터에 대한 const 참조 반환
    const std::vector<std::unique_ptr<JPlacement>>& getPlacements() const;


    // BBox 캐시를 설정하는 함수
    void setCachedBBox(std::unique_ptr<JLayout::BBox> bbox) {
        cachedBBox = std::move(bbox);
    }

    // BBox 캐시를 반환하는 함수
    const JLayout::BBox* getCachedBBox() const {
        return cachedBBox.get();  // unique_ptr에서 포인터를 반환
    }

private:
    CellName* name;
    std::unordered_map<JLayout::Layer, std::vector<std::unique_ptr<JShape>>, JLayout::Layer::HashFunction> shapesByLayer;
    std::vector<std::unique_ptr<JPlacement>> placements;
    std::unordered_set<JCell*> children;

    // BBox 캐시 변수
    std::unique_ptr<JLayout::BBox> cachedBBox = nullptr;
};


// LayoutBuilder 정의
class JLayoutBuilder : public OasisBuilder {
public:
    explicit JLayoutBuilder(OasisBuilder& builder);

    void beginFile(const string& version, const Oreal& unit, Validation::Scheme valScheme) override;
    void beginCell(CellName* cellName) override;
    void endCell() override;
    void endFile() override;

    void beginPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep) override;
    void beginRectangle(Ulong layer, Ulong datatype, long x, long y, long width, long height, const Repetition* rep) override;
    void beginPolygon(Ulong layer, Ulong datatype, long x, long y, const PointList& points, const Repetition* rep) override;
    void beginText(Ulong textlayer, Ulong texttype, long x, long y, TextString* text, const Repetition* rep) override;
    void beginPath(Ulong layer, Ulong datatype, long x, long y, long halfwidth, long startExtn, long endExtn, const PointList& points, const Repetition* rep) override;
    void beginTrapezoid(Ulong layer, Ulong datatype, long x, long y, const Trapezoid& trap, const Repetition* rep) override;
    void beginCircle(Ulong layer, Ulong datatype, long x, long y, long radius, const Repetition* rep) override;

    void updateCellHierarchy(CellName* parent, CellName* child);
    JCell* findRefCell(CellName* cellName) const;

    // Cell BBox 계산 함수
    JLayout::BBox calculateCellBBox(const JCell* cell, std::unordered_set<const JCell*>& visited) const;

    // 레이아웃 정보를 파일로 생성하는 함수
    void generateBinary();

    // 레이아웃 정보를 터미널 출력하는 함수
    void printLayoutInfo() const;

private:
    OasisBuilder& creator;
    std::string fileVersion;
    Oreal fileUnit;
    Validation::Scheme fileValidationScheme;

    std::unordered_map<std::string, std::unique_ptr<JCell>> cells;
    JCell* currentCell = nullptr;

    // OasisBuilder interface
public:

    void beginXElement(SoftJin::Ulong attribute, const string &data) override;
    void beginXGeometry(SoftJin::Ulong layer, SoftJin::Ulong datatype, long x, long y, SoftJin::Ulong attribute, const string &data, const Repetition *rep) override;

    void addFileProperty(Property *prop) override;
    void addCellProperty(Property *prop) override;
    void addElementProperty(Property *prop) override;

    void registerCellName(CellName *cellName) override;
    void registerTextString(TextString *textString) override;
    void registerPropName(PropName *propName) override;
    void registerPropString(PropString *propString) override;
    void registerLayerName(LayerName *layerName) override;
    void registerXName(XName *xname) override;

};

} // namespace Oasis

#endif // OASIS_LAYOUTBUILDER_H


