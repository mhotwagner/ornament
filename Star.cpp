/*
  Star.cpp - IoT LED Star
  Michael Hotwagner
  mhotwagner@gmail.com
  Released into the public domain.
*/

#include "Arduino.h"
#include "Star.h"

#include <Adafruit_NeoPixel.h>

// Star(int data_pin);

// Star(int data_pin, bool auto_init);

const string char* = "star";

void Star::every_other(int c_a, int c_b) {
  int i = 0;
  while (i < 6) {
    if (i % 2 == 0) {
      _leds.setPixelColor(i, c_a);
    } else {
      _leds.setPixelColor(i, c_b);
    }
    i++;
  }
  _leds.show();
}

void Star::alternate_every_other(int c_a, int c_b) {
  int i = 0;
  while (i < 10) {
    // c_a first
    every_other(c_a, c_b);
    delay(500);    
    // c_b first
    every_other(c_b, c_a);
    delay(500);
    i++;
  }
  _leds.fill();
  _leds.show();
}

void Star::xmas() {
  Serial.println("[INFO] XMAS Mode!");
  alternate_every_other(c_red, c_green);
}

void Star::jmas() {
  Serial.println("[INFO] JMAS Mode!");
  alternate_every_other(c_white, c_blue);
}