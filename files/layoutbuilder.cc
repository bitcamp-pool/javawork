#include "layoutbuilder.h"
#include <iostream>
#include <iomanip>


namespace Oasis {
using namespace JLayout;

// Repetition 처리 함수
void JLayout::unpackRepetition(long x, long y, const Repetition* rep, std::vector<std::pair<long, long>>& positions) {
    if (!rep) {
        // Repetition이 없으면 단일 위치를 저장
        positions.push_back({x, y});
        return;
    }

    // 반복 타입에 따른 배치 좌표 처리
    switch (rep->getType()) {
    case Rep_Matrix: {
        Ulong xdimen = rep->getMatrixXdimen();
        Ulong ydimen = rep->getMatrixYdimen();
        long  xspace = rep->getMatrixXspace();
        long  yspace = rep->getMatrixYspace();

        for (Ulong i = 0; i < xdimen; ++i) {
            for (Ulong j = 0; j < ydimen; ++j) {
                long newX = x + i * xspace;
                long newY = y + j * yspace;
                positions.push_back({newX, newY});
            }
        }
        break;
    }
    case Rep_UniformX: {
        Ulong dimen = rep->getDimen();
        long xspace = rep->getUniformXspace();

        for (Ulong i = 0; i < dimen; ++i) {
            long newX = x + i * xspace;
            positions.push_back({newX, y});
        }
        break;
    }
    case Rep_UniformY: {
        Ulong dimen = rep->getDimen();
        long yspace = rep->getUniformYspace();

        for (Ulong i = 0; i < dimen; ++i) {
            long newY = y + i * yspace;
            positions.push_back({x, newY});
        }
        break;
    }
    case Rep_TiltedMatrix: {
        Ulong ndimen = rep->getMatrixNdimen();
        Ulong mdimen = rep->getMatrixMdimen();
        Delta  ndisp = rep->getMatrixNdelta();
        Delta  mdisp = rep->getMatrixMdelta();

        for (Ulong i = 0; i < ndimen; ++i) {
            for (Ulong j = 0; j < mdimen; ++j) {
                long newX = x + i * ndisp.x + j * mdisp.x;
                long newY = y + i * ndisp.y + j * mdisp.y;
                positions.push_back({newX, newY});
            }
        }
        break;
    }
    case Rep_Diagonal: {
        Ulong dimen = rep->getDimen();
        Delta delta = rep->getDiagonalDelta();

        for (Ulong i = 0; i < dimen; ++i) {
            long newX = x + i * delta.x;
            long newY = y + i * delta.y;
            positions.push_back({newX, newY});
        }
        break;
    }
    case Rep_Arbitrary:
    case Rep_GridArbitrary: {
        Ulong dimen = rep->getDimen();

        for (Ulong i = 0; i < dimen; ++i) {
            Delta delta = rep->getDelta(i);
            long newX = x + delta.x;
            long newY = y + delta.y;
            positions.push_back({newX, newY});
        }
        break;
    }
    // Varying 및 GridVarying 처리
    case Rep_VaryingX :
    case Rep_GridVaryingX : {
        Ulong dimen = rep->getDimen();

        for (Ulong i = 0; i < dimen; ++i){
            long newX = x + rep->getVaryingXoffset(i);
            positions.push_back({newX, y});
        }
        break;
    }
    case Rep_VaryingY :
    case Rep_GridVaryingY : {
        Ulong dimen = rep->getDimen();

        for (Ulong i = 0; i < dimen; ++i){
            long newY = y + rep->getVaryingYoffset(i);
            positions.push_back({x, newY});
        }
        break;
    }
    default:
        // 기본 단일 배치
        positions.push_back({x, y});
        break;
    }
}

// JRectangle Implementation

BBox JRectangle::getBBox() const {
    long x_min = LONG_MAX, y_min = LONG_MAX;
    long x_max = LONG_MIN, y_max = LONG_MIN;

    x_min = std::min(x_min, x);
    y_min = std::min(y_min, y);
    x_max = std::max(x_max, x + width);
    y_max = std::max(y_max, y + height);

    return {x_min, y_min, x_max, y_max};
}


void JRectangle::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions){
        creator.beginRectangle(layer, datatype, pos.first, pos.second, width, height, nullptr);
    }
}

std::vector<std::pair<long, long> > JRectangle::getRepeatedPositions() const
{
    return repeatedPositions;
}

// JSquare Implementation

BBox JSquare::getBBox() const {
    long x_min = LONG_MAX, y_min = LONG_MAX;
    long x_max = LONG_MIN, y_max = LONG_MIN;

    // 정사각형이므로 width = height
    x_min = std::min(x_min, x);
    y_min = std::min(y_min, y);
    x_max = std::max(x_max, x + width);
    y_max = std::max(y_max, y + width);

    return {x_min, y_min, x_max, y_max};
}


void JSquare::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginRectangle(layer, datatype, pos.first, pos.second, width, width, nullptr);
    }
}

std::vector<std::pair<long, long> > JSquare::getRepeatedPositions() const
{
    return repeatedPositions;
}

// JPolygon Implementation

BBox JPolygon::getBBox() const {
    long x_min = LONG_MAX, y_min = LONG_MAX;
    long x_max = LONG_MIN, y_max = LONG_MIN;

    // Calculate BBox from the points list
    for (const auto& point : points) {
        if (point.x < x_min) x_min = point.x;
        if (point.x > x_max) x_max = point.x;
        if (point.y < y_min) y_min = point.y;
        if (point.y > y_max) y_max = point.y;
    }
    return {x_min + x , y_min + y, x_max + x, y_max + y};
}

void JPolygon::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginPolygon(layer, datatype, pos.first, pos.second, points, nullptr);
    }
}

std::vector<std::pair<long, long> > JPolygon::getRepeatedPositions() const
{
    return repeatedPositions;
}


// JPath Implementation

BBox JPath::getBBox() const {
    long x_min = LONG_MAX, y_min = LONG_MAX;
    long x_max = LONG_MIN, y_max = LONG_MIN;

    for (const auto& point : points) {
        if (point.x < x_min) x_min = point.x;
        if (point.x > x_max) x_max = point.x;
        if (point.y < y_min) y_min = point.y;
        if (point.y > y_max) y_max = point.y;
    }
    return {x_min + x, y_min + y, x_max + x, y_max + y};
}

void JPath::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginPath(layer, datatype, pos.first, pos.second, halfwidth, startExtn, endExtn, points, nullptr);
    }
}

std::vector<std::pair<long, long> > JPath::getRepeatedPositions() const
{
    return repeatedPositions;
}

// JTrapezoid Implementation

BBox JTrapezoid::getBBox() const {
    long x_min = LONG_MAX, y_min = LONG_MAX;
    long x_max = LONG_MIN, y_max = LONG_MIN;

    x_min = std::min(x_min, x);
    y_min = std::min(y_min, y);
    x_max = std::max(x_max, x + trapezoid.getWidth());
    y_max = std::max(y_max, y + trapezoid.getHeight());

    return {x_min, y_min, x_max, y_max};
}


void JTrapezoid::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginTrapezoid(layer, datatype, pos.first, pos.second, trapezoid, nullptr);
    }
}

std::vector<std::pair<long, long> > JTrapezoid::getRepeatedPositions() const
{
    return repeatedPositions;
}

// JCircle Implementation

BBox JCircle::getBBox() const {
    long x_min = x - radius;
    long y_min = y - radius;
    long x_max = x + radius;
    long y_max = y + radius;

    return {x_min, y_min, x_max, y_max};
}


void JCircle::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginCircle(layer, datatype, pos.first, pos.second, radius, nullptr);
    }
}

std::vector<std::pair<long, long> > JCircle::getRepeatedPositions() const
{
    return repeatedPositions;
}

// JText Implementation

BBox JText::getBBox() const {
    long x_min = LONG_MAX, y_min = LONG_MAX;
    long x_max = LONG_MIN, y_max = LONG_MIN;

    long textWidth = text->getName().length() * 10;  // 텍스트 폭 계산 (임시)
    x_min = std::min(x_min, x);
    y_min = std::min(y_min, y);
    x_max = std::max(x_max, x + textWidth);
    y_max = std::max(y_max, y + 20);  // 텍스트 높이 임시 값

    return {x_min, y_min, x_max, y_max};
}


void JText::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginText(layer, datatype, pos.first, pos.second, text, nullptr);
    }
}

std::vector<std::pair<long, long> > JText::getRepeatedPositions() const
{
    return repeatedPositions;
}


// JPlacement Implementation

JPlacement::JPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep)
    : cellName(cellName), x(x), y(y), mag(mag), angle(angle), flip(flip), rep(rep) {
    JLayout::unpackRepetition(x, y, rep, repeatedPositions);
}

void JPlacement::generateBinary(OasisBuilder& creator) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginPlacement(cellName, pos.first, pos.second, mag, angle, flip, nullptr);
    }
}

std::vector<std::pair<long, long> > JPlacement::getRepeatedPositions() const
{
    return repeatedPositions;
}

CellName *JPlacement::getName() const
{
    return cellName;
}

long JPlacement::getX() const
{
    return x;
}

long JPlacement::getY() const
{
    return y;
}


// JCell Implementation

JCell::JCell(CellName* name)
    : name(name) {}

void JCell::addShape(const Layer& layerKey, std::unique_ptr<JShape> shape) {
    shapesByLayer[layerKey].push_back(std::move(shape));
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

void JCell::generateBinary(OasisBuilder& creator) const {

    // Generate placements
    for (const auto& placement : placements) {
        placement->generateBinary(creator);
    }

    // Generate shapes and print BBox information
    for (const auto& pair : shapesByLayer) {
        Ulong layer     = pair.first.layer;
        Ulong datatype  = pair.first.datatype;

        for (const auto& shape : pair.second) {

            switch (shape->getShapeType()) {
            case JLayout::Rectangle:
                static_cast<JRectangle*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JLayout::Square:
                static_cast<JSquare*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JLayout::Polygon:
                static_cast<JPolygon*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JLayout::Path:
                static_cast<JPath*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JLayout::Trapezoid:
                static_cast<JTrapezoid*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JLayout::Circle:
                static_cast<JCircle*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JLayout::Text:
                static_cast<JText*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            default:
                throw std::runtime_error("Unknown shape type");
            }
        }
    }
}


const std::vector<std::unique_ptr<JPlacement>>& JCell::getPlacements() const {
    return placements;
}

// JLayoutBuilder Implementation
JLayoutBuilder::JLayoutBuilder(OasisBuilder& creator)
    : creator(creator) {}

void JLayoutBuilder::beginFile(const std::string& version, const Oreal& unit, Validation::Scheme valScheme) {
    fileVersion = version;
    fileUnit = unit;
    fileValidationScheme = valScheme;

    creator.beginFile(version, unit, valScheme);
}

void JLayoutBuilder::beginCell(CellName* cellName) {
    currentCell = new JCell(cellName);
    cells[cellName->getName()] = std::unique_ptr<JCell>(currentCell);
}

void JLayoutBuilder::endCell() {
    currentCell = nullptr;
}

void JLayoutBuilder::endFile()
{
    generateBinary();
}

void JLayoutBuilder::beginRectangle(Ulong layer, Ulong datatype, long x, long y, long width, long height, const Repetition* rep) {
    if (currentCell) {
        Layer layerKey{layer, datatype};
        if (width == height){
            currentCell->addShape(layerKey, std::unique_ptr<JShape>(new JSquare(x, y, width, rep)));
        }
        currentCell->addShape(layerKey, std::unique_ptr<JShape>(new JRectangle(x, y, width, height, rep)));
    }
}

void JLayoutBuilder::beginPolygon(Ulong layer, Ulong datatype, long x, long y, const PointList& points, const Repetition* rep) {
    if (currentCell) {
        Layer layerKey{layer, datatype};
        currentCell->addShape(layerKey, std::unique_ptr<JShape>(new JPolygon(x, y, points, rep)));
    }
}

void JLayoutBuilder::beginPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep) {
    if (!currentCell) {
        return;
    }

    std::unique_ptr<JPlacement> placement(new JPlacement(cellName, x, y, mag, angle, flip, rep));
    currentCell->addPlacement(std::move(placement));
    updateCellHierarchy(currentCell->getName(), cellName);
}

void JLayoutBuilder::beginText(Ulong textlayer, Ulong texttype, long x, long y, TextString* text, const Repetition* rep) {
    if (currentCell) {
        Layer layerKey{textlayer, texttype};
        currentCell->addShape(layerKey, std::make_unique<JText>(x, y, text, rep));
    }
}

void JLayoutBuilder::beginPath(Ulong layer, Ulong datatype, long x, long y, long halfwidth, long startExtn, long endExtn, const PointList& points, const Repetition* rep) {
    if (currentCell) {
        Layer layerKey{layer, datatype};
        currentCell->addShape(layerKey, std::make_unique<JPath>(x, y, halfwidth, startExtn, endExtn, points, rep));
    }
}

void JLayoutBuilder::beginTrapezoid(Ulong layer, Ulong datatype, long x, long y, const Oasis::Trapezoid& trap, const Repetition* rep) {
    if (currentCell) {
        Layer layerKey{layer, datatype};
        currentCell->addShape(layerKey, std::make_unique<JTrapezoid>(x, y, trap, rep));
    }
}

void JLayoutBuilder::beginCircle(Ulong layer, Ulong datatype, long x, long y, long radius, const Repetition* rep) {
    if (currentCell) {
        Layer layerKey{layer, datatype};
        currentCell->addShape(layerKey, std::make_unique<JCircle>(x, y, radius, rep));
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
    auto it = cells.find(cellName->getName());
    if (it != cells.end()) {
        return it->second.get();
    }
    return nullptr;
}


// 함수 정의 수정
JLayout::BBox JLayoutBuilder::calculateCellBBox(const JCell* cell, std::unordered_set<const JCell*>& visited) const {
    // Cell의 BBox 캐시를 확인 (이미 계산된 경우)
    if (cell->getCachedBBox()) {
        return *(cell->getCachedBBox());
    }

    // 순환 참조 방지
    if (visited.find(cell) != visited.end()) {
        throw std::runtime_error("Circular reference detected in cell hierarchy");
    }
    visited.insert(cell);

    long x_min = LONG_MAX, y_min = LONG_MAX;
    long x_max = LONG_MIN, y_max = LONG_MIN;

    // 각 shape에 대해 BBox를 계산
    for (const auto& layerShapes : cell->getShapesByLayer()) {
        for (const auto& shape : layerShapes.second) {
            JLayout::BBox shapeBBox = shape->getBBox();
            x_min = std::min(x_min, shapeBBox.x_min);
            y_min = std::min(y_min, shapeBBox.y_min);
            x_max = std::max(x_max, shapeBBox.x_max);
            y_max = std::max(y_max, shapeBBox.y_max);
        }
    }

    // 각 placement에 대해 BBox 계산
    for (const auto& placement : cell->getPlacements()) {
        long placement_x_min = LONG_MAX, placement_y_min = LONG_MAX;
        long placement_x_max = LONG_MIN, placement_y_max = LONG_MIN;

        // repeatedPositions에서 각 위치의 min/max 값 계산
        for (const auto& pos : placement->getRepeatedPositions()) {
            placement_x_min = std::min(placement_x_min, pos.first);
            placement_y_min = std::min(placement_y_min, pos.second);
            placement_x_max = std::max(placement_x_max, pos.first);
            placement_y_max = std::max(placement_y_max, pos.second);
        }

        // 참조된 셀의 BBox를 가져와서 placement의 좌표와 더함
        const JCell* referencedCell = findRootCell(placement->getName());
        if (referencedCell) {
            JLayout::BBox referencedCellBBox = calculateCellBBox(referencedCell, visited);
            x_min = std::min(x_min, placement_x_min + referencedCellBBox.x_min);
            y_min = std::min(y_min, placement_y_min + referencedCellBBox.y_min);
            x_max = std::max(x_max, placement_x_max + referencedCellBBox.x_max);
            y_max = std::max(y_max, placement_y_max + referencedCellBBox.y_max);
        }
    }

    // 계산된 BBox를 Cell에 캐싱
    const_cast<JCell*>(cell)->setCachedBBox(std::unique_ptr<JLayout::BBox>(new JLayout::BBox{x_min, y_min, x_max, y_max}));

    // visited에서 제거
    visited.erase(cell);

    return {x_min, y_min, x_max, y_max};
}





void JLayoutBuilder::generateBinary() {

    for (const auto& cellPair : cells)
    {
        JCell* rootCell = findRootCell(cellPair.second->getName());

        creator.beginCell(rootCell->getName());

        if (rootCell) {
            rootCell->generateBinary(creator);
        }

        creator.endCell();
        currentCell = nullptr;
    }

    creator.endFile();

    printLayoutInfo();
}


// JLayoutBuilder::printLayoutInfo 함수 구현
void JLayoutBuilder::printLayoutInfo() const {
    std::cout << std::left
              << std::setw(10) << "Layer"    // Layer는 10칸으로, 왼쪽 정렬
              << std::setw(50) << "Cell"     // Cell 이름은 50칸으로, 왼쪽 정렬
              << std::setw(30) << "BBox"     // BBox는 30칸으로, 왼쪽 정렬
              << std::endl;

    std::cout << "----------------------------------------------------------------------" << std::endl;

    std::unordered_set<const JCell*> visited;

    // 셀 정보 출력
    for (const auto& cellPair : cells) {
        JCell* cell = cellPair.second.get();
        std::string cellName = cell->getName()->getName();  // 셀 이름 가져오기

        JLayout::BBox cellBBox = calculateCellBBox(cell, visited);  // Cell의 BBox 계산

        // 셀 이름이 너무 길 경우 자르기
        std::string cellOutput = cellName;
        if (cellOutput.length() > 50) {
            cellOutput = cellOutput.substr(0, 47) + "...";
        }

        // 정보 출력 (왼쪽 정렬)
        std::cout << std::left
                  << std::setw(10) << " "  // Layer는 비워둠
                  << std::setw(50) << cellOutput   // Cell 이름 출력
                  << std::setw(30) << "(" + std::to_string(cellBBox.x_min) + ", " + std::to_string(cellBBox.y_min) + ", "
                                          + std::to_string(cellBBox.x_max) + ", " + std::to_string(cellBBox.y_max) + ")"  // BBox 출력
                  << std::endl;
    }

    std::cout << "----------------------------------------------------------------------" << std::endl;
}



void JLayoutBuilder::beginXElement(SoftJin::Ulong attribute, const string &data)
{
    creator.beginXElement(attribute, data);
}

void JLayoutBuilder::beginXGeometry(SoftJin::Ulong layer, SoftJin::Ulong datatype, long x, long y, SoftJin::Ulong attribute, const string &data, const Repetition *rep)
{
    creator.beginXGeometry(layer, datatype, x, y, attribute, data, rep);
}

void JLayoutBuilder::addFileProperty(Property *prop)
{
    creator.addFileProperty(prop);
}

void JLayoutBuilder::addCellProperty(Property *prop)
{
    creator.addCellProperty(prop);
}

void JLayoutBuilder::addElementProperty(Property *prop)
{
    creator.addElementProperty(prop);
}

void JLayoutBuilder::registerCellName(CellName *cellName)
{
    creator.registerCellName(cellName);
}

void JLayoutBuilder::registerTextString(TextString *textString)
{
    creator.registerTextString(textString);
}

void JLayoutBuilder::registerPropName(PropName *propName)
{
    creator.registerPropName(propName);
}

void JLayoutBuilder::registerPropString(PropString *propString)
{
    creator.registerPropString(propString);
}

void JLayoutBuilder::registerLayerName(LayerName *layerName)
{
    creator.registerLayerName(layerName);
}

void JLayoutBuilder::registerXName(XName *xname)
{
    creator.registerXName(xname);
}

} // namespace Oasis
