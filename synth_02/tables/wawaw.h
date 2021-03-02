#ifndef WAWAW_H_
#define WAWAW_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "mozzi_pgmspace.h"

#define WAWAW_NUM_CELLS 8192
#define WAWAW_SAMPLERATE 8192

CONSTTABLE_STORAGE(int8_t) WAWAW_DATA []  =
        {0,0,0,0,-1,-1,0,0,-1,-1,0,0,-1,-1,0,0,-1,-1,0,0,-1,0,0,-1,-1,0,0,-1,0,0,0,0,0,-1,0,0,-1,-1,0,0,-1,-1,0,0,-1,0,0,-1,-1,0,0,-1,0,0,0,0,0,-1,0,0,-1,-1,0,0,-1,-1,0,0,-1,0,0,-1,-1,0,0,0,-1,-1,0,0,-1,-1,0,0,-1,-1,0,0,-1,0,0,-1,-1,0,0,-1,-1,0,0,-1,0,0,-1,-1,0,0,-1,-1,0,0,0,-1,-1,0,0,0,-1,-1,0,0,-1,-1,0,0,-1,-1,-1,-1,-1,-1,-2,-2,-2,-4,-3,-4,-3,-5,-4,-6,-5,-6,-6,-7,-8,-7,-8,-7,-9,-7,-10,-8,-10,-8,-11,-9,-11,-9,-11,-9,-10,-8,-9,-8,-9,-7,-8,-7,-8,-7,-7,-7,-7,-7,-6,-7,-5,-7,-5,-6,-4,-5,-4,-4,-3,-3,-3,-2,-3,-2,-3,-2,-3,-2,-3,-2,-2,-2,-2,-2,-2,-2,-1,-2,-1,-1,0,0,2,0,2,0,3,0,4,1,5,1,6,2,6,2,5,1,5,1,5,1,6,2,6,4,6,5,7,6,6,7,5,7,5,8,5,8,5,8,4,9,4,9,3,9,2,8,2,8,4,7,5,7,6,7,7,8,8,9,10,8,11,7,13,7,14,7,15,6,15,8,14,10,14,11,15,12,16,13,18,14,17,16,14,15,13,14,13,13,12,13,12,13,12,13,12,12,9,11,6,10,3,9,3,8,11,8,21,10,22,11,14,11,5,11,2,12,8,14,17,16,21,17,17,18,9,19,6,19,5,19,9,19,14,16,14,13,9,13,10,14,13,14,15,11,16,7,16,5,16,5,16,6,17,7,18,8,19,10,18,11,17,12,15,11,14,10,15,10,14,9,10,6,1,-2,-15,-13,-25,-19,-24,-18,-23,-17,-24,-19,-25,-19,-25,-20,-25,-20,-24,-19,-25,-18,-25,-17,-26,-17,-27,-17,-27,-15,-25,-12,-23,-10,-23,-10,-23,-9,-23,-9,-22,-10,-20,-11,-19,-12,-16,-11,-14,-9,-14,-8,-14,-9,-13,-10,-10,-10,-8,-9,-6,-10,-5,-11,-5,-13,-4,-13,-1,-11,0,-10,1,-10,1,-10,1,-9,1,-8,4,-6,6,-3,5,1,2,4,2,5,3,5,3,5,4,6,3,8,2,7,0,5,0,2,1,0,0,-2,-3,-2,-6,-2,-9,-3,-11,-6,-12,-10,-11,-11,-10,-10,-10,-7,-12,-4,-13,-3,-11,-3,-7,-3,-4,-1,0,2,4,2,5,3,3,5,1,7,3,10,5,13,8,13,11,11,11,11,7,12,6,10,6,5,6,0,10,-2,12,-2,11,-3,8,-3,9,1,10,4,12,5,14,6,14,8,15,8,18,11,24,18,28,25,28,27,25,26,24,25,23,24,23,23,21,23,19,21,17,19,15,16,14,14,13,13,12,13,12,13,10,12,8,11,7,10,6,9,7,9,9,9,9,8,7,7,6,6,7,6,8,5,8,5,8,5,7,4,6,2,5,1,1,0,-4,-4,-10,-10,-20,-21,-37,-38,-54,-52,-58,-52,-59,-48,-61,-50,-53,-50,-34,-51,-21,-54,-24,-54,-40,-53,-52,-52,-54,-48,-46,-43,-33,-40,-24,-38,-26,-37,-35,-33,-43,-27,-49,-25,-50,-23,-47,-24,-39,-24,-31,-24,-29,-26,-28,-27,-23,-24,-19,-22,-16,-21,-11,-22,-2,-18,5,-10,9,-3,10,-2,11,-2,11,-2,11,-2,10,-2,9,-1,9,-2,8,-2,6,0,4,0,1,-2,0,-2,-3,-1,-6,-1,-8,-2,-9,0,-11,2,-12,3,-15,2,-17,0,-15,-1,-13,-3,-12,-4,-12,-4,-13,-3,-13,-1,-14,0,-15,0,-16,1,-16,1,-16,0,-13,-2,-8,-2,-4,-1,-3,1,-2,3,2,4,4,5,5,4,6,2,7,-1,7,-3,8,-3,12,-3,14,-3,12,-2,9,-3,8,-5,8,-4,8,-3,9,-1,8,1,6,2,5,2,5,2,3,2,2,2,1,2,0,2,1,2,2,3,0,4,-3,4,-5,2,-5,0,-5,-2,-4,-4,-4,-5,-5,-4,-6,-3,-5,-1,-4,1,-4,0,-4,-2,-3,-1,-2,1,-2,1,-1,1,0,2,1,2,2,3,2,3,3,4,4,4,5,3,5,1,5,0,5,0,5,0,4,-1,3,-2,3,-4,3,-6,1,-10,-9,-21,-26,-36,-33,-39,-29,-32,-28,-31,-26,-29,-22,-25,-22,-23,-20,-18,-19,-16,-18,-15,-16,-16,-15,-17,-15,-18,-16,-21,-16,-22,-16,-23,-16,-23,-19,-23,-21,-22,-22,-20,-23,-17,-23,-11,-20,-4,-17,-1,-15,0,-10,0,-4,0,0,-2,3,-3,4,-2,6,1,9,5,12,6,15,3,18,-1,16,-1,6,5,-1,10,5,7,10,4,11,2,10,-2,8,-1,5,1,-2,6,-7,9,2,9,17,10,24,12,22,13,15,12,5,14,-2,14,4,15,15,16,20,17,22,19,19,20,15,20,12,20,9,21,6,21,10,20,16,17,14,14,12,14,12,14,15,15,18,15,20,16,22,17,22,17,24,16,27,16,27,17,25,18,24,18,23,17,23,16,23,15,22,15,21,16,20,16,19,16,18,16,18,16,15,17,13,17,12,19,11,20,9,19,7,17,6,17,5,18,3,18,0,19,1,20,3,20,4,19,3,16,3,14,5,14,7,14,8,12,9,11,12,11,14,12,13,13,11,12,10,13,11,15,13,16,15,15,16,13,14,12,10,12,12,12,16,12,16,13,15,13,15,12,16,10,16,9,15,7,12,3,2,-10,-21,-32,-39,-45,-35,-40,-30,-37,-33,-38,-34,-35,-38,-34,-37,-35,-33,-35,-30,-34,-29,-30,-30,-27,-30,-23,-30,-23,-27,-23,-28,-24,-29,-23,-30,-20,-30,-18,-29,-17,-28,-16,-24,-13,-19,-13,-16,-13,-16,-12,-16,-10,-15,-9,-15,-8,-14,-5,-10,-1,0,4,13,9,21,14,22,15,21,14,23,12,24,11,24,11,25,12,26,12,26,12,25,14,23,16,23,17,23,17,22,16,20,16,19,17,18,18,18,17,19,17,21,17,22,17,21,18,19,19,18,19,17,20,15,21,13,20,8,14,-1,1,-13,-12,-17,-17,-17,-17,-18,-17,-20,-16,-18,-13,-16,-11,-13,-8,-10,-3,-5,1,1,1,6,-2,10,-3,10,-2,10,1,12,2,12,0,10,-2,10,-3,9,-4,8,-7,6,-9,3,-8,-2,-7,-9,-8,-16,-8,-19,-6,-12,-5,3,-4,15,-1,14,4,3,10,-9,13,-12,15,-9,16,4,14,17,12,19,13,17,14,10,15,0,14,-8,15,-10,15,-4,13,8,9,13,6,11,6,9,6,9,4,9,4,8,3,8,4,10,3,12,2,14,1,18,1,21,4,20,8,19,10,19,11,18,13,18,12,18,8,14,2,2,-10,-20,-26,-35,-35,-34,-33,-33,-28,-35,-27,-35,-25,-35,-24,-35,-22,-36,-20,-36,-18,-34,-15,-33,-15,-32,-16,-32,-18,-30,-17,-28,-15,-24,-13,-21,-11,-19,-9,-19,-9,-19,-9,-17,-11,-13,-15,-11,-17,-13,-17,-12,-14,-10,-12,-10,-8,-9,-6,-8,-6,-7,-6,-6,-5,-3,-4,2,-2,5,-2,4,-1,4,1,6,3,10,4,12,4,11,1,11,0,13,-1,14,-1,12,1,12,1,13,1,13,3,10,6,6,8,4,10,1,10,-1,9,-3,8,-4,8,-4,9,-2,8,-1,7,-1,9,1,9,2,9,2,10,3,11,4,11,5,11,6,10,9,8,9,5,8,5,8,5,8,7,9,7,10,7,12,8,12,8,13,8,14,9,15,10,16,13,18,13,18,13,18,13,19,13,19,16,17,19,15,18,14,14,13,10,14,6,16,4,15,5,14,9,14,12,14,11,12,7,10,7,9,9,5,9,1,7,0,7,-2,7,-4,9,-4,10,-2,10,1,11,3,12,5,12,8,11,11,9,14,8,15,6,14,6,14,5,14,4,15,2,14,0,9,2,5,3,2,2,1,2,3,0,6,-2,7,-2,7,0,3,0,-4,-6,-15,-16,-25,-25,-29,-26,-29,-24,-28,-24,-24,-23,-19,-22,-17,-22,-19,-20,-23,-19,-24,-19,-24,-19,-23,-19,-19,-18,-14,-17,-13,-16,-16,-14,-19,-13,-20,-13,-19,-13,-18,-14,-16,-14,-13,-13,-14,-13,-16,-13,-15,-13,-14,-14,-12,-13,-11,-13,-9,-12,-9,-12,-8,-11,-7,-11,-5,-10,-2,-9,0,-8,-1,-7,-4,-6,-5,-6,-5,-6,-6,-5,-2,0,12,12,34,31,42,42,36,37,33,35,28,32,23,29,20,29,14,28,12,30,11,30,10,28,10,28,10,30,11,30,13,28,14,26,15,24,16,22,17,21,20,23,23,24,25,23,27,20,24,19,20,19,18,19,20,19,21,21,20,21,21,18,22,18,21,18,23,17,27,16,27,16,23,17,21,16,21,15,20,15,21,14,23,11,22,10,20,9,17,7,14,4,13,4,12,6,10,4,10,2,10,-1,11,-3,6,-2,-6,4,-13,7,-9,5,-4,5,0,5,1,4,-2,2,-4,0,-4,0,-4,0,-3,-1,-2,-1,-2,-3,-3,-4,-4,-5,-6,-5,-8,-5,-9,-6,-8,-9,-8,-11,-6,-11,-4,-10,-3,-10,-5,-11,-6,-12,-5,-12,-5,-11,-5,-12,-6,-13,-7,-14,-12,-17,-21,-27,-36,-42,-43,-47,-39,-41,-37,-42,-37,-44,-37,-43,-36,-42,-33,-39,-33,-40,-32,-44,-33,-44,-36,-40,-37,-38,-37,-40,-34,-40,-35,-37,-40,-34,-44,-32,-46,-30,-46,-29,-44,-28,-43,-31,-43,-32,-39,-29,-30,-26,-24,-28,-21,-29,-20,-29,-21,-30,-20,-31,-18,-28,-17,-25,-15,-25,-14,-24,-13,-21,-15,-19,-16,-20,-15,-22,-13,-26,-14,-29,-17,-29,-20,-27,-20,-22,-23,-18,-29,-16,-33,-15,-25,-13,-10,-11,-1,-9,-2,-8,-7,-7,-15,-8,-26,-10,-32,-12,-23,-13,-10,-14,-5,-13,-8,-11,-17,-12,-23,-14,-27,-13,-24,-10,-17,-10,-7,-10,-2,-9,-5,-7,-7,-6,-4,-4,0,-2,-2,-2,-2,-4,0,-6,-1,-8,-1,-8,0,-7,2,-6,3,-3,5,-2,8,-1,10,-1,10,-2,8,-2,6,-2,2,0,0,1,-1,3,-2,5,-6,6,-8,5,-9,6,-10,8,-10,7,-11,5,-13,3,-15,1,-13,-1,-9,0,-8,1,-10,2,-13,1,-15,1,-12,2,-10,3,-9,4,-8,4,-5,5,-2,7,-1,7,-2,8,-1,8,4,7,7,6,7,7,4,3,-11,-14,-34,-36,-40,-45,-34,-41,-30,-39,-29,-39,-27,-36,-23,-34,-18,-30,-16,-28,-19,-28,-26,-31,-35,-36,-38,-38,-36,-36,-33,-35,-32,-33,-30,-31,-29,-29,-27,-27,-25,-25,-24,-24,-22,-22,-21,-20,-20,-18,-18,-16,-17,-15,-15,-14,-14,-13,-12,-10,-11,-8,-10,-5,-8,-4,-7,-4,-5,-3,-4,-1,-2,1,1,2,3,3,5,4,7,5,10,7,14,9,16,10,15,12,16,13,18,13,20,13,21,14,22,16,23,17,24,17,25,19,24,20,25,21,26,23,27,25,28,26,30,27,31,29,33,29,33,29,32,30,31,31,30,32,29,32,28,31,27,30,27,29,28,30,30,31,30,32,30,33,30,36,30,38,31,39,32,39,32,38,33,37,34,38,36,39,40,40,44,41,46,41,46,39,49,37,53,34,53,33,49,32,45,32,43,33,44,33,45,33,43,34,43,34,41,35,39,36,36,37,30,39,23,39,18,38,24,36,39,35,50,35,48,36,35,38,22,38,17,41,20,43,27,42,36,40,42,36,38,31,29,28,23,28,22,28,22,29,23,30,30,30,31,29,29,30,30,30,32,29,32,27,34,26,40,28,44,30,43,29,41,28,40,28,39,28,36,29,32,29,29,27,25,23,23,21,19,20,9,10,-8,-9,-21,-22,-22,-22,-20,-17,-23,-16,-25,-14,-25,-13,-25,-15,-24,-14,-26,-13,-25,-13,-25,-13,-25,-14,-25,-15,-24,-16,-23,-15,-22,-14,-21,-13,-20,-12,-18,-12,-15,-14,-13,-13,-12,-12,-14,-10,-16,-10,-18,-9,-17,-8,-16,-6,-14,-5,-9,-4,-3,-2,-2,0,-1,-1,4,-2,6,-5,5,-9,3,-11,0,-12,0,-12,-1,-11,-1,-11,0,-10,0,-10,0,-8,0,-7,1,-5,0,-3,-1,-1,-1,0,-3,-1,-4,0,-3,2,-3,1,-5,-1,-7,-2,-8,-4,-7,-4,-7,-3,-10,-3,-13,-3,-13,-1,-13,-2,-13,-4,-13,-4,-13,-4,-12,-4,-9,-5,-6,-4,-5,-3,-3,-2,-1,-1,0,1,1,3,0,2,-1,-1,2,-5,4,-5,4,-4,4,-4,6,-3,8,-2,7,-4,7,-7,5,-7,4,-5,5,-1,7,0,7,0,3,3,0,3,0,1,1,0,1,0,0,1,2,3,8,10,15,18,19,21,17,19,15,17,13,15,12,14,10,13,8,12,8,11,9,9,8,9,6,8,5,8,6,6,4,6,2,4,1,3,1,1,-1,1,-2,1,0,0,2,-2,3,-4,3,-5,3,-5,1,-6,-1,-6,-3,-6,-6,-8,-11,-16,-26,-35,-50,-58,-62,-65,-62,-60,-67,-55,-67,-51,-57,-48,-45,-48,-41,-46,-47,-46,-52,-47,-54,-47,-55,-44,-50,-42,-39,-44,-31,-44,-33,-42,-38,-42,-45,-44,-46,-43,-45,-41,-42,-38,-36,-35,-32,-33,-31,-34,-28,-37,-23,-39,-27,-34,-37,-26,-36,-23,-24,-25,-12,-20,-1,-11,6,-3,7,0,7,0,7,0,7,-2,6,-2,5,-3,3,-4,1,-7,-1,-8,-3,-8,-5,-9,-7,-9,-10,-7,-11,-7,-11,-8,-12,-8,-13,-6,-14,-3,-14,0,-13,2,-12,3,-12,3,-14,3,-16,2,-15,1,-13,-1,-13,-3,-13,-5,-12,-5,-13,-6,-13,-8,-12,-9,-11,-8,-11,-6,-10,-5,-6,-5,-2,-4,1,-2,2,-1,3,-2,2,-3,2,-6,3,-7,3,-6,3,-4,5,-2,7,-2,9,-2,10,-3,8,-3,6,-3,3,-2,1,-1,1,-2,2,-2,3,-1,0,0,-2,-1,-3,-3,-3,-3,-2,-2,-2,0,-3,1,-5,1,-6,-1,-6,-3,-6,-3,-5,-3,-4,-2,-4,-1,-5,1,-6,2,-6,2,-5,0,-6,-3,-5,-3,-4,-4,-4,-5,-4,-5,-2,-4,-2,-3,-1,-3,0,-2,2,0,4,2,6,2,7,2,5,2,4,2,4,2,4,1,1,-1,-6,-9,-16,-23,-23,-32,-22,-30,-24,-32,-28,-37,-26,-36,-25,-34,-22,-31,-23,-28,-25,-24,-22,-21,-21,-22,-20,-19,-19,-16,-18,-14,-18,-14,-18,-14,-16,-13,-13,-12,-12,-11,-12,-8,-13,-5,-13,-5,-14,-7,-14,-9,-9,-7,-3,-6,1,-5,1,-5,-1,-3,0,0,4,2,7,2,8,2,10,0,14,-1,15,1,14,5,11,7,11,8,11,11,9,15,5,17,1,16,-3,15,-2,16,7,16,20,15,25,12,21,11,15,12,11,14,8,14,7,15,14,15,23,13,26,11,23,10,14,11,4,12,-2,14,-2,15,6,15,17,15,24,16,23,19,20,21,21,22,22,22,23,22,22,22,23,24,22,25,20,24,20,22,23,21,26,20,27,20,25,20,25,19,25,18,24,17,24,17,24,18,23,19,22,19,22,18,20,17,18,18,15,19,13,20,11,19,9,18,8,17,9,15,10,14,9,14,8,15,7,16,5,17,4,19,4,20,5,20,5,19,6,18,8,18,11,16,13,14,12,14,10,15,11,17,13,17,15,16,16,14,17,14,17,13,16,12,19,13,20,13,19,14,16,15,14,14,14,12,12,8,7,2,-4,-11,-20,-30,-32,-44,-27,-43,-21,-40,-22,-40,-22,-38,-22,-36,-24,-35,-26,-33,-31,-31,-33,-28,-36,-26,-36,-24,-34,-21,-32,-18,-29,-14,-29,-9,-27,-8,-26,-8,-25,-8,-23,-10,-21,-12,-19,-12,-17,-12,-15,-12,-13,-14,-11,-14,-11,-12,-8,-6,0,3,8,11,14,12,17,10,21,11,24,14,26,18,27,19,27,18,27,19,26,21,24,22,22,21,21,19,21,17,22,16,21,15,21,14,21,13,21,13,20,13,19,12,17,11,16,11,17,13,17,15,17,17,16,19,15,20,12,18,1,11,-16,-2,-23,-9,-20,-8,-16,-6,-16,-5,-15,-3,-14,-3,-9,-5,-3,-7,1,-8,4,-9,5,-10,4,-12,4,-13,6,-11,7,-9,5,-7,4,-4,4,-1,4,-2,4,-6,5,-5,4,-1,3,1,-1,1,-7,2,-13,4,-14,7,-3,7,12,7,19,7,18,7,9,8,-5,7,-15,5,-15,6,-7,7,6,7,16,6,19,6,15,4,7,1,-2,-1,-9,-1,-11,3,-5,6,6,8,8,10,6,13,5,15,9,16,13,18,13,18,14,14,18,9,20,7,20,8,19,7,20,6,19,5,16,6,15,8,15,8,15,6,13,0,4,-9,-14,-22,-31,-32,-33,-33,-32,-29,-33,-28,-31,-28,-31,-26,-32,-23,-32,-21,-32,-20,-31,-18,-31,-17,-31,-17,-31,-19,-29,-20,-27,-20,-27,-20,-26,-18,-24,-14,-22,-11,-21,-10,-20,-10,-18,-9,-15,-7,-13,-5,-13,-4,-13,-6,-10,-7,-6,-6,-4,-5,-2,-6,-1,-6,-2,-6,2,-6,8,-6,9,-7,6,-7,4,-6,2,-2,2,1,5,3,11,5,13,6,11,6,8,6,8,6,9,6,9,6,8,5,6,3,4,3,4,4,4,6,4,6,3,5,1,4,0,6,-2,8,0,10,2,11,3,11,3,9,2,6,2,5,2,7,2,9,3,9,4,9,8,9,10,10,11,10,13,9,12,8,13,7,13,9,12,11,9,12,8,11,8,10,11,9,13,9,14,9,15,9,20,8,23,9,17,14,11,21,14,20,18,17,20,13,23,8,21,6,17,5,14,4,13,5,11,6,8,7,6,6,4,6,3,6,3,5,2,6,-3,7,-5,8,-2,9,0,9,2,9,3,8,3,8,3,9,4,9,4,8,6,5,7,1,7,-2,11,-1,16,2,17,3,17,4,14,5,11,5,9,4,7,3,7,2,4,0,-3,-3,-16,-12,-27,-21,-29,-25,-29,-23,-28,-23,-24,-23,-16,-21,-12,-22,-13,-22,-19,-22,-24,-22,-24,-21,-23,-21,-21,-20,-18,-18,-17,-17,-19,-17,-20,-17,-20,-17,-19,-16,-19,-16,-18,-14,-15,-12,-13,-11,-13,-10,-13,-10,-12,-10,-11,-10,-11,-10,-12,-9,-11,-8,-10,-8,-9,-9,-8,-9,-6,-9,-4,-9,-3,-9,-3,-8,-1,-7,6,-3,24,10,41,27,39,29,33,26,34,29,30,31,24,34,23,34,21,30,18,28,16,25,17,25,16,25,17,26,17,27,15,29,10,31,8,31,10,32,10,32,10,30,10,26,12,23,11,21,11,21,12,20,13,19,12,19,14,20,16,20,17,18,16,16,19,15,21,13,22,11,22,9,25,9,28,10,26,12,21,13,18,12,18,10,18,8,17,6,16,6,15,6,14,6,12,6,11,7,11,7,12,4,12,3,9,3,7,5,5,6,2,4,1,2,0,2,-1,2,-1,1,-2,0,-4,0,-6,0,-6,-1,-7,-1,-10,-2,-11,-4,-11,-6,-9,-7,-7,-6,-6,-6,-8,-7,-9,-9,-9,-11,-8,-11,-6,-9,-5,-9,-6,-8,-6,-8,-5,-8,-6,-9,-7,-10,-8,-13,-9,-15,-9,-17,-12,-21,-20,-31,-34,-49,-43,-59,-40,-53,-37,-48,-37,-45,-34,-41,-35,-40,-36,-38,-35,-35,-36,-35,-36,-33,-37,-32,-35,-31,-36,-32,-38,-33,-39,-36,-40,-39,-42,-41,-42,-40,-41,-38,-41,-36,-39,-34,-35,-34,-32,-33,-30,-30,-28,-28,-28,-28,-25,-28,-24,-27,-24,-25,-25,-24,-23,-23,-18,-21,-13,-19,-11,-20,-11,-20,-11,-21,-12,-20,-15,-21,-16,-22,-17,-21,-18,-21,-20,-21,-25,-22,-30,-20,-32,-18,-27,-18,-13,-18,-2,-17,0,-15,-7,-15,-17,-15,-25,-14,-28,-13,-22,-13,-10,-13,-1,-11,1,-10,-2,-9,-12,-10,-22,-9,-26,-7,-25,-6,-19,-5,-10,-4,-5,-3,-6,-4,-9,-6,-11,-7,-6,-6,-1,-4,1,-3,3,-3,6,-4,7,-5,7,-5,8,-6,8,-6,7,-5,6,-3,4,-1,3,1,3,0,3,-1,3,0,3,1,4,0,3,-2,0,-2,-2,-2,-3,1,-4,5,-6,7,-8,7,-10,7,-12,8,-15,6,-17,5,-18,6,-17,6,-13,6,-7,5,-4,7,-4,7,-4,6,-4,5,-4,4,-4,5,-2,6,-2,7,-1,6,4,6,7,6,4,2,-8,-12,-28,-33,-39,-42,-36,-39,-28,-36,-25,-36,-23,-34,-23,-33,-23,-31,-22,-29,-22,-28,-25,-31,-32,-36,-36,-38,-35,-36,-33,-35,-32,-33,-29,-31,-27,-29,-26,-28,-24,-26,-23,-24,-21,-22,-20,-21,-19,-19,-18,-17,-16,-15,-15,-13,-13,-10,-12,-9,-10,-8,-9,-6,-8,-5,-6,-4,-5,-3,-4,-1,-2,0,0,1,2,2,5,4,8,6,11,9,13,10,16,11,17,12,18,13,17,14,19,15,20,17,19,17,20,17,22,17,25,19,27,21,27,21,26,20,26,21,28,23,30,24,29,25,27,26,27,26,28,26,29,28,31,30,32,31,31,33,30,35,30,35,30,34,31,33,31,33,32,34,34,36,37,37,39,37,39,38,37,38,35,37,34,37,34,37,34,36,35,35,36,34,39,34,43,36,46,39,46,40,47,42,47,43,46,43,44,42,43,40,42,39,41,36,44,34,44,33,41,32,34,32,26,32,20,34,23,35,36,36,47,35,49,32,42,31,29,32,21,33,20,35,23,37,33,39,44,40,46,39,42,37,32,35,23,36,20,36,21,36,29,35,39,33,41,29,33,28,24,28,22,28,27,27,29,27,28,27,27,27,28,27,30,26,32,26,34,26,35,26,36,27,35,27,33,25,29,21,21,13,4,-2,-13,-16,-19,-19,-19,-17,-21,-18,-22,-19,-23,-18,-24,-18,-23,-17,-22,-17,-21,-15,-22,-12,-22,-10,-24,-9,-25,-11,-24,-13,-22,-11,-24,-3,-29,3,-28,-3,-25,-9,-22,-10,-19,-12,-16,-13,-12,-13,-9,-12,-8,-12,-6,-13,-4,-13,-6,-12,-7,-10,-6,-9,-7,-9,-8,-9,-6,-7,-4,-6,-2,-6,0,-6,0,-7,0,-8,0,-6,2,-5,3,-5,2,-6,1,-8,1,-6,3,-3,5,-2,3,-3,0,-3,-3,-4,-5,-6,-8,-5,-10,-5,-11,-5,-12,-6,-11,-6,-11,-6,-11,-5,-9,-3,-11,-1,-13,-1,-13,1,-11,3,-10,2,-11,-2,-10,-4,-9,-3,-9,0,-7,0,-2,-2,1,-4,0,-3,0,-2,2,-2,4,-5,4,-7,4,-5,4,-3,2,-2,1,-1,2,-3,3,-4,2,-4,2,-2,3,1,5,2,5,-1,3,-4,2,-6,1,-7,1,-4,1,-1,2,1,1,2,0,1,1,3,8,9,15,15,19,17,18,17,16,16,14,15,11,14,11,14,9,14,7,13,5,11,4,10,4,8,4,7,4,5,3,3,2,1,1,1,2,1,2,0,2,-1,2,-1,3,-1,3,-3,2,-5,1,-7,-1,-7,-3,-7,-7,-9,-17,-18,-36,-38,-54,-57,-61,-60,-65,-58,-67,-55,-60,-54,-48,-56,-40,-57,-42,-57,-47,-54,-54,-50,-61,-48,-62,-46,-53,-43,-38,-37,-29,-33,-27,-32,-34,-35,-37,-37,-39,-36,-42,-34,-43,-31,-37,-29,-29,-28,-32,-29,-34,-30,-30,-32,-23,-32,-23,-32,-21,-29,-13,-23,-5,-14,0,-10,3,-9,3,-9,4,-9,4,-9,4,-7,4,-6,5,-7,4,-6,1,-5,-2,-5,-5,-5,-6,-4,-7,-3,-8,-4,-10,-5,-11,-6,-10,-6,-12,-5,-15,-5,-18,-4,-20,-4,-20,-5,-18,-5,-17,-5,-16,-5,-16,-4,-17,-2,-17,0,-16,1,-15,0,-12,-1,-9,-2,-7,-3,-4,-4,-4,-6,-3,-8,-1,-10,1,-9,2,-6,4,-4,5,-4,4,-4,2,-4,3,-3,2,-1,0,0,-2,-1,-2,-3,-1,-5,0,-5,1,-6,2,-5,3,-3,3,-2,2,-1,3,-2,4,-3,4,-3,1,-4,-1,-3,-1,-2,0,-1,-3,0,-5,1,-5,2,-6,2,-5,1,-5,-1,-6,-3,-6,-3,-7,-2,-5,-1,-3,-2,-2,-2,-2,-1,-1,0,-1,-1,-3,-1,-3,-1,-4,0,-3,1,-1,1,1,1,1,-1,1,-4,0,-5,1,-5,2,-3,3,-2,3,-2,3,-2,4,-3,-2,-7,-14,-20,-27,-33,-30,-33,-29,-28,-29,-26,-24,-21,-22,-21,-20,-22,-17,-23,-17,-25,-17,-25,-19,-24,-18,-23,-16,-22,-15,-20,-14,-20,-12,-19,-13,-16,-16,-14,-18,-13,-19,-13,-17,-11,-13,-7,-10,-5,-10,-6,-13,-8,-15,-8,-13,-7,-7,-5,1,-2,6,1,8,2,11,3,14,4,15,6,14,6,12,6,12,6,11,7,10,9,6,10,5,11,7,12,9,12,11,12,9,13,4,12,1,12,9,11,21,10,26,10,23,10,15,10,7,11,5,13,7,15,14,17,20,19,22,21,19,20,14,20,10,20,11,20,13,19,17,16,22,15,22,17,17,20,13,21,15,20,18,18,18,17,18,16,20,16,22,16,26,17,28,19,29,19,29,19,29,21,28,22,26,22,24,22,23,20,21,21,20,22,20,24,19,23,19,22,18,20,17,19,16,18,13,18,10,18,7,18,5,17,6,16,6,16,5,16,4,16,4,15,4,15,4,15,4,16,6,17,8,17,11,18,15,18,18,19,18,18,15,17,14,17,14,17,14,16,14,16,14,15,13,14,12,12,14,12,16,12,17,11,16,10,15,8,13,4,9,-1,3,-7,-8,-21,-24,-36,-30,-38,-27,-33,-29,-34,-26,-33,-27,-32,-31,-32,-31,-28,-29,-26,-25,-25,-24,-25,-24,-26,-25,-26,-27,-27,-28,-25,-28,-22,-25,-17,-24,-14,-26,-13,-26,-13,-25,-12,-25,-12,-25,-12,-23,-12,-19,-12,-16,-14,-11,-11,-1,-1,11,11,18,18,18,20,18,20,19,19,21,17,22,14,21,10,21,9,21,11,21,15,22,17,23,17,24,17,25,16,24,16,23,16,23,16,22,19,20,20,21,19,21,19,20,20,19,21,21,21,22,19,20,17,19,16,17,15,15,12,7,4,-7,-9,-19,-18,-22,-18,-19,-14,-20,-10,-21,-7,-20,-6,-20,-7,-19,-6,-15,-6,-10,-7,-6,-9,0,-11,8,-10,11,-5,5,4,0,11,8,8,15,3,16,0,14,-3,12,-2,11,-3,11,-4,10,-3,5,-3,0,-3,-5,-3,-14,-2,-18,-2,-9,1,9,4,17,7,15,9,6,12,-4,14,-10,15,-13,15,-5,14,8,13,14,11,11,9,3,7,-3,5,-3,2,-3,-1,3,-2,10,-3,14,-2,12,0,10,2,10,4,12,6,14,8,14,10,14,13,14,15,13,16,13,14,16,12,18,12,18,10,18,8,18,8,18,7,12,1,-5,-14,-27,-28,-35,-31,-33,-28,-33,-28,-33,-29,-34,-28,-36,-28,-35,-26,-32,-25,-31,-23,-31,-22,-30,-21,-29,-19,-28,-19,-27,-18,-26,-19,-24,-18,-23,-17,-21,-15,-21,-13,-20,-12,-19,-10,-18,-9,-16,-8,-14,-7,-12,-8,-11,-7,-8,-6,-6,-4,-6,-3,-6,-2,-5,-2,-3,-2,-2,-2,4,-1,7,-2,7,-2,6,-1,7,0,7,-1,7,0,7,2,9,4,9,4,6,1,5,0,9,1,15,2,16,2,14,2,11,2,7,1,4,2,1,4,-1,6,-2,8,-4,10,-5,10,-2,7,2,6,5,8,5,11,4,12,3,13,5,14,5,13,3,13,3,13,3,12,5,10,8,10,10,11,12,12,12,15,11,16,14,14,17,11,17,10,15,7,16,5,17,4,17,5,18,5,17,5,15,5,13,6,11,8,11,9,13,10,13,11,13,11,14,12,14,15,13,17,12,15,13,13,12,12,10,10,10,9,9,9,6,8,5,5,4,4,3,3,3,3,3,3,2,4,0,5,-3,6,-3,9,0,12,3,13,5,12,6,13,5,15,4,12,6,8,11,6,18,6,22,6,19,1,14,-5,10,-9,9,-11,3,-14,-10,-20,-23,-26,-28,-28,-27,-25,-28,-24,-29,-24,-28,-24,-26,-24,-21,-23,-18,-22,-19,-21,-22,-19,-24,-17,-23,-16,-22,-16,-20,-16,-16,-15,-15,-13,-15,-14,-16,-15,-18,-16,-18,-15,-18,-15,-16,-15,-14,-15,-13,-15,-15,-14,-15,-14,-14,-13,-13,-13,-12,-12,-11,-12,-9,-11,-9,-9,-8,-7,-7,-6,-6,-6,-4,-6,-2,-5,2,-2,16,9,37,26,45,33,41,28,41,26,40,23,35,21,32,22,27,21,22,20,16,20,11,21,9,23,12,25,16,26,14,28,11,32,9,34,9,36,8,36,6,35,5,30,8,27,10,26,9,27,10,28,13,25,16,21,16,18,16,15,18,15,19,14,20,11,19,9,19,7,20,6,18,6,18,8,21,10,22,11,22,11,22,11,22,12,22,14,20,15,18,14,14,11,11,8,10,6,11,3,10,2,8,1,8,2,9,3,9,5,7,5,6,2,3,-1,-1,-1,-4,1,-5,2,-4,2,-5,3,-7,3,-10,3,-11,1,-12,-2,-15,-4,-14,-6,-12,-7,-11,-7,-11,-7,-10,-8,-9,-8,-7,-9,-5,-10,-3,-11,-3,-10,-3,-9,-3,-10,-4,-11,-7,-13,-7,-14,-8,-16,-8,-16,-10,-16,-14,-19,-27,-31,-41,-46,-39,-48,-34,-47,-36,-50,-36,-45,-36,-41,-35,-40,-34,-39,-38,-40,-41,-39,-41,-38,-41,-35,-42,-33,-42,-34,-42,-37,-42,-38,-39,-38,-36,-38,-33,-36,-29,-33,-26,-31,-27,-31,-29,-32,-29,-32,-30,-31,-32,-28,-32,-24,-29,-22,-24,-21,-22,-23,-20,-25,-20,-25,-20,-24,-19,-24,-17,-23,-14,-22,-11,-21,-9,-22,-9,-23,-10,-26,-11,-27,-15,-24,-21,-19,-25,-17,-28,-15,-32,-13,-32,-12,-22,-12,-6,-12,1,-11,-1,-9,-7,-10,-15,-10,-26,-10,-32,-10,-23,-10,-11,-10,-6,-11,-4,-12,-7,-12,-10,-13,-14,-13,-18,-13,-17,-12,-12,-8,-1,-7,2,-8,0,-8,-4,-7,-4,-6,-3,-5,-1,-3,1,-2,3,-1,3,0,4,2,5,4,7,4,7,5,7,6,6,4,5,2,4,1,3,1,2,1,2,0,1,-1,-1,-2,-2,-4,-2,-4,-2,-4,-2,-5,-3,-5,-4,-5,-6,-1,-9,4,-12,8,-13,8,-13,8,-13,9,-13,10,-14,11,-14,10,-13,8,-12,7,-8,8,-6,9,-4,9,0,7,4,5,6,4,8,3,6,-2,-8,-15,-30,-35,-40,-44,-36,-41,-34,-38,-32,-37,-26,-34,-25,-32,-25,-30,-23,-27,-21,-26,-23,-27,-30,-33,-35,-37,-34,-37,-32,-35,-30,-33,-26,-32,-23,-30,-25,-27,-26,-24,-24,-23,-21,-23,-19,-22,-17,-20,-16,-19,-14,-17,-14,-15,-14,-12,-12,-11,-11,-9,-10,-7,-8,-4,-6,-2,-5,-1,-3,0,-1,2,1,3,2,4,3,6,4,7,7,8,10,7,12,8,13,9,14,10,16,11,19,12,21,13,23,14,23,17,23,19,24,20,24,21,23,22,24,24,27,24,29,25,31,25,30,25,29,26,29,26,31,25,32,26,33,27,32,28,32,29,32,30,31,32,31,33,31,32,32,32,32,33,30,34,27,36,28,39,31,40,34,40,35,39,39,38,43,39,44,39,40,40,38,41,37,40,36,40,37,39,38,38,39,37,43,35,50,34,54,33,51,32,46,32,42,32,42,31,43,32,42,33,37,35,29,36,21,37,18,37,22,39,35,39,47,39,49,39,41,38,30,37,24,36,19,35,21,35,33,35,45,36,51,36,48,31,39,26,29,25,21,28,23,31,28,33,34,36,33,35,25,33,17,33,20,32,27,29,30,27,31,27,31,30,31,30,33,28,35,26,34,27,33,27,31,27,28,25,25,22,21,14,9,-1,-10,-18,-19,-24,-16,-21,-16,-19,-18,-19,-19,-17,-21,-19,-21,-18,-22,-15,-24,-14,-24,-14,-24,-15,-23,-15,-23,-12,-23,-9,-23,-7,-23,-7,-24,-9,-23,-9,-22,-8,-20,-6,-18,-5,-18,-5,-18,-8,-17,-10,-14,-11,-14,-11,-15,-10,-14,-9,-12,-9,-10,-9,-7,-9,-4,-8,-4,-7,-3,-7,2,-8,4,-9,2,-7,0,-6,0,-7,1,-8,2,-8,5,-7,8,-6,6,-6,3,-6,2,-5,3,-4,4,-3,5,-2,3,-2,-3,-1,-5,-2,-5,-3,-6,-3,-11,-4,-15,-6,-16,-8,-14,-8,-13,-6,-13,-4,-14,-4,-14,-3,-12,-2,-11,-1,-12,0,-12,1,-10,3,-7,4,-5,5,-4,3,-3,1,-2,-2,1,-4,0,-3,-3,-5,-5,-9,-2,-11,3,-11,8,-9,10,-8,11,-6,12,-2,11,1,8,3,7,4,6,4,5,5,3,6,0,5,-1,3,-1,0,-1,-3,-1,-6,-1,-6,-1,-5,2,-2,9,7,15,16,15,16,13,14,13,13,13,14,10,15,7,15,5,14,5,13,5,11,3,9,3,7,3,5,3,4,3,3,4,3,5,2,6,1,5,0,4,-1,3,-1,2,-2,0,-4,-1,-6,-1,-7,-2,-7,-5,-10,-12,-19,-26,-38,-45,-56,-54,-59,-60,-57,-68,-56,-68,-53,-61,-51,-46,-50,-33,-50,-30,-51,-39,-50,-53,-46,-60,-41,-60,-41,-51,-41,-40,-43,-28,-43,-27,-44,-35,-43,-43,-42,-47,-41,-46,-37,-44,-32,-37,-29,-29,-29,-27,-29,-31,-29,-33,-26,-32,-24,-28,-23,-20,-18,-7,-9,2,-2,4,-2,4,-4,7,-5,9,-5,8,-4,7,-4,6,-5,5,-7,2,-9,-3,-10,-4,-11,-3,-11,-4,-11,-8,-11,-10,-11,-9,-9,-10,-7,-12,-6,-11,-3,-11,-1,-12,0,-12,0,-13,0,-14,-1,-16,0,-17,1,-21,1,-22,-1,-19,-1,-16,-1,-16,-2,-14,-3,-12,-6,-10,-7,-8,-5,-8,-4,-8,-4,-4,-4,0,-5,1,-5,2,-7,3,-7,1,-6,0,-5,5,-3,8,-2,9,-1,8,-2,8,-3,8,-3,7,-4,7,-5,5,-6,3,-5,0,-4,-1,-2,-1,1,-1,2,-1,1,-2,-2,-4,-3,-4,-2,-2,-2,-3,-2,-6,-1,-8,-1,-8,-2,-5,-3,-3,-4,-2,-3,-3,-2,-4,-1,-5,-2,-5,-3,-6,-3,-6,-2,-5,0,-3,2,-2,2,-1,3,-1,4,0,4,1,1,2,-1,3,-1,2,-1,2,-3,4,-4,6,-4,6,-4,5,-3,3,-3,-3,-7,-15,-21,-30,-37,-29,-37,-22,-29,-23,-27,-23,-24,-23,-20,-21,-19,-18,-19,-19,-21,-21,-21,-23,-23,-24,-24,-20,-24,-16,-22,-17,-20,-18,-19,-16,-18,-16,-18,-16,-16,-13,-13,-9,-12,-6,-14,-6,-13,-7,-9,-9,-6,-8,-5,-5,-4,-3,-2,-3,3,-3,6,-3,8,-2,8,3,8,9,8,12,9,14,9,15,7,15,3,14,3,15,6,15,8,15,8,13,7,10,7,6,8,0,8,-6,8,-5,8,7,9,20,10,26,12,25,14,21,15,15,15,8,16,4,18,9,18,17,17,22,16,21,19,16,20,12,20,10,18,12,15,10,17,10,22,16,21,19,19,17,20,20,20,23,20,25,22,26,24,28,24,28,25,26,25,24,23,23,21,23,20,24,19,24,18,24,16,22,15,21,15,22,15,22,14,22,14,22,14,20,15,17,16,15,18,13,19,10,19,9,20,7,20,5,19,5,19,6,19,7,21,7,21,7,21,8,20,8,20,7,20,7,19,8,18,9,17,12,16,13,15,12,14,10,14,10,13,14,12,17,12,18,13,18,13,16,13,14,13,15,13,17,13,17,13,15,13,12,10,8,5,2,-2,-8,-15,-23,-34,-31,-42,-30,-41,-32,-41,-31,-39,-28,-37,-27,-37,-26,-36,-28,-34,-29,-31,-30,-25,-30,-21,-30,-18,-31,-17,-31,-17,-29,-18,-25,-17,-22,-16,-21,-14,-20,-13,-17,-10,-14,-4,-15,-1,-17,-4,-17,-8,-13,-6,-5,-2,4,4,12,8,12,8,10,7,10,7,12,7,15,7,18,8,19,12,19,16,21,19,23,19,25,18,26,18,25,20,23,21,19,20,17,19,17,19,18,19,16,19,17,19,18,17,21,16,22,15,21,15,21,15,21,15,20,16,17,16,11,11,2,-1,-6,-14,-9,-19,-11,-17,-13,-15,-13,-14,-11,-13,-10,-12,-11,-10,-16,-9,-18,-7,-14,-5,-9,-4,-4,-4,-2,-1,-3,2,-2,1,3,-1,7,-1,8,-3,7,-4,7,-4,9,-4,9,-2,7,-1,7,-1,6,2,4,5,2,6,0,4,-7,3,-15,3,-14,3,-1,5,16,7,23,9,21,10,12,9,0,10,-7,9,-6,8,0,10,10,11,16,10,12,8,7,7,2,5,-1,2,-1,0,2,1,8,3,9,5,7,6,4,6,5,7,8,10,9,13,11,15,14,14,16,14,17,14,18,15,19,14,18,11,16,9,15,8,11,2,-1,-14,-21,-30,-31,-37,-29,-34,-28,-32,-29,-31,-27,-29,-26,-28,-26,-27,-28,-25,-30,-22,-28,-20,-27,-18,-27,-16,-28,-16,-28,-15,-28,-15,-26,-14,-26,-13,-27,-11,-26,-10,-24,-11,-21,-10,-18,-10,-16,-12,-15,-12,-14,-10,-13,-11,-13,-10,-11,-8,-8,-8,-6,-8,-3,-8,0,-7,0,-5,-1,-4,3,-2,7,1,9,3,7,7,5,9,6,8,11,7,15,7,16,7,13,5,10,5,9,4,9,3,8,2,6,1,4,0,3,-1,4,-2,4,-1,5,0,7,2,7,5,4,8,2,9,1,11,0,12,-1,11,-2,10,0,11,2,12,4,10,4,8,5,10,4,12,2,11,3,10,6,11,9,13,10,13,11,11,13,8,13,7,13,5,12,4,15,5,17,9,18,12,19,15,19,14,19,14,19,16,19,17,20,16,21,15,20,14,18,10,19,7,17,6,13,5,10,3,8,2,7,3,6,4,4,5,2,4,1,3,3,3,4,6,5,8,4,9,4,11,2,13,0,12,0,12,0,12,0,9,2,7,4,5,4,7,4,8,5,7,6,6,8,5,12,5,15,3,16,0,15,-1,14,0,14,-2,10,-6,-3,-13,-18,-22,-26,-26,-25,-25,-25,-24,-27,-24,-28,-22,-27,-21,-24,-21,-19,-21,-15,-22,-16,-22,-21,-21,-23,-20,-23,-20,-21,-19,-18,-19,-15,-17,-14,-16,-16,-15,-19,-15,-19,-14,-18,-13,-18,-12,-17,-12,-15,-12,-14,-12,-14,-11,-14,-11,-12,-12,-10,-12,-9,-12,-9,-11,-8,-11,-8,-10,-8,-10,-7,-9,-5,-7,0,-2,14,10,37,29,48,37,44,29,41,26,38,28,33,25,33,25,31,24,29,25,26,25,21,23,15,24,10,25,10,26,9,26,7,28,6,26,6,26,6,26,5,25,4,26,4,26,6,24,9,22,10,19,9,19,8,19,9,18,13,17,17,18,18,19,17,17,19,13,19,12,18,12,18,13,19,12,18,11,17,11,21,11,22,11,18,13,14,14,13,13,15,11,17,8,16,6,13,5,10,6,7,4,8,3,11,3,12,3,9,3,6,4,4,5,4,3,3,1,2,1,0,-1,-3,-2,-5,-3,-7,-3,-9,-3,-10,-3,-9,-4,-8,-4,-10,-4,-13,-4,-14,-4,-13,-5,-13,-5,-12,-6,-10,-8,-8,-9,-6,-10,-5,-11,-6,-13,-6,-13,-6,-13,-6,-13,-5,-13,-3,-13,-3,-13,-6,-11,-14,-8,-19,-13,-28,-27,-41,-41,-43,-44,-41,-42,-45,-45,-45,-48,-42,-49,-40,-52,-33,-50,-30,-48,-29,-44,-28,-42,-28,-42,-28,-41,-31,-40,-35,-39,-37,-38,-37,-37,-37,-36,-35,-32,-34,-29,-36,-26,-40,-27,-41,-27,-38,-27,-34,-27,-32,-26,-30,-24,-28,-23,-24,-22,-19,-18,-19,-16,-20,-18,-20,-20,-17,-21,-15,-22,-15,-23,-16,-23,-17,-25,-15,-28,-11,-29,-9,-27,-9,-23,-8,-19,-9,-16,-14,-13,-23,-11,-33,-10,-35,-9,-24,-10,-10,-13,-3,-17,-4,-20,-9,-21,-16,-21,-24,-22,-29,-21,-20,-17,-9,-13,-3,-10,-2,-7,-6,-6,-11,-5,-18,-3,-22,-1,-19,0,-9,1,1,2,1,1,-4,0,-6,-1,-2,-1,2,0,3,0,3,-2,5,-5,7,-7,8,-7,7,-5,7,-4,6,-4,5,-4,6,-4,6,-3,6,-1,5,0,4,1,3,2,2,4,1,5,-1,5,-1,5,-2,4,-5,4,-9,3,-10,3,-8,3,-5,3,-7,4,-11,4,-12,4,-14,4,-16,4,-14,4,-8,5,-3,6,-3,7,-3,8,0,8,4,7,7,9,7,10,5,11,5,13,4,12,-4,5,-23,-15};
#endif