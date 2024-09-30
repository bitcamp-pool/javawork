#include "layoutbuilder.h"
#include <iostream>
#include <iomanip>
#include <map>


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
        long xspace = rep->getMatrixXspace();
        long yspace = rep->getMatrixYspace();

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
        Delta ndisp = rep->getMatrixNdelta();
        Delta mdisp = rep->getMatrixMdelta();

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
    default:
        // 기본 단일 배치
        positions.push_back({x, y});
        break;
    }
}

// JRectangle Implementation

BBox JRectangle::getBBox() const {
    BBox bbox = {x, y, x + width, y + height};
    return bbox;
}

void JRectangle::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions){
        creator.beginRectangle(layer, datatype, pos.first, pos.second, width, height, nullptr);
    }
}

// JSquare Implementation

BBox JSquare::getBBox() const {
    BBox bbox = {x, y, x + width, y + width}; // Square, so width = height
    return bbox;
}

void JSquare::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginRectangle(layer, datatype, pos.first, pos.second, width, width, nullptr);
    }
}

// JPolygon Implementation

BBox JPolygon::getBBox() const {
    // Calculate BBox from the points list
    long x_min = LONG_MAX, y_min = LONG_MAX, x_max = LONG_MIN, y_max = LONG_MIN;
    for (const auto& point : points) {
        if (point.x < x_min) x_min = point.x;
        if (point.x > x_max) x_max = point.x;
        if (point.y < y_min) y_min = point.y;
        if (point.y > y_max) y_max = point.y;
    }
    return {x_min + x, y_min + y, x_max + x, y_max + y};
}

void JPolygon::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginPolygon(layer, datatype, pos.first, pos.second, points, nullptr);
    }
}


// JPath Implementation

BBox JPath::getBBox() const {
    long x_min = x, y_min = y, x_max = x, y_max = y;
    for (const auto& point : points) {
        if (point.x < x_min) x_min = point.x;
        if (point.x > x_max) x_max = point.x;
        if (point.y < y_min) y_min = point.y;
        if (point.y > y_max) y_max = point.y;
    }
    return {x_min, y_min, x_max, y_max};
}

void JPath::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginPath(layer, datatype, pos.first, pos.second, halfwidth, startExtn, endExtn, points, nullptr);
    }
}

// JTrapezoid Implementation

BBox JTrapezoid::getBBox() const {
    // Calculate BBox based on trapezoid's geometric properties
    long x_min = x, y_min = y, x_max = x + trapezoid.getWidth(), y_max = y + trapezoid.getHeight();
    return {x_min, y_min, x_max, y_max};
}

void JTrapezoid::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginTrapezoid(layer, datatype, pos.first, pos.second, trapezoid, nullptr);
    }
}

// JCircle Implementation

BBox JCircle::getBBox() const {
    BBox bbox = {x - radius, y - radius, x + radius, y + radius};
    return bbox;
}

void JCircle::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginCircle(layer, datatype, pos.first, pos.second, radius, nullptr);
    }
}

// JText Implementation

BBox JText::getBBox() const {
    // Simplified text BBox (actual calculation depends on font and text size)
    long textWidth = text->getName().length() * 10;  // Placeholder for text width
    BBox bbox = {x, y, x + textWidth, y + 20};  // Placeholder height
    return bbox;
}

void JText::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    for (const auto& pos : repeatedPositions) {
        creator.beginText(layer, datatype, pos.first, pos.second, text, nullptr);
    }
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
            std::string shapeType;

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
    auto cellIter = cells.find(cellName->getName());
    if (cellIter != cells.end()) {
        return cellIter->second.get();
    }
    return nullptr;
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
    std::cout << std::setw(30) << "[Layout Info]" << std::endl;
    std::cout << "File Version: " << fileVersion << ", Unit: " << fileUnit.getValue() << std::endl;
    std::cout << "______________________________________________________________________" << std::endl;
    std::cout << std::left  // 왼쪽 정렬
              << std::setw(12) << "Layer"
              << std::setw(16) << "Cell"
              << std::setw(12) << "Type"
              << std::setw(24) << "BBox" << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;

    // std::multimap을 사용하여 layer 기준으로 오름차순 정렬
    std::multimap<std::string, std::tuple<std::string, std::string, JLayout::BBox>> sortedShapes;

    for (const auto& cellPair : cells) {
        const JCell* cell = cellPair.second.get();
        std::string cellName = cell->getName()->getName();  // 셀 이름 가져오기

        for (const auto& layerShapes : cell->getShapesByLayer()) {
            const JLayout::Layer& layerKey = layerShapes.first;
            std::string layerKeyStr = std::to_string(layerKey.layer) + "." + std::to_string(layerKey.datatype);  // layer + datatype

            for (const auto& shape : layerShapes.second) {
                JLayout::BBox bbox = shape->getBBox();
                std::string shapeType;

                switch (shape->getShapeType()) {
                case JLayout::Rectangle: shapeType = "Rectangle"; break;
                case JLayout::Square: shapeType = "Square"; break;
                case JLayout::Polygon: shapeType = "Polygon"; break;
                case JLayout::Path: shapeType = "Path"; break;
                case JLayout::Trapezoid: shapeType = "Trapezoid"; break;
                case JLayout::Circle: shapeType = "Circle"; break;
                case JLayout::Text: shapeType = "Text"; break;
                default: shapeType = "Unknown"; break;
                }

                // Layer 정보와 함께 저장
                sortedShapes.emplace(layerKeyStr, std::make_tuple(cellName, shapeType, bbox));
            }
        }
    }

    std::string prevLayer;
    std::string prevCell;

    // 정렬된 Layer 순서대로 출력
    for (const auto& shapeInfo : sortedShapes) {
        const std::string& layerStr = shapeInfo.first;
        const std::string& cellName = std::get<0>(shapeInfo.second);  // 셀 이름
        const std::string& shapeType = std::get<1>(shapeInfo.second);  // 도형 타입
        const JLayout::BBox& bbox = std::get<2>(shapeInfo.second);  // BBox 정보

        // 같은 Layer와 Cell 이름일 때 빈칸 출력
        std::string layerOutput = (layerStr == prevLayer) ? "" : layerStr;
        std::string cellOutput = (cellName == prevCell) ? "" : cellName;

        std::cout << std::left  // 왼쪽 정렬
                  << std::setw(12) << layerOutput  // layer 출력 (layer + datatype)
                  << std::setw(16) << cellOutput  // cell 이름 출력
                  << std::setw(12) << shapeType  // 도형 타입 출력
                  << "(" << bbox.x_min << ", " << bbox.y_min << ", "
                  << bbox.x_max << ", " << bbox.y_max << ")" << std::endl;

        // 이전 Layer와 Cell 저장
        prevLayer = layerStr;
        prevCell = cellName;
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
