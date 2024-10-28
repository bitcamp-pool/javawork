
OasisStatisticsBuilder::OasisStatisticsBuilder(OasisStatistics& stats, CSVWriter& csvWriter)
    : oasisStats(stats),
      writer(csvWriter),
      currentCellRefCount(0),
      currentCellShapeCount(0),
      currentCellCBlockCount(0),
      cellStartPosition(0)
{
}

// 셀 시작(초기화)
void
OasisStatisticsBuilder::BeginCell(CellName* cellName, long long startCellOffset) {
    currentCellName = cellName->getName();
    currentCellRefCount = 0;
    currentCellShapeCount = 0;
    currentCellCBlockCount = 0;
    cellStartPosition = startCellOffset;

    // Increase the total cell count
    oasisStats.cellCount++;
    cellStats.emplace_back(currentCellName);
}

void
OasisStatisticsBuilder::EndCell(long long nextCellStartOffset) {
    long long cellSize = nextCellStartOffset - cellStartPosition;
    oasisStats.avgCellSize += cellSize;

    // Update max and min cell size
    if (cellSize > oasisStats.maxCellSize) {
        oasisStats.maxCellSize = cellSize;
        oasisStats.cellMaxCellSize = currentCellName;
    }
    if (cellSize < oasisStats.minCellSize && currentCellShapeCount > 0) {
        oasisStats.minCellSize = cellSize;
        oasisStats.cellMinCellSize = currentCellName;
    }

    // Update cell classification statistics
    if (currentCellShapeCount == 0 && currentCellRefCount == 0) {
        oasisStats.cellEmptyCount++;
    } else if (currentCellShapeCount > 0 && currentCellRefCount > 0) {
        oasisStats.cellMixedCount++;
    } else if (currentCellShapeCount == 0 && currentCellRefCount > 0) {
        oasisStats.cellNoShapeCount++;
    } else if (currentCellShapeCount > 0 && currentCellRefCount == 0) {
        oasisStats.cellPrimitiveCount++;
    }

    // Update max references count
    if (currentCellRefCount > oasisStats.maxRefs) {
        oasisStats.maxRefs = currentCellRefCount;
        oasisStats.cellMaxRefs = currentCellName;
    }
}

// Begin a placement element
void
OasisStatisticsBuilder::BeginPlacement(CellName* cellName, const Repetition* rep) {
    currentCellRefCount++;
    updateReferenceStatistics(rep, oasisStats.refCount, oasisStats.refCountExpanded);
}

// Begin a rectangle element
void
OasisStatisticsBuilder::BeginRectangle(SoftJin::Ulong layer, SoftJin::Ulong datatype, const Repetition* rep) {
    currentCellShapeCount++;
    oasisStats.rectangleCount++;
    updateShapeStatistics(rep, oasisStats.shapeCount, oasisStats.shapeCountExpanded);
}

// Begin a polygon element
void
OasisStatisticsBuilder::BeginPolygon(SoftJin::Ulong layer, SoftJin::Ulong datatype, const PointList& ptlist, const Repetition* rep) {
    currentCellShapeCount++;
    oasisStats.polygonCount++;
    updateShapeStatistics(rep, oasisStats.shapeCount, oasisStats.shapeCountExpanded);
}

// Begin a path element
void
OasisStatisticsBuilder::BeginPath(SoftJin::Ulong layer, SoftJin::Ulong datatype, const PointList& ptlist, const Repetition* rep) {
    currentCellShapeCount++;
    oasisStats.pathCount++;
    updateShapeStatistics(rep, oasisStats.shapeCount, oasisStats.shapeCountExpanded);
}

// Begin a trapezoid element
void
OasisStatisticsBuilder::BeginTrapezoid(SoftJin::Ulong layer, SoftJin::Ulong datatype, const Repetition* rep) {
    currentCellShapeCount++;
    oasisStats.trapezoidCount++;
    updateShapeStatistics(rep, oasisStats.shapeCount, oasisStats.shapeCountExpanded);
}

void OasisStatisticsBuilder::BeginCTrapezoid(SoftJin::Ulong layer, SoftJin::Ulong datatype, const Repetition *rep)
{
    currentCellShapeCount++;
    oasisStats.ctrapezoidCount++;
    updateShapeStatistics(rep, oasisStats.shapeCount, oasisStats.shapeCountExpanded);
}

// Begin a circle element
void
OasisStatisticsBuilder::BeginCircle(SoftJin::Ulong layer, SoftJin::Ulong datatype, const Repetition* rep) {
    currentCellShapeCount++;
    oasisStats.circleCount++;
    updateShapeStatistics(rep, oasisStats.shapeCount, oasisStats.shapeCountExpanded);
}

void OasisStatisticsBuilder::BeginText(SoftJin::Ulong textlayer, SoftJin::Ulong texttype, const Repetition *rep)
{
    oasisStats.textCount++;
}

void OasisStatisticsBuilder::BeginXGeometry(SoftJin::Ulong layer, SoftJin::Ulong datatype, const Repetition *rep)
{
    oasisStats.xgeometryCount++;
}

// End the current element (currently a placeholder)
void
OasisStatisticsBuilder::EndElement() {
    // Placeholder for any finalization needed per element
}

void
OasisStatisticsBuilder::finalizeStatistics() {
    if (oasisStats.cellCount > 0) {
        oasisStats.avgCellSize /= oasisStats.cellCount;
    }
    writer.OasisStatisticsWrite(oasisStats);
}

void
OasisStatisticsBuilder::updateShapeStatistics(const Repetition* repetition, long long& count, long long& expandedCount) {
    count++;
    expandedCount += getExpandedCount(repetition);
}

void
OasisStatisticsBuilder::updateReferenceStatistics(const Repetition* repetition, long long& count, long long& expandedCount) {
    count++;
    expandedCount += getExpandedCount(repetition);
}

void
OasisStatisticsBuilder::updateRepetitionStatistics(const Repetition *rep, std::vector<long long>& repetitionCounts)
{
    if (rep == nullptr)
        return;

    RepetitionType repType = rep->getType();

    switch (repType) {
    case Rep_ReusePrevious:
        ++repetitionCounts[0];
        break;
    case Rep_Matrix:
        ++repetitionCounts[1];
        break;
    default:
        break;
    }

}

void
OasisStatisticsBuilder::updateRepetitionExpandedStatistics(const Repetition* rep, std::vector<long long>& repetitionCountsExpanded)
{
    if (rep == nullptr)
        return;

    // 기본 반복 횟수를 계산
    long long expandedCount = 1;

    switch (rep->getType()) {
    case Rep_ReusePrevious:
        repetitionCountsExpanded[0] += expandedCount;
        break;

    case Rep_Matrix:
        expandedCount = rep->getMatrixXdimen() * rep->getMatrixYdimen();
        repetitionCountsExpanded[1] += expandedCount;
        break;

    default:
        // 처리하지 않는 유형은 생략
        break;
    }
}




long long
OasisStatisticsBuilder::getVertexCount(const PointList& ptlist) const {
    return ptlist.size();
}

long long
OasisStatisticsBuilder::getExpandedCount(const Repetition *repetition) const
{
        if (!repetition) {
            return 1;
        }

        RepetitionType repType = repetition->getType();
        long long expandedCount = 0;

        switch(repType) {
        case Rep_ReusePrevious:
            expandedCount = 1;
            break;
        case Rep_Matrix:
            expandedCount = repetition->getMatrixXdimen() * repetition->getMatrixYdimen();
            break;
        case Rep_UniformX:
        case Rep_UniformY:
        case Rep_VaryingX:
        case Rep_VaryingY:
        case Rep_GridVaryingX:
        case Rep_GridVaryingY:
        case Rep_Arbitrary:
        case Rep_GridArbitrary:
        case Rep_Diagonal:
            expandedCount = repetition->getDimen();
            break;
        case Rep_TiltedMatrix:
            expandedCount = repetition->getMatrixNdimen() * repetition->getMatrixMdimen();
            break;
        default:
            expandedCount = 1;
            break;
        }

        return expandedCount;
}
