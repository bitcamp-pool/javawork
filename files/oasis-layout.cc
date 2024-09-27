​
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <unistd.h>
#include "misc/utils.h"
#include "creator.h"
#include "parser.h"
#include <iostream>
#include "layoutbuilder.h"

    using namespace std;
using namespace SoftJin;
using namespace Oasis;

const char UsageMessage[] =
    "usage:  %s [-c cellname] [-ilntvxzs] input-oasis-file output-oasis-file\n"
    "Options:\n"
    "  -c cellname  Select cell(s). Specify the name(s) of the cell(s) to process.\n"
    "  -i  Write name records immediately to the file.\n"
    "  -l  Ignore LAYERNAME records.\n"
    "  -n  Do not insist on strict conformance to the OASIS specification.\n"
    "  -t  Ignore TEXT and TEXTSTRING records.\n"
    "  -v  Ignore the validation scheme and signature in the END record.\n"
    "  -x  Ignore XNAME, XELEMENT, and XGEOMETRY records.\n"
    "  -z  Disable compression for the output file.\n"
    "  -s  Disable strict mode.\n"
    "Notes:\n"
    "  - The input and output files must have the '.oas' extension.\n";

static void UsageError()
{
    fprintf(stderr, UsageMessage, GetProgramName());
    exit(1);
}

static void DisplayWarning(const char *msg)
{
    Error("%s", msg);
}

bool isOasisFile(const std::string &str)
{
    return str.size() > 4 && str.substr(str.size() - 4) == ".oas";
}

int main(int argc, char *argv[])
{
    SetProgramName(argv[0]);

    std::vector<std::string> enteredCellNames;
    OasisParserOptions parserOptions;
    OasisCreatorOptions creatorOptions(false, true, false, true);
    bool isCellNames = false;

    int opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, "c:lntvxizs")) != EOF)
    {
        switch (opt)
        {
        case 'c':
        {
            // 첫 번째 셀 이름 추가
            enteredCellNames.emplace_back(optarg);
            // 나머지 셀 이름 추가
            while (optind < argc && argv[optind][0] != '-' && !isOasisFile(argv[optind]))
            {
                enteredCellNames.emplace_back(argv[optind]);
                ++optind;
            }
            break;
        }
        case 'l':
            parserOptions.wantLayerName = false;
            break;
        case 'n':
            parserOptions.strictConformance = false;
            break;
        case 't':
            parserOptions.wantText = false;
            break;
        case 'v':
            parserOptions.wantValidation = false;
            break;
        case 'x':
            parserOptions.wantExtensions = false;
            break;
        case 'i':
            creatorOptions.immediateNames = true;
            break;
        case 'z':
            creatorOptions._mustCompressed = false;
            break;
        case 's':
            creatorOptions._mustStrict = false;
            break;
        default:
            UsageError();
        }
    }

    isCellNames = !enteredCellNames.empty();
    creatorOptions._hasCellNames = isCellNames;

    // 마지막 두 개의 인자는 입력 및 출력 파일로, 반드시 .oas 확장자여야 함
    if (optind != argc - 2 || !isOasisFile(argv[optind]) || !isOasisFile(argv[optind + 1]))
    {
        UsageError();
    }

    const char *infilename = argv[optind];
    const char *outfilename = argv[optind + 1];

    try
    {
        OasisParser parser(infilename, DisplayWarning, parserOptions);
        OasisCreator creator(outfilename, creatorOptions);
        JLayoutBuilder layoutBuilder(creator);

        // 셀 이름이 지정되지 않은 경우 전체 파일 파싱
        if (!isCellNames)
        {
            parser.parseFile(&layoutBuilder);
        }
        else
        {
            // 지정된 셀 이름이 있는 경우
            if (!parser.JCreateLayoutDataBase(enteredCellNames, &layoutBuilder))
            {
                FatalError("file '%s' has no cell name you entered.", infilename);
            }
        }

        // layoutBuilder.generateBinary(); // binary 생성

        if (fclose(stdout) == EOF)
        {
            FatalError("cannot close standard output: %s", strerror(errno));
        }
    }
    catch (const std::exception &exc)
    {
        FatalError("%s", exc.what());
    }

    return 0;
}
