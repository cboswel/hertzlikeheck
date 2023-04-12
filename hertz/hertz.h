#ifndef HERTZ_H
#define HERTZ_H

struct data {
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
  // etc, etc....
};

void new_cycle();
int sanity_check();
void check_encoder();
void menu_change();
void open_menu(int next);
int hopefully();

#endif
