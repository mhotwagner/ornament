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

const uint32_t Ornament::c_red = Adafruit_NeoPixel::Color(0, 255, 0);
const uint32_t Ornament::c_green = Adafruit_NeoPixel::Color(255, 0, 0);
const uint32_t Ornament::c_blue =  Adafruit_NeoPixel::Color(0, 0, 255);

const uint32_t Ornament::c_yellow = Adafruit_NeoPixel::Color(255, 255, 0);
const uint32_t Ornament::c_purple = Adafruit_NeoPixel::Color(0, 255, 255);
const uint32_t Ornament::c_teal = Adafruit_NeoPixel::Color(255, 0, 255);


const uint32_t Ornament::c_white = Adafruit_NeoPixel::Color(255, 255, 255);

const uint32_t Ornament::c_white_100 = Adafruit_NeoPixel::Color(255, 255, 255);
const uint32_t Ornament::c_white_75 = Adafruit_NeoPixel::Color(191, 191, 191);
const uint32_t Ornament::c_white_50 = Adafruit_NeoPixel::Color(255, 255, 127);
const uint32_t Ornament::c_white_25 = Adafruit_NeoPixel::Color(63, 63, 63);

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

void Ornament::execute() {
  if (refTime && nextTime && millis() >= nextTime) next(*this);
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
  refTime = 0;
  logger->log("XMAS Mode!", _logLevel);
  alternate_every_other(c_red, c_green);
}

void Ornament::jmas() {
  refTime = 0;
  logger->log("JMAS Mode!", _logLevel);
  alternate_every_other(c_white, c_blue);
}

// void Ornament::breathe() {
//   logger->log("Breathing!", logger->ERROR);
//   for (int i = 0; i < 10; i++) {
//     if (i%2 != 0) {
//       logger->log("breathing in...", logger->ERROR);
//       for (float j = .2; j < .8; j += .02) {
//         int v = (int) (ease.easeInOut(j) * 255);
//         if (v != _leds.getBrightness()) {
//           _leds.setBrightness(v);
//           _leds.show();
//         }
//         delay(25);
//       }
//     } else {
//       // breathe out
//       logger->log("breathing out...", logger->ERROR);
//       for (float j = .8; j > .2; j -= .02) {
//         int v = (int) (ease.easeInOut(j) * 255);
//         // logger->log("Step " + String(j) + " " + String(v));
//         if (v != _leds.getBrightness()) {
//           _leds.setBrightness(v);
//           _leds.show();
//         }
//         delay(25);
//       }
//     }
//   }
// }

void Ornament::breathe() {
  // logger->log("Are we doing this?", logger->ERROR);
  next = [](Ornament& ornament) {
    int dt = millis() - ornament.refTime;
    int step = dt / ornament.offset;
    int steps = 12; // 5% step

    int dir = (step / steps) % 2;
    int db = (step % steps);
    int brightness;

    if (dir) { // down, doesn't really mater which direction
      brightness = (int) (ornament.ease.easeInOut(0.8 - (db * .05)) * 255);
    } else {
      brightness = (int) (ornament.ease.easeInOut(0.2 + (db * .05)) * 255);
    }
    // ornament.logger->log(brightness);
    if (brightness != ornament._leds.getBrightness()) {
      ornament._leds.setBrightness(brightness);
      ornament._leds.show();
    }
    ornament.nextTime = millis() + ornament.offset;
  };
  refTime = millis();
  offset = 25;
  nextTime = refTime + offset;
  // logger->log(nextTime); 
}

uint32_t Ornament::getRainbowColor(int n) {
  switch (n) {
    case 0:
      return c_green;
    case 1:
      return c_yellow;
    case 2:
      return c_red;
    case 3:
      return c_purple;
    case 4:
      return c_blue;
    case 5:
     return c_teal;
  }
}

void Ornament::breathingRainbow() {
  logger->log("breathing rainbow!", logger->ERROR);
  next = [](Ornament& ornament) {

    // ornament.logger->log("ORNAMENT STEP", ornament.logger->ERROR);
    // ornament.logger->log(ornament.refTime);
    unsigned long t = millis();
    // ornament.logger->log(t);
    unsigned long dt = t - ornament.refTime;
    // ornament.logger->log(dt);
    unsigned long step = dt / ornament.offset;
    // ornament.logger->log(step, ornament.logger->ERROR);
    
    int steps = 14; // 5% step

    // ornament.logger->log("STEP" + step);
    // ornament.logger->log(step, ornament.logger->ERROR);

    unsigned long cycle = step / steps;
    // ornament.logger->log(cycle, ornament.logger->ERROR);
    bool dir = !!(cycle % 2);
    // ornament.logger->log(dir ? "up" : "down", ornament.logger->ERROR);
    int db = (step % steps);
    int brightness;

    if (!dir) { // down, doesn't really mater which direction
      // ornament.logger->log("down", ornament.logger->ERROR);
      brightness = (int) (ornament.ease.easeInOut(0.8 - (db * .05)) * 255);
    } else {
      // ornament.logger->log("up", ornament.logger->ERROR);
      brightness = (int) (ornament.ease.easeInOut(0.1 + (db * .05)) * 255);
    }

    // ornament.logger->log(brightness, ornament.logger->ERROR);
    
    
    // if (brightness != ornament._leds.getBrightness()) {
      // ornament.logger->log("changing brightness");
      if ((step % 28) == 14) {
        // ornament.logger->log("XXX CHANGING COLOR", ornament.logger->ERROR);
        unsigned long rainbowOffset = cycle / 2;
        unsigned long rainbowStart = rainbowOffset % 6;
        // ornament.logger->log(rainbowOffset, ornament.logger->ERROR);
        for (int i = 0; i < 6; i++) {
          int j = i + (int) rainbowStart;
          if (j >= 6) j -= 6;
          // ornament.logger->log(j, ornament.logger->ERROR);
          // uint32_t rc = ornament.getRainbowColor((int) j);
          // ornament.logger->log("COLOR");
          // ornament.logger->log(rc, ornament.logger->ERROR);
    
          ornament._leds.setPixelColor(i, ornament.getRainbowColor(j));
        }
      }
      ornament._leds.setBrightness(brightness);
      ornament._leds.show();
    // }
    ornament.nextTime = t + ornament.offset;
  };
  refTime = millis();
  offset = 50;
  nextTime = refTime + offset;
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

