
#include <map>
#include <iostream>

/** _______________________________________________________________________________
 *
 *  [CELL_HIERARCHY]
 *  CREATE
 *  - TreeNode, HierarchyTree
 */

class JTreeNode {
    CellName* _cellName;
    std::vector<JTreeNode*> _children;
    bool _visited;

public:
    JTreeNode(CellName* name) : _cellName(name), _visited(false){}

    void addChild(JTreeNode* child) {
        _children.push_back(child);
    }
public:
    bool getVisited() const { return _visited; }
    void setVisited(bool newVisited) { _visited = newVisited; }

    const std::vector<JTreeNode *> &getChildren() const {
        return _children;
    }

    CellName *getCellName() const { return _cellName; }
    void setCellName(CellName *newCellName) {
        _cellName = newCellName;
    }
};

class JCellHierarchy {
public:
    std::map<std::string, TreeNode*> _cellTreeMap;

    // 노드를 찾거나 없으면 새로 생성하는 함수
    JTreeNode* findOrCreateNode(CellName* cellName){
        std::string name = cellName->getName();
        if (_cellTreeMap.find(name) == _cellTreeMap.end()){
            _cellTreeMap[name] = new JTreeNode(cellName);
        }
        return _cellTreeMap[name];
    }

    ~JCellHierarchy() {
        for (auto& pair : _cellTreeMap){
            delete pair.second;
        }
    }
};

/**  _______________________________________________________________________________*/

class ParserImpl {

    OasisScanner        scanner;
    OasisRecordReader   recReader;      // returns records one by one
    OasisParserOptions  parserOptions;
    WarningHandler      warnHandler;    // callback for warning messages
    OasisBuilder*       builder;
    ModalVars           modvars;        // store all modal variables

    // Dictionaries for cells and the six types of names.
    CellDict            cellDict;       // map from CellName* to Cell*
    CellNameDict        cellNameDict;
    PropNameDict        propNameDict;
    PropStringDict      propStringDict;
    TextStringDict      textStringDict;
    XNameDict           xnameDict;
    LayerNameDict       layerNameDict;

    // unregistered PropNames and TextStrings
    PointerVector<PropName>     unregPropNames;
    PointerVector<TextString>   unregTextStrings;

    // Information from START and END records
    string              fileVersion;    // from START record
    Oreal               fileUnit;       // from START record
    Validation          fileValidation; // from END record

    Ullong              recordsSeen;
    OasisRecord*        currRecord;             // current record being parsed
    bool                rereadCurrRecord;       // T => record was unread
    bool                allNamesParsed;         // all <name> records parsed
    bool                haveAllCellOffsets;     // all CELL records parsed
    bool                haveValidation;         // parsed validation in END
    bool                haveTableOffsets;       // parsed table-offsets
    vector<PropValue*>  propValuesToCheck;
    string              filename;
    Ullong              fileSize;
    PropName*           separatorPropName;

    /**
     *  [CELL_HIERARCHY]
     *  ADD
     *  - Cell Hierarchy
     */
    JCellHierarchy       _cellHierarchy;


public:
                ParserImpl (const char* fname, WarningHandler warner,
                            const OasisParserOptions& options);
                ~ParserImpl();
    void        validateFile();
    Validation  parseValidation();
    void        parseFile (OasisBuilder* builder);
    bool        parseCell (const char* cellName, OasisBuilder* builder);

    /** [INPUT_CELLNAMES]
     *  [CELL_HIERARCHY]
     *  CREATE
     *   - CreateLDB, BeginCell, BeginAllCell, BeginCellRecursive
     */
    bool        JCreateLDB (const std::vector<std::string>& cellnames, OasisBuilder* builder);
    bool        JBeginCell (CellName* cellName);
    void        JBeginAllCell();
    void        JBeginCellRecursive (JTreeNode* node);


ParserImpl::ParserImpl (const char* fname, WarningHandler warner,
                        const OasisParserOptions& options)
  : scanner(fname, warner),
    recReader(scanner),
    parserOptions(options),
    warnHandler(warner),
    filename(fname),
    /**
     *  [CELL_HIERARCHY]
     *  ADD
     *  - cellHierarchy
     */
    _cellHierarchy()
{
    scanner.verifyMagic();      // abort unless file begins with magic string
    builder = Null;
    currRecord = Null;
    rereadCurrRecord = false;
    allNamesParsed = false;     // set by parseAllNames()
    haveAllCellOffsets = false;
    haveTableOffsets = false;   // set by parseTableOffsets()
    haveValidation = false;     // set by parseEndRecord(), but not always
    recordsSeen = 0;
    fileSize = scanner.getFileSize();
    fileValidation.scheme = Validation::None;

    separatorPropName = makePropName("*");      // the name is arbitrary
    recReader.setValidationWanted(parserOptions.wantValidation);
}


/** [CELL_HIERARCHY]
 *  [INPUT_CELLNAMES]
 *  CREATE
 */
bool
ParserImpl::BeginCell (CellName* cellName)
{
    /** [CELL_HIERARCHY]
     *  ADD
     *   - Find or create a CellNode for the given cellName in the CellhierarchyTree.
     */
    JTreeNode* cellNode = _cellHierarchy.findOrCreateNode(cellName);
    cellNode->setVisited(true);


    Cell*  cell = cellDict.lookup(cellName, false);
    if (cell == Null  ||  ! cell->haveOffset())
        getAllCellOffsets();
    if ((cell = cellDict.lookup(cellName, false)) == Null
            ||  ! cell->haveOffset())
        return false;

    off_t  cellOffset = cell->getOffset();
    if (cellOffset == 0)
        return false;

    seekTo(cellOffset);
    OasisRecord*  orecp = readNextRecord();
    if (orecp->recID != RID_CELL_NAMED  &&  orecp->recID != RID_CELL_REF)
        abortParser("cell %s does not begin with CELL record", cellName->getName().c_str());

    parseCell(static_cast<CellRecord*>(orecp));

    return true;
}


/** [CELL_HIERARCHY]
 *  [INPUT_CELLNAMES]
 *  CREATE
 *   - 모든 노드에 대해 BeginCell 호출
 */
void
ParserImpl::JBeginAllCell()
{
    for (auto& pair : _cellHierarchy._cellTreeMap) {
        if (pair.second){
            JBeginCellRecursive(pair.second);
        }
    }
}

/** [CELL_HIERARCHY]
 *  [INPUT_CELLNAMES]
 *  CREATE
 *   - 재귀적으로 셀을 방문하여 beginCell 호출
 */
void
ParserImpl::JBeginCellRecursive(TreeNode* node)
{
    if (!node || node->getVisited()) return;

    JBeginCell(node->getCellName());
    node->setVisited(true);

    // 자식 노드에 대해 재귀적으로 BeginCell 호출
    for (JTreeNode* child : node->getChildren()) {
        JBeginCellRecursive(child);
    }
}


/** [CELL_HIERARCHY]
 *  [INPUT_CELLNAMES]
 *  CREATE
 */
bool
ParserImpl::JCreateLDB (const std::vector<std::string>& cellnames, OasisBuilder* builder)
{
    this->builder = builder;

    parseStartAndEndRecords();
    parseAllNames();
    seekTo(StartRecordOffset);
    (void) readNextRecord();

    builder->beginFile(fileVersion, fileUnit, fileValidation.scheme);

    registerAllNamesWithBuilder();
    parsePropertiesForBuilder(PC_File);

    for (const std::string& name : cellnames) {
        CellName*  cellName = cellNameDict.lookupName(name, false);
        if (cellName == Null){
            std::cerr << "File has no cell '" << name << "'" << std::endl;
            return false;
        }
        JBeginCell(cellName);
    }

    JBeginAllCell();

    builder->endFile();

    return true;
}

void
ParserImpl::parsePlacement (const CellName* parentCell,
                            const PlacementRecord* recp)
{
    // Section 22:  PLACEMENT record
    // `17' placement-info-byte [reference-number | cellname-string]
    //      [x] [y] [repetition]
    // placement-info-byte ::= CNXYRAAF
    //
    // `18' placement-info-byte [reference-number | cellname-string]
    //      [magnification] [angle] [x] [y] [repetition]
    // placement-info-byte ::= CNXYRMAF

    assert (recp->recID == RID_PLACEMENT
            ||  recp->recID == RID_PLACEMENT_TRANSFORM);
    using namespace PlacementInfoByte;

    int  infoByte = recp->infoByte;
    CellName*  cellName = getPlacementCell(infoByte & CellExplicitBit,
                                           infoByte & RefnumBit,
                                           recp->name, recp->refnum);
    // 22.10
    if (cellName == parentCell)
        abortParser("recursive reference to containing cell");

    // Check the magnification and angle.  For type-17 records there is
    // no magnification and the angle is encoded in the infobyte.

    Oreal   mag, angle;

    if (recp->recID == RID_PLACEMENT) {
        mag = 1;
        angle = GetAngle(infoByte);
    } else {
        mag   = (infoByte & MagBit) ? recp->mag : Oreal(1);
        angle = (infoByte & AngleBit) ? recp->angle : Oreal(0);
    }
    double  magValue = mag.getValue();
    if (!isfinite(magValue)  ||  magValue <= 0.0)
        abortParser("invalid magnification %.15g", magValue);

    double  angleValue = angle.getValue();
    if (!isfinite(angleValue))
        abortParser("invalid angle %.15g", angleValue);

    long  x = getPlacementX(infoByte & XBit, recp->x);
    long  y = getPlacementY(infoByte & YBit, recp->y);
    const Repetition*  rep = getRepetition(infoByte & RepBit, recp->rawrep);

    builder->beginPlacement(cellName, x, y, mag, angle, (infoByte & FlipBit),
                            rep);
    parsePropertiesForBuilder(PC_Element);
    builder->endElement();


    /** [CELL_HIERARCHY]
     *  ADD
     *   - Find or create a CellNode for the given cellName in the CellhierarchyTree.
     */
    JTreeNode* parent = _cellHierarchy.findOrCreateNode(const_cast<CellName*>(parentCell));
    JTreeNode*  child = _cellHierarchy.findOrCreateNode(cellName);
    parent->addChild(child);

}

