
#ifndef TABLES_H_
#define TABLES_H_

#include "tables/analogSqu.h"
#include "tables/chebyshev.h"
#include "tables/chum.h"
#include "tables/cos.h"
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
#include "tables/noAlias.h"
#include "tables/noise_b.h"
#include "tables/noise_p.h"
#include "tables/noise_s.h"
#include "tables/noise_w.h"
#include "tables/phasor.h"
#include "tables/psy_kick.h"
#include "tables/psy_kick2.h"
#include "tables/psy_kick3.h"
#include "tables/saw.h"
#include "tables/sawAnalog.h"
#include "tables/sin.h"
#include "tables/smoothSqu.h"
#include "tables/triCubed.h"
#include "tables/triHermes.h"
#include "tables/triSquare.h"
#include "tables/triValve.h"
#include "tables/triValve2.h"
#include "tables/triangle.h"
#include "tables/waveSig.h"
#include "tables/waveSoft.h"
#include "tables/waveTan.h"
#include "tables/wawaw.h"

struct Table {
    const int8_t* table;
    const char* tableName;
};

Table tables[] = {
    {ANALOGSQU_DATA, "analogSqu"},
    {CHEBYSHEV_DATA, "chebyshev"},
    {CHUM_DATA, "chum"},
    {COS_DATA, "cos"},
    {DIRTKIK_DATA, "dirtkik"},
    {GUITAR2_DATA, "guitar2"},
    {GUITAR3_DATA, "guitar3"},
    {GUITAR5_DATA, "guitar5"},
    {GUITAR7_DATA, "guitar7"},
    {HIHAT2_DATA, "hihat2"},
    {KICK_DATA, "kick"},
    {KICK001_DATA, "kick001"},
    {KICK002_DATA, "kick002"},
    {KICK003_DATA, "kick003"},
    {KICK004_DATA, "kick004"},
    {KICK005_DATA, "kick005"},
    {KICK006_DATA, "kick006"},
    {NOALIAS_DATA, "noAlias"},
    {NOISE_B_DATA, "noise_b"},
    {NOISE_P_DATA, "noise_p"},
    {NOISE_S_DATA, "noise_s"},
    {NOISE_W_DATA, "noise_w"},
    {PHASOR_DATA, "phasor"},
    {PSY_KICK_DATA, "psy_kick"},
    {PSY_KICK2_DATA, "psy_kick2"},
    {PSY_KICK3_DATA, "psy_kick3"},
    {SAW_DATA, "saw"},
    {SAWANALOG_DATA, "sawAnalog"},
    {SIN_DATA, "sin"},
    {SMOOTHSQU_DATA, "smoothSqu"},
    {TRICUBED_DATA, "triCubed"},
    {TRIHERMES_DATA, "triHermes"},
    {TRISQUARE_DATA, "triSquare"},
    {TRIVALVE_DATA, "triValve"},
    {TRIVALVE2_DATA, "triValve2"},
    {TRIANGLE_DATA, "triangle"},
    {WAVESIG_DATA, "waveSig"},
    {WAVESOFT_DATA, "waveSoft"},
    {WAVETAN_DATA, "waveTan"},
    {WAWAW_DATA, "wawaw"}
};

#define TABLES_COUNT sizeof tables / sizeof tables[0]

#endif