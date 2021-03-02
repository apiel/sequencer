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

void setTable(byte toneIdx, byte tableId) {
    if (tableId == 1) {
        tones[toneIdx].setTable(PHASOR_DATA);
        tones[toneIdx].tableName = "phasor";
    } else if (tableId == 2) {
        tones[toneIdx].setTable(TRIANGLE_DATA);
        tones[toneIdx].tableName = "triangle";
    } else if (tableId == 3) {
        tones[toneIdx].setTable(TRIANGLE_HERMES_DATA);
        tones[toneIdx].tableName = "triHermes";
    } else if (tableId == 4) {
        tones[toneIdx].setTable(TRIANGLE_DIST_CUBED_DATA);
        tones[toneIdx].tableName = "triCubed";
    } else if (tableId == 5) {
        tones[toneIdx].setTable(TRIANGLE_DIST_SQUARED_DATA);
        tones[toneIdx].tableName = "triSquare";
    } else if (tableId == 6) {
        tones[toneIdx].setTable(TRIANGLE_VALVE_DATA);
        tones[toneIdx].tableName = "triValve";
    } else if (tableId == 7) {
        tones[toneIdx].setTable(TRIANGLE_VALVE_2_DATA);
        tones[toneIdx].tableName = "triValve2";
    } else if (tableId == 8) {
        tones[toneIdx].setTable(COS8192_DATA);
        tones[toneIdx].tableName = "cos";
    } else if (tableId == 9) {
        tones[toneIdx].setTable(SQUARE_ANALOG_DATA);
        tones[toneIdx].tableName = "analogSqu";
    } else if (tableId == 10) {
        tones[toneIdx].setTable(WHITENOISE8192_DATA);
        tones[toneIdx].tableName = "noise_w";
    } else if (tableId == 11) {
        tones[toneIdx].setTable(BROWNNOISE8192_DATA);
        tones[toneIdx].tableName = "noise_b";
    } else if (tableId == 12) {
        tones[toneIdx].setTable(PINKNOISE8192_DATA);
        tones[toneIdx].tableName = "noise_p";
    } else if (tableId == 13) {
        tones[toneIdx].setTable(SAW8192_DATA);
        tones[toneIdx].tableName = "saw";
    } else if (tableId == 14) {
        tones[toneIdx].setTable(SAW_ANALOG_DATA);
        tones[toneIdx].tableName = "sawAnalog";
    } else if (tableId == 15) {
        tones[toneIdx].setTable(SMOOTHSQUARE8192_DATA);
        tones[toneIdx].tableName = "smoothSqu";
    } else if (tableId == 16) {
        tones[toneIdx].setTable(WAVESHAPE_CHEBYSHEV_3RD_DATA);
        tones[toneIdx].tableName = "chebyshev";
    } else if (tableId == 17) {
        tones[toneIdx].setTable(WAVESHAPE1_SOFTCLIP_DATA);
        tones[toneIdx].tableName = "waveSoft";
    } else if (tableId == 18) {
        tones[toneIdx].setTable(WAVESHAPE_SIGMOID_DATA);
        tones[toneIdx].tableName = "waveSig";
    } else if (tableId == 19) {
        tones[toneIdx].setTable(SQUARE_NO_ALIAS_DATA);
        tones[toneIdx].tableName = "noAlias";
    } else if (tableId == 20) {
        tones[toneIdx].setTable(PSY_KICK_DATA);
        tones[toneIdx].tableName = "psyKick";
    } else if (tableId == 21) {
        tones[toneIdx].setTable(PSY_KICK2_DATA);
        tones[toneIdx].tableName = "psyKick2";
    } else if (tableId == 22) {
        tones[toneIdx].setTable(PSY_KICK3_DATA);
        tones[toneIdx].tableName = "psyKick3";
    } else if (tableId == 23) {
        tones[toneIdx].setTable(KICK_DATA);
        tones[toneIdx].tableName = "kick";
    } else {
        tones[toneIdx].setTable(SIN8192_DATA);
        tones[toneIdx].tableName = "sin";
    }
}