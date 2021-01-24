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

void setTable(byte drum, byte tableId) {
    if (tableId == 1) {
        phases[drum].setTable(PHASOR_DATA);
        phases[drum].name = "phasor";
    } else if (tableId == 2) {
        phases[drum].setTable(TRIANGLE_DATA);
        phases[drum].name = "triangle";
    } else if (tableId == 3) {
        phases[drum].setTable(TRIANGLE_HERMES_DATA);
        phases[drum].name = "triHermes";
    } else if (tableId == 4) {
        phases[drum].setTable(TRIANGLE_DIST_CUBED_DATA);
        phases[drum].name = "triCubed";
    } else if (tableId == 5) {
        phases[drum].setTable(TRIANGLE_DIST_SQUARED_DATA);
        phases[drum].name = "triSquare";
    } else if (tableId == 6) {
        phases[drum].setTable(TRIANGLE_VALVE_DATA);
        phases[drum].name = "triValve";
    } else if (tableId == 7) {
        phases[drum].setTable(TRIANGLE_VALVE_2_DATA);
        phases[drum].name = "triValve2";
    } else if (tableId == 8) {
        phases[drum].setTable(COS8192_DATA);
        phases[drum].name = "cos";
    } else if (tableId == 9) {
        phases[drum].setTable(SQUARE_ANALOG_DATA);
        phases[drum].name = "analogSqu";
    } else if (tableId == 10) {
        phases[drum].setTable(WHITENOISE8192_DATA);
        phases[drum].name = "noise_w";
    } else if (tableId == 11) {
        phases[drum].setTable(BROWNNOISE8192_DATA);
        phases[drum].name = "noise_b";
    } else if (tableId == 12) {
        phases[drum].setTable(PINKNOISE8192_DATA);
        phases[drum].name = "noise_p";
    } else if (tableId == 13) {
        phases[drum].setTable(SAW8192_DATA);
        phases[drum].name = "saw";
    } else if (tableId == 14) {
        phases[drum].setTable(SAW_ANALOG_DATA);
        phases[drum].name = "sawAnalog";
    } else if (tableId == 15) {
        phases[drum].setTable(SMOOTHSQUARE8192_DATA);
        phases[drum].name = "smoothSqu";
    } else if (tableId == 16) {
        phases[drum].setTable(WAVESHAPE_CHEBYSHEV_3RD_DATA);
        phases[drum].name = "chebyshev";
    } else if (tableId == 17) {
        phases[drum].setTable(WAVESHAPE1_SOFTCLIP_DATA);
        phases[drum].name = "waveSoft";
    } else if (tableId == 18) {
        phases[drum].setTable(WAVESHAPE_SIGMOID_DATA);
        phases[drum].name = "waveSig";
    } else if (tableId == 19) {
        phases[drum].setTable(SQUARE_NO_ALIAS_DATA);
        phases[drum].name = "noAlias";
    } else {
        phases[drum].setTable(SIN8192_DATA);
        phases[drum].name = "sin";
    }
}