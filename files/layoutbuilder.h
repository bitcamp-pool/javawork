​
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

class JShape {
public:
  virtual void generateBinary(OasisBuilder& builder) const = 0;
  virtual ~JShape() = default;
};

class JRectangle : public JShape {
public:
  JRectangle(long x, long y, long width, long height, Ulong layer, Ulong datatype, const Repetition* rep);
  void generateBinary(OasisBuilder& builder) const override;

private:
  long x, y, width, height;
  Ulong layer, datatype;
  const Repetition* rep;
};

class JPolygon : public JShape {
public:
  JPolygon(long x, long y, Ulong layer, Ulong datatype, const PointList& points, const Repetition* rep);
  void generateBinary(OasisBuilder& builder) const override;

private:
  long x, y;
  Ulong layer, datatype;
  const Repetition* rep;
  PointList points;
};

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
};

class JCell {
public:
  explicit JCell(CellName* name);

  void addShape(std::unique_ptr<JShape> shape);
  void addPlacement(std::unique_ptr<JPlacement> placement);
  void addParent(JCell* parent);
  void addChild(JCell* child);
  CellName* getName() const;
  void generateBinary(OasisBuilder& builder) const;

  JCell* parent = nullptr;

private:
  CellName* name;
  std::vector<std::unique_ptr<JShape>> shapes;
  std::vector<std::unique_ptr<JPlacement>> placements;
  std::unordered_set<JCell*> children;
};

class JCellsHierarchy {
public:
  void addChild(CellName* parent, CellName* child, std::unordered_map<CellName*, std::unique_ptr<JCell>>& cells);
  void generateBinary(OasisBuilder& builder, const std::unordered_map<CellName*, std::unique_ptr<JCell>>& cells);

private:
  std::unordered_map<CellName*, JCell*> hierarchy;
};

class JLayoutBuilder : public OasisBuilder {
public:
  explicit JLayoutBuilder(OasisBuilder& builder);
  void beginCell(CellName* cellName) override;
  void endCell() override;
  void beginRectangle(Ulong layer, Ulong datatype, long x, long y, long width, long height, const Repetition* rep) override;
  void beginPolygon(Ulong layer, Ulong datatype, long x, long y, const PointList& points, const Repetition* rep) override;
  void beginPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep) override;
  void addChildToHierarchy(CellName* parent, CellName* child);
  void generateBinary();

private:
  OasisBuilder& builder;
  std::unordered_map<CellName*, std::unique_ptr<JCell>> cells;
  JCell* currentCell = nullptr;
  JCellsHierarchy cellHierarchy;
};

}

#endif // OASIS_LAYOUTBUILDER_H

