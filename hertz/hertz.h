#ifndef HERTZ_H
#define HERTZ_H
#include <LiquidCrystal.h>

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
  int encoder_scroll_value;
  int counter;
  int period;
  int prev_time;
  float threshold;
  float average_freq;
  float display_freq;
  char buffer[5];
};

static int mux = 6;
static int display_message = 5;
static int encoder_click = 3;
static int encoder_scroll = 4;
static int sq_wave = 2;
static int lcdRegSel = 11;
static int lcdEnable = 12;

extern struct Data data;
extern LiquidCrystal lcd(lcdRegSel, lcdEnable, 7, 8, 9, 10);

void new_cycle();
int sanity_check();
void check_encoder();
void menu_change();
void open_menu(int next);
void float_to_string();

#endif
