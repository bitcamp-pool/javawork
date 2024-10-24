/** oasis-analysis.cc
 *
    [기능 개요]
    - LAYPOP에 입력되는 OASIS 파일의 구성 요소 중 성능에 영향을 주는 인자를 출력
    - Usage : oasis-analysis in.oas out.csv

    [SW 요건]
    - layout format 중 oasis만 입력 대상
    - 도형 및 placement를 메모리로 저장하면 안됨
    - 도형/placement 개수 산출 시 repetition을 해제하면 안됨. 해제 없이 개수만 증가
    - 통계 추출을 위한 구조체만 메모리에 새로 생성(cell별 구조체 생성은 OK, layer별 구조체는 필요 없음)
    - 숫자는 모두 long long
    - 출력 파일은 out.csv 형식

    [추가 소스 파일]
    /oasis-analysis
    ├── oasis-analysis.cc    // 메인 엔트리 포인트
    ├── analyzer.h           // 분석기 클래스 정의
    ├── analyzer.cc          // 분석기 클래스 구현
    ├── csv_writer.h         // CSV 출력 클래스 정의
    └── csv_writer.cc        // CSV 출력 클래스 구현

    [History]
    first        /writer : 2024-10-24 / 정용관
    last modified/writer : 2024-10-24 / 정용관
*/


#include <cstdio>
#include <cstring>
#include <unistd.h>
#include "misc/utils.h"
#include "parser.h"

#include <iostream>
#include <chrono>
#include "analyzer.h"
#include "csv_writer.h"

using namespace std;
using namespace SoftJin;
using namespace Oasis;
using namespace chrono;

const char  UsageMessage[] =
    "usage:  %s [-lntvx] in.oas out.csv\n"
    "Options:\n"
    "    -l  Ignore LAYERNAME records.\n"
    "\n"
    "    -n  Do not insist on strict conformance to the OASIS specification.\n"
    "        The default is to abort for (almost) any deviation.\n"
    "\n"
    "    -t  Ignore TEXT and TEXTSTRING records.\n"
    "\n"
    "    -v  Ignore the validation scheme and signature in the END record.\n"
    "\n"
    "    -x  Ignore XNAME, XELEMENT, and XGEOMETRY records.\n"
    "\n";


static void
UsageError() {
    fprintf(stderr, UsageMessage, GetProgramName());
    exit(1);
}

static void
DisplayWarning(const char* msg) {
    Error("%s", msg);
}

int
main(int argc, char* argv[])
{
    SetProgramName(argv[0]);

    OasisParserOptions parserOptions;

    int opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, "lntvx")) != EOF) {
        switch (opt) {
        case 'l':  parserOptions.wantLayerName     = false;   break;
        case 'n':  parserOptions.strictConformance = false;   break;
        case 't':  parserOptions.wantText          = false;   break;
        case 'v':  parserOptions.wantValidation    = false;   break;
        case 'x':  parserOptions.wantExtensions    = false;   break;
        default:   UsageError();
        }
    }

    if (optind != argc -2)
        UsageError();

    const char* infilename = argv[optind];
    const char* outfilename = argv[optind + 1];

    CSVWriter writer(outfilename);
    Analyzer analyzer;

    auto start = high_resolution_clock::now();

    try {
        Oasis::OasisParser parser(infilename, DisplayWarning, parserOptions);
        parser.parseFile(&analyzer);
    } catch (const std::exception& exc) {
        FatalError("%s", exc.what());
        return 1;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(end - start).count();
    writer.StatisticsWrite(analyzer.getStatistics());
    cout << "Analysis completed in " << duration << " seconds." << endl;

    return 0;
}
