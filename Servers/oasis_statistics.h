// oasis_statistics.h

#ifndef OASIS_STATISTICS_H
#define OASIS_STATISTICS_H

#include <string>
#include <unordered_map>
#include <vector>

namespace Oasis {
namespace Jeong {

using namespace std;


struct Layer {
    std::string layerName;
    long long shapeCount = 0;
    Layer(const std::string& name) : layerName(name) {}
};

struct CellStatistics {
    std::string cellName;

    long long cellRefCount = 0;
    long long cellShapeCount = 0;
    long long cellCBlockCount = 0;

    long long offset = 0;

    vector<Layer> layers;

    CellStatistics(const std::string& name) : cellName(name) {}
};

struct OasisStatistics {
    std::string filename;                       // input file name
    long long analysisTimeSec = 0;              // 분석 수행 시간(초)
    long long filesizeMB = 0;                   // file size를 MB단위 출력(MB)

    long long cellCount = 0;                    // oasis내 전체 cell 개수
    long long layerCount = 0;                   // oasis내 전체 layer.datatype의 개수
    long long shapeCount = 0;                   // geometry(도형) 개수(repeat 고려 안함)
    long long shapeCountExpanded = 0;           // geometry(도형) 개수(repeat 해제 시 개수)
    long long refCount = 0;                     // 참조(placement) 개수(repeat 고려 안함)
    long long refCountExpanded = 0;             // 참조(placement) 개수(repeat 해제 시 개수)

    bool cblock = false;                        // on/off 여부
    bool strict = false;                        // on/off 여부

    long long textCount = 0;                    // text 개수
    long long rectangleCount = 0;               // geometry 중 rectangle 개수(repeat 고려 안함)
    long long polygonCount = 0;                 // geometry 중 polygon 개수(repeat 고려 안함)
    long long pathCount = 0;                    // geometry 중 path 개수(repeat 고려 안함)
    long long trapezoidCount = 0;               // geometry 중 trapezoid 개수(repeat 고려 안함)
    long long ctrapezoidCount = 0;              // geometry 중 ctrapezoid 개수(repeat 고려 안함)
    long long circleCount = 0;                  // geometry 중 circle 개수(repeat 고려 안함)
    long long xgeometryCount = 0;               // geometry 중 xgeometry 개수(repeat 고려 안함)
    long long propertyCount = 0;                // property 개수

    long long cellEmptyCount = 0;               // shapes(X) placement(X) cell의 개수
    long long cellMixedCount = 0;               // shapes(O) placement(O) cell의 개수
    long long cellNoShapeCount = 0;             // shapes(X) placement(O) cell의 개수
    long long cellPrimitiveCount = 0;           // shapes(O) placement(X) cell의 개수

    bool xyrelative = false;                    // cell들 중에서 한 번이라도 선언된 적이 있으면 1, 없으면 0
    bool xyabsolute = false;                    // cell들 중에서 한 번이라도 선언된 적이 있으면 1, 없으면 0

    long long maxRefs = 0;                      // 모든 cell을 순회하면서 cell이 가지고 있는 refs의 개수 중 max
    long long maxShapesALayer = 0;              // 모든 cell을 순회, cell내 모든 layer를 순회하면서 layer 중 가장 많은 shapes 개수
    long long maxShapesAllLayer = 0;            // 모든 cell을 순회, cell이 갖는 #shapes(모든 layer의 합) 가장 큰 값

    string cellMaxRefs;                         // maxrefs를 갖고 있는 cell 이름
    string cellMaxShapesALayer;                 // maxshapes_a_layer를 갖고 있는 cell 이름
    string layerMaxShapesALayer;                // maxshapes_a_layer를 갖고 있는 cell의 layer
    string cellMaxShapesAllLayer;               // maxshapes-all-layer를 갖고 있는 cell 이름

    long long cellNameRec3Count = 0;            // '3' cellname-string 레코드가 등록된 회수
    long long cellNameRec4Count = 0;            // '4' cellname-string reference-number 레코드가 등록된 회수
    long long cellRec13Count = 0;               // ‘13’ reference-number 레코드가 등록된 회수
    long long cellRec14Count = 0;               // '14' cellname-string 레코드가 등록된 회수
    long long maxCBlockCountAcell = 0;          // cell안에 cblock이 여러번 선언될 수 있음. 선언된 회수 중 가장 큰 값
    string cellMaxCBlockCountAcell;             // maxCBlockCountAcell을 갖는 cell 이름

    long long maxCellSize = 0;                  // 가장 큰 cell size : cell 시작과 끝의 총 파일 사이즈(단위: bytes)
    long long avgCellSize = 0;                  // 평균 cellsize(empty cell 제외)
    long long minCellSize = 0;                  // 가장 작은 cell size(empty cell 제외)
    string cellMaxCellSize;                     // 가장 큰 cell size를 갖고 있는 cell 이름
    string cellMinCellSize;                     // 가장 작은 cell size를 갖고 있는 cell 이름(empty cell제외)

    long long cellSizeInterval = 0;             // maxCellSize / 10
    vector<long long> cellSizes;                // cellsize_interval*(idx) ~ cellsize_interval*(idx+1)에 속하는 cell 개수

    vector<long long> srepCounts;               // shapes 중 repeatition type이 idx가 나온 회수
    vector<long long> srepCountsExpanded;       // shapes 중 repeatition type이 idx가 나온 회수의 총합(repeation 해제 시 개수의 합)
    vector<long long> prepCounts;               // placement 중 repeatition type이 idx가 나온 회수
    vector<long long> prepCountsExpanded;       // placement 중 repeatition type이 idx가 나온 회수의 총합(repeation 해제 시 개수의 합)

    long long maxPlistCount = 0;                // 가장 긴 plist의 vertex 개수
    string cellMaxPlistCount;                   // maxPlistCount를 갖는 cell 이름
    string layerMaxPlistCount;                  // maxPlistCount를 갖는 layer
    vector<long long> plists;                   // vertex 개수가 {0~2, 3~6, 7~14, 15~62, 63~}의 범위에 속하는 회수

    unordered_map<std::string, void*> mapper;   // 데이터 매핑용
    vector<std::string> keyOrder;          // 출력 순서 저장용

    OasisStatistics(const std::string& file)
        : filename(file),
        cellSizes(10, 0),
        srepCounts(12, 0),
        srepCountsExpanded(12, 0),
        prepCounts(12, 0),
        prepCountsExpanded(12, 0),
        plists(5, 0)
    {
        // Initialize the mapper


        addEntry("filename", &filename);
        addEntry("TAT(s)", &analysisTimeSec);
        addEntry("filesize(MB)", &filesizeMB);
        addEntry("#cells", &cellCount);
        addEntry("#layers", &layerCount);
        addEntry("#shapes", &shapeCount);
        addEntry("#shapes_expand", &shapeCountExpanded);
        addEntry("#refs", &refCount);
        addEntry("#refs_expand", &refCountExpanded);
        addEntry("cblock", &cblock);
        addEntry("strict", &strict);
        addEntry("#text", &textCount);
        addEntry("#rectangle", &rectangleCount);
        addEntry("#polygon", &polygonCount);
        addEntry("#path", &pathCount);
        addEntry("#trapezoid", &trapezoidCount);
        addEntry("#ctrapezoid", &ctrapezoidCount);
        addEntry("#circle", &circleCount);
        addEntry("#xgeometry", &xgeometryCount);
        addEntry("#property", &propertyCount);
        addEntry("#cell_empty", &cellEmptyCount);
        addEntry("#cell_mixed", &cellMixedCount);
        addEntry("#cell_noshape", &cellNoShapeCount);
        addEntry("#cell_primitive", &cellPrimitiveCount);
        addEntry("xyrelative", &xyrelative);
        addEntry("xyabsolute", &xyabsolute);
        addEntry("#maxrefs", &maxRefs);
        addEntry("#maxshapes_a_layer", &maxShapesALayer);
        addEntry("#maxshapes_all_layer", &maxShapesAllLayer);
        addEntry("cell_maxrefs", &cellMaxRefs);
        addEntry("cell_maxshapes_a_layer", &cellMaxShapesALayer);
        addEntry("layer_maxshapes_a_layer", &layerMaxShapesALayer);
        addEntry("cell_maxshapes_all_layer", &cellMaxShapesAllLayer);
        addEntry("#cellname_rec_str_3", &cellNameRec3Count);
        addEntry("#cellname_rec_str_num_4", &cellNameRec4Count);
        addEntry("#cell_rec_number_13", &cellRec13Count);
        addEntry("#cell_rec_name_14", &cellRec14Count);
        addEntry("#maxcblockcount_a_cell", &maxCBlockCountAcell);
        addEntry("cell_maxcblockcount_a_cell", &cellMaxCBlockCountAcell);
        addEntry("maxcellsize", &maxCellSize);
        addEntry("avgcellsize", &avgCellSize);
        addEntry("mincellsize", &minCellSize);
        addEntry("cell_maxcellsize", &cellMaxCellSize);
        addEntry("cell_mincellsize", &cellMinCellSize);
        addEntry("#cellsize_interval", &cellSizeInterval);
        addEntry("#cellsize01", &cellSizes[0]);
        addEntry("#cellsize02", &cellSizes[1]);
        addEntry("#cellsize03", &cellSizes[2]);
        addEntry("#cellsize04", &cellSizes[3]);
        addEntry("#cellsize05", &cellSizes[4]);
        addEntry("#cellsize06", &cellSizes[5]);
        addEntry("#cellsize07", &cellSizes[6]);
        addEntry("#cellsize08", &cellSizes[7]);
        addEntry("#cellsize09", &cellSizes[8]);
        addEntry("#cellsize10", &cellSizes[9]);
        addEntry("#srep_00", &srepCounts[0]);
        addEntry("#srep_01", &srepCounts[1]);
        addEntry("#srep_02", &srepCounts[2]);
        addEntry("#srep_03", &srepCounts[3]);
        addEntry("#srep_04", &srepCounts[4]);
        addEntry("#srep_05", &srepCounts[5]);
        addEntry("#srep_06", &srepCounts[6]);
        addEntry("#srep_07", &srepCounts[7]);
        addEntry("#srep_08", &srepCounts[8]);
        addEntry("#srep_09", &srepCounts[9]);
        addEntry("#srep_10", &srepCounts[10]);
        addEntry("#srep_11", &srepCounts[11]);
        addEntry("#srep_00_expand", &srepCountsExpanded[0]);
        addEntry("#srep_01_expand", &srepCountsExpanded[1]);
        addEntry("#srep_02_expand", &srepCountsExpanded[2]);
        addEntry("#srep_03_expand", &srepCountsExpanded[3]);
        addEntry("#srep_04_expand", &srepCountsExpanded[4]);
        addEntry("#srep_05_expand", &srepCountsExpanded[5]);
        addEntry("#srep_06_expand", &srepCountsExpanded[6]);
        addEntry("#srep_07_expand", &srepCountsExpanded[7]);
        addEntry("#srep_08_expand", &srepCountsExpanded[8]);
        addEntry("#srep_09_expand", &srepCountsExpanded[9]);
        addEntry("#srep_10_expand", &srepCountsExpanded[10]);
        addEntry("#srep_11_expand", &srepCountsExpanded[11]);
        addEntry("#prep_00", &prepCounts[0]);
        addEntry("#prep_01", &prepCounts[1]);
        addEntry("#prep_02", &prepCounts[2]);
        addEntry("#prep_03", &prepCounts[3]);
        addEntry("#prep_04", &prepCounts[4]);
        addEntry("#prep_05", &prepCounts[5]);
        addEntry("#prep_06", &prepCounts[6]);
        addEntry("#prep_07", &prepCounts[7]);
        addEntry("#prep_08", &prepCounts[8]);
        addEntry("#prep_09", &prepCounts[9]);
        addEntry("#prep_10", &prepCounts[10]);
        addEntry("#prep_11", &prepCounts[11]);
        addEntry("#prep_00_expand", &prepCountsExpanded[0]);
        addEntry("#prep_01_expand", &prepCountsExpanded[1]);
        addEntry("#prep_02_expand", &prepCountsExpanded[2]);
        addEntry("#prep_03_expand", &prepCountsExpanded[3]);
        addEntry("#prep_04_expand", &prepCountsExpanded[4]);
        addEntry("#prep_05_expand", &prepCountsExpanded[5]);
        addEntry("#prep_06_expand", &prepCountsExpanded[6]);
        addEntry("#prep_07_expand", &prepCountsExpanded[7]);
        addEntry("#prep_08_expand", &prepCountsExpanded[8]);
        addEntry("#prep_09_expand", &prepCountsExpanded[9]);
        addEntry("#prep_10_expand", &prepCountsExpanded[10]);
        addEntry("#prep_11_expand", &prepCountsExpanded[11]);
        addEntry("#maxplist", &maxPlistCount);
        addEntry("cell_maxplist", &cellMaxPlistCount);
        addEntry("layer_maxplist", &layerMaxPlistCount);
        addEntry("#plist_00_02", &plists[0]);
        addEntry("#plist_03_06", &plists[1]);
        addEntry("#plist_07_14", &plists[2]);
        addEntry("#plist_15_62", &plists[3]);
        addEntry("#plist_63_xx", &plists[4]);

    }

private :
    void addEntry(const std::string& key, void* value) {
        mapper[key] = value;
        keyOrder.push_back(key);  // 삽입 순서 기록
    }
};

} // namespace Jeong
} // namespace Oasis
#endif
