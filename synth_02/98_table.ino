#include "Tables.h"

byte getTablesCount() { return TABLES_COUNT; }

void setTable(Tone* ptrTone, byte tableId) {
    if (tableId < TABLES_COUNT) {
        ptrTone->tableId = tableId;
        ptrTone->setTable(tables[tableId].table);
        ptrTone->tableName = tables[tableId].tableName;
    }
}
