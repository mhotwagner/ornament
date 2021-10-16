/*
  Star.h - IoT LED Ornament
  Michael Hotwagner
  mhotwagner@gmail.com
  Released into the public domain.
*/
#ifndef Star_h
#define Star_h

#include "Arduino.h"

#include <Ornament.h>
#include <Logger.h>
#include <Easing.h>
#include <Adafruit_NeoPixel.h>

class Star : public Ornament {
  public:
    Star(int data_pin, Logger* _logger, bool autoInit, int logLevel)
      : Ornament(data_pin, _logger, autoInit, logLevel)
      {};
    Star(int data_pin, Logger* _logger, bool autoInit)
      : Ornament(data_pin, _logger, autoInit)
      {};
    Star(int data_pin, Logger* _logger)
      : Ornament(data_pin, _logger)
      {};
};
#endif