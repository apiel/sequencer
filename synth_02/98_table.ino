#include "Tables.h"

byte getTablesCount() { return TABLES_COUNT; }

void setTable(byte tableId) {
    kick.setTable(tables[tableId].table);
    kick.tableName = tables[tableId].tableName;
}
