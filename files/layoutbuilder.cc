#include "layoutbuilder.h"

namespace Oasis {


void JRectangle::generateBinary(OasisBuilder& builder) const {
    builder.beginRectangle(layer, datatype, x, y, width, height, rep);
}

void JPolygon::generateBinary(OasisBuilder& builder) const {
    builder.beginPolygon(layer, datatype, x, y, points, rep);
}

JPlacement::JPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep)
    : cellName(cellName), x(x), y(y), mag(mag), angle(angle), flip(flip), rep(rep) {}

void JPlacement::generateBinary(OasisBuilder& builder) const {
    builder.beginPlacement(cellName, x, y, mag, angle, flip, rep);
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

JLayoutBuilder::JLayoutBuilder(OasisBuilder& builder)
    : builder(builder) {}

void JLayoutBuilder::beginFile(const std::string& version, const Oreal& unit, Validation::Scheme valScheme) {
    fileVersion = version;
    fileUnit = unit;
    fileValidationScheme = valScheme;
    builder.beginFile(version, unit, valScheme);
}

void JLayoutBuilder::beginCell(CellName* cellName) {
    currentCell = new JCell(cellName);
    cells[cellName->getName()] = std::unique_ptr<JCell>(currentCell);

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
        currentCell->addShape(std::unique_ptr<JShape>(new JRectangle(x, y, width, height, layer, datatype, rep)));
    }
}

void JLayoutBuilder::beginPolygon(Ulong layer, Ulong datatype, long x, long y, const PointList& points, const Repetition* rep) {
    if (currentCell) {
        currentCell->addShape(std::unique_ptr<JShape>(new JPolygon(x, y, layer, datatype, points, rep)));
    }
}

void JLayoutBuilder::beginPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep) {
    if (currentCell) {
        currentCell->addPlacement(std::unique_ptr<JPlacement>(new JPlacement(cellName, x, y, mag, angle, flip, rep)));
        updateCellHierarchy(currentCell->getName(), cellName);
    }
}

void JLayoutBuilder::updateCellHierarchy(CellName* parent, CellName* child) {
    auto parentCell = cells.find(parent->getName());
    if (parentCell != cells.end()) {
        auto childCell = cells.find(child->getName());
        if (childCell != cells.end()) {
            parentCell->second->addChild(childCell->second.get());
            childCell->second->addParent(parentCell->second.get());
        }
    }
}

JCell* JLayoutBuilder::findRootCell(CellName* cellName) const {
    auto cellIter = cells.find(cellName->getName());
    if (cellIter != cells.end()) {
        return cellIter->second.get();
    }
    return nullptr;
}

void JLayoutBuilder::generateBinary() {
    for (const auto& cellPair : cells) {
        JCell* rootCell = findRootCell(cellPair.second->getName());
        if (rootCell) {
            rootCell->generateBinary(builder);
        }
    }
}

} // namespace Oasis
