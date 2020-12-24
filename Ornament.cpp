/*
  Ornament.cpp - IoT LED Ornament
  Michael Hotwagner
  mhotwagner@gmail.com
  Released into the public domain.
*/

#include "Arduino.h"
#include "Ornament.h"
#include "Logger.h"

#include <Easing.h>
#include <Adafruit_NeoPixel.h>

const int Ornament::led_count = 6;

const int Ornament::c_red = Adafruit_NeoPixel::Color(0, 255, 0);
const int Ornament::c_green = Adafruit_NeoPixel::Color(255, 0, 0);
const int Ornament::c_blue =  Adafruit_NeoPixel::Color(0, 0, 255);
const int Ornament::c_yellow = Adafruit_NeoPixel::Color(255, 255, 0);
const int Ornament::c_white = Adafruit_NeoPixel::Color(255, 255, 255);

const int Ornament::c_white_100 = Adafruit_NeoPixel::Color(255, 255, 255);
const int Ornament::c_white_75 = Adafruit_NeoPixel::Color(191, 191, 191);
const int Ornament::c_white_50 = Adafruit_NeoPixel::Color(255, 255, 127);
const int Ornament::c_white_25 = Adafruit_NeoPixel::Color(63, 63, 63);

Ornament::Ornament(int data_pin, Logger* _logger, bool autoInit, int logLevel) {
  logger = _logger;
  _logLevel = logLevel;
  data_pin = data_pin;
  _leds = Adafruit_NeoPixel(led_count, data_pin, NEO_GRB + NEO_KHZ800);
  if (autoInit) {
    init();
  }
}

Ornament::Ornament(int data_pin, Logger* _logger, bool autoInit) {
  logger = _logger;
  _logLevel = logger->INFO;
  data_pin = data_pin;
  _leds = Adafruit_NeoPixel(led_count, data_pin, NEO_GRB + NEO_KHZ800);
  if (autoInit) {
    init();
  }
}

Ornament::Ornament(int data_pin, Logger* _logger) {
  Ornament(data_pin, _logger, false);
}

void Ornament::init() {
  _leds.begin();
}

void Ornament::off() {
  logger->log("Turning off LEDs", _logLevel);
  _leds.fill();
  _leds.show();
}

void Ornament::on() {
  logger->log("Turning on LEDs", _logLevel);
  _leds.show();
}

void Ornament::on(int c) {
  logger->log("Turning on LEDs to color " + String(c), _logLevel);
  _leds.fill(c);
  _leds.show();
}

void Ornament::on(int c, int b) {
  logger->log("Turning on LEDs to color " + String(c) + " at " + b + "%", _logLevel);
  _leds.fill(c);
  _leds.setBrightness(b);
  _leds.show();
}

void Ornament::set_color(int c) {
  on(c);
}

void Ornament::set_brightness(int b) {
  logger->log("Setting LED brightness to " + String(b) + "%", _logLevel);
  _leds.setBrightness(b);
  _leds.show();
}

void Ornament::blink(int n, int c) {
  logger->log("Blinking LEDs", _logLevel);
  int i = 0;

  // first, lear the LEDs
  // logger->log("eh?", _logLevel);
  _leds.fill();
  // logger->log("eh?", _logLevel);
  _leds.show();
  // logger->log("eh?", _logLevel);
  
  while (i < n) {
    i++;
    logger->log("blink!", _logLevel);
    _leds.fill(c);
    _leds.show();
    delay(100);
    _leds.fill();
    _leds.show();
    delay(100);
  }
}

void Ornament::blink(int n) {
  logger->log("Blinking LEDs", _logLevel);
  blink(n, c_white);
}

void Ornament::blink() {
  logger->log("Blinking LEDs", _logLevel);
  blink(1, c_white);
}

void Ornament::success_blink() {
  logger->log("Success blink", _logLevel);
  blink(3, c_green);
}

void Ornament::error_blink() {
  logger->log("Error blink", _logLevel);
  blink(3, c_red);
}

void Ornament::info_blink() {
  logger->log("Info blink", _logLevel);
  blink(3, c_yellow);
}

void Ornament::every_other(int c_a, int c_b) {
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

void Ornament::alternate_every_other(int c_a, int c_b) {
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

void Ornament::xmas() {
  logger->log("XMAS Mode!", _logLevel);
  alternate_every_other(c_red, c_green);
}

void Ornament::jmas() {
  logger->log("JMAS Mode!", _logLevel);
  alternate_every_other(c_white, c_blue);
}

void Ornament::breathe() {
  logger->log("Breathing!", logger->ERROR);
  for (int i = 0; i < 10; i++) {
    if (i%2 != 0) {
      logger->log("breathing in...", logger->ERROR);
      for (float j = .2; j < .8; j += .05) {
        int v = (int) (ease.easeInOut(j) * 255);
        logger->log("Step " + String(j) + " " + String(v), logger->ERROR);
        _leds.setBrightness(v);
        _leds.show();
        delay(100);
      }
    } else {
      // breathe out
      logger->log("breathing out...", logger->ERROR);
      for (float j = .8; j > .2; j -= .05) {
        int v = (int) (ease.easeInOut(j) * 255);
        logger->log("Step " + String(j) + " " + String(v), logger->ERROR);
        _leds.setBrightness(v);
        _leds.show();
        delay(100);
      }
    }
  }
}

// void Ornament::spin() {
//   logger->log("Spinning!", _logLevel);
//   int i = 0;
//   while (i < 10) {
//     while (j < 6) {
//       if (i % 3 == 0) {
//         _leds.setPixelColor(i, c_white_75);
//       } else {
//         _leds.setPixelColor(i, c_white_25);
//       }

//     }
//     i++;
//   }
// }

