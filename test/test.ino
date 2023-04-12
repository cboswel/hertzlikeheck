#include <AUnit.h>
#include <LiquidCrystal.h>
#include "/home/charlie/hertzlikeheck/hertz/functions.ino"

// map pins
int mux = 6;
int display_message = 5;
int encoder_click = 3;
int encoder_scroll = 4;
int sq_wave = 2;
int lcdRegSel = 11;
int lcdEnable = 12;

struct data data; // initialise data struct
LiquidCrystal lcd(lcdRegSel, lcdEnable, 7, 8, 9, 10);

test(fuck) {
	assertEqual(hopefully(), (int) 7);
}

void setup() {
	Serial.begin(115200);
}

void loop() {
	aunit::TestRunner::run();
}
