// oasis/analyzer.h -- high-level interface for reading and analysis OASIS files
//
// last modified:   2024/10/26


#ifndef OASIS_ANALYZER_H_INCLUDED
#define OASIS_ANALYZER_H_INCLUDED

#include "misc/utils.h"         // for WarningHandler
#include "builder.h"
#include "oasis_statistics.h"
#include "csv_writer.h"


namespace Oasis {
namespace Jeong {

using SoftJin::WarningHandler;


class OasisStatisticsBuilder : public OasisBuilder {
public:
    // Constructor
    OasisStatisticsBuilder(OasisStatistics& stats, CSVWriter& csvWriter);

    void BeginCell(CellName* cellName, long long startCellOffset);
    void EndCell();
    void BeginPlacement(CellName* cellName, const Repetition* rep);
    void BeginRectangle(Ulong layer, Ulong datatype, const Repetition* rep);
    void BeginPolygon(Ulong layer, Ulong datatype, const PointList& ptlist, const Repetition* rep);
    void BeginPath(Ulong layer, Ulong datatype, const PointList& ptlist, const Repetition* rep);
    void BeginTrapezoid(Ulong layer, Ulong datatype, const Repetition* rep);
    void BeginCTrapezoid(Ulong layer, Ulong datatype, const Repetition* rep);
    void BeginCircle(Ulong layer, Ulong datatype, const Repetition* rep);
    void BeginText(Ulong textlayer, Ulong texttype, const Repetition* rep);
    void BeginXGeometry(Ulong layer, Ulong datatype, const Repetition* rep);
    void EndElement();
    void EndFile(long long endFileOffset);

    // Custom functions to manage statistics collection and CSV output
    void finalizeStatistics();

private:
    OasisStatistics& oasisStats;
    vector<CellStatistics> cellStats;
    CSVWriter& writer;

    string currentCellName;
    long long currentCellRefCount;
    long long currentCellShapeCount;
    long long currentCellCBlockCount;
    long long cellStartPosition;

    void initializeCurrentCell(const std::string& name, long long offset);

/*
enum RepetitionType {
    Rep_ReusePrevious   = 0,
    Rep_Matrix          = 1,    // array aligned with the axes
    Rep_UniformX        = 2,    // uniformly spaced in a row
    Rep_UniformY        = 3,    // uniformly spaced in a column
    Rep_VaryingX        = 4,    // in a row with varying spaces between elems
    Rep_GridVaryingX    = 5,    // like VaryingX but elems are on grid points
    Rep_VaryingY        = 6,    // in a col with varying spaces between elems
    Rep_GridVaryingY    = 7,    // like VaryingY but elems are on grid points
    Rep_TiltedMatrix    = 8,    // like Matrix but may be tilted
    Rep_Diagonal        = 9,    // uniform spacing in line at any angle
    Rep_Arbitrary       = 10,   // elements can be anywhere
    Rep_GridArbitrary   = 11    // elements can be on any grid point
};
 */

    void updateElementStats (
        long long& elementCount,
        const Repetition* rep,
        std::vector<long long>& repCounts,
        std::vector<long long>& repCountsExpanded);

    void updateRepetitionFrequency (
        const Repetition* rep,
        std::vector<long long>& counts,
        bool expanded);

    void updateNormalOrExpandedCount(const Repetition* rep, long long& count, long long& expandedCount);
    void updateRepetitionTypeFrequency(const Repetition* rep, std::vector<long long>& repetitionCounts);
    void updateRepetitionTypeExpandedFrequency(const Repetition* rep, std::vector<long long>& repetitionCountsExpanded);

    long long getVertexCount(const PointList& ptlist) const;
    long long getExpandedCount(const Repetition* repetition) const;

    // OasisBuilder interface
public:
    void addFileProperty(Property *prop) override;
    void addCellProperty(Property *prop) override;
    void addElementProperty(Property *prop) override;
    void registerCellName(CellName *cellName) override;
    void registerTextString(TextString *textString) override;
    void registerPropName(PropName *propName) override;
    void registerPropString(PropString *propString) override;
    void registerLayerName(LayerName *layerName) override;
    void registerXName(XName *xname) override;
};

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

class ParserImpl;

class OasisParser {
    ParserImpl* impl;   // all requests are forwarded to this body instance

public:
                OasisParser (const char* fname, WarningHandler warner,
                             const OasisParserOptions& options);
                ~OasisParser();
    void        validateFile();
    Validation  parseValidation();
    void        parseFile (OasisStatisticsBuilder* builder);
    bool        parseCell (const char* cellname, OasisStatisticsBuilder* builder);

private:
                OasisParser (const OasisParser&);       // forbidden
    void        operator= (const OasisParser&);         // forbidden
};

}  // namespace Jeong
}  // namespace Oasis

#endif  // OASIS_ANALYZER_H_INCLUDED
