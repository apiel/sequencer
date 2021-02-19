#include "tables/brownnoise8192_int8.h"
#include "tables/cos8192_int8.h"
#include "tables/phasor.h"
#include "tables/pinknoise8192_int8.h"
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
#include "tables/psy_kick.h"
// we could remove one of the kick
#include "tables/psy_kick2.h"
#include "tables/psy_kick3.h"
#include "tables/kick.h"

#define TABLES_COUNT 24

byte getTablesCount() {
    return TABLES_COUNT;
}

void setTable(byte tableId) {
    if (tableId == 1) {
        phase.setTable(PHASOR_DATA);
        phase.tableName = "phasor";
    } else if (tableId == 2) {
        phase.setTable(TRIANGLE_DATA);
        phase.tableName = "triangle";
    } else if (tableId == 3) {
        phase.setTable(TRIANGLE_HERMES_DATA);
        phase.tableName = "triHermes";
    } else if (tableId == 4) {
        phase.setTable(TRIANGLE_DIST_CUBED_DATA);
        phase.tableName = "triCubed";
    } else if (tableId == 5) {
        phase.setTable(TRIANGLE_DIST_SQUARED_DATA);
        phase.tableName = "triSquare";
    } else if (tableId == 6) {
        phase.setTable(TRIANGLE_VALVE_DATA);
        phase.tableName = "triValve";
    } else if (tableId == 7) {
        phase.setTable(TRIANGLE_VALVE_2_DATA);
        phase.tableName = "triValve2";
    } else if (tableId == 8) {
        phase.setTable(COS8192_DATA);
        phase.tableName = "cos";
    } else if (tableId == 9) {
        phase.setTable(SQUARE_ANALOG_DATA);
        phase.tableName = "analogSqu";
    } else if (tableId == 10) {
        phase.setTable(WHITENOISE8192_DATA);
        phase.tableName = "noise_w";
    } else if (tableId == 11) {
        phase.setTable(BROWNNOISE8192_DATA);
        phase.tableName = "noise_b";
    } else if (tableId == 12) {
        phase.setTable(PINKNOISE8192_DATA);
        phase.tableName = "noise_p";
    } else if (tableId == 13) {
        phase.setTable(SAW8192_DATA);
        phase.tableName = "saw";
    } else if (tableId == 14) {
        phase.setTable(SAW_ANALOG_DATA);
        phase.tableName = "sawAnalog";
    } else if (tableId == 15) {
        phase.setTable(SMOOTHSQUARE8192_DATA);
        phase.tableName = "smoothSqu";
    } else if (tableId == 16) {
        phase.setTable(WAVESHAPE_CHEBYSHEV_3RD_DATA);
        phase.tableName = "chebyshev";
    } else if (tableId == 17) {
        phase.setTable(WAVESHAPE1_SOFTCLIP_DATA);
        phase.tableName = "waveSoft";
    } else if (tableId == 18) {
        phase.setTable(WAVESHAPE_SIGMOID_DATA);
        phase.tableName = "waveSig";
    } else if (tableId == 19) {
        phase.setTable(SQUARE_NO_ALIAS_DATA);
        phase.tableName = "noAlias";
    } else if (tableId == 20) {
        phase.setTable(PSY_KICK_DATA);
        phase.tableName = "psyKick";
    } else if (tableId == 21) {
        phase.setTable(PSY_KICK2_DATA);
        phase.tableName = "psyKick2";
    } else if (tableId == 22) {
        phase.setTable(PSY_KICK3_DATA);
        phase.tableName = "psyKick3";
    } else if (tableId == 23) {
        phase.setTable(KICK_DATA);
        phase.tableName = "kick";
    } else {
        phase.setTable(SIN8192_DATA);
        phase.tableName = "sin";
    }
}