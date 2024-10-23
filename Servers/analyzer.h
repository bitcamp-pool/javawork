
// oasis/analyzer.h -- Analyze and extract statistics from OASIS files
//
// last modified:   15-Oct-2024  Tue  22:09
//
// Copyright (c) 2004 SoftJin Infotech Private Ltd.
// This software may be used only under the terms of the SoftJin
// Source License.  See the accompanying file LICENSE for details.
//
// Analyzer는 OasisBuilder의 서브클래스로, OASIS 파일의 내용을 통해
// 성능에 영향을 미치는 요소들을 찾기 위한 통계 정보를 수집합니다.
// 도형, 배치, 참조, 레이어의 개수를 추출하는 등 메트릭을 수집하며,
// 도형 데이터를 메모리에 저장하지 않고도 분석을 수행하는 것이 목적입니다.
//
// Analyzer 클래스는 논리적 수준에서 동작합니다. OasisToAsciiConverter와 같은
// 다른 변환 도구들이 구문적 내용에 집중하는 반면, Analyzer는 성능 분석과 관련된
// 통계를 수집하는 데 중점을 둡니다. 이러한 통계는 레이아웃의 복잡도, 배치 분포,
// 그리고 잠재적인 성능 병목 구간을 평가하는 데 사용될 수 있습니다.
//
// 이 도구는 OASISBuilder의 메서드를 활용하여 효율적인 분석을 지원하며,
// 통계 및 셀 메타데이터와 같은 최소한의 구조 정보만 메모리에 저장합니다.
// 따라서 기하학적 데이터나 배치 데이터를 메모리에 적재하지 않는다는 요구사항을 준수합니다.



// analyzer.h -- OASIS 파일 성능 분석기
//
// last modified:   23-Oct-2024  Wed
// Copyright (c) 2004 SoftJin Infotech Private Ltd.

#ifndef OASIS_ANALYZER_H_INCLUDED
#define OASIS_ANALYZER_H_INCLUDED

#include <vector>
#include <string>
#include <set>
#include <limits>
#include "builder.h"

namespace Oasis {

using std::string;
using std::vector;
using std::set;
using SoftJin::Ulong;

struct CellInfo {
    string name;                   // Cell 이름
    long long numShapes = 0;        // 도형 개수 (반복 해제 안함)
    long long numShapesExpand = 0;  // 반복 해제 시 도형 개수
    long long numRefs = 0;          // 참조(placement) 개수 (반복 해제 안함)
    long long numRefsExpand = 0;    // 반복 해제 시 참조 개수
    long long cellSize = 0;         // Cell의 크기 (bytes)
    long long maxLayerShapes = 0;   // 특정 Layer의 최대 도형 수
};

struct Statistics {
    long long totalCells = 0;
    long long totalLayers = 0;
    long long totalShapes = 0;
    long long totalShapesExpand = 0;
    long long totalPlacements = 0;
    long long totalPlacementsExpand = 0;
    long long totalText = 0;

    long long maxRefs = 0;
    long long maxShapesPerLayer = 0;
    long long maxShapesInCell = 0;

    string cellWithMaxRefs;
    string cellWithMaxShapes;

    set<int> xyrelative, xyabsolute;

    long long maxCellSize = 0;
    long long minCellSize = std::numeric_limits<long long>::max();
    long long totalCellSize = 0;

    vector<long long> cellSizeBins = vector<long long>(10, 0);
    vector<long long> plistCounts = vector<long long>(5, 0);
};

class Analyzer : public OasisBuilder {
public:
    Analyzer();
    virtual ~Analyzer();

    const Statistics& getStatistics() const;
    void exportToCSV(const string& filename, const string& inputFilename, double elapsedTime, long long fileSizeMB) const;

    // OASISBuilder 메서드 오버라이드
    void beginFile(const std::string& version, const Oreal& unit, Validation::Scheme valScheme) override;
    void endFile() override;
    void beginCell(CellName* cellName) override;
    void endCell() override;
    void beginPlacement(CellName* cellName, long x, long y, const Oreal& mag, const Oreal& angle, bool flip, const Repetition* rep) override;
    void beginRectangle(Ulong layer, Ulong datatype, long x, long y, long width, long height, const Repetition* rep) override;
    void beginPolygon(Ulong layer, Ulong datatype, long x, long y, const PointList& ptlist, const Repetition* rep) override;

private:
    vector<CellInfo> cells;         // Cell 정보를 저장하는 벡터
    Statistics stats;               // 전체 통계 정보

    string currentCellName;         // 현재 분석 중인 Cell 이름
    long long currentCellShapes = 0;
    long long currentCellRefs = 0;

    void updateMaxValues();
};

}  // namespace Oasis

#endif  // OASIS_ANALYZER_H_INCLUDED
