// analyzer.cc -- OASIS 파일 성능 분석기 구현
// last modified:   23-Oct-2024  Wed

#include <cerrno>
#include <cstring>
#include <iostream>
#include "oasis.h"
#include "analyzer.h"



namespace Oasis {

using namespace std;
using namespace SoftJin;


Analyzer::Analyzer () {}

/*virtual*/
Analyzer::~Analyzer() { }

const Statistics& Analyzer::getStatistics() const {
    return stats;
}

Ulong Analyzer::getRepetitionCount() const {
    switch (type) {
    case RepetitionType::Rep_ReusePrevious:
        return 1;  // 이전 반복을 재사용

    case RepetitionType::Rep_Matrix:
        return xdimen * ydimen;

    case RepetitionType::Rep_UniformX:
        return dimen;

    case RepetitionType::Rep_UniformY:
        return dimen;

    case RepetitionType::Rep_VaryingX:
    case RepetitionType::Rep_GridVaryingX:
        return xOffsets.size();

    case RepetitionType::Rep_VaryingY:
    case RepetitionType::Rep_GridVaryingY:
        return yOffsets.size();

    case RepetitionType::Rep_TiltedMatrix:
        return xdimen * ydimen;

    case RepetitionType::Rep_Diagonal:
        return dimen;

    case RepetitionType::Rep_Arbitrary:
    case RepetitionType::Rep_GridArbitrary:
        return deltas.size();

    default:
        throw std::runtime_error("Unknown RepetitionType.");
    }
}

void Analyzer::updateRepetitionStats(const Repetition* rep) {
    if (!rep) return;
    Ulong repCount = rep->getRepetitionCount();
    stats.srepCounts[static_cast<int>(rep->type)]++;
    stats.srepExpandCounts[static_cast<int>(rep->type)] += repCount - 1;
}

void Analyzer::updateMaxValues() {
    if (currentCellRefs > stats.maxRefs) {
        stats.maxRefs = currentCellRefs;
        stats.cellWithMaxRefs = currentCellName;
    }

    if (currentCellShapes > stats.maxShapesInCell) {
        stats.maxShapesInCell = currentCellShapes;
        stats.cellWithMaxShapes = currentCellName;
    }
}

/*virtual*/ void
Analyzer::beginFile (const string& version,
                         const Oreal&  unit,
                         Validation::Scheme valScheme)
{
    cout << "Analyzing OASIS file." << endl;
    cout << "Version: " << version  << endl;
    cout << "Unit: " << unit.getValue()  << endl;
    cout << "ValidationScheme: " << valScheme  << endl;
}

/*virtual*/ void
Analyzer::beginCell (CellName* cellName)
{
    currentCellName = cellName->getName();
    currentCellShapes = 0;
    currentCellRefs = 0;

    if (cells.empty()) stats.emptyCells++;
}

/*virtual*/ void
Analyzer::endFile() {
    std::cout << "OASIS file analysis complete." << std::endl;
}

/*virtual*/ void
Analyzer::endCell() {
    CellInfo& cell = cells.back();
    cell.numShapes = currentCellShapes;
    cell.numRefs = currentCellRefs;

    updateMaxValues();
    stats.totalCells++;
}

/*virtual*/ void
Analyzer::beginPlacement (CellName*  cellName,
                              long x, long y,
                              const Oreal&  mag,
                              const Oreal&  angle,
                              bool flip,
                              const Repetition* rep)
{
    currentCellRefs++;
    stats.totalPlacements++;

    if (rep) {

    }
}

/*virtual*/ void
Analyzer::beginText (Ulong textlayer, Ulong texttype,
                         long x, long y,
                         TextString*  textString,
                         const Repetition*  rep)
{

}

/*virtual*/ void
Analyzer::beginRectangle (Ulong layer, Ulong datatype,
                              long x, long y,
                              long width, long height,
                              const Repetition* rep)
{
    stats.totalRectangles++;
    updateRepetitionStats(rep);
}

/*virtual*/ void
Analyzer::beginPolygon (Ulong layer, Ulong datatype,
                            long x, long y,
                            const PointList& ptlist,
                            const Repetition* rep)
{
    currentCellShapes++;
    stats.totalShapes++;

    size_t numVertices = ptlist.size();
    if (numVertices <= 2) stats.plistCounts[0]++;
    else if (numVertices <= 6) stats.plistCounts[1]++;
    else if (numVertices <= 14) stats.plistCounts[2]++;
    else if (numVertices <= 62) stats.plistCounts[3]++;
    else stats.plistCounts[4]++;

    if (rep) {

    }
}

/*virtual*/ void
Analyzer::beginPath (Ulong layer, Ulong datatype,
                         long x, long  y,
                         long halfwidth,
                         long startExtn, long endExtn,
                         const PointList&  ptlist,
                         const Repetition* rep)
{

}

/*virtual*/ void
Analyzer::beginTrapezoid (Ulong layer, Ulong datatype,
                              long x, long  y,
                              const Trapezoid& trap,
                              const Repetition* rep)
{

}

/*virtual*/ void
Analyzer::beginCircle (Ulong layer, Ulong datatype,
                           long x, long y,
                           long radius,
                           const Repetition* rep)
{

}

/*virtual*/ void
Analyzer::beginXElement (Ulong attribute, const string& data)
{

}

/*virtual*/ void
Analyzer::beginXGeometry (Ulong layer, Ulong datatype,
                              long x, long y,
                              Ulong attribute,
                              const string& data,
                              const Repetition* rep)
{

}

/*virtual*/ void
Analyzer::addFileProperty (Property* prop) {

}

/*virtual*/ void
Analyzer::addCellProperty (Property* prop) {

}

/*virtual*/ void
Analyzer::addElementProperty (Property* prop) {

}

/*virtual*/ void
Analyzer::registerCellName (CellName* cellName) {

}

/*virtual*/ void
Analyzer::registerTextString (TextString* textString) {

}

/*virtual*/ void
Analyzer::registerPropName (PropName* propName) {

}

/*virtual*/ void
Analyzer::registerPropString (PropString* propString) {

}

/*virtual*/ void
Analyzer::registerLayerName (LayerName* layerName) {

}

/*virtual*/ void
Analyzer::registerXName (XName* xname) {

}

} // namespace Oasis
