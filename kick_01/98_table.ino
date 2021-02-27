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
        kick.setTable(PHASOR_DATA);
        kick.tableName = "phasor";
    } else if (tableId == 2) {
        kick.setTable(TRIANGLE_DATA);
        kick.tableName = "triangle";
    } else if (tableId == 3) {
        kick.setTable(TRIANGLE_HERMES_DATA);
        kick.tableName = "triHermes";
    } else if (tableId == 4) {
        kick.setTable(TRIANGLE_DIST_CUBED_DATA);
        kick.tableName = "triCubed";
    } else if (tableId == 5) {
        kick.setTable(TRIANGLE_DIST_SQUARED_DATA);
        kick.tableName = "triSquare";
    } else if (tableId == 6) {
        kick.setTable(TRIANGLE_VALVE_DATA);
        kick.tableName = "triValve";
    } else if (tableId == 7) {
        kick.setTable(TRIANGLE_VALVE_2_DATA);
        kick.tableName = "triValve2";
    } else if (tableId == 8) {
        kick.setTable(COS8192_DATA);
        kick.tableName = "cos";
    } else if (tableId == 9) {
        kick.setTable(SQUARE_ANALOG_DATA);
        kick.tableName = "analogSqu";
    } else if (tableId == 10) {
        kick.setTable(WHITENOISE8192_DATA);
        kick.tableName = "noise_w";
    } else if (tableId == 11) {
        kick.setTable(BROWNNOISE8192_DATA);
        kick.tableName = "noise_b";
    } else if (tableId == 12) {
        kick.setTable(PINKNOISE8192_DATA);
        kick.tableName = "noise_p";
    } else if (tableId == 13) {
        kick.setTable(SAW8192_DATA);
        kick.tableName = "saw";
    } else if (tableId == 14) {
        kick.setTable(SAW_ANALOG_DATA);
        kick.tableName = "sawAnalog";
    } else if (tableId == 15) {
        kick.setTable(SMOOTHSQUARE8192_DATA);
        kick.tableName = "smoothSqu";
    } else if (tableId == 16) {
        kick.setTable(WAVESHAPE_CHEBYSHEV_3RD_DATA);
        kick.tableName = "chebyshev";
    } else if (tableId == 17) {
        kick.setTable(WAVESHAPE1_SOFTCLIP_DATA);
        kick.tableName = "waveSoft";
    } else if (tableId == 18) {
        kick.setTable(WAVESHAPE_SIGMOID_DATA);
        kick.tableName = "waveSig";
    } else if (tableId == 19) {
        kick.setTable(SQUARE_NO_ALIAS_DATA);
        kick.tableName = "noAlias";
    } else if (tableId == 20) {
        kick.setTable(PSY_KICK_DATA);
        kick.tableName = "psyKick";
    } else if (tableId == 21) {
        kick.setTable(PSY_KICK2_DATA);
        kick.tableName = "psyKick2";
    } else if (tableId == 22) {
        kick.setTable(PSY_KICK3_DATA);
        kick.tableName = "psyKick3";
    } else if (tableId == 23) {
        kick.setTable(KICK_DATA);
        kick.tableName = "kick";
    } else {
        kick.setTable(SIN8192_DATA);
        kick.tableName = "sin";
    }
}