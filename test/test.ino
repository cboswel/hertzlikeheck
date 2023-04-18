#include <AUnit.h>
#include "/home/charlie/hertzlikeheck/hertz/functions.ino"

struct Data data;

test(float_to_string) {
	data.display_freq = 12.34567;
	float_to_string();
	for(int i=0; i<5; i++) {
        	char c = char(data.buffer[i]);
        	Serial.println(c);
    	}
	assertEqual(data.buffer[0], (char) '1');
	assertEqual(data.buffer[1], (char) '2');
	assertEqual(data.buffer[2], (char) '.');
	assertEqual(data.buffer[3], (char) '3');
	assertEqual(data.buffer[4], (char) '4');
	Serial.println(data.buffer);
}

test(frequency_calc) {
	double freq = random(4950, 5050) / 100.0;
	int period_us = 1000000 / freq;
	for (int i=0; i<100; i++) {
		new_cycle();
		delayMicroseconds(period_us);
	}
	double average_freq = data.display_freq;
	double error = 0.005;
	assertNear(average_freq, freq, error);
}

//test(threshold) {
	

void setup() {
	Serial.begin(115200);
	randomSeed(analogRead(0)); // pin 0 must be floating for this to work well
	lcd.init();
	lcd.backlight();
	lcd.print("HertzLikeHeck :)");
}

void loop() {
	aunit::TestRunner::run();
}

/**

Tests planned:
x The digit splitter works
x For a given number of hits over time, frequency is correct
Problematic case detection (49.5 - 50.5 hz, 1000 identical readings, measured voltage)
Alarm level goes high
Threshold is adjustable
Temperature stuff (fan on, power off)
Startup sequence


**/
