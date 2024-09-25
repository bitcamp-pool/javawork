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

namespace Oasis
{

    using SoftJin::HashMap;
    using SoftJin::HashPointer;
    using SoftJin::Uint;
    using SoftJin::Ulong;
    using std::string;
    using std::unique_ptr;

    struct BBox
    {
        long x_min, y_min, x_max, y_max;
    };

    // Shape 정의
    class JShape
    {
    public:
        enum Type
        {
            Rectangle,
            Polygon,
            Path,
            Trapezoid,
            Circle,
            Text
        };

        virtual BBox getBBox() const = 0; 
        virtual void generateBinary(OasisBuilder &builder) const = 0;
        virtual ~JShape() = default;

    protected:
        Type shapeType;
        Ulong layer;
        Ulong datatype;

        JShape(Type type, Ulong lay, Ulong dtype)
            : shapeType(type), layer(lay), datatype(dtype) {}
    };

    class JRectangle : public JShape
    {
    public:
        JRectangle(long x, long y, long width, long height, Ulong layer, Ulong datatype, const Repetition *rep)
            : JShape(Rectangle, layer, datatype), x(x), y(y), width(width), height(height), rep(rep) {}

        BBox getBBox() const override;
        void generateBinary(OasisBuilder &builder) const override;

    private:
        long x, y, width, height;
        const Repetition *rep;
    };

    class JPolygon : public JShape
    {
    public:
        JPolygon(long x, long y, Ulong layer, Ulong datatype, const PointList &points, const Repetition *rep)
            : JShape(Polygon, layer, datatype), x(x), y(y), points(points), rep(rep) {}

        BBox getBBox() const override
        void generateBinary(OasisBuilder &builder) const override;

    private:
        long x, y;
        PointList points;
        const Repetition *rep;
    };

    // Placement 정의
    class JPlacement
    {
    public:
        JPlacement(CellName *cellName, long x, long y, const Oreal &mag, const Oreal &angle, bool flip, const Repetition *rep);
        void generateBinary(OasisBuilder &builder) const;

    private:
        CellName *cellName;
        long x, y;
        Oreal mag, angle;
        bool flip;
        const Repetition *rep;
    };

    // Cell 정의
    class JCell
    {
    public:
        explicit JCell(CellName *name);

        void addShape(std::unique_ptr<JShape> shape);
        void addPlacement(std::unique_ptr<JPlacement> placement);
        void addParent(JCell *parent);
        void addChild(JCell *child);
        CellName *getName() const;
        void generateBinary(OasisBuilder &builder) const;

        JCell *parent = nullptr;

    private:
        CellName *name;
        std::vector<std::unique_ptr<JShape>> shapes;
        std::vector<std::unique_ptr<JPlacement>> placements;
        std::unordered_set<JCell *> children;
    };

    // LayoutBuilder 정의
    class JLayoutBuilder : public OasisBuilder
    {
    public:
        explicit JLayoutBuilder(OasisBuilder &builder);

        void beginFile(const string &version, const Oreal &unit, Validation::Scheme valScheme) override;
        void beginCell(CellName *cellName) override;
        void endCell() override;
        void beginRectangle(Ulong layer, Ulong datatype, long x, long y, long width, long height, const Repetition *rep) override;
        void beginPolygon(Ulong layer, Ulong datatype, long x, long y, const PointList &points, const Repetition *rep) override;
        void beginPlacement(CellName *cellName, long x, long y, const Oreal &mag, const Oreal &angle, bool flip, const Repetition *rep) override;

        void updateCellHierarchy(CellName *parent, CellName *child);

        JCell *findRootCell(CellName *cellName) const;
        void generateBinary();

    private:
        OasisBuilder &builder;

        std::string fileVersion;
        Oreal fileUnit;
        Validation::Scheme fileValidationScheme;

        std::unordered_map<std::string, std::unique_ptr<JCell>> cells;
        JCell *currentCell = nullptr;
    };

}

#endif // OASIS_LAYOUTBUILDER_H
