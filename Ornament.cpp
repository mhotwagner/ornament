/*
  Ornament.cpp - IoT LED Ornament
  Michael Hotwagner
  mhotwagner@gmail.com
  Released into the public domain.
*/

#include "Arduino.h"
#include "Ornament.h"

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


Ornament::Ornament(int data_pin) {
  data_pin = data_pin;
  _leds = Adafruit_NeoPixel(led_count, data_pin, NEO_GRB + NEO_KHZ800);
}

Ornament::Ornament(int data_pin, bool auto_init) {
  data_pin = data_pin;
  _leds = Adafruit_NeoPixel(led_count, data_pin, NEO_GRB + NEO_KHZ800);
  if (auto_init) {
    init();
  }
}

char* get_type() {
  return _type;
};

void Ornament::init() {
  Serial.println("[INFO] Initializing Ornament");
  _leds.begin();
  success_blink();
}

void Ornament::off() {
  Serial.println("[INFO] Turning off LEDs");
  _leds.fill();
  _leds.show();
}

void Ornament::on() {
  Serial.println("[INFO] Turning on LEDs");
  Serial.println("(maybe, honestly it depends on what's in there)");
  _leds.show();
}

void Ornament::on(int c) {
  Serial.print("[Turning on LEDs to color ");
  Serial.println(c);
  _leds.fill(c);
  _leds.show();
}

void Ornament::on(int c, int b) {
  Serial.print("[INFO] Turning on LEDs to color ");
  Serial.print(c);
  Serial.print(" at ");
  Serial.print(b);
  Serial.println("% brightness");
  _leds.fill(c);
  _leds.setBrightness(b);
  _leds.show();
}

void Ornament::set_color(int c) {
  on(c);
}

void Ornament::set_brightness(int b) {
  Serial.print("[INFO] Setting LED brightness to ");
  Serial.print(b);
  Serial.println("%");
  _leds.setBrightness(b);
  _leds.show();
}

void Ornament::blink(int n, int c) {
  Serial.println("[INFO] Blinking LEDs");
  int i = 0;

  // first, clear the LEDs
  _leds.fill();
  _leds.show();
  
  while (i < n) {
    i++;
    Serial.println("[INFO] blink!");
    _leds.fill(c);
    _leds.show();
    delay(100);
    _leds.fill();
    _leds.show();
    delay(100);
  }
}

void Ornament::blink(int n) {
  Serial.println("[INFO] Blinking LEDs");
  blink(n, c_white);
}

void Ornament::blink() {
  Serial.println("[INFO] Blinking LEDs");
  blink(1, c_white);
}

void Ornament::success_blink() {
  Serial.println("[INFO] Success blink");
  blink(3, c_green);
}

void Ornament::error_blink() {
  Serial.println("[INFO] Error blink");
  blink(3, c_red);
}

void Ornament::info_blink() {
  Serial.println("[INFO] Info blink");
  blink(3, c_yellow);
}

// void Ornament::spin() {
//   Serial.println("[INFO] Spinning!");
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

