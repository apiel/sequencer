#ifndef TABLES_H_
#define TABLES_H_

#include "tables/brownnoise8192_int8.h"
#include "tables/cos8192_int8.h"
#include "tables/dirtkik.h"
#include "tables/guitar2.h"
#include "tables/guitar3.h"
#include "tables/guitar5.h"
#include "tables/guitar7.h"
#include "tables/hihat2.h"
#include "tables/kick.h"
#include "tables/kick001.h"
#include "tables/kick002.h"
#include "tables/kick003.h"
#include "tables/kick004.h"
#include "tables/kick005.h"
#include "tables/kick006.h"
#include "tables/phasor.h"
#include "tables/pinknoise8192_int8.h"
#include "tables/psy_kick.h"
#include "tables/psy_kick2.h"
#include "tables/psy_kick3.h"
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
#include "tables/wawaw.h"
#include "tables/whitenoise8192_int8.h"

struct Table {
    const int8_t* table;
    const char* tableName;
};

Table tables[] = {
    {SIN8192_DATA, "sin"},
    {PHASOR_DATA, "phasor"},
    {TRIANGLE_DATA, "triangle"},
    {TRIANGLE_HERMES_DATA, "triHermes"},
    {TRIANGLE_DIST_CUBED_DATA, "triCubed"},
    {TRIANGLE_DIST_SQUARED_DATA, "triSquare"},
    {TRIANGLE_VALVE_DATA, "triValve"},
    {TRIANGLE_VALVE_2_DATA, "triValve2"},
    {COS8192_DATA, "cos"},
    {SQUARE_ANALOG_DATA, "analogSqu"},
    {WHITENOISE8192_DATA, "noise_w"},
    {BROWNNOISE8192_DATA, "noise_b"},
    {PINKNOISE8192_DATA, "noise_p"},
    {SAW8192_DATA, "saw"},
    {SAW_ANALOG_DATA, "sawAnalog"},
    {SMOOTHSQUARE8192_DATA, "smoothSqu"},
    {WAVESHAPE_CHEBYSHEV_3RD_DATA, "chebyshev"},
    {WAVESHAPE1_SOFTCLIP_DATA, "waveSoft"},
    {WAVESHAPE_SIGMOID_DATA, "waveSig"},
    {SQUARE_NO_ALIAS_DATA, "noAlias"},
    {PSY_KICK_DATA, "psyKick"},
    {PSY_KICK2_DATA, "psyKick2"},
    {PSY_KICK3_DATA, "psyKick3"},
    {KICK_DATA, "kick000"},
    {KICK001_DATA, "kick001"},
    {KICK002_DATA, "kick002"},
    {KICK003_DATA, "kick003"},
    {KICK004_DATA, "kick004"},
    {KICK005_DATA, "kick005"},
    {KICK006_DATA, "kick006"},
    {GUITAR2_DATA, "guitar2"},
    {GUITAR3_DATA, "guitar3"},
    {GUITAR5_DATA, "guitar5"},
    {GUITAR7_DATA, "guitar7"},
    {DIRTKIK_DATA, "dirtkik"},
    {HIHAT2_DATA, "hihat2"},
    {WAWAW_DATA, "wawaw"}
};

#define TABLES_COUNT sizeof tables / sizeof tables[0]

#endif
