
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
