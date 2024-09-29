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



namespace Oasis {

using std::unique_ptr;
using std::string;
using SoftJin::Uint;
using SoftJin::Ulong;
using SoftJin::HashMap;
using SoftJin::HashPointer;


namespace JLayout {

struct BBox {
    long x_min, y_min, x_max, y_max;
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

private:
    CellName* cellName;
    long x, y;
    Oreal mag, angle;
    bool flip;
    const Repetition* rep;
    // 추가: 여러 반복된 위치를 저장할 수 있도록 벡터 추가
    std::vector<std::pair<long, long>> repeatedPositions; // 반복된 위치들
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

private:
    CellName* name;
    std::unordered_map<JLayout::Layer, std::vector<std::unique_ptr<JShape>>, JLayout::Layer::HashFunction> shapesByLayer;
    std::vector<std::unique_ptr<JPlacement>> placements;
    std::unordered_set<JCell*> children;
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
    JCell* findRootCell(CellName* cellName) const;

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


