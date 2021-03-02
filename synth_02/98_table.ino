#include "Tables.h"

byte getTablesCount() { return TABLES_COUNT; }

void setTable(byte tableId) {
    tone.setTable(tables[tableId].table);
    tone.tableName = tables[tableId].tableName;
}
