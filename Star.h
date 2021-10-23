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
    Star(int data_pin, Logger* logger, bool auto_init, int log_level)
      : Ornament(data_pin, 6, logger, auto_init, log_level)
      {};
    Star(int data_pin, Logger* logger, bool auto_init)
      : Ornament(data_pin, 6, logger, auto_init)
      {};
    Star(int data_pin, Logger* logger)
      : Ornament(data_pin, 6, logger)
      {};
};
#endif