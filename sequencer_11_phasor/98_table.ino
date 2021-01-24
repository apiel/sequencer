#include "tables/cos8192_int8.h"
#include "tables/sin8192_int8.h"
#include "tables/triangle_dist_cubed.h"
#include "tables/phasor.h"
#include "tables/triangle.h"
#include "tables/triangle_hermes.h"
#include "tables/triangle_dist_squared.h"
#include "tables/triangle_valve.h"
#include "tables/triangle_valve_2.h"
#include "tables/square_analog.h"
#include "tables/whitenoise8192_int8.h"
#include "tables/brownnoise8192_int8.h"
#include "tables/pinknoise8192_int8.h"
#include "tables/saw8192_int8.h"
#include "tables/saw_analog.h"
#include "tables/smoothsquare8192_int8.h"
#include "tables/waveshape_chebyshev_3rd.h"
#include "tables/waveshape1_softclip.h"
#include "tables/waveshape_sigmoid.h"
#include "tables/square_no_alias.h"

void setTable(byte phase, byte tableId) {
    if (tableId == 1) {
        phases[phase].setTable(PHASOR_DATA);
        phases[phase].tableName = "phasor";
    } else if (tableId == 2) {
        phases[phase].setTable(TRIANGLE_DATA);
        phases[phase].tableName = "triangle";
    } else if (tableId == 3) {
        phases[phase].setTable(TRIANGLE_HERMES_DATA);
        phases[phase].tableName = "triHermes";
    } else if (tableId == 4) {
        phases[phase].setTable(TRIANGLE_DIST_CUBED_DATA);
        phases[phase].tableName = "triCubed";
    } else if (tableId == 5) {
        phases[phase].setTable(TRIANGLE_DIST_SQUARED_DATA);
        phases[phase].tableName = "triSquare";
    } else if (tableId == 6) {
        phases[phase].setTable(TRIANGLE_VALVE_DATA);
        phases[phase].tableName = "triValve";
    } else if (tableId == 7) {
        phases[phase].setTable(TRIANGLE_VALVE_2_DATA);
        phases[phase].tableName = "triValve2";
    } else if (tableId == 8) {
        phases[phase].setTable(COS8192_DATA);
        phases[phase].tableName = "cos";
    } else if (tableId == 9) {
        phases[phase].setTable(SQUARE_ANALOG_DATA);
        phases[phase].tableName = "analogSqu";
    } else if (tableId == 10) {
        phases[phase].setTable(WHITENOISE8192_DATA);
        phases[phase].tableName = "noise_w";
    } else if (tableId == 11) {
        phases[phase].setTable(BROWNNOISE8192_DATA);
        phases[phase].tableName = "noise_b";
    } else if (tableId == 12) {
        phases[phase].setTable(PINKNOISE8192_DATA);
        phases[phase].tableName = "noise_p";
    } else if (tableId == 13) {
        phases[phase].setTable(SAW8192_DATA);
        phases[phase].tableName = "saw";
    } else if (tableId == 14) {
        phases[phase].setTable(SAW_ANALOG_DATA);
        phases[phase].tableName = "sawAnalog";
    } else if (tableId == 15) {
        phases[phase].setTable(SMOOTHSQUARE8192_DATA);
        phases[phase].tableName = "smoothSqu";
    } else if (tableId == 16) {
        phases[phase].setTable(WAVESHAPE_CHEBYSHEV_3RD_DATA);
        phases[phase].tableName = "chebyshev";
    } else if (tableId == 17) {
        phases[phase].setTable(WAVESHAPE1_SOFTCLIP_DATA);
        phases[phase].tableName = "waveSoft";
    } else if (tableId == 18) {
        phases[phase].setTable(WAVESHAPE_SIGMOID_DATA);
        phases[phase].tableName = "waveSig";
    } else if (tableId == 19) {
        phases[phase].setTable(SQUARE_NO_ALIAS_DATA);
        phases[phase].tableName = "noAlias";
    } else {
        phases[phase].setTable(SIN8192_DATA);
        phases[phase].tableName = "sin";
    }
}