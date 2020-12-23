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


Ornament::Ornament(int data_pin, Logger* _logger, bool autoInit) {
  logger = _logger;
  loggerOnline = true;
  data_pin = data_pin;
  _leds = Adafruit_NeoPixel(led_count, data_pin, NEO_GRB + NEO_KHZ800);
  if (autoInit) {
    init();
  }
}

Ornament::Ornament(int data_pin, Logger* _logger) {
  Ornament(data_pin, _logger, false);
}

Ornament::Ornament(int data_pin, OfflineLogger* _oLogger, bool autoInit) {
  oLogger = _oLogger;
  loggerOnline = false;
  data_pin = data_pin;
  _leds = Adafruit_NeoPixel(led_count, data_pin, NEO_GRB + NEO_KHZ800);
  if (autoInit) {
    init();
  }
}

Ornament::Ornament(int data_pin, OfflineLogger* _oLogger) {
  Ornament(data_pin, _oLogger, false);
}

void Ornament::init() {
  _leds.begin();
}

void Ornament::off() {
  log("[INFO] Turning off LEDs");
  _leds.fill();
  _leds.show();
}

void Ornament::on() {
  log("[INFO] Turning on LEDs");
  _leds.show();
}

void Ornament::on(int c) {
  log("[INFO] Turning on LEDs to color " + c);
  _leds.fill(c);
  _leds.show();
}

void Ornament::on(int c, int b) {
  log("[INFO] Turning on LEDs to color " + String(c) + " at " + b + "%");
  _leds.fill(c);
  _leds.setBrightness(b);
  _leds.show();
}

void Ornament::log(String message) {
  if (loggerOnline) {
    logger->log(message);
  } else {
    oLogger->log(message);
  }
}

void Ornament::log(double message) {
  log(String(message));
}

void Ornament::set_color(int c) {
  on(c);
}

void Ornament::set_brightness(int b) {
  log("[INFO] Setting LED brightness to " + String(b) + "%");
  _leds.setBrightness(b);
  _leds.show();
}

void Ornament::blink(int n, int c) {
  log("[INFO] Blinking LEDs");
  int i = 0;

  // first, lear the LEDs
  // log("eh?");
  _leds.fill();
  // log("eh?");
  _leds.show();
  // log("eh?");
  
  while (i < n) {
    i++;
    log("[INFO] blink!");
    _leds.fill(c);
    _leds.show();
    delay(100);
    _leds.fill();
    _leds.show();
    delay(100);
  }
}

void Ornament::blink(int n) {
  log("[INFO] Blinking LEDs");
  blink(n, c_white);
}

void Ornament::blink() {
  log("[INFO] Blinking LEDs");
  blink(1, c_white);
}

void Ornament::success_blink() {
  log("[INFO] Success blink");
  blink(3, c_green);
}

void Ornament::error_blink() {
  log("[INFO] Error blink");
  blink(3, c_red);
}

void Ornament::info_blink() {
  log("[INFO] Info blink");
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
  log("[INFO] XMAS Mode!");
  alternate_every_other(c_red, c_green);
}

void Ornament::jmas() {
  log("[INFO] JMAS Mode!");
  alternate_every_other(c_white, c_blue);
}

void Ornament::breathe() {
  log("[INFO] Breathing!");
  for (int i = 0; i < 10; i++) {
    if (i%2 != 0) {
      log("[INFO] breathing in...");
      for (float j = 0; j < 1; j += .05) {
        float v = ease.easeInOut(j) * 255;
        log("[INFO] Step " + String(j) + " " + String(v));
        _leds.setBrightness((int) v);
        _leds.show();
        delay(100);
      }
    } else {
      // breathe out
      log("[INFO] breathing out...");
      for (float j = 1; j > 0; j -= .05) {
        float v = ease.easeInOut(j) * 255;
        log("[INFO] Step " + String(j) + " " + String(v));
        _leds.setBrightness((int) v);
        _leds.show();
        delay(100);
      }
    }
  }
}

// void Ornament::spin() {
//   log("[INFO] Spinning!");
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

