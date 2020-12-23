/*
  Ornament.h - IoT LED Ornament
  Michael Hotwagner
  mhotwagner@gmail.com
  Released into the public domain.
*/
#ifndef Ornament_h
#define Ornament_h

#include "Arduino.h"
#include "Logger.h"

#include <Easing.h>
#include <Adafruit_NeoPixel.h>

class Ornament{
	public:
        Ornament(int data_pin, Logger* _logger, bool autoInit, int logLevel);
        Ornament(int data_pin, Logger* _logger, bool autoInit);
		Ornament(int data_pin, Logger* _logger);

        Logger* logger;

        void init();

        void off();

        void on();
        void on(int c);
        void on(int c, int b);

        void log(String message);
        void log(double message);

        void set_color(int c);
        void set_brightness(int b);

        void blink(int n, int c);
        void blink(int n);
        void blink();

        void success_blink();
        void error_blink();
        void info_blink();

        void every_other(int c_a, int c_b);
        void alternate_every_other(int c_a, int c_b);

        void xmas();
        void jmas();

        void spin();

        void breathe();

		static const int data_pin;
        static const int led_count;

        static const int c_red;
        static const int c_green;
        static const int c_blue;
        static const int c_yellow;
        static const int c_white;

        static const int c_white_100;
        static const int c_white_75;
        static const int c_white_50;
        static const int c_white_25;

        EasingFunc<Ease::Cubic> ease;

	private:
		Adafruit_NeoPixel _leds;

        int _logLevel;

};

#endif