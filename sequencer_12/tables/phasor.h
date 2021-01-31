#ifndef PHASOR_TABLE_H_
#define PHASOR_TABLE_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "mozzi_pgmspace.h"

#define PHASOR_NUM_CELLS 8192
#define PHASOR_SAMPLERATE 8192

CONSTTABLE_STORAGE(int8_t) PHASOR_DATA []  =
        {-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-128,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-127,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-126,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-124,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-122,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-120,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-118,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-116,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-115,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-113,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-111,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-110,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-108,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-106,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-105,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-103,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-101,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-99,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-97,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-95,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-93,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-91,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-89,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-87,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-85,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-84,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-83,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-82,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-80,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-79,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-78,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-77,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-76,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-74,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-72,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-70,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-69,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-67,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-65,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-63,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-62,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-61,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-60,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-58,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-57,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-56,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-55,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-54,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-52,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-51,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-49,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-47,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-46,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-45,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-43,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-41,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-39,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-37,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-35,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-34,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-33,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-31,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-29,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-27,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-26,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-24,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-22,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-21,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-19,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-18,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-16,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-14,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-13,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-11,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-9,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-8,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,31,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,35,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,37,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,39,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,41,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,43,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,47,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,49,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,57,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,59,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,61,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,63,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,65,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,69,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,71,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,82,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,84,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,86,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,88,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,91,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,92,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,93,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,94,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,96,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,98,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,125,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126,126};
#endif