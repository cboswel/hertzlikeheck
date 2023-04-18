#ifndef HERTZ_H
#define HERTZ_H
#include <LiquidCrystal_I2C.h>

static int mux = 6;
static int display_message = 5;
static int encoder_click = 12;
static int encoder_a = 2;
static int encoder_b = 11;
static int sq_wave = 3;
static int lcdsda = 4;
static int lcdscl = 5;

//extern struct Data data;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void new_cycle();
int sanity_check();
void check_encoder();
void menu_change();
void open_menu(int next);
void float_to_string();

#endif
