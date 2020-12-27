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

        // next stuff
        unsigned long nextTime;
        unsigned long refTime;
        int offset;
        void (*next) (Ornament& ornament);

        void execute();

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
        void breathingRainbow();

        uint32_t getRainbowColor(int i);

		static const int data_pin;
        static const int led_count;

        static const uint32_t c_red;
        static const uint32_t c_green;
        static const uint32_t c_blue;
        static const uint32_t c_yellow;
        static const uint32_t c_purple;
        static const uint32_t c_teal;
        

        static const uint32_t c_white;
        static const uint32_t c_white_100;
        static const uint32_t c_white_75;
        static const uint32_t c_white_50;
        static const uint32_t c_white_25;

        static const int rainbow[];

        EasingFunc<Ease::Cubic> ease;

	private:
		Adafruit_NeoPixel _leds;

        int _logLevel;

};

#endif