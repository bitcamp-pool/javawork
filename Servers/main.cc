/*
/anuvad-analysis
│
├── main.cc              // 메인 엔트리 포인트
├── analyzer.h           // 분석기 클래스 정의
├── analyzer.cc          // 분석기 클래스 구현
├── csv_writer.h         // CSV 출력 클래스 정의
├── csv_writer.cc        // CSV 출력 클래스 구현
├── CMakeLists.txt       // CMake 빌드 스크립트 (빌드 자동화)
└── include/oasis        // 파서 및 관련 소스 (이미 업로드된 parser, printer 포함)

*/

#include <iostream>
#include <chrono>
#include "parser.h"
#include "analyzer.h"
#include "csv_writer.h"

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: anuvad-analysis <input.oas> <output.csv>" << endl;
        return 1;
    }

    const char* inputFile = argv[1];
    const char* outputFile = argv[2];

    auto start = high_resolution_clock::now();

    try {
        Oasis::OasisParser parser(inputFile);
        Analyzer analyzer;

        parser.parseFile(&analyzer);

        CSVWriter writer(outputFile);
        writer.write(analyzer.getStatistics());

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(end - start).count();
    cout << "Analysis completed in " << duration << " seconds." << endl;

    return 0;
}
