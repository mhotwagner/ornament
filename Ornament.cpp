/*
  Ornament.cpp - IoT LED Ornament
  Michael Hotwagner
  mhotwagner@gmail.com
  Released into the public domain.
*/

#include "Arduino.h"
#include "Ornament.h"

#include <Adafruit_NeoPixel.h>

const int Ornament::c_red = Adafruit_NeoPixel::Color(0, 255, 0);
const int Ornament::c_green = Adafruit_NeoPixel::Color(255, 0, 0);
const int Ornament::c_blue =  Adafruit_NeoPixel::Color(0, 0, 255);
const int Ornament::c_yellow = Adafruit_NeoPixel::Color(255, 255, 0);
const int Ornament::c_white = Adafruit_NeoPixel::Color(255, 255, 255);

Ornament::Ornament(Adafruit_NeoPixel *leds) {
  _leds = leds;
}

void Ornament::init() {
  _leds->begin();
  successBlink();
}

void Ornament::off() {
  Serial.println("[INFO] Turning off LEDs");
  _leds->fill();
  _leds->show();
}

void Ornament::on() {
  Serial.println("[INFO] Turning on LEDs");
  Serial.println("(maybe, honestly it depends on what's in there)");
  _leds->show();
}

void Ornament::on(int c) {
  Serial.print("[Turning on LEDs to color ");
  Serial.println(c);
  _leds->fill(c);
  _leds->show();
}

void Ornament::on(int c, int b) {
  Serial.print("[INFO] Turning on LEDs to color ");
  Serial.print(c);
  Serial.print(" at ");
  Serial.print(b);
  Serial.println("% brightness");
  _leds->fill(c);
  _leds->setBrightness(b);
  _leds->show();
}

void Ornament::setColor(int c) {
  on(c);
}

void Ornament::setBrightness(int b) {
  Serial.print("[INFO] Setting LED brightness to ");
  Serial.print(b);
  Serial.println("%");
  _leds->setBrightness(b);
  _leds->show();
}

void Ornament::blink(int n, int c) {
  Serial.print("[INFO] Blinking LEDs at color ");
  Serial.println(c);
  int i = 0;

  // first, clear the LEDs
  _leds->fill();
  _leds->show();
  
  while (i < n) {
    i++;
    Serial.println("[INFO] blink!");
    _leds->fill(c);
    _leds->show();
    delay(100);
    _leds->fill();
    _leds->show();
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

void Ornament::successBlink() {
  Serial.println("[INFO] Success blink");
  blink(3, c_green);
}

void Ornament::errorBlink() {
  Serial.println("[INFO] Error blink");
  blink(3, c_red);
}

void Ornament::infoBlink() {
  Serial.println("[INFO] Info blink");
  blink(3, c_yellow);
}

void Ornament::every_other(int c_a, int c_b) {
  int i = 0;
  while (i < 10) {
    int j = 0;
    // red first
    while (j < 6) {
      if (j % 2 == 0) {
        _leds->setPixelColor(j, c_a);
      } else {
        _leds->setPixelColor(j, c_b);
      }
      j++;
    }
    _leds->show();
    delay(500);
    
    // greeen first
    j = 0;
    while (j < 6) {
      if (j % 2 == 0) {
        _leds->setPixelColor(j, c_b);
      } else {
        _leds->setPixelColor(j, c_a);
      }
      j++;
    }
    _leds->show();
    delay(500);
    i++;
  }
  _leds->fill();
  _leds->show();
}

void Ornament::xmas() {
  Serial.println("[INFO] XMAS Mode!");
  every_other(c_red, c_green);
}

void Ornament::jmas() {
  Serial.println("[INFO] JMAS Mode!");
  every_other(c_white, c_blue);
}
