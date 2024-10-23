// analyzer.cc -- OASIS 파일 성능 분석기 구현
//
// last modified:   23-Oct-2024  Wed

#include "analyzer.h"
#include <iostream>
#include <fstream>
#include <algorithm>

namespace Oasis {

Analyzer::Analyzer() = default;

Analyzer::~Analyzer() = default;

const Statistics& Analyzer::getStatistics() const {
    return stats;
}

void Analyzer::beginFile(const std::string& version, const Oreal& unit, Validation::Scheme valScheme) {
    std::cout << "Analyzing OASIS file. Version: " << version << std::endl;
}

void Analyzer::endFile() {
    std::cout << "OASIS file analysis complete." << std::endl;
}

void Analyzer::beginCell(CellName* cellName) {
    currentCellName = cellName->getName();
    currentCellShapes = 0;
    currentCellRefs = 0;
    cells.emplace_back(CellInfo{currentCellName});
}

void Analyzer::endCell() {
    CellInfo& cell = cells.back();
    cell.numShapes = currentCellShapes;
    cell.numRefs = currentCellRefs;

    updateMaxValues();
    stats.totalCells++;
}

void Analyzer::beginPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep) {
    currentCellRefs++;
    stats.totalPlacements++;

    if (rep) {
        stats.totalPlacementsExpand += rep->getCount() - 1;
    }
}

void Analyzer::beginRectangle(Ulong layer, Ulong datatype, long x, long y, long width, long height, const Repetition* rep) {
    currentCellShapes++;
    stats.totalShapes++;

    if (rep) {
        stats.totalShapesExpand += rep->getCount() - 1;
    }
}

void Analyzer::beginPolygon(Ulong layer, Ulong datatype, long x, long y, const PointList& ptlist, const Repetition* rep) {
    currentCellShapes++;
    stats.totalShapes++;

    size_t numVertices = ptlist.size();
    if (numVertices <= 2) stats.plistCounts[0]++;
    else if (numVertices <= 6) stats.plistCounts[1]++;
    else if (numVertices <= 14) stats.plistCounts[2]++;
    else if (numVertices <= 62) stats.plistCounts[3]++;
    else stats.plistCounts[4]++;

    if (rep) {
        stats.totalShapesExpand += rep->getCount() - 1;
    }
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

void Analyzer::exportToCSV(const string& filename, const string& inputFilename, double elapsedTime, long long fileSizeMB) const {
    std::ofstream outFile(filename);
    outFile << "name,value\n";
    outFile << "filename," << inputFilename << "\n";
    outFile << "TAT(s)," << elapsedTime << "\n";
    outFile << "filesize(MB)," << fileSizeMB << "\n";
    outFile << "#cells," << stats.totalCells << "\n";
    outFile << "#layers," << stats.totalLayers << "\n";
    outFile << "#shapes," << stats.totalShapes << "\n";
    outFile << "#shapes_expand," << stats.totalShapesExpand << "\n";
    outFile << "#refs," << stats.totalPlacements << "\n";
    outFile << "#refs_expand," << stats.totalPlacementsExpand << "\n";
    outFile << "maxrefs," << stats.maxRefs << "\n";
    outFile << "cell_maxrefs," << stats.cellWithMaxRefs << "\n";
    outFile << "maxshapes_all_layer," << stats.maxShapesInCell << "\n";
    outFile << "cell_maxshapes_all_layer," << stats.cellWithMaxShapes << "\n";
    outFile.close();
}

}  // namespace Oasis
