
// oasis/analyzer.h -- Analyze and extract statistics from OASIS files

// [OASIS 파일 성능 분석기]

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

// last modified:   23-Oct-2024  Wed


#ifndef OASIS_ANALYZER_H_INCLUDED
#define OASIS_ANALYZER_H_INCLUDED


#include <string>
#include <set>
#include <limits>
#include "builder.h"


namespace Oasis {

using std::FILE;
using std::string;
using SoftJin::Ulong;


struct CellInfo {
    string name;                    // Cell 이름
    long long numShapes = 0;        // 도형 개수 (반복 해제 안함)
    long long numShapesExpand = 0;  // 반복 해제 시 도형 개수
    long long numRefs = 0;          // 참조(placement) 개수 (반복 해제 안함)
    long long numRefsExpand = 0;    // 반복 해제 시 참조 개수
    long long cellSize = 0;         // Cell의 크기 (bytes)
    long long maxLayerShapes = 0;   // 특정 Layer의 최대 도형 수

    CellInfo(const std::string& cellName) : name(cellName) {}
};

// struct Statistics {
//     long long totalCells = 0;
//     long long totalLayers = 0;
//     long long totalShapes = 0;
//     long long totalShapesExpand = 0;
//     long long totalPlacements = 0;
//     long long totalPlacementsExpand = 0;
//     long long totalText = 0;

//     long long maxRefs = 0;
//     long long maxShapesPerLayer = 0;
//     long long maxShapesInCell = 0;

//     string cellWithMaxRefs;
//     string cellWithMaxShapes;

//     std::set<int> xyrelative, xyabsolute;

//     long long maxCellSize = 0;
//     long long minCellSize = std::numeric_limits<long long>::max();
//     long long totalCellSize = 0;

//     vector<long long> cellSizeBins = vector<long long>(10, 0);
//     vector<long long> plistCounts = vector<long long>(5, 0); // 00-02, 03-04, 05-14, 15-62, 63 이상
// };

struct Statistics {
    std::string filename;
    double TAT;  // 분석 수행 시간
    long long fileSizeMB;
    Ulong totalCells = 0;
    Ulong totalLayers = 0;
    Ulong totalShapes = 0;
    Ulong totalShapesExpand = 0;
    Ulong totalPlacements = 0;
    Ulong totalPlacementsExpand = 0;

    bool cblock = false;
    bool strict = false;
    Ulong totalText = 0;
    Ulong totalRectangles = 0;
    Ulong totalPolygons = 0;
    Ulong totalPaths = 0;
    Ulong totalTrapezoids = 0;
    Ulong totalCTrapezoids = 0;
    Ulong totalCircles = 0;
    Ulong totalXGeometry = 0;
    Ulong totalProperties = 0;

    Ulong emptyCells = 0;
    Ulong mixedCells = 0;
    Ulong noShapeCells = 0;
    Ulong primitiveCells = 0;

    Ulong maxRefs = 0;
    Ulong maxShapesInLayer = 0;
    Ulong maxShapesAllLayer = 0;
    std::string cellMaxRefs;
    std::string cellMaxShapesInLayer;
    std::string layerMaxShapesInLayer;
    std::string cellMaxShapesAllLayer;

    // 반복 유형별 통계
    std::array<Ulong, 12> srepCounts = {0};
    std::array<Ulong, 12> srepExpandCounts = {0};
    std::array<Ulong, 12> prepCounts = {0};
    std::array<Ulong, 12> prepExpandCounts = {0};

    // 기타 통계
    Ulong maxPList = 0;
    std::string cellMaxPList;
    std::string layerMaxPList;
};

class Analyzer : public OasisBuilder {

public:
       const Statistics& getStatistics() const;

private:
       vector<CellInfo> cells;         // Cell 정보를 저장하는 벡터
       Statistics stats;               // 전체 통계 정보

       string currentCellName;         // 현재 분석 중인 Cell 이름
       long long currentCellShapes = 0;
       long long currentCellRefs = 0;

       void updateMaxValues();
       Ulong getRepetitionCount() const;
       void updateRepetitionStats(const Repetition* rep);

public:
                  Analyzer ();
    virtual       ~Analyzer();

    virtual void  beginFile (const std::string&  version,
                             const Oreal&        unit,
                             Validation::Scheme  valScheme);
    virtual void  endFile();

    virtual void  beginCell (CellName* cellName);
    virtual void  endCell();

    virtual void  beginPlacement (CellName*  cellName,
                                  long x, long y,
                                  const Oreal&  mag,
                                  const Oreal&  angle,
                                  bool flip,
                                  const Repetition*  rep);

    virtual void  beginText (Ulong textlayer, Ulong texttype,
                             long x, long y,
                             TextString* text,
                             const Repetition* rep);

    virtual void  beginRectangle (Ulong layer, Ulong datatype,
                                  long x, long y,
                                  long width, long height,
                                  const Repetition*  rep);

    virtual void  beginPolygon (Ulong layer, Ulong datatype,
                                long x, long y,
                                const PointList&  ptlist,
                                const Repetition*  rep);

    virtual void  beginPath (Ulong layer, Ulong datatype,
                             long x, long  y,
                             long halfwidth,
                             long startExtn, long endExtn,
                             const PointList&  ptlist,
                             const Repetition*  rep);

    virtual void  beginTrapezoid (Ulong layer, Ulong datatype,
                                  long x, long  y,
                                  const Trapezoid&  trap,
                                  const Repetition*  rep);

    virtual void  beginCircle (Ulong layer, Ulong datatype,
                               long x, long y,
                               long radius,
                               const Repetition*  rep);

    virtual void  beginXElement (Ulong attribute, const std::string& data);

    virtual void  beginXGeometry (Ulong layer, Ulong datatype,
                                  long x, long y,
                                  Ulong attribute,
                                  const std::string& data,
                                  const Repetition*  rep);

    virtual void  addFileProperty (Property* prop);
    virtual void  addCellProperty (Property* prop);
    virtual void  addElementProperty (Property* prop);

    virtual void  registerCellName   (CellName*   cellName);
    virtual void  registerTextString (TextString* textString);
    virtual void  registerPropName   (PropName*   propName);
    virtual void  registerPropString (PropString* propString);
    virtual void  registerLayerName  (LayerName*  layerName);
    virtual void  registerXName      (XName*      xname);

private:
                Analyzer (const Analyzer&);     // forbidden
    void        operator= (const Analyzer&);    // forbidden
};


} // namespace Oasis

#endif  // OASIS_ANALYZER_H_INCLUDED
