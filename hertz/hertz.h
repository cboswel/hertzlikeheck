#ifndef HERTZ_H
#define HERTZ_H
#include <LiquidCrystal_I2C.h>

struct Data {
  bool alarm;
  bool restarted_flag;
  bool calibration_mode;
  bool encoder_right;
  bool encoder_left;
  int menu;
  int next_menu;
  int dp[4];
  int cursorPos;
  int counter;
  int period;
  int prev_time;
  int encoder_a;
  int encoder_b;
  int prev_encoder_a;
  int last_click;
  float threshold;
  float average_freq;
  float display_freq;
  char buffer[5];
};

static int mux = 6;
static int display_message = 5;
static int encoder_click = 12;
static int encoder_a = 2;
static int encoder_b = 11;
static int sq_wave = 3;
static int lcdsda = 4;
static int lcdscl = 5;

//extern struct Data data;
extern LiquidCrystal_I2C lcd(0x27, 16, 2);

void new_cycle();
int sanity_check();
void check_encoder();
void menu_change();
void open_menu(int next);
void float_to_string();

#endif
