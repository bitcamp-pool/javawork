#include "layoutbuilder.h"

namespace Oasis {

// JRectangle Implementation

BBox JRectangle::getBBox() const {
    BBox bbox = {x, y, x + width, y + height};
    return bbox;
}

void JRectangle::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    creator.beginRectangle(layer, datatype, x, y, width, height, rep); // Layer/datatype values assumed as placeholders
}

// JSquare Implementation

BBox JSquare::getBBox() const {
    BBox bbox = {x, y, x + width, y + width}; // Square, so width = height
    return bbox;
}

void JSquare::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    creator.beginRectangle(layer, datatype, x, y, width, width, rep); // Placeholder values
}

// JPolygon Implementation

BBox JPolygon::getBBox() const {
    // Calculate BBox from the points list
    long x_min = x, y_min = y, x_max = x, y_max = y;
    for (const auto& point : points) {
        if (point.x < x_min) x_min = point.x;
        if (point.x > x_max) x_max = point.x;
        if (point.y < y_min) y_min = point.y;
        if (point.y > y_max) y_max = point.y;
    }
    return {x_min, y_min, x_max, y_max};
}

void JPolygon::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    creator.beginPolygon(layer, datatype, x, y, points, rep); // Placeholder values
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
    creator.beginPath(layer, datatype, x, y, halfwidth, startExtn, endExtn, points, rep); // Placeholder values
}

// JTrapezoid Implementation

BBox JTrapezoid::getBBox() const {
    // Calculate BBox based on trapezoid's geometric properties
    long x_min = x, y_min = y, x_max = x + trapezoid.getWidth(), y_max = y + trapezoid.getHeight();
    return {x_min, y_min, x_max, y_max};
}

void JTrapezoid::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    creator.beginTrapezoid(layer, datatype, x, y, trapezoid, rep); // Placeholder values
}

// JCircle Implementation

BBox JCircle::getBBox() const {
    BBox bbox = {x - radius, y - radius, x + radius, y + radius};
    return bbox;
}

void JCircle::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    creator.beginCircle(layer, datatype, x, y, radius, rep); // Placeholder values
}

// JText Implementation

BBox JText::getBBox() const {
    // Simplified text BBox (actual calculation depends on font and text size)
    long textWidth = text->getName().length() * 10;  // Placeholder for text width
    BBox bbox = {x, y, x + textWidth, y + 20};  // Placeholder height
    return bbox;
}

void JText::generateBinary(OasisBuilder& creator, Ulong layer, Ulong datatype) const {
    creator.beginText(layer, datatype, x, y, text, rep); // Placeholder values
}


// JPlacement Implementation

JPlacement::JPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep)
    : cellName(cellName), x(x), y(y), mag(mag), angle(angle), flip(flip), rep(rep) {}

void JPlacement::generateBinary(OasisBuilder& creator) const {
    creator.beginPlacement(cellName, x, y, mag, angle, flip, rep);
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
    // Generate shapes
    for (const auto& pair : shapesByLayer) {
        for (const auto& shape : pair.second) {
            Ulong layer     = pair.first.layer;
            Ulong datatype  = pair.first.datatype;

            switch (shape->getShapeType()) {
            case JShape::Rectangle:
                static_cast<JRectangle*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JShape::Square:
                static_cast<JSquare*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JShape::Polygon:
                static_cast<JPolygon*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JShape::Path:
                static_cast<JPath*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JShape::Trapezoid:
                static_cast<JTrapezoid*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JShape::Circle:
                static_cast<JCircle*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            case JShape::Text:
                static_cast<JText*>(shape.get())->generateBinary(creator, layer, datatype);
                break;
            default:
                throw std::runtime_error("Unknown shape type");
            }
        }
    }

    // Generate placements
    for (const auto& placement : placements) {
        placement->generateBinary(creator);
    }
}

// JLayoutBuilder Implementation
JLayoutBuilder::JLayoutBuilder(OasisBuilder& creator)
    : creator(creator) {}

void JLayoutBuilder::beginFile(const std::string& version, const Oreal& unit, Validation::Scheme valScheme) {
    fileVersion = version;
    fileUnit = unit;
    fileValidationScheme = valScheme;

    creator.beginFile(version, uint, valScheme);
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
    if (currentCell) {
        currentCell->addPlacement(std::unique_ptr<JPlacement>(new JPlacement(cellName, x, y, mag, angle, flip, rep)));
        updateCellHierarchy(currentCell->getName(), cellName);
    }
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

void JLayoutBuilder::beginTrapezoid(Ulong layer, Ulong datatype, long x, long y, const Trapezoid& trap, const Repetition* rep) {
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
    for (const auto& cellPair : cells) {
        JCell* rootCell = findRootCell(cellPair.second->getName());
        creator.beginCell(rootCell->getName());

        if (rootCell) {
            rootCell->generateBinary(creator);
        }

        creator.endCell();
        currentCell = nullptr;
    }

    creator.endFile();
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
