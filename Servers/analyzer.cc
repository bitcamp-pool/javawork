
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

    initializeCurrentCell(cellName->getName(), startCellOffset);

    // Increase the total cell count
    oasisStats.cellCount++;
    cellStats.emplace_back(currentCellName);
}

void
OasisStatisticsBuilder::EndCell() {

    cellStats.back().cellRefCount = currentCellRefCount;
    cellStats.back().cellShapeCount = currentCellShapeCount;
    cellStats.back().cellCBlockCount = currentCellCBlockCount;
    cellStats.back().offset = cellStartPosition;

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
    updateNormalOrExpandedCount(rep, oasisStats.refCount, oasisStats.refCountExpanded);
    updateRepetitionTypeFrequency(rep, oasisStats.prepCounts);
    updateRepetitionTypeExpandedFrequency(rep, oasisStats.prepCountsExpanded);

    currentCellRefCount++;
}

// Begin a rectangle element
void
OasisStatisticsBuilder::BeginRectangle(SoftJin::Ulong layer, SoftJin::Ulong datatype, const Repetition* rep) {
    updateElementStats(oasisStats.rectangleCount, rep, oasisStats.srepCounts, oasisStats.srepCountsExpanded);
    currentCellShapeCount++;
}

// Begin a polygon element
void
OasisStatisticsBuilder::BeginPolygon(SoftJin::Ulong layer, SoftJin::Ulong datatype, const PointList& ptlist, const Repetition* rep) {
    updateElementStats(oasisStats.polygonCount, rep, oasisStats.srepCounts, oasisStats.srepCountsExpanded);
    currentCellShapeCount++;
}

// Begin a path element
void
OasisStatisticsBuilder::BeginPath(SoftJin::Ulong layer, SoftJin::Ulong datatype, const PointList& ptlist, const Repetition* rep) {
    updateElementStats(oasisStats.pathCount, rep, oasisStats.srepCounts, oasisStats.srepCountsExpanded);
    currentCellShapeCount++;
}

// Begin a trapezoid element
void
OasisStatisticsBuilder::BeginTrapezoid(SoftJin::Ulong layer, SoftJin::Ulong datatype, const Repetition* rep) {
    updateElementStats(oasisStats.trapezoidCount, rep, oasisStats.srepCounts, oasisStats.srepCountsExpanded);
    currentCellShapeCount++;
}

void OasisStatisticsBuilder::BeginCTrapezoid(SoftJin::Ulong layer, SoftJin::Ulong datatype, const Repetition *rep)
{
    updateElementStats(oasisStats.ctrapezoidCount, rep, oasisStats.srepCounts, oasisStats.srepCountsExpanded);
    currentCellShapeCount++;
}

// Begin a circle element
void
OasisStatisticsBuilder::BeginCircle(SoftJin::Ulong layer, SoftJin::Ulong datatype, const Repetition* rep) {
    updateElementStats(oasisStats.circleCount, rep, oasisStats.srepCounts, oasisStats.srepCountsExpanded);
    currentCellShapeCount++;
}

void OasisStatisticsBuilder::BeginText(SoftJin::Ulong textlayer, SoftJin::Ulong texttype, const Repetition *rep)
{
    oasisStats.textCount++;
}

void OasisStatisticsBuilder::BeginXGeometry(SoftJin::Ulong layer, SoftJin::Ulong datatype, const Repetition *rep)
{
    oasisStats.xgeometryCount++;

    updateNormalOrExpandedCount(rep, oasisStats.shapeCount, oasisStats.shapeCountExpanded);
    updateRepetitionTypeFrequency(rep, oasisStats.srepCounts);
    updateRepetitionTypeExpandedFrequency(rep, oasisStats.srepCountsExpanded);
}

void
OasisStatisticsBuilder::EndElement()
{

}

void
OasisStatisticsBuilder::EndFile(long long endFileOffset)
{
    oasisStats.filesizeMB = endFileOffset + EndRecordSize;
}

void
OasisStatisticsBuilder::finalizeStatistics() {

    /* 성능 분석 항목 최종 추출
       .......
     */

    writer.OasisStatisticsWrite(oasisStats);
}

void OasisStatisticsBuilder::initializeCurrentCell(const string &name, long long offset)
{
    currentCellName = name;
    currentCellRefCount = 0;
    currentCellShapeCount = 0;
    currentCellCBlockCount = 0;
    cellStartPosition = offset;
}

void OasisStatisticsBuilder::updateElementStats(
    long long &elementCount,
    const Repetition *rep,
    std::vector<long long> &repCounts,
    std::vector<long long> &repCountsExpanded)
{
    elementCount++;  // 요소 개수 증가
    updateNormalOrExpandedCount(rep, oasisStats.shapeCount, oasisStats.shapeCountExpanded);
    updateRepetitionTypeFrequency(rep, repCounts);
    updateRepetitionTypeExpandedFrequency(rep, repCountsExpanded);
}

void OasisStatisticsBuilder::updateRepetitionFrequency(const Repetition *rep, std::vector<long long> &counts, bool expanded)
{
    if (!rep) return;

    int index = static_cast<int>(rep->getType());
    long long count = (expanded) ? getExpandedCount(rep) : 1;
    counts[index] += count;
}

void
OasisStatisticsBuilder::updateNormalOrExpandedCount(const Repetition* repetition, long long& count, long long& expandedCount) {
    count++;
    expandedCount += getExpandedCount(repetition);
}


void
OasisStatisticsBuilder::updateRepetitionTypeFrequency(const Repetition *rep, std::vector<long long>& repetitionCounts)
{
    updateRepetitionFrequency(rep, repetitionCounts, false);
}

void
OasisStatisticsBuilder::updateRepetitionTypeExpandedFrequency(const Repetition* rep, std::vector<long long>& repetitionCountsExpanded)
{
    updateRepetitionFrequency(rep, repetitionCountsExpanded, true);
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

void OasisStatisticsBuilder::addFileProperty(Property *prop)
{

}

void OasisStatisticsBuilder::addCellProperty(Property *prop)
{

}

void OasisStatisticsBuilder::addElementProperty(Property *prop)
{

}

void OasisStatisticsBuilder::registerCellName(CellName *cellName)
{

}

void OasisStatisticsBuilder::registerTextString(TextString *textString)
{

}

void OasisStatisticsBuilder::registerPropName(PropName *propName)
{

}

void OasisStatisticsBuilder::registerPropString(PropString *propString)
{

}

void OasisStatisticsBuilder::registerLayerName(LayerName *layerName)
{

}

void OasisStatisticsBuilder::registerXName(XName *xname)
{

}
