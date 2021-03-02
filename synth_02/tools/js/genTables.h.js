const { readdirSync, writeFileSync } = require('fs');
const { parse } = require('path');

const files = readdirSync(__dirname + '/../../tables');

const tables = files.map(
    (file) => `    {${parse(file).name.toUpperCase()}_DATA, "${parse(file).name}"}`,
).join(',\n');

const content = `
#ifndef TABLES_H_
#define TABLES_H_

${files.map((file) => `#include "tables/${file}"`).join('\n')}

struct Table {
    const int8_t* table;
    const char* tableName;
};

Table tables[] = {
${tables}
};

#define TABLES_COUNT sizeof tables / sizeof tables[0]

#endif`;

writeFileSync(__dirname + '/../../Tables.h', content);

console.log(`Added ${files.length} tables.`);
