#ifndef KICK001_H_
#define KICK001_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "mozzi_pgmspace.h"

#define KICK001_NUM_CELLS 8192
#define KICK001_SAMPLERATE 8192

CONSTTABLE_STORAGE(int8_t) KICK001_DATA []  =
        {-1,-1,0,0,-1,-1,3,3,25,26,41,42,45,47,37,38,18,19,-8,-8,-35,-36,-54,-56,-62,-63,-54,-55,-33,-34,-4,-4,27,28,54,55,69,72,72,75,62,64,40,41,11,12,-19,-19,-45,-47,-64,-65,-71,-73,-66,-68,-51,-53,-29,-30,-2,-2,25,26,49,50,65,67,74,76,73,75,63,65,47,49,27,28,4,4,-18,-19,-37,-38,-52,-54,-61,-63,-64,-66,-62,-64,-54,-56,-43,-44,-29,-29,-13,-14,1,2,15,16,27,28,36,37,42,43,45,46,45,46,43,44,38,40,33,34,26,26,18,19,11,11,3,3,-4,-4,-10,-10,-15,-16,-20,-20,-24,-24,-26,-27,-28,-29,-29,-30,-29,-30,-29,-30,-28,-29,-26,-27,-24,-25,-22,-23,-20,-20,-17,-17,-14,-14,-11,-11,-8,-8,-5,-6,-3,-3,0,0,2,2,5,5,7,7,8,9,10,10,11,12,12,13,13,14,14,15,15,15,15,15,15,16,15,16,15,16,15,15,14,15,14,14,13,14,13,13,12,12,11,12,10,11,9,10,8,9,7,7,6,6,5,5,3,4,2,2,1,1,-1,-1,-2,-2,-4,-4,-6,-6,-7,-7,-9,-9,-11,-11,-12,-13,-14,-14,-16,-16,-17,-18,-19,-19,-20,-21,-22,-22,-23,-24,-24,-25,-26,-26,-27,-27,-28,-28,-28,-29,-29,-30,-30,-30,-30,-31,-30,-31,-30,-31,-30,-31,-30,-30,-29,-30,-28,-29,-27,-28,-26,-27,-25,-26,-24,-24,-22,-23,-20,-21,-19,-19,-17,-17,-15,-15,-12,-13,-10,-10,-8,-8,-5,-5,-3,-3,0,0,2,3,5,5,8,8,10,11,13,13,15,16,18,18,20,21,23,23,25,26,27,28,29,30,31,32,33,34,35,36,37,38,38,39,39,41,41,42,42,43,42,44,43,44,44,45,44,45,44,46,44,46,44,45,44,45,43,44,42,44,42,43,41,42,39,41,38,39,37,38,35,36,33,34,31,32,29,30,27,28,25,26,23,24,20,21,18,19,15,16,13,13,10,10,7,8,4,5,2,2,-1,-1,-4,-4,-7,-7,-10,-10,-13,-13,-16,-16,-18,-19,-21,-22,-24,-24,-26,-27,-29,-30,-32,-32,-34,-35,-36,-37,-39,-40,-41,-42,-43,-44,-45,-46,-47,-48,-49,-50,-50,-52,-52,-53,-53,-55,-54,-56,-55,-57,-56,-58,-57,-59,-58,-60,-58,-60,-59,-61,-59,-61,-59,-61,-59,-61,-59,-61,-59,-60,-58,-60,-58,-59,-57,-59,-56,-58,-55,-57,-54,-55,-52,-54,-51,-53,-50,-51,-48,-49,-46,-47,-44,-46,-42,-43,-40,-41,-38,-39,-36,-37,-33,-34,-31,-32,-28,-29,-26,-27,-23,-24,-21,-21,-18,-18,-15,-15,-12,-13,-9,-10,-6,-7,-4,-4,-1,-1,2,2,5,5,8,8,11,11,14,14,17,17,19,20,22,23,25,26,28,29,30,31,33,34,35,36,38,39,40,41,42,44,45,46,47,48,49,50,51,52,52,54,54,56,56,57,57,59,58,60,60,62,61,63,62,64,63,65,64,66,64,66,65,67,65,67,65,67,66,68,66,68,65,67,65,67,65,67,64,66,64,66,63,65,62,64,61,63,60,62,59,61,58,59,56,58,55,56,53,55,51,53,49,51,48,49,45,47,43,45,41,43,39,40,37,38,34,35,32,33,29,30,27,28,24,25,22,22,19,19,16,17,13,14,11,11,8,8,5,5,2,2,-1,-1,-3,-3,-6,-6,-9,-9,-12,-12,-14,-15,-17,-18,-20,-20,-22,-23,-25,-26,-28,-28,-30,-31,-32,-33,-35,-36,-37,-38,-39,-40,-41,-43,-44,-45,-46,-47,-47,-49,-49,-51,-51,-52,-53,-54,-54,-56,-56,-57,-57,-59,-58,-60,-59,-61,-60,-62,-61,-63,-62,-64,-63,-64,-63,-65,-64,-65,-64,-66,-64,-66,-64,-66,-64,-66,-64,-66,-64,-66,-63,-65,-63,-65,-62,-64,-62,-63,-61,-63,-60,-62,-59,-61,-58,-59,-57,-58,-55,-57,-54,-55,-52,-54,-51,-52,-49,-50,-47,-49,-45,-47,-43,-45,-42,-43,-39,-41,-37,-38,-35,-36,-33,-34,-31,-32,-28,-29,-26,-27,-24,-24,-21,-22,-19,-19,-16,-17,-14,-14,-11,-11,-8,-9,-6,-6,-3,-3,-1,-1,2,2,4,4,7,7,9,10,12,12,14,15,16,17,19,19,21,22,23,24,26,26,28,29,30,31,32,33,34,35,36,37,37,39,39,40,41,42,42,44,44,45,45,47,47,48,48,49,49,51,50,52,51,53,52,53,53,54,53,55,54,55,54,56,54,56,55,56,55,57,55,57,55,56,55,56,54,56,54,56,53,55,53,54,52,54,51,53,50,52,49,51,48,50,47,49,46,47,45,46,43,45,42,43,40,42,39,40,37,38,35,36,33,35,32,33,30,31,28,29,26,27,24,24,22,22,20,20,17,18,15,16,13,13,11,11,9,9,6,7,4,4,2,2,0,0,-3,-3,-5,-5,-7,-7,-9,-9,-11,-12,-13,-14,-16,-16,-18,-18,-20,-20,-22,-22,-24,-24,-25,-26,-27,-28,-29,-30,-31,-32,-32,-33,-34,-35,-35,-36,-37,-38,-38,-39,-40,-41,-41,-42,-42,-43,-43,-44,-44,-45,-45,-46,-46,-47,-46,-48,-47,-48,-47,-49,-48,-49,-48,-50,-48,-50,-49,-50,-49,-50,-49,-50,-49,-50,-48,-50,-48,-50,-48,-49,-47,-49,-47,-48,-46,-47,-45,-47,-45,-46,-44,-45,-43,-44,-42,-43,-41,-42,-39,-41,-38,-39,-37,-38,-36,-37,-34,-35,-33,-34,-31,-32,-29,-30,-28,-29,-26,-27,-24,-25,-23,-23,-21,-21,-19,-20,-17,-18,-15,-16,-13,-14,-11,-12,-9,-10,-7,-8,-5,-6,-4,-4,-2,-2,0,0,2,2,4,4,6,6,8,8,10,10,12,12,14,14,15,16,17,18,19,20,21,21,22,23,24,25,25,26,27,28,28,29,30,31,31,32,32,33,33,34,34,36,36,37,36,38,37,39,38,39,39,40,40,41,40,41,41,42,41,42,41,43,42,43,42,43,42,43,42,43,42,43,42,43,42,43,41,43,41,42,41,42,40,41,40,41,39,40,38,39,37,39,37,38,36,37,35,36,34,35,32,33,31,32,30,31,29,30,27,28,26,27,25,25,23,24,22,22,20,21,18,19,17,17,15,16,14,14,12,12,10,11,8,9,7,7,5,5,3,3,2,2,0,0,-2,-2,-4,-4,-5,-5,-7,-7,-9,-9,-10,-11,-12,-12,-14,-14,-15,-16,-17,-17,-18,-19,-20,-20,-21,-22,-22,-23,-24,-24,-25,-26,-26,-27,-28,-28,-29,-29,-30,-31,-31,-32,-32,-33,-33,-34,-33,-34,-34,-35,-35,-36,-36,-37,-36,-37,-37,-38,-37,-38,-37,-38,-38,-39,-38,-39,-38,-39,-38,-39,-38,-39,-38,-39,-38,-39,-38,-39,-38,-39,-37,-38,-37,-38,-36,-37,-36,-37,-35,-36,-35,-36,-34,-35,-33,-34,-32,-33,-31,-32,-30,-31,-29,-30,-28,-29,-27,-28,-26,-27,-25,-26,-24,-24,-22,-23,-21,-22,-20,-20,-19,-19,-17,-18,-16,-16,-14,-15,-13,-13,-11,-12,-10,-10,-8,-9,-7,-7,-5,-5,-4,-4,-2,-2,-1,-1,1,1,2,2,4,4,5,5,7,7,8,8,9,10,11,11,12,13,14,14,15,15,16,17,17,18,19,19,20,20,21,22,22,23,23,24,24,25,25,26,26,27,27,27,27,28,28,29,29,30,29,30,30,31,30,31,31,32,31,32,31,32,32,33,32,33,32,33,32,33,32,33,32,33,32,33,32,33,31,32,31,32,31,32,30,31,30,31,29,30,29,30,28,29,27,28,27,28,26,27,25,26,24,25,23,24,22,23,21,22,20,21,19,20,18,19,17,18,16,16,15,15,14,14,12,13,11,11,10,10,9,9,7,8,6,6,5,5,3,4,2,2,1,1,-1,-1,-2,-2,-3,-3,-4,-4,-6,-6,-7,-7,-8,-8,-9,-10,-11,-11,-12,-12,-13,-13,-14,-14,-15,-15,-16,-17,-17,-18,-18,-19,-19,-20,-20,-21,-21,-21,-22,-22,-22,-23,-23,-24,-24,-25,-25,-25,-25,-26,-26,-26,-26,-27,-27,-27,-27,-28,-27,-28,-28,-28,-28,-29,-28,-29,-28,-29,-28,-29,-28,-29,-28,-29,-28,-29,-28,-29,-28,-29,-28,-29,-28,-28,-27,-28,-27,-28,-26,-27,-26,-27,-26,-26,-25,-26,-24,-25,-24,-24,-23,-24,-22,-23,-22,-22,-21,-21,-20,-21,-19,-20,-18,-19,-17,-18,-16,-17,-15,-16,-14,-15,-13,-14,-12,-13,-11,-12,-10,-11,-9,-9,-8,-8,-7,-7,-6,-6,-5,-5,-4,-4,-3,-3,-2,-2,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,14,15,15,16,16,17,17,17,17,18,18,19,19,19,19,20,20,21,20,21,21,21,21,22,22,22,22,23,22,23,22,23,23,23,23,24,23,24,23,24,23,24,23,24,23,24,23,24,23,23,22,23,22,23,22,23,22,22,21,22,21,22,20,21,20,21,19,20,19,20,18,19,18,18,17,18,16,17,16,16,15,16,14,15,13,14,13,13,12,12,11,11,10,11,9,10,8,9,8,8,7,7,6,6,5,5,4,4,3,3,2,2,1,1,0,0,-1,-1,-2,-2,-3,-3,-4,-4,-4,-5,-5,-5,-6,-6,-7,-7,-8,-8,-9,-9,-10,-10,-10,-11,-11,-11,-12,-12,-13,-13,-13,-14,-14,-14,-15,-15,-15,-16,-16,-16,-16,-17,-17,-17,-17,-18,-18,-18,-18,-19,-18,-19,-19,-19,-19,-20,-19,-20,-20,-20,-20,-20,-20,-21,-20,-21,-20,-21,-20,-21,-20,-21,-20,-21,-20,-21,-20,-21,-20,-20,-20,-20,-20,-20,-19,-20,-19,-20,-19,-19,-18,-19,-18,-19,-18,-18,-17,-18,-17,-17,-16,-17,-16,-16,-15,-16,-15,-15,-14,-14,-13,-14,-13,-13,-12,-13,-12,-12,-11,-11,-10,-10,-9,-10,-9,-9,-8,-8,-7,-7,-6,-7,-6,-6,-5,-5,-4,-4,-3,-3,-3,-3,-2,-2,-1,-1,0,0,0,0,1,1,2,2,3,3,3,4,4,4,5,5,6,6,6,6,7,7,8,8,8,8,9,9,9,10,10,10,10,11,11,11,11,12,12,12,12,13,13,13,13,14,14,14,14,14,14,15,14,15,15,15,15,15,15,16,15,16,15,16,15,16,15,16,16,16,16,16,16,16,15,16,15,16,15,16,15,16,15,15,15,15,15,15,14,15,14,14,14,14,13,14,13,13,13,13,12,13,12,12,11,12,11,11,10,11,10,10,9,10,9,9,8,9,8,8,7,7,7,7,6,6,5,6,5,5,4,4,4,4,3,3,2,3,2,2,1,1,1,1,0,0,-1,-1,-1,-1,-2,-2,-3,-3,-3,-3,-4,-4,-4,-4,-5,-5,-5,-6,-6,-6,-7,-7,-7,-7,-8,-8,-8,-8,-9,-9,-9,-9,-9,-10,-10,-10,-10,-10,-11,-11,-11,-11,-11,-12,-12,-12,-12,-12,-12,-12,-12,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-14,-13,-14,-13,-14,-13,-14,-13,-14,-13,-14,-13,-14,-13,-14,-13,-14,-13,-14,-13,-13,-13,-13,-13,-13,-13,-13,-12,-13,-12,-13,-12,-12,-12,-12,-11,-12,-11,-11,-11,-11,-10,-11,-10,-10,-10,-10,-9,-10,-9,-9,-9,-9,-8,-8,-8,-8,-7,-7,-7,-7,-6,-6,-6,-6,-5,-5,-5,-5,-4,-4,-4,-4,-3,-3,-3,-3,-2,-2,-2,-2,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,2,2,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,8,8,9,8,9,9,9,9,9,9,9,9,9,9,10,9,10,9,10,9,10,9,10,9,10,9,10,9,10,9,10,9,10,9,10,9,10,9,9,9,9,9,9,9,9,8,9,8,9,8,8,8,8,8,8,7,8,7,7,7,7,7,7,6,6,6,6,6,6,5,6,5,5,5,5,4,4,4,4,4,4,3,3,3,3,2,3,2,2,2,2,1,1,1,1,1,1,0,0,0,0,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-2,-3,-3,-3,-3,-3,-3,-4,-4,-4,-4,-4,-4,-5,-5,-5,-5,-5,-5,-5,-6,-6,-6,-6,-6,-6,-6,-6,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-7,-8,-7,-8,-7,-7,-7,-7,-7,-7,-7,-7,-7,-7,-6,-6,-6,-6,-6,-6,-6,-6,-5,-6,-5,-5,-5,-5,-5,-5,-4,-5,-4,-4,-4,-4,-4,-4,-3,-3,-3,-3,-3,-3,-3,-3,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,4,5,4,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,4,3,3,3,3,3,3,3,3,3,3,2,3,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-4,-3,-4,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,0,0,0,-1,0,0,0,-1,0,0,0,-1,0,-1,0,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
#endif