/*
  Ornament.h - IoT LED Ornament
  Michael Hotwagner
  mhotwagner@gmail.com
  Released into the public domain.
*/
#ifndef Ornament_h
#define Ornament_h

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

class Ornament{
	public:
		Ornament(Adafruit_NeoPixel *leds);

    void init();

    void off();

    void on();
    void on(int c);
    void on(int c, int b);

    void setColor(int c);
    void setBrightness(int b);

    void blink(int n, int c);
    void blink(int n);
    void blink();

    void successBlink();
    void errorBlink();
    void infoBlink();

    void every_other(int c_a, int c_b);

    void xmas();
    void jmas();

		static const int c_red;
        static const int c_green;
        static const int c_blue;
        static const int c_yellow;
        static const int c_white;

	private:
		Adafruit_NeoPixel *_leds;

};

#endif