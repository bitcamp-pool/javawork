#ifndef ANALYZER_H
#define ANALYZER_H

#include <unordered_map>
#include <string>
#include <vector>
#include <limits>
#include <set>
#include "builder.h"

struct Statistics {
    long long totalCells = 0;
    long long totalLayers = 0;
    long long totalShapes = 0;
    long long totalPlacements = 0;
    long long totalText = 0;

    long long maxRefs = 0;
    long long maxShapesPerLayer = 0;
    long long maxShapesInCell = 0;
    
    std::string cellWithMaxRefs;
    std::string cellWithMaxShapes;
    
    std::set<int> xyrelative, xyabsolute;

    std::vector<long long> plistCounts = {0, 0, 0, 0, 0};  // 00-02, 03-04, 05-14, 15-62, 63 이상
};

class Analyzer : public Oasis::OasisBuilder {
public:
    Analyzer();
    void beginCell(Oasis::CellName* cellName) override;
    void endCell() override;
    
    void beginRectangle(Oasis::Ulong, Oasis::Ulong, long, long, long, long, const Oasis::Repetition*) override;
    void beginText(Oasis::Ulong, Oasis::Ulong, long, long, const std::string&, const Oasis::Repetition*) override;
    void beginPlacement(Oasis::CellName*, long, long, const Oasis::Repetition*) override;

    const Statistics& getStatistics() const;

private:
    Statistics stats;
    std::string currentCellName;
    long long currentCellRefs = 0;
    long long currentCellShapes = 0;

    void updateMaxRefs();
    void updateMaxShapes();
};

#endif  // ANALYZER_H
