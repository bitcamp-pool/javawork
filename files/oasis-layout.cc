#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <unistd.h>
#include "misc/utils.h"
#include "creator.h"
#include "parser.h"
#include "layoutbuilder.h"

#include "iostream"

using namespace std;
using namespace SoftJin;
using namespace Oasis;

const char  UsageMessage[] =
    "usage:  %s [-c cellname] [-ilntvxzs] input-oasis-file output-oasis-file\n"
    "Options:\n"
    "    -c cellname   Select cell(s). Specify the name(s) of the cell(s) to process.\n"
    "    -i            Write name records immediately to the file.\n"
    "    -l            Ignore LAYERNAME records.\n"
    "    -n            Do not insist on strict conformance to the OASIS specification.\n"
    "    -t            Ignore TEXT and TEXTSTRING records.\n"
    "    -v            Ignore the validation scheme and signature in the END record.\n"
    "    -x            Ignore XNAME, XELEMENT, and XGEOMETRY records.\n"
    "    -z            Disable compression for the output file.\n"
    "    -s            Disable strict mode.\n"
    "Notes:\n"
    "    - The input and output files must have the '.oas' extension.\n";

static void UsageError() {
    fprintf(stderr, UsageMessage, GetProgramName());
    exit(1);
}

static void DisplayWarning(const char* msg) {
    Error("%s", msg);
}

bool isOasisFile(const std::string& str) {
    return str.size() > 4 && str.substr(str.size() - 4) == ".oas";
}

// 메뉴 표시 함수
void displayMenu() {
    std::cout << endl;
    std::cout << "[Menu]\n";
    std::cout << "1. Print BBox of a Specific TOP CELL\n";
    std::cout << "2. Print BBoxes of All Cells\n";
    std::cout << "3. Print BBoxes of Layers\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

// 특정 TOP CELL의 BBox 출력 함수
void printSpecificTopCellBBox(JLayoutBuilder& layoutBuilder) {
    std::string cellName;
    std::cout << "Enter the TOP CELL name: ";
    std::cin >> cellName;

    JCell* cell = layoutBuilder.findRefCell(new CellName(cellName));
    if (cell) {
        std::unordered_set<const JCell*> visited;
        JLayout::BBox bbox = layoutBuilder.calculateCellBBox(cell, visited);
        std::cout << "BBox for TOP CELL " << cellName << ": ("
                  << bbox.x_min / 1000.0 << ", " << bbox.y_min / 1000.0 << ") ("
                  << bbox.x_max / 1000.0 << ", " << bbox.y_max / 1000.0 << ")\n";
    } else {
        std::cout << "TOP CELL " << cellName << " not found.\n";
    }
}

// 전체 셀의 BBox 출력 함수
void printAllCellBBoxes(const JLayoutBuilder& layoutBuilder) {
    layoutBuilder.printLayoutCellBBoxes();
}

void printBBoxesByLayer(const JLayoutBuilder& layoutBuilder) {
    layoutBuilder.printLayoutBBoxesByLayer();
}

int main(int argc, char* argv[]) {
    SetProgramName(argv[0]);

    std::vector<std::string> enteredCellNames;
    OasisParserOptions parserOptions;
    OasisCreatorOptions creatorOptions(false, true, false, true);
    bool isCellNames = false;

    int opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, "c:lntvxizs")) != EOF) {
        switch (opt) {
            case 'c': {
                // 첫 번째 셀 이름 추가
                enteredCellNames.emplace_back(optarg);
                // 나머지 셀 이름 추가
                while (optind < argc && argv[optind][0] != '-' && !isOasisFile(argv[optind])) {
                    enteredCellNames.emplace_back(argv[optind]);
                    ++optind;
                }
                break;
            }
            case 'l':  parserOptions.wantLayerName     = false;   break;
            case 'n':  parserOptions.strictConformance = false;   break;
            case 't':  parserOptions.wantText          = false;   break;
            case 'v':  parserOptions.wantValidation    = false;   break;
            case 'x':  parserOptions.wantExtensions    = false;   break;
            case 'i':  creatorOptions.immediateNames   = true;    break;
            case 'z':  creatorOptions._mustCompressed  = false;   break;
            case 's':  creatorOptions._mustStrict      = false;   break;
            default:   UsageError();
        }
    }

    isCellNames = !enteredCellNames.empty();
    creatorOptions._hasCellNames = isCellNames;

    // 마지막 두 개의 인자는 입력 및 출력 파일로, 반드시 .oas 확장자여야 함
    if (optind != argc - 2 || !isOasisFile(argv[optind]) || !isOasisFile(argv[optind + 1])) {
        UsageError();
    }

    const char* infilename = argv[optind];
    const char* outfilename = argv[optind + 1];

    try {
        OasisParser parser(infilename, DisplayWarning, parserOptions);
        OasisCreator creator(outfilename, creatorOptions);
        JLayoutBuilder layoutBuilder(creator);

        parser.parseFile(&layoutBuilder);

        int choice;
        do {
            displayMenu();
            std::cin >> choice;

            // 입력 오류 처리
            if (std::cin.fail()) {
                std::cin.clear();  // 오류 플래그 초기화
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 입력 버퍼 비우기
                std::cout << "Invalid input. Please enter a valid option.\n";
                continue;
            }

            switch (choice) {
            case 1:
                std::cout << endl;
                printSpecificTopCellBBox(layoutBuilder);
                break;
            case 2:
                std::cout << endl;
                printAllCellBBoxes(layoutBuilder);
                break;
            case 3:
                std::cout << endl;
                printBBoxesByLayer(layoutBuilder);
                break;                
            case 4:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        } while (choice != 4);
    } catch (const std::exception& exc) {
        FatalError("%s", exc.what());
    }

    return 0;
}
