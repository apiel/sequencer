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

void setTable(byte phaseIdx, byte tableId) {
    if (tableId == 1) {
        phases[phaseIdx].setTable(PHASOR_DATA);
        phases[phaseIdx].tableName = "phasor";
    } else if (tableId == 2) {
        phases[phaseIdx].setTable(TRIANGLE_DATA);
        phases[phaseIdx].tableName = "triangle";
    } else if (tableId == 3) {
        phases[phaseIdx].setTable(TRIANGLE_HERMES_DATA);
        phases[phaseIdx].tableName = "triHermes";
    } else if (tableId == 4) {
        phases[phaseIdx].setTable(TRIANGLE_DIST_CUBED_DATA);
        phases[phaseIdx].tableName = "triCubed";
    } else if (tableId == 5) {
        phases[phaseIdx].setTable(TRIANGLE_DIST_SQUARED_DATA);
        phases[phaseIdx].tableName = "triSquare";
    } else if (tableId == 6) {
        phases[phaseIdx].setTable(TRIANGLE_VALVE_DATA);
        phases[phaseIdx].tableName = "triValve";
    } else if (tableId == 7) {
        phases[phaseIdx].setTable(TRIANGLE_VALVE_2_DATA);
        phases[phaseIdx].tableName = "triValve2";
    } else if (tableId == 8) {
        phases[phaseIdx].setTable(COS8192_DATA);
        phases[phaseIdx].tableName = "cos";
    } else if (tableId == 9) {
        phases[phaseIdx].setTable(SQUARE_ANALOG_DATA);
        phases[phaseIdx].tableName = "analogSqu";
    } else if (tableId == 10) {
        phases[phaseIdx].setTable(WHITENOISE8192_DATA);
        phases[phaseIdx].tableName = "noise_w";
    } else if (tableId == 11) {
        phases[phaseIdx].setTable(BROWNNOISE8192_DATA);
        phases[phaseIdx].tableName = "noise_b";
    } else if (tableId == 12) {
        phases[phaseIdx].setTable(PINKNOISE8192_DATA);
        phases[phaseIdx].tableName = "noise_p";
    } else if (tableId == 13) {
        phases[phaseIdx].setTable(SAW8192_DATA);
        phases[phaseIdx].tableName = "saw";
    } else if (tableId == 14) {
        phases[phaseIdx].setTable(SAW_ANALOG_DATA);
        phases[phaseIdx].tableName = "sawAnalog";
    } else if (tableId == 15) {
        phases[phaseIdx].setTable(SMOOTHSQUARE8192_DATA);
        phases[phaseIdx].tableName = "smoothSqu";
    } else if (tableId == 16) {
        phases[phaseIdx].setTable(WAVESHAPE_CHEBYSHEV_3RD_DATA);
        phases[phaseIdx].tableName = "chebyshev";
    } else if (tableId == 17) {
        phases[phaseIdx].setTable(WAVESHAPE1_SOFTCLIP_DATA);
        phases[phaseIdx].tableName = "waveSoft";
    } else if (tableId == 18) {
        phases[phaseIdx].setTable(WAVESHAPE_SIGMOID_DATA);
        phases[phaseIdx].tableName = "waveSig";
    } else if (tableId == 19) {
        phases[phaseIdx].setTable(SQUARE_NO_ALIAS_DATA);
        phases[phaseIdx].tableName = "noAlias";
    } else if (tableId == 20) {
        phases[phaseIdx].setTable(PSY_KICK_DATA);
        phases[phaseIdx].tableName = "psyKick";
    } else if (tableId == 21) {
        phases[phaseIdx].setTable(PSY_KICK2_DATA);
        phases[phaseIdx].tableName = "psyKick2";
    } else if (tableId == 22) {
        phases[phaseIdx].setTable(PSY_KICK3_DATA);
        phases[phaseIdx].tableName = "psyKick3";
    } else if (tableId == 23) {
        phases[phaseIdx].setTable(KICK_DATA);
        phases[phaseIdx].tableName = "kick";
    } else {
        phases[phaseIdx].setTable(SIN8192_DATA);
        phases[phaseIdx].tableName = "sin";
    }
}