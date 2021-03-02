#include "Tables.h"

byte getTablesCount() { return TABLES_COUNT; }

void setTable(Tone * ptrTone, byte tableId) {
    ptrTone->setTable(tables[tableId].table);
    ptrTone->tableName = tables[tableId].tableName;
}
