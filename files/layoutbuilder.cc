#include "layoutbuilder.h"
#include <iostream>

namespace Oasis {

JRectangle::JRectangle(long x, long y, long width, long height, Ulong layer, Ulong datatype, const Repetition* rep)
    : x(x), y(y), width(width), height(height), layer(layer), datatype(datatype), rep(rep) {}

void JRectangle::generateBinary(OasisBuilder& builder) const {
    builder.beginRectangle(layer, datatype, x, y, width, height, rep);
}

JPolygon::JPolygon(long x, long y, Ulong layer, Ulong datatype, const PointList& points, const Repetition* rep)
    : x(x), y(y), layer(layer), datatype(datatype), rep(rep), points(points) {}

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

void JCellsHierarchy::addChild(CellName* parent, CellName* child, std::unordered_map<CellName*, std::unique_ptr<JCell>>& cells) {
    auto parentCellIt = cells.find(parent);
    auto childCellIt = cells.find(child);

    if (parentCellIt != cells.end() && childCellIt != cells.end()) {
        JCell* parentCell = parentCellIt->second.get();
        JCell* childCell = childCellIt->second.get();

        parentCell->addChild(childCell);
        childCell->addParent(parentCell);

        hierarchy[child] = parentCell;
    } else {
        // 부모 셀 또는 자식 셀이 없는 경우 처리.
        if (parentCellIt == cells.end()) {
            hierarchy[child] = nullptr;  // 부모가 없는 경우 최상위 셀로 간주
        }
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

void JLayoutBuilder::beginFile(const string& version, const Oreal& unit, Validation::Scheme valScheme) {
    fileVersion = version;
    fileUnit = unit;
    fileValidationScheme = valScheme;

    // 실제 파일의 메타정보를 기록하기 위해 OasisBuilder의 beginFile 호출
    builder.beginFile(version, unit, valScheme);
}

void JLayoutBuilder::beginCell(CellName* cellName) {
    auto cell = std::unique_ptr<JCell>(new JCell(cellName));
    currentCell = cell.get(); // 새로운 셀을 currentCell로 설정
    cells[cellName] = std::move(cell);  // 셀을 map에 저장

    if (cells[cellName]->parent != nullptr) {
        addChildToHierarchy(cells[cellName]->parent->getName(), cellName);
    }

    builder.beginCell(cellName);
}

void JLayoutBuilder::endCell() {
    builder.endCell();
}

void JLayoutBuilder::beginRectangle(Ulong layer, Ulong datatype, long x, long y, long width, long height, const Repetition* rep) {
    if (currentCell) {
        std::unique_ptr<JRectangle> rectangle(new JRectangle(x, y, width, height, layer, datatype, rep));
        currentCell->addShape(std::move(rectangle));
    }
}

void JLayoutBuilder::beginPolygon(Ulong layer, Ulong datatype, long x, long y, const PointList& points, const Repetition* rep) {
    if (currentCell) {
        std::unique_ptr<JPolygon> polygon(new JPolygon(x, y, layer, datatype, points, rep));
        currentCell->addShape(std::move(polygon));
    }
}

void JLayoutBuilder::beginPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep) {
    if (currentCell) {
        std::unique_ptr<JPlacement> placement(new JPlacement(cellName, x, y, mag, angle, flip, rep));
        currentCell->addPlacement(std::move(placement));
        addChildToHierarchy(currentCell->getName(), cellName);
    }
}

void JLayoutBuilder::addChildToHierarchy(CellName* parent, CellName* child) {
    cellHierarchy.addChild(parent, child, cells);
}

JCell* JLayoutBuilder::findRootCell(CellName* cellName) const {
    auto it = cells.find(cellName);
    if (it == cells.end()) {
        return nullptr; // 해당 셀이 존재하지 않음
    }

    // 지정된 셀의 최상위 셀을 탐색하여 반환합니다. parent가 nullptr일 때까지 탐색합니다.
    JCell* currentCell = it->second.get();
    while (currentCell->parent != nullptr) {
        currentCell = currentCell->parent;
    }
    return currentCell; // 최상위 셀 반환
}

void JLayoutBuilder::generateBinary() {
    cellHierarchy.generateBinary(builder, cells);
}

}
