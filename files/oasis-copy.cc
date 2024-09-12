/** *******************************************************************************
 oasis/oasis-copy.cc -- OasisCreator를 이용한 OASIS binary stream 생성
 마지막 수정일 :   2024.08.25
 작성자        :   정용관
 구현 항목     :
 1. [INPUT_CELLNAMES::OASCOPY] 
 2. [INPUT_CELLNAMES::CREATOR] 
 3. [INPUT_CELLNAMES::PARSER]  
 4. [CBLOCK_ON_OFF::OASISCOPY] 
 5. [CBLOCK_ON_OFF::CREATOR]  
 6. [STRICT_ON_OFF::OASISCOPY]  
 7. [STRICT_ON_OFF::CREATOR] 
 8. [CELLS_HIERARCHY::PARSER]  


 usage:  oasis-copy [-c cellname] [-lntvxizh] input-oasis-file output-oasis-file

 *********************************************************************************/

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <unistd.h>
#include <iostream>

#include "misc/utils.h"
#include "creator.h"
#include "parser.h"


using namespace std;
using namespace Anuvad::SoftJin;
using namespace Anuvad::Oasis;


const char  UsageMessage[] =
"usage:  %s [-c cellname] [-ilntvx] input-oasis-file output-oasis-file\n"
"Options:\n"
"    -c cellname\n"
"        Select cell.  Create binary stream for only the specified cell.\n"
"        The default is to create the entire file.\n"
"\n"
"    -i  Write name records immediately to the file.\n"
"        Use this option if you need to ensure compatibility with\n"
"        tools that require names to appear before their references.\n"
"        By default, name records are written at the end of the file.\n"
"\n"
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
DisplayWarning (const char* msg) {
    Error("%s", msg);
}



int
main (int argc, char* argv[])
{
    SetProgramName(argv[0]);

    std::vector<std::string> enteredCellNames;
    OasisParserOptions  parserOptions;

    /** [CBLOCK_ON_OFF] 
     *  [INPUT_CELLNAMES]
     *  [STRICT_ON_OFF]
     *  ADD
     *   - immediateNames(false), mustCompressed(true), hasCellNames(false), strict(true)
     */
    OasisCreatorOptions creatorOptions(false, true, false, true);
    bool isCellNames = false;

    int  opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, "c:lntvxizs")) != EOF) {
        switch (opt) {
            case 'c': 
            {
                enteredCellNames.emplace_back(optarg); // 첫 번째 셀 이름 추가
                while (optind < argc && argv[optind][0] != '-') {
                        enteredCellNames.emplace_back(argv[optind++]); // 나머지 셀 이름 추가
                }
                break;
            }
            case 'l':  parserOptions.wantLayerName     = false;   break;
            case 'n':  parserOptions.strictConformance = false;   break;
            case 't':  parserOptions.wantText          = false;   break;
            case 'v':  parserOptions.wantValidation    = false;   break;
            case 'x':  parserOptions.wantExtensions    = false;   break;
            case 'i':  creatorOptions.immediateNames   = true;    break;
            case 'z':  creatorOptions.mustCompressed   = false;   break;
            case 's':  creatorOptions.strict           = false;   break;
            default:   UsageError();
        }
    }
    isCellNames = !enteredCellNames.empty(); // 셀 이름이 수집된 경우 true
    creatorOptions._hasCellNames = isCellNames;

    if (optind != argc-2)   // 수정 : 입력 및 출력 파일 모두 필요
        UsageError();

    const char*  infilename  = argv[optind];
    const char*  outfilename = argv[optind + 1];

    try {
        OasisParser   parser(infilename, DisplayWarning, parserOptions);
        OasisCreator  creator(outfilename, creatorOptions);

        if (!isCellNames) {  // 셀 이름이 지정되지 않은 경우
            parser.parseFile(&creator);
        } else if (!parser.JCreateLayoutDataBase(enteredCellNames, &creator)) {
            FatalError("file '%s' has no cell name you entered.", infilename);
        }

        if (fclose(stdout) == EOF)
            FatalError("cannot close standard output: %s", strerror(errno));
    }
    catch (const std::exception& exc) {
        FatalError("%s", exc.what());
    }
    return 0;
}


/**********************Original Code********************************************

int
main (int argc, char* argv[])
{
    SetProgramName(argv[0]);

    const char*  cellname = Null;
    OasisParserOptions  parserOptions;
    OasisCreatorOptions creatorOptions(false, true, cellname, true);

    int  opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, "c:lntvxizs")) != EOF) {
        switch (opt) {
            case 'c':  cellname = optarg;                         break;
            case 'l':  parserOptions.wantLayerName     = false;   break;
            case 'n':  parserOptions.strictConformance = false;   break;
            case 't':  parserOptions.wantText          = false;   break;
            case 'v':  parserOptions.wantValidation    = false;   break;
            case 'x':  parserOptions.wantExtensions    = false;   break;
            case 'i':  creatorOptions.immediateNames   = true;    break;
            case 'z':  creatorOptions.mustCompressed   = false;   break;
            case 's':  creatorOptions.strict           = false;   break;
            default:   UsageError();
        }
    }
    creatorOptions.inputCellName = cellname;

    if (optind != argc-2)   // 수정 : 입력 및 출력 파일 모두 필요
        UsageError();
    const char*  infilename  = argv[optind];
    const char*  outfilename = argv[optind + 1];

    try {
        OasisParser   parser(infilename, DisplayWarning, parserOptions);

        // OasisCreator 초기화
        OasisCreator  creator(outfilename, creatorOptions);

        if (cellname == Null)
            parser.parseFile(&creator);
        // [OASCOPY::INPUT_CELLNAME]
        else if (! parser.CreateLayoutDataBase (cellname, &creator))
            FatalError("file '%s' has no cell '%s'", infilename, cellname);

        if (fclose(stdout) == EOF)
            FatalError("cannot close standard output: %s", strerror(errno));
    }
    catch (const std::exception& exc) {
        FatalError("%s", exc.what());
    }
    return 0;
}


********************************************************************************/

