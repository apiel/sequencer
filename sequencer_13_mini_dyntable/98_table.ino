#include "tables/brownnoise8192_int8.h"
#include "tables/cos8192_int8.h"
#include "tables/phasor.h"
#include "tables/pinknoise8192_int8.h"
#include "tables/psy_kick.h"
#include "tables/saw8192_int8.h"
#include "tables/saw_analog.h"
#include "tables/sin8192_int8.h"
#include "tables/smoothsquare8192_int8.h"
#include "tables/square_analog.h"
#include "tables/square_no_alias.h"
#include "tables/triangle.h"
#include "tables/triangle_dist_cubed.h"
#include "tables/triangle_dist_squared.h"
#include "tables/triangle_hermes.h"
#include "tables/triangle_valve.h"
#include "tables/triangle_valve_2.h"
#include "tables/waveshape1_softclip.h"
#include "tables/waveshape_chebyshev_3rd.h"
#include "tables/waveshape_sigmoid.h"
#include "tables/whitenoise8192_int8.h"
// we could remove one of the kick
#include "tables/kick.h"
#include "tables/psy_kick2.h"
#include "tables/psy_kick3.h"

// #define PI 3.141592653589793
#define TABLES_COUNT 29

int8_t dynTables[6][MAX_NUM_CELLS];

byte getTablesCount() { return TABLES_COUNT; }

void yoyoyo(unsigned int x, int8_t y) {
    Serial.print("yoyoyo ");
    Serial.print(x);
    Serial.print(" ");
    Serial.println(y);
    dynTables[0][x] = y;
}

void setTable(byte tableId) {
    if (tableId == 0) {
        phase.tableName = "dynTabl0";
        unsigned int x = 0;
        for (; x < 10; x++) {
            dynTables[tableId][x] = 127 - ((int)(x * x * 0.1) % 255);
        }
        for (; x < 50; x++) {
            dynTables[tableId][x] = 127 - ((int)(1 + x) % 255);
        }
        for (; x < 40; x++) {
            dynTables[tableId][x] = 127 - ((int)(80 + (int8_t)(1 + x * 3)) % 255);
        }
        for (; x < 470; x++) {
            dynTables[tableId][x] = 127 - ((int)(x * x * 0.5) % 255);
        }
        for (; x < 600; x++) {
            dynTables[tableId][x] = 127 - ((int)(x * x * 0.1) % 255);
        }
        for (; x < 6144; x++) {
            dynTables[tableId][x] = -(int8_t)(x * 0.1);
        }
        for (; x < 7168; x++) {
            dynTables[tableId][x] = 127 - (int8_t)(1 + x * 0.1);
        }
        for (; x < 8192; x++) {
            dynTables[tableId][x] = 127 - (int8_t)(1 + x * 0.1);
        }
        phase.setTable(dynTables[tableId]);

    } else if (tableId == 1) {
        phase.tableName = "dynTabl1";
        for (unsigned int x = 0; x < MAX_NUM_CELLS; x++) {
            dynTables[tableId][x] = cos(x) * 100;

            // dynTables[tableId][x] = sin(tan(x)) * 100;
            // dynTables[tableId][x] = cos(x) * 100;
            // dynTables[tableId][x] = (cos(2*PI*x-PI)+1)/2 * 100;
            // dynTables[tableId][x] = (sin(PI / (x + 1))) * 1000;
            // dynTables[tableId][x] = (tan(PI / (x + 1))) * 1000;
            // dynTables[tableId][x] = (tan(PI / (x + 1))) + sin(x) * 1000;
            // dynTables[tableId][x] =
            //     5 + 3 * cos(x) + 2 * sin(2 * x) - 5 * cos(4 * x);
            // dynTables[tableId][x] = sin(2 * PI * x) * 127;

            // if (x < MAX_NUM_CELLS/2) {
            //     dynTables[tableId][x] = sin(x) * 100;
            // } else {
            //     dynTables[tableId][x] = cos(x) * 100;
            // }
        }
        phase.setTable(dynTables[tableId]);
    } else if (tableId == 2) {
        phase.tableName = "dynTabl2";
        for (unsigned int x = 0; x < MAX_NUM_CELLS; x++) {
            dynTables[tableId][x] = sin(x) * 100;
        }
        phase.setTable(dynTables[tableId]);
    } else if (tableId == 3) {
        phase.tableName = "dynTabl3";
        for (unsigned int x = 0; x < MAX_NUM_CELLS; x++) {
            dynTables[tableId][x] = (tan(PI / (x + 1))) * 1000;
        }
        phase.setTable(dynTables[tableId]);
    } else if (tableId == 4) {
        phase.tableName = "dynTabl4";
        for (unsigned int x = 0; x < MAX_NUM_CELLS; x++) {
            dynTables[tableId][x] = (sin(PI / (x + 1))) * 1000;
        }
        phase.setTable(dynTables[tableId]);
    } else if (tableId == 5) {
        phase.tableName = "dynTabl5";
        for (unsigned int x = 0; x < MAX_NUM_CELLS; x++) {
            dynTables[tableId][x] = (cos(2 * PI * x - PI) + 1) / 2 * 100;
        }
        phase.setTable(dynTables[tableId]);
    } else if (tableId == 6) {
        phase.setTable(PHASOR_DATA);
        phase.tableName = "phasor";
    } else if (tableId == 7) {
        phase.setTable(TRIANGLE_DATA);
        phase.tableName = "triangle";
    } else if (tableId == 8) {
        phase.setTable(TRIANGLE_HERMES_DATA);
        phase.tableName = "triHermes";
    } else if (tableId == 9) {
        phase.setTable(TRIANGLE_DIST_CUBED_DATA);
        phase.tableName = "triCubed";
    } else if (tableId == 10) {
        phase.setTable(TRIANGLE_DIST_SQUARED_DATA);
        phase.tableName = "triSquare";
    } else if (tableId == 11) {
        phase.setTable(TRIANGLE_VALVE_DATA);
        phase.tableName = "triValve";
    } else if (tableId == 12) {
        phase.setTable(TRIANGLE_VALVE_2_DATA);
        phase.tableName = "triValve2";
    } else if (tableId == 13) {
        phase.setTable(COS8192_DATA);
        phase.tableName = "cos";
    } else if (tableId == 14) {
        phase.setTable(SQUARE_ANALOG_DATA);
        phase.tableName = "analogSqu";
    } else if (tableId == 15) {
        phase.setTable(WHITENOISE8192_DATA);
        phase.tableName = "noise_w";
    } else if (tableId == 16) {
        phase.setTable(BROWNNOISE8192_DATA);
        phase.tableName = "noise_b";
    } else if (tableId == 17) {
        phase.setTable(PINKNOISE8192_DATA);
        phase.tableName = "noise_p";
    } else if (tableId == 18) {
        phase.setTable(SAW8192_DATA);
        phase.tableName = "saw";
    } else if (tableId == 19) {
        phase.setTable(SAW_ANALOG_DATA);
        phase.tableName = "sawAnalog";
    } else if (tableId == 20) {
        phase.setTable(SMOOTHSQUARE8192_DATA);
        phase.tableName = "smoothSqu";
    } else if (tableId == 21) {
        phase.setTable(WAVESHAPE_CHEBYSHEV_3RD_DATA);
        phase.tableName = "chebyshev";
    } else if (tableId == 22) {
        phase.setTable(WAVESHAPE1_SOFTCLIP_DATA);
        phase.tableName = "waveSoft";
    } else if (tableId == 23) {
        phase.setTable(WAVESHAPE_SIGMOID_DATA);
        phase.tableName = "waveSig";
    } else if (tableId == 24) {
        phase.setTable(SQUARE_NO_ALIAS_DATA);
        phase.tableName = "noAlias";
    } else if (tableId == 25) {
        phase.setTable(PSY_KICK_DATA);
        phase.tableName = "psyKick";
    } else if (tableId == 26) {
        phase.setTable(PSY_KICK2_DATA);
        phase.tableName = "psyKick2";
    } else if (tableId == 27) {
        phase.setTable(PSY_KICK3_DATA);
        phase.tableName = "psyKick3";
    } else if (tableId == 28) {
        phase.setTable(KICK_DATA);
        phase.tableName = "kick";
    } else {
        phase.setTable(SIN8192_DATA);
        phase.tableName = "sin";
    }
}