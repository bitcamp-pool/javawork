
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

struct Statistics {
    std::string filename;
    double TAT;  // 분석 수행 시간
    long long fileSizeMB;
    Ulong totalCells = 0;
    Ulong totalLayers = 0;
    Ulong totalShapes = 0; // geometry 개수(반복X)
    Ulong totalShapesExpand = 0; // geometry 개수(반복 해제)
    Ulong totalPlacements = 0; // refs 개수(반복X)
    Ulong totalPlacementsExpand = 0; // refs 개수(반복 해제)

    bool cblock = false;
    bool strict = false;
    Ulong totalText = 0;
    Ulong totalRectangles = 0; // 반복X
    Ulong totalPolygons = 0;
    Ulong totalPaths = 0;
    Ulong totalTrapezoids = 0;
    Ulong totalCTrapezoids = 0;
    Ulong totalCircles = 0;
    Ulong totalXGeometry = 0;
    Ulong totalProperties = 0;

    Ulong emptyCells = 0;     // Shapes(X) Placement(X)
    Ulong mixedCells = 0;     // Shapes(O) Placement(O)
    Ulong noShapeCells = 0;   // Shapes(X) Placement(O)
    Ulong primitiveCells = 0; // Shapes(O) Placement(X)

    bool xyRelative = false; // cell들 중에서 한 번이라도 선언된 적이 있으면 true, 없으면 false
    bool xyAbsolute = false;

    Ulong maxRefs = 0;                 // 모든 cell을 순회하면서 cell이 가지고 있는 refs의 개수 중 max
    Ulong maxShapesInLayer = 0;        // 모든 cell을 순회, cell내 모든 layer를 순회하면서 layer 중 가장 많은 shapes 개수
    Ulong maxShapesAllLayer = 0;       // 모든 cell을 순회, cell이 갖는 totalShapes(모든 layer의 합) 가장 큰 값
    std::string cellMaxRefs;           // maxrefs를 갖고 있는 cell 이름
    std::string cellMaxShapesInLayer;  // maxshapes_a_layer를 갖고 있는 cell 이름
    std::string layerMaxShapesInLayer; // maxshapes_a_layer를 갖고 있는 cell의 layer
    std::string cellMaxShapesAllLayer; // maxshpaes_all_layer를 갖고 있는 cell 이름

    Ulong cellNameRecord3Types = 0;    // '3' cellname-string
    Ulong cellNameRecord4Types = 0;    // '4' cellname-string reference-number
    Ulong cellRecord13Types = 0;       // '13' reference-number
    Ulong cellRecord14Types = 0;       // '14' cellname-string

    Ulong maxCblockCountAcell = 0;     // cell안에 cblock이 여러번 선언될 수 있음. 선언된 회수 중 가장 큰 값
    std::string cellMaxCblockCountAcell; // maxCblockCountAcell 갖는 cell 이름

    Ulong maxCellSize = 0;             // 가장 큰 cellsize(cell 시작과 끝의 파일내 거리) 단위: bytes
    Ulong avgCellSize = 0;             // empty cell 제외   
    Ulong minCellSize = 0;             // empty cell 제외
    double cellSizeInterval = 0.0;     // maxCellSize / 10 

    std::string cellMaxCellSize;       // 가장 큰 cellSize를 갖고 있는 cell 이름
    std::string cellMinCellSize;       // empty cell 제외

    // cellsize 통계(cellSizeInterval*0 ~ cellSizeInterval*1) ~ (cellSizeInterval*9 ~ cellSizeInterval*10) 범위에 속하는 cell의 개수
    std::array<Ulong, 10> cellSizeCounts = {0};

    // repetition 통계
    std::array<Ulong, 12> srepCounts = {0};         // shapes 중 repetition type에 따른 회수
    std::array<Ulong, 12> srepExpandCounts = {0};   // shapes 중 repetition type에 따른 회수(반복 해제)
    std::array<Ulong, 12> prepCounts = {0};
    std::array<Ulong, 12> prepExpandCounts = {0};

    // 기타 통계
    Ulong maxPList = 0;              // 가장 긴 plist의 vertex 개수
    std::string cellMaxPList;        // 가장 긴 plist를 갖고 있는 cell 이름
    std::string layerMaxPList;       // 가장 긴 plist의 layer

    // plist 통계
    std::array<Ulong, 5> plistCounts = {0}; // vertex 개수가 00-2, 03-06, 07-14, 15-62, 63 이상 범위의 회수
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
