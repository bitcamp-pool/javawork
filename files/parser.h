// oasis/parser.h -- high-level interface for reading OASIS files
//
// last modified:   25-Dec-2009  Fri  10:33
//
// Copyright (c) 2004 SoftJin Infotech Private Ltd.
// This software may be used only under the terms of the SoftJin
// Source License.  See the accompanying file LICENSE for details.

#ifndef OASIS_PARSER_H_INCLUDED
#define OASIS_PARSER_H_INCLUDED

#include "misc/utils.h"         // for WarningHandler
#include "builder.h"

namespace Anuvad {
namespace Oasis {

using Anuvad::SoftJin::WarningHandler;


// OasisParserOptions -- options for OasisParser
//
// The flag strictConformance says whether the parser should strictly
// conform to the spec.  Some programs generate non-conforming OASIS
// files; strictConformance must be set to false when parsing such
// files.  Below are some of the checks dropped when it is false.

// strictConformance 플래그는 파서가 OASIS 파일 형식에 대해 엄격한 규격 준수를
// 해야 하는지 여부를 결정합니다. 이 플래그가 true로 설정된 경우, 파서는
// OASIS 파일 사양에 엄격히 따라야 하며, 사소한 규격 위반도 허용되지 않습니다.
// 반대로 false로 설정된 경우, 파서는 사소한 규격 위반을 허용하고 유연하게 동작합니다.
// strictConformance가 false일 때 생략되는 몇 가지 검사 항목을 설명하고 있습니다.

//    - Standard properties are not checked to verify that they appear
//      in the right context.

//      표준 속성의 맥락 확인: 표준 속성(Standard properties)이 올바른 맥락(Context)에서
//      나타나는지 여부를 검사하지 않습니다.
//
//    - PROPERTY records can contain property names instead of refnums
//      even when the PROPNAME table has the strict flag set, and can
//      contain string values instead of refnums even when the
//      PROPSTRING table has the strict flag set.
//
//      PROPNAME 및 PROPSTRING 테이블의 엄격 모드:
//      PROPNAME 테이블이 엄격 모드(strict flag)로 설정된 경우에도 PROPERTY 레코드가
//      프로퍼티 이름 대신 참조 번호(refnums)를 포함할 수 있습니다. PROPSTRING 테이블이
//      엄격 모드로 설정된 경우에도 문자열 값 대신 참조 번호를 사용할 수 있습니다.

//    - All characters in the range 0x1 - 0x7f are allowed in a-strings.
//      (The spec restricts the range to 0x20 - 0x7e.)
//
//      문자열 허용 범위: a-strings에서 0x1에서 0x7f 범위의 모든 문자를 허용합니다.
//      (사양에서는 0x20에서 0x7e 범위로 제한합니다.)

//    - Unused bits are ignored in the info-byte of TEXT, POLYGON,
//      CIRCLE, and XGEOMETRY records.  Normally the parser aborts if
//      any of the unused bits is set.
//
//      텍스트, 폴리곤, 원, X기하 레코드의 정보 바이트: 텍스트(TEXT), 폴리곤(POLYGON), 원(CIRCLE),
//      X기하(XGEOMETRY) 레코드의 정보 바이트에 사용되지 않은 비트가 설정된 경우에도 파서가 중단되지 않습니다.
//      (보통은 사용되지 않은 비트가 설정되어 있으면 파서가 중단됩니다.)

//    - Bytes after the END record are ignored.
//      END 레코드 이후의 바이트: END 레코드 이후에 나오는 바이트들은 무시됩니다.

//      이러한 사항들은 파서가 보다 유연하게 동작할 수 있도록 해줍니다.
//      특히, 사양을 엄격히 준수하지 않는 OASIS 파일을 처리할 때 유용합니다.

// The flag wantValidation allows parsing of OASIS files with mangled
// END records.  When this is false, OasisParser ignores the validation
// scheme and signature in the END record.  In the call to
// OasisBuilder::beginFile() it sets valScheme to Validation::None.
//
// wantValidation 플래그: 이 플래그는 OASIS 파일의 END 레코드에서 유효성 검사 스키마와 서명을 확인할지 여부를 결정합니다.
// 플래그가 false인 경우:
// OasisParser는 OASIS 파일의 END 레코드에 있는 유효성 검사 스키마와 서명을 무시합니다.
// 결과적으로, OasisBuilder::beginFile() 메서드를 호출할 때 valScheme을 Validation::None으로 설정합니다.
// 이는 유효성 검사를 수행하지 않는 것을 의미합니다.
// 이 플래그를 사용하면 END 레코드가 손상되었거나 비정상적으로 구성된 OASIS 파일을 처리할 수 있습니다.
// wantValidation이 false로 설정되면 파서는 유효성 검사를 건너뛰고 파일을 읽어들이는 데 집중합니다.

// Normally the parser begins by parsing both START and END records.
// But if wantValidation is false and table-offsets is in the START
// record, it parses only START.  Thus the END record need not begin
// exactly 256 bytes before the end of the file as the spec requires,
// and need not contain anything but the record ID.
//
// 일반적인 경우:
//    파서는 OASIS 파일의 START 및 END 레코드를 모두 파싱하는 것으로 시작합니다.
//    이는 파일의 구조와 무결성을 확인하기 위해 필요한 단계입니다.
// wantValidation이 false인 경우:
//    파서는 START 레코드에서 테이블 오프셋을 확인하면 END 레코드를 파싱하지 않고 무시할 수 있습니다.
//    따라서 END 레코드가 파일의 끝에서 정확히 256바이트 전에 시작해야 한다는 명세서의 요구사항을 충족하지 않아도 됩니다.
//    또한 END 레코드가 단순히 레코드 ID만 포함하고 있어도 무방합니다.
// 즉, wantValidation이 false로 설정되면 파서는 END 레코드의 정확한 위치나 내용에 대해 엄격하게 검사하지 않습니다.
// 이는 유효성 검사 없이도 파일을 파싱할 수 있도록 유연성을 제공합니다.

// The flags wantText, wantLayerName, and wantExtensions specify whether
// the parser should parse TEXT, TEXTSTRING, LAYERNAME, and extension
// records (and any following PROPERTY records).  Applications that are
// not interested in any of those records should set the corresponding
// flag to false.  This might speed up parsing.  Some OASIS tools set
// strict=0, offset=0 in the table offsets when there are no <name>
// records of a particular kind.  (The strict flag should be 1 instead.)
// Normally the parser makes a preliminary pass to collect <name>
// records if any name table is non-strict.  But if the application does
// not want records of some kind, the parser need not care whether the
// corresponding table is strict because it is going to ignore those
// records.  The name-parsing pass can thus be avoided in some cases.

// OasisParserOptions 구조체에 있는 여러 플래그의 역할과, 이 플래그들이 파서의 동작 방식에 미치는 영향을 설명합니다.
// wantText, wantLayerName, wantExtensions 플래그:
//    이 플래그들은 각각 파서가 TEXT, TEXTSTRING, LAYERNAME, 확장 레코드(및 그에 따라오는 PROPERTY 레코드)를
//    파싱할지 여부를 지정합니다. 애플리케이션이 이러한 레코드들에 관심이 없으면,
//    해당 플래그를 false로 설정할 수 있습니다. 이렇게 하면 파싱 속도가 빨라질 수 있습니다.
// <name> 테이블의 엄격성:
//    일부 OASIS 도구들은 특정 종류의 <name> 레코드가 없을 때,
//    테이블 오프셋에서 strict=0, offset=0으로 설정할 수 있습니다.(사실, strict 플래그는 1이어야 합니다.)
//    파서는 일반적으로 <name> 테이블이 비엄격한 경우 해당 <name> 레코드들을 수집하기 위해 사전 패스를 수행합니다.
//    하지만 애플리케이션이 특정 종류의 레코드를 원하지 않는 경우,
//    파서는 해당 테이블이 엄격한지 여부를 신경 쓸 필요가 없습니다. 어차피 해당 레코드를 무시할 것이기 때문입니다.
//    따라서, 특정한 경우에는 이름 파싱 패스를 생략할 수 있습니다.
// 이 요약은 파서의 최적화 옵션들을 잘 활용함으로써 필요하지 않은 데이터의 파싱을 피하고,
// 전체적인 파싱 시간을 단축할 수 있다는 점을 강조합니다.
//
// If any of the wantFoo flags is false, most validity checks on the
// corresponding records are dropped, even if strictConformance is true.
// For example, if wantText is false the parser does not verify that at
// most one of the TEXTSTRING record types 5 and 6 appears in the file.
// But OasisRecordReader and OasisScanner still check for errors that
// will affect parsing the rest of the file.  For example,
// OasisRecordReader throws runtime_error if a LAYERNAME record has an
// invalid interval type, even if wantLayerName is false.

// wantFoo 플래그가 false로 설정된 경우, 해당 플래그와 관련된 레코드들에 대한 유효성 검사 방법이
// 어떻게 변경되는지를 설명합니다.
// wantFoo 플래그:
//    wantFoo는 wantText, wantLayerName, wantExtensions 등의 플래그를 의미합니다.
//    이 플래그들 중 하나라도 false로 설정되면, 해당 레코드들에 대한 대부분의 유효성 검사는 수행되지 않습니다.
//    이는 strictConformance가 true로 설정된 경우에도 마찬가지입니다.
//    예를 들어, wantText가 false일 때는 파일 내에 TEXTSTRING 레코드 유형 5와 6이 최대 하나만 나타나야 한다는
//    유효성 검사가 수행되지 않습니다.
// 중요한 오류 검사:
//    그러나 OasisRecordReader와 OasisScanner는 파일의 나머지 부분을 파싱하는 데 영향을 미치는 오류에 대해서는
//    여전히 검사합니다. 예를 들어, wantLayerName이 false인 경우에도 OasisRecordReader는 LAYERNAME 레코드에
//    잘못된 interval 타입이 있는 경우 런타임 오류를 발생시킵니다.
// 불필요한 레코드에 대한 검사 비용을 줄이기 위해 특정 플래그를 사용하지만,
// 중요한 파일 파싱 오류는 여전히 확인하여 파일의 나머지 부분을 제대로 파싱할 수 있도록 보장한다는 점을 설명합니다.


struct OasisParserOptions {
    bool  strictConformance;    // false => allow minor deviations from spec
    bool  wantValidation;       // false => ignore validation in END
    bool  wantText;             // false => ignore TEXT and TEXTSTRING
    bool  wantLayerName;        // false => ignore LAYERNAME
    bool  wantExtensions;       // false => ignore XNAME, XELEMENT, XGEOMETRY

public:
    OasisParserOptions() {
        strictConformance = true;
        wantValidation = true;
        wantText = true;
        wantLayerName = true;
        wantExtensions = true;
    }

    void
    resetAll() {
        strictConformance = false;
        wantValidation = false;
        wantText = false;
        wantLayerName = false;
        wantExtensions = false;
    }
};

// OASIS 파서 클래스의 설계 방식에 대해 설명합니다.
// 구체적으로, Handle/Body (또는 Pimpl) 패턴을 사용하여 클래스의 구현 세부 사항을 사용자로부터 숨기고 있음을 강조합니다.
// 이를 통해 코드의 모듈성을 유지하고, 구현 변경 시 인터페이스에 영향을 미치지 않도록 하는 것입니다.
// 주요 내용은 다음과 같습니다:

// 클래스 크기: OASIS 파서 클래스는 20개 이상의 데이터 멤버와 80개 이상의 메서드를 가지고 있으며,
// 이는 매우 크고 복잡한 구조임을 나타냅니다.

// 프라이빗 멤버: 이 클래스의 거의 모든 메서드는 프라이빗(private)으로 선언되어 있습니다.
// 이는 클래스 외부에서 직접 접근할 수 없으며, 내부 구현 세부 사항을 숨기기 위한 것입니다.

// Handle/Body (Pimpl) 패턴 사용: 이 패턴은 클래스를 두 부분으로 나누는 방법을 제시합니다.
//   Body (구현):         실제 기능 구현을 담당하는 클래스입니다.
//                        여기서는 ParserImpl 클래스로, parser.cc 파일에 정의되어 있습니다.
//   Handle (인터페이스): 외부에 노출되는 인터페이스 클래스입니다.
//                        여기서는 OasisParser 클래스가 그 역할을 합니다.

// 구현 세부 사항 숨기기: OasisParser 클래스는 ParserImpl 객체에 대한 포인터를 유지하고 있으며,
// 모든 요청을 ParserImpl 객체로 전달합니다. 사용자는 OasisParser의 인터페이스를 통해서만 파서를 사용할 수 있으며,
// 내부 구현인 ParserImpl의 세부 사항을 알 필요가 없습니다.

// 이 방식의 주요 장점은:
//    구현과 인터페이스의 분리: 내부 구현이 변경되어도 외부 인터페이스는 그대로 유지될 수 있어,
//                              코드의 유연성과 유지 보수성을 높일 수 있습니다.
//    컴파일 시간 단축:         구현 클래스의 변경이 있을 때마다 전체 프로그램을 다시 컴파일할 필요가 없습니다.
//                              인터페이스 클래스와 구현 클래스 간의 명확한 분리가 있기 때문입니다.

// OasisBuilder 문서 참고: parseFile() 및 parseCell() 메서드의 사용 방법에 대해 알고 싶다면,
// builder.h 파일에 있는 OasisBuilder 클래스의 문서를 참조해야 한다.
// OasisBuilder는 파서가 파싱하는 동안 호출되는 콜백 메서드들을 정의하고 있습니다.
// parseFile()과 parseCell()은 OASIS 파일 전체 또는 특정 셀을 파싱하는 기능을 제공하며,
// 이 과정에서 OasisBuilder가 어떻게 사용되는지에 대한 구체적인 설명이 builder.h에 나와 있습니다.

// 파일 유효성 검사: validateFile() 메서드는 파일에 있는 CRC(순환 중복 검사) 또는 체크섬을 검사합니다.
// 파일에 이러한 유효성 검증 데이터가 있는 경우, validateFile()은 이를 확인하고 올바르지 않으면 runtime_error 예외를 발생시킵니다.
// 이는 파일의 무결성을 확인하는 중요한 단계로, 파일 전송 중 오류나 변조 여부를 확인할 수 있습니다.

// The OASIS parser class is large, with over 20 data members and over
// 80 methods.  Because almost all those methods are private, we use the
// Handle/Body (or Pimpl) idiom to hide that mess from the users of this
// library.  The body class which has all the code is ParserImpl in
// parser.cc.  The handle class is OasisParser, declared here.
// OasisParser keeps a pointer to a ParserImpl object and forwards all
// requests to it.
//
// See the OasisBuilder documentation in builder.h for how to use
// parseFile() and parseCell().  validateFile() checks the CRC/checksum
// in the file, if any, and throws a runtime_error if it's wrong.

class ParserImpl;

class OasisParser {
    /**
     * @brief impl
     * OasisParser 클래스의 모든 메서드는 실제 구현을 포함하는 이 ParserImpl 객체로 전달됩니다.
     * 이는 Pimpl(핸들/바디) 패턴을 사용하여 구현 세부 사항을 숨기고, 인터페이스와 구현을 분리하는 역할을 합니다.
     */
    ParserImpl* impl;   // all requests are forwarded to this body instance

public:
                OasisParser (const char* fname, WarningHandler warner,
                             const OasisParserOptions& options);
                ~OasisParser();

    void        validateFile();
    Validation  parseValidation(); // 파일의 유효성 검사 정보를 파싱합니다. 이는 파일의 검증 체계(예: 체크섬 방식)를 반환합니다.
    void        parseFile (OasisBuilder* builder); // 전체 OASIS 파일을 파싱하며, 파싱 중 발견되는 다양한 요소에 대해 OasisBuilder의 콜백 메서드를 호출합니다.
    bool        parseCell (const char* cellname, OasisBuilder* builder); // 특정 셀 이름에 해당하는 셀을 파싱합니다. 셀을 찾고 파싱에 성공하면 true를, 그렇지 않으면 false를 반환합니다.

    /** [INPUT_CELLNAMES]
     *  CREATE
     */
    bool        CreateLayoutDataBase (const std::vector<std::string>& cellnames, OasisBuilder* builder);

    // OasisBuilder는 파싱된 데이터를 수신하고 처리하는 역할을 하며,
    // Pimpl 패턴을 통해 구현 세부 사항을 감추고 인터페이스를 깔끔하게 유지할 수 있습니다.

private:
                OasisParser (const OasisParser&);       // forbidden
    void        operator= (const OasisParser&);         // forbidden
};


}  // namespace Oasis
}  // namespace Anuvad

#endif  // OASIS_PARSER_H_INCLUDED
