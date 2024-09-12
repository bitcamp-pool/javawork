OasisCreator::OasisCreator (const char* fname,
                            const OasisCreatorOptions& options)
  : writer(fname),
    s_cell_offset(S_CELL_OFFSET),
    options(options),

    cellNameTable(new CellNameTable),
    textStringTable(new TextStringTable),
    propNameTable(new PropNameTable),
    propStringTable(new PropStringTable),
    layerNameTable(new LayerNameTable),
    xnameTable(new XNameTable),
    /**
     * [INPUT_CELLNAMES]
     */
    _currCellNameTable(new CellNameTable)   
{
    // mustCompress = true;                // default is to compress
    nowCompressing = false;

    /** [CBLOCK_ON_OFF]
     *  UPDATE
     */
    mustCompress = options.mustCompressed;

    repReuse.makeReuse();
    cellOffsetPropName = Null;
    deletePropName = false;
}


/**
  [STRICT_ON_OFF]
    - STRICT OFF 이면 Table Offset Flag = 0
    - writeNameTable()
  [INPUT_CELLNAMES]
    - currCellNameTable
 */
/*virtual*/ void
OasisCreator::beginFile (const string&  version,
                         const Oreal&  unit,
                         Validation::Scheme  valScheme)
{
    writer.beginFile(valScheme);
    writer.writeBytes(OasisMagic, OasisMagicLength);

    // Section 13:  START record
    // `1' version-string unit offset-flag [table-offsets]
    //
    // Write 1 for offset-flag because we always put the table-offsets
    // in the END record.

    beginRecord(RID_START);
    writeString(version);
    writeReal(unit);

    /**
     * [STRICT_ON_OFF] 
     */
    if (options._strict)
        writeUInt(1);
    else {
        writeUInt(0);

        if (!options._hasCellNames){
            cellNameTable->notStrict();
            writeTableInfo(cellNameTable.get());
        } else {
            _currCellNameTable->notStrict();
            writeTableInfo(currCellNameTable.get());
        }

        textStringTable->notStrict();
        propNameTable->notStrict();
        propStringTable->notStrict();
        layerNameTable->notStrict();
        xnameTable->notStrict();

        writeTableInfo(textStringTable.get());
        writeTableInfo(propNameTable.get());
        writeTableInfo(propStringTable.get());
        writeTableInfo(layerNameTable.get());
        writeTableInfo(xnameTable.get());
    }
}



/**
  [STRICT_ON_OFF]
    - STRICT OFF 이면 writeTableInfo 수행하지 않음
  [INPUT_CELLNAMES]
    - currCellNameTable
 */
/*virtual*/ void
OasisCreator::endFile()
{
    writeNameTables();

    // Section 14:  END record
    // `2' [table-offsets] padding-string validation-scheme
    //     [validation-signature]

    // Table 11 in the spec gives the order of the entries.

    beginRecord(RID_END);
    if (options._strict)
    {
        if (!options._hasCellNames)
            writeTableInfo(cellNameTable.get());
        else
            writeTableInfo(_currCellNameTable.get());

        writeTableInfo(textStringTable.get());
        writeTableInfo(propNameTable.get());
        writeTableInfo(propStringTable.get());
        writeTableInfo(layerNameTable.get());
        writeTableInfo(xnameTable.get());

    }
    // This writes the padding string and validation.
    writer.endFile();
}


void
OasisCreator::writeTableInfo (const NameTable* ntab)
{
    // For each table, the first integer is 1 if the table is strict and
    // 0 otherwise.  The second integer is the file offset of the table;
    // 0 if the table is absent.

    writeUInt(ntab->getStrict());
    writeUInt64(ntab->getOffset());
}

/** [CREATOR::INPUT_CELLNAME]
 *  UPDATE
 *   - 입력된 CELL NAME과 참조 CELL NAME을 저장하는 테이블 업데이트
 */
/*virtual*/ void
OasisCreator::beginCell (CellName* cellName)
{
    // Save the cell's offset for use when writing the cellName's
    // S_CELL_OFFSET property.
    cellOffsets[cellName] = writer.currFileOffset();

    // If the cellName has been registered, use the refnum form of the
    // CELL record.  Otherwise use the name form and mark the table as
    // being non-strict.

    /* start ************************* Original Code *************************
    Ulong  refnum;
    if (cellNameTable->getRefnum(cellName, &refnum)) {
        beginRecord(RID_CELL_REF);
        writeUInt(refnum);
    } else {
        beginRecord(RID_CELL_NAMED);
        writeString(cellName->getName());
        cellNameTable->notStrict();
    }
    ********************************************************************end */

    /** [INPUT_CELLNAMES]
     *  UPDATE * *************************************************************/

    Ulong refnum;
    bool nameRegistered = false;
    if (options._hasCellNames) {
        nameRegistered = _currCellNameTable->getRefnum(cellName, &refnum);
        if (!nameRegistered) {
            _currCellNameTable->registerName(cellName);
            nameRegistered = _currCellNameTable->getRefnum(cellName, &refnum);
        }
    } else {
        nameRegistered = cellNameTable->getRefnum(cellName, &refnum);
    }

    if (nameRegistered){
        beginRecord(RID_CELL_REF);
        writeUInt(refnum);
    } else {
        beginRecord(RID_CELL_NAMED);
        writeString(cellName->getName());
        if (options._hasCellNames)
            _currCellNameTable->notStrict();
        else
            cellNameTable->notStrict();
    }

    /** **********************************************************************/

    // Begin compression if requested in the constructor and reset all
    // modal variables to the uninitialized or default state.

    beginBlock();
    modvars.reset();            // 10.1
}

/** [INPUT_CELLNAMES]
 *  UPDATE
 *   - currCellNameTable 에서 참조번호 처리
 */
/*virtual*/ void
OasisCreator::beginPlacement (CellName*  cellName,
                              long x, long y,
                              const Oreal&  mag,
                              const Oreal&  angle,
                              bool  flip,
                              const Repetition*  rep)
{
    // Section 22:  PLACEMENT record
    // `17' placement-info-byte [reference-number | cellname-string]
    //      [x] [y] [repetition]
    // placement-info-byte ::= CNXYRAAF
    //
    // `18' placement-info-byte [reference-number | cellname-string]
    //      [magnification] [angle] [x] [y] [repetition]
    // placement-info-byte ::= CNXYRMAF

    using namespace PlacementInfoByte;

    int         infoByte = 0;
    RecordID    recID = RID_PLACEMENT;

    // If magnification is 1 and angle is one of (0,90,180,270), use
    // record type 17 (RID_PLACEMENT) and set the AA bits.  Otherwise use
    // record type 18 (RID_PLACEMENT_TRANSFORM) and set the M and A bits.

    int  angleBits = 0;         // AA bits for type 17 or A bit for type 18
    double  angleValue = angle.getValue();
    if (mag.getValue() == 1.0) {
        if (angleValue == 0.0)         angleBits = AngleZero;
        else if (angleValue == 90.0)   angleBits = Angle90;
        else if (angleValue == 180.0)  angleBits = Angle180;
        else if (angleValue == 270.0)  angleBits = Angle270;
        else {
            recID = RID_PLACEMENT_TRANSFORM;
            angleBits = AngleBit;
        }
    } else {
        recID = RID_PLACEMENT_TRANSFORM;
        infoByte |= MagBit;
        if (angleValue != 0.0)
            angleBits = AngleBit;
    }
    infoByte |= angleBits;

    // Set the C and N bits and update placement-cell.
    // C = 1 => a cell name or reference is present.  C = 0 => use the same
    // cell as in the modal state.  If C = 1, then N = 0 means a name
    // appears and N = 1 means a reference-number appears.

    // XXX: Because the cellName is stored in modvars, all cellNames
    // passed in must be permanent.

    /* start *************Original Code************************
    Ulong  refnum;
    setPlacementCell (&infoByte, CellExplicitBit, cellName);
    if (infoByte & CellExplicitBit) {
        if (cellNameTable->getRefnum(cellName, &refnum))
            infoByte |= RefnumBit;
        else
            cellNameTable->notStrict();
    }
    *******************************************************end*/

/** [INPUT_CELLNAMES]
 *  UPDATE *******************************************************************/

    Ulong refnum;
    setPlacementCell (&infoByte, CellExplicitBit, cellName);
    bool nameRegistered = false;

    if (infoByte & CellExplicitBit) {
        if (!options._hasCellNames){
            if (cellNameTable->getRefnum(cellName, &refnum))
                infoByte |= RefnumBit;
            else
                cellNameTable->notStrict();
        } else {
            nameRegistered = _currCellNameTable->getRefnum(cellName, &refnum);
            if (!nameRegistered)
                _currCellNameTable->registerName(cellName);
            if (_currCellNameTable->getRefnum(cellName, &refnum))
                infoByte |= RefnumBit;
            else
                _currCellNameTable->notStrict();
        }
    }
    /** ******************************************************************** */

    // setPlacementX() and setPlacementY() relativize x and y if they
    // must be written and xy-mode is relative.

    setPlacementX (&infoByte, XBit, &x);
    setPlacementY (&infoByte, YBit, &y);
    setRepetition (&infoByte, RepBit, &rep);
    if (flip)
        infoByte |= FlipBit;

    // Write the fields.

    beginRecord(recID);
    writeInfoByte(infoByte);
    if (infoByte & CellExplicitBit) {
        if (infoByte & RefnumBit)
            writeUInt(refnum);
        else
            writeString(cellName->getName());
    }
    if (recID == RID_PLACEMENT_TRANSFORM) {
        if (infoByte & MagBit)    writeReal(mag);
        if (infoByte & AngleBit)  writeReal(angle);
    }
    if (infoByte & XBit)    writeSInt(x);
    if (infoByte & YBit)    writeSInt(y);
    if (infoByte & RepBit)  writeRepetition(rep);
}

/** [INPUT_CELLNAMES]
 *  UPDATE
 *   - currCellNameTalbe
 */
void
OasisCreator::writeNameTables()
{
    // If immediateNames is true, each name record was written
    // immediately on registration.  There are no name tables to write.

    if (options.immediateNames)
        return;

    // Locate or create a PropName for S_CELL_OFFSET.  We shall need it
    // when writing CELLNAME records, but only if some cells were written.

    if (! cellOffsets.empty())
        makeCellOffsetPropName();

    if (! propNameTable->empty())    writePropNameTable();
    if (! propStringTable->empty())  writePropStringTable();

    // [INPUT_CELLNAMES]
    if (!options._hasCellNames){    // 입력된 셀 이름들이 없을 경우 
        if (! cellNameTable->empty())     writeCellNameTable();
    } else {
        if (! _currCellNameTable->empty()) writeCellNameTable();
    }

    if (! textStringTable->empty())  writeTextStringTable();
    if (! layerNameTable->empty())   writeLayerNameTable();
    if (! xnameTable->empty())       writeXNameTable();
}


void
OasisCreator::writeCellNameTable()
{
   /** [INPUT_CELLNAMES]
    *  UPDATE
    *   - currCellNameTalbe
    */
    if (options._hasCellNames)
        _currCellNameTable->setOffset(writer.currFileOffset());
    else
        cellNameTable->setOffset(writer.currFileOffset());

    beginBlock();

    CellNameTable::const_iterator  iter;
    CellNameTable::const_iterator  end;

    if (options._hasCellNames){
        iter = _currCellNameTable->begin();
        end  = _currCellNameTable->end();
    } else {
        iter = cellNameTable->begin();
        end  = cellNameTable->end();
    }

    for ( ;  iter != end;  ++iter)
        writeCellName(*iter);

    endBlock();
}





























