/*
  Star.h - IoT LED Ornament
  Michael Hotwagner
  mhotwagner@gmail.com
  Released into the public domain.
*/
#ifndef Star_h
#define Star_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <Ornament.h>

class Star : public Ornament {
  public:
    // Star(int data_pin);
    // Star(int data_pin, bool auto_init);

    void every_other(int c_a, int c_b);
    void alternate_every_other(int c_a, int c_b);

    void xmas();
    void jmas();

    void spin();
};
#endif