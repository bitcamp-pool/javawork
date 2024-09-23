​
#include "layoutbuilder.h"
#include <iostream>

namespace Oasis {

JRectangle::JRectangle(int x, int y, int width, int height, int layer, int datatype, const Repetition* rep)
  : x(x), y(y), width(width), height(height), layer(layer), datatype(datatype), rep(rep) {}

void JRectangle::generateBinary(OasisBuilder& builder) const {
  builder.beginRectangle(layer, datatype, x, y, width, height, rep);
}

JPolygon::JPolygon(int x, int y, int layer, int datatype, const PointList& points, const Repetition* rep)
  : x(x), y(y), layer(layer), datatype(datatype), rep(rep), points(points) {}

void JPolygon::generateBinary(OasisBuilder& builder) const {
  builder.beginPolygon(layer, datatype, x, y, points, rep);
}

JPlacement::JPlacement(CellName* cellName, int x, int y, double mag, double angle, bool flip, const Repetition* repetition)
  : cellName(cellName), x(x), y(y), mag(mag), angle(angle), flip(flip), repetition(repetition) {}

void JPlacement::generateBinary(OasisBuilder& builder) const {
  builder.beginPlacement(cellName, x, y, Oreal(mag), Oreal(angle), flip, repetition);
}

JCell::JCell(CellName* name) : name(name) {}

void JCell::addShape(std::unique_ptr<JShape> shape) {
  shapes.push_back(std::move(shape));
}

void JCell::addPlacement(std::unique_ptr<JPlacement> placement) {
  placements.push_back(std::move(placement));
}

void JCell::addParent(JCell* parent) {
  this->parent = parent;
}

void JCell::addChild(JCell* child) {
  children.insert(child);
}

CellName* JCell::getName() const {
  return name;
}

void JCell::generateBinary(OasisBuilder& builder) const {
  for (const auto& shape : shapes) {
  shape->generateBinary(builder);
  }
  for (const auto& placement : placements) {
  placement->generateBinary(builder);
  }
}

// 부모 셀이 없는 셀도 있음!!!!
void JCellsHierarchy::addChild(CellName* parent, CellName* child, std::unordered_map<CellName*, std::unique_ptr<JCell>>& cells) {
  if (cells.find(parent) != cells.end() && cells.find(child) != cells.end()) {
  JCell* parentCell = cells[parent].get();
  JCell* childCell = cells[child].get();

  parentCell->addChild(childCell);
  childCell->addParent(parentCell);

  hierarchy[child] = parentCell;
  } else {
  std::cerr << "Parent or Child cell not found in cells map" << std::endl;
  }
}

void JCellsHierarchy::addChild(CellName parent, CellName child, std::unordered_map>& cells) {
    // 자식 셀은 반드시 존재해야 함
    if (cells.find(child) != cells.end()) {
        JCell* childCell = cells[child].get();
        
        // 부모 셀을 찾지 못한 경우, 부모가 없음을 허용
        if (cells.find(parent) != cells.end()) {
            JCell* parentCell = cells[parent].get();
            parentCell->addChild(childCell);
            childCell->addParent(parentCell);
            hierarchy[child] = parentCell;
        } else {
            // 부모가 없는 경우, 자식 셀만 추가
            childCell->addParent(nullptr); // 부모가 없음을 명시
            hierarchy[child] = nullptr; // 부모가 없음을 기록
        }
    } else {
        std::cerr << "Child cell not found in cells map" << std::endl;
    }
}







void JCellsHierarchy::generateBinary(OasisBuilder& builder, const std::unordered_map<CellName*, std::unique_ptr<JCell>>& cells) {
  for (const auto& pair : hierarchy) {
  CellName* childCellName = pair.first;
  JCell* parentCell = pair.second;

  if (parentCell != nullptr) {
  parentCell->generateBinary(builder);
  }

  if (childCellName != nullptr) {
  auto childCellIter = cells.find(childCellName);
  if (childCellIter != cells.end()) {
  childCellIter->second->generateBinary(builder);
  }
  }
  }
}

JLayoutBuilder::JLayoutBuilder(OasisBuilder& builder) : builder(builder) {}

void JLayoutBuilder::beginCell(CellName* cellName) {
  // Check if the cellName is already in the map
  if (cells.find(cellName) == cells.end()) {
  auto cell = std::make_unique<JCell>(cellName); // C++14 임!!!!!!!!!!!!!
  cells[cellName] = std::move(cell);
  }

  if (cells[cellName]->parent != nullptr) {
  addChildToHierarchy(cells[cellName]->parent->getName(), cellName);
  }

  builder.beginCell(cellName);
}


void JLayoutBuilder::endCell() {
  if (currentCell) {
  builder.endCell();
  currentCell = nullptr;
  }
}

void JLayoutBuilder::beginRectangle(Ulong layer, Ulong datatype, long x, long y, long width, long height, const Repetition* rep) {
  if (currentCell) {
  auto rectangle = std::make_unique<JRectangle>(x, y, width, height, layer, datatype, rep);
  currentCell->addShape(std::move(rectangle));
  }
}

void JLayoutBuilder::beginPolygon(Ulong layer, Ulong datatype, long x, long y, const PointList& points, const Repetition* rep) {
  if (currentCell) {
  auto polygon = std::make_unique<JPolygon>(x, y, layer, datatype, points, rep);
  currentCell->addShape(std::move(polygon));
  }
}

void JLayoutBuilder::beginPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep) {
  if (cells.begin()->second) {
  auto placement = std::make_unique<JPlacement>(cellName, x, y, mag.getValue(), angle.getValue(), flip, rep);
  cells.begin()->second->addPlacement(std::move(placement));
  addChildToHierarchy(cells.begin()->second->getName(), cellName); // Ensure parent-child linkage
  }
}


void JLayoutBuilder::addChildToHierarchy(CellName* parent, CellName* child) {
  cellHierarchy.addChild(parent, child, cells);
}

void JLayoutBuilder::generateBinary() {
  cellHierarchy.generateBinary(builder, cells);
}

}

