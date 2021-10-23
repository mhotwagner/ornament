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

Ornament::Ornament(int data_pin, int led_count, Logger* logger, bool auto_init, int log_level) {
  _data_pin = data_pin;
  _led_count = led_count;
  _logger = logger;
  _log_level = log_level;
  _data_pin = data_pin;
  _leds = Adafruit_NeoPixel(led_count, data_pin, NEO_GRB + NEO_KHZ800);
  if (auto_init) {
    init();
  }
}

Ornament::Ornament(int data_pin, int led_count, Logger* logger, bool auto_init) {
  _data_pin = data_pin;
  _led_count = led_count;
  _logger = logger;
  _log_level = _logger->DEBUG;
  _leds = Adafruit_NeoPixel(led_count, data_pin, NEO_GRB + NEO_KHZ800);
  if (auto_init) {
    init();
  }
}

Ornament::Ornament(int data_pin, int led_count, Logger* logger) {
  Ornament(data_pin, led_count, logger, false);
}

void Ornament::execute() {
  if (refTime && nextTime && millis() >= nextTime) next(*this);
}

void Ornament::init() {
  _leds.begin();
}

void Ornament::off() {
  _logger->log("Turning off LEDs", _log_level);
  _leds.fill();
  _leds.show();
}

void Ornament::on() {
  _logger->log("Turning on LEDs", _log_level);
  _leds.show();
}

void Ornament::on(int c) {
  _logger->log("Turning on LEDs to color " + String(c), _log_level);
  _leds.fill(c);
  _leds.show();
}

void Ornament::on(int c, int b) {
  _logger->log("Turning on LEDs to color " + String(c) + " at " + b + "%", _log_level);
  _leds.fill(c);
  _leds.setBrightness(b);
  _leds.show();
}

void Ornament::set_color(int c) {
  on(c);
}

void Ornament::set_brightness(int b) {
  _logger->log("Setting LED brightness to " + String(b) + "%", _log_level);
  _leds.setBrightness(b);
  _leds.show();
}

void Ornament::blink(int n, int c) {
  _logger->log("Blinking LEDs", _log_level);
  int i = 0;

  // first, lear the LEDs
  // _logger->log("eh?", _log_level);
  _leds.fill();
  // _logger->log("eh?", _log_level);
  _leds.show();
  // _logger->log("eh?", _log_level);
  
  while (i < n) {
    i++;
    _logger->log("blink!", _log_level);
    _leds.fill(c);
    _leds.show();
    delay(100);
    _leds.fill();
    _leds.show();
    delay(100);
  }
}

void Ornament::blink(int n) {
  _logger->log("Blinking LEDs", _log_level);
  blink(n, c_white);
}

void Ornament::blink() {
  _logger->log("Blinking LEDs", _log_level);
  blink(1, c_white);
}

void Ornament::success_blink() {
  _logger->log("Success blink", _log_level);
  blink(3, c_green);
}

void Ornament::error_blink() {
  _logger->log("Error blink", _log_level);
  blink(3, c_red);
}

void Ornament::info_blink() {
  _logger->log("Info blink", _log_level);
  blink(3, c_yellow);
}

void Ornament::info_blink(int n) {
  _logger->log("Info blink", _log_level);
  blink(n, c_yellow);
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
  _logger->log("XMAS Mode!", _log_level);
  alternate_every_other(c_red, c_green);
}

void Ornament::jmas() {
  refTime = 0;
  _logger->log("JMAS Mode!", _log_level);
  alternate_every_other(c_white, c_blue);
}

// void Ornament::breathe() {
//   _logger->log("Breathing!", _logger->ERROR);
//   for (int i = 0; i < 10; i++) {
//     if (i%2 != 0) {
//       _logger->log("breathing in...", _logger->ERROR);
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
//       _logger->log("breathing out...", _logger->ERROR);
//       for (float j = .8; j > .2; j -= .02) {
//         int v = (int) (ease.easeInOut(j) * 255);
//         // _logger->log("Step " + String(j) + " " + String(v));
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
  // _logger->log("Are we doing this?", _logger->ERROR);
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
    // ornament._logger->log(brightness);
    if (brightness != ornament._leds.getBrightness()) {
      ornament._leds.setBrightness(brightness);
      ornament._leds.show();
    }
    ornament.nextTime = millis() + ornament.offset;
  };
  refTime = millis();
  offset = 25;
  nextTime = refTime + offset;
  // _logger->log(nextTime); 
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
  _logger->log("breathing rainbow!", _logger->log_level);
  next = [](Ornament& ornament) {

    // ornament._logger->log("ORNAMENT STEP", ornament._logger->ERROR);
    // ornament._logger->log(ornament.refTime);
    unsigned long t = millis();
    // ornament._logger->log(t);
    unsigned long dt = t - ornament.refTime;
    // ornament._logger->log(dt);
    unsigned long step = dt / ornament.offset;
    // ornament._logger->log(step, ornament._logger->ERROR);
    
    int steps = 14; // 5% step

    // ornament._logger->log("STEP" + step);
    // ornament._logger->log(step, ornament._logger->ERROR);

    unsigned long cycle = step / steps;
    // ornament._logger->log(cycle, ornament._logger->ERROR);
    bool dir = !!(cycle % 2);
    // ornament._logger->log(dir ? "up" : "down", ornament._logger->ERROR);
    int db = (step % steps);
    int brightness;

    if (!dir) { // down, doesn't really mater which direction
      // ornament._logger->log("down", ornament._logger->ERROR);
      brightness = (int) (ornament.ease.easeInOut(0.8 - (db * .05)) * 255);
    } else {
      // ornament._logger->log("up", ornament._logger->ERROR);
      brightness = (int) (ornament.ease.easeInOut(0.1 + (db * .05)) * 255);
    }

    // ornament._logger->log(brightness, ornament._logger->ERROR);
    
    
    // if (brightness != ornament._leds.getBrightness()) {
      // ornament._logger->log("changing brightness");
      if ((step % 28) == 14) {
        // ornament._logger->log("XXX CHANGING COLOR", ornament._logger->ERROR);
        unsigned long rainbowOffset = cycle / 2;
        unsigned long rainbowStart = rainbowOffset % 6;
        // ornament._logger->log(rainbowOffset, ornament._logger->ERROR);
        for (int i = 0; i < 6; i++) {
          int j = i + (int) rainbowStart;
          if (j >= 6) j -= 6;
          // ornament._logger->log(j, ornament._logger->ERROR);
          // uint32_t rc = ornament.getRainbowColor((int) j);
          // ornament._logger->log("COLOR");
          // ornament._logger->log(rc, ornament._logger->ERROR);
    
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
//   _logger->log("Spinning!", _log_level);
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

