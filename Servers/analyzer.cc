#include "analyzer.h"
#include <algorithm>

Analyzer::Analyzer() {}

void Analyzer::beginCell(Oasis::CellName* cellName) {
    stats.totalCells++;
    currentCellName = cellName->getName();
    currentCellRefs = 0;
    currentCellShapes = 0;
}

void Analyzer::endCell() {
    updateMaxRefs();
    updateMaxShapes();
}

void Analyzer::beginRectangle(Oasis::Ulong, Oasis::Ulong, long, long, long, long, const Oasis::Repetition* rep) {
    stats.totalShapes++;
    currentCellShapes++;

    if (rep) stats.totalPlacements++;
}

void Analyzer::beginText(Oasis::Ulong, Oasis::Ulong, long, long, const std::string&, const Oasis::Repetition* rep) {
    stats.totalText++;
    if (rep) stats.totalPlacements++;
}

void Analyzer::beginPlacement(Oasis::CellName*, long, long, const Oasis::Repetition* rep) {
    currentCellRefs++;
    if (rep) stats.totalPlacements++;
}

void Analyzer::updateMaxRefs() {
    if (currentCellRefs > stats.maxRefs) {
        stats.maxRefs = currentCellRefs;
        stats.cellWithMaxRefs = currentCellName;
    }
}

void Analyzer::updateMaxShapes() {
    if (currentCellShapes > stats.maxShapesInCell) {
        stats.maxShapesInCell = currentCellShapes;
        stats.cellWithMaxShapes = currentCellName;
    }
}

const Statistics& Analyzer::getStatistics() const {
    return stats;
}
