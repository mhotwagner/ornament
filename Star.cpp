/*
  Star.cpp - IoT LED Star
  Michael Hotwagner
  mhotwagner@gmail.com
  Released into the public domain.
*/

#include "Arduino.h"
#include "Star.h"
#include "Logger.h"

#include <Adafruit_NeoPixel.h>

const char* type = "star";

// Star::Star(int data_pin, Logger* _logger, bool autoInit, int logLevel) {
//   Ornament(data_pin, _logger, autoInit, logLevel);
// }

// Star::Star(int data_pin, Logger* _logger, bool autoInit) {
//   Ornament(data_pin, _logger, autoInit);
// }

// Star::Star(int data_pin, Logger* _logger) {
//   Star(data_pin, _logger, false);
// }