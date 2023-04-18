#include "hertz.h"

void new_cycle() {
  // This runs when a rising edge square wave arrives. What should happen?
  period = millis() - prev_time;
  average_freq = (period + (counter * average_freq)) / counter + 1;
  counter++;
  prev_time = millis();
  if (counter > 23) {
    display_freq = average_freq;
    counter = 0;
    average_freq = 0;
  }
}

int sanity_check() {
  // This can be used to check that values aren't erroneous, e.g. frequency is 1000000000 or 0 or something
  int error_code = 0;
  return error_code;
}

void check_encoder() {
   // check whether encoder was moved, and queue up a moved flag if so
   if (digitalRead(encoder_b) == 1) {
      encoder_left = 1;
      delay(100);
   }
   else {
      encoder_right = 1;
      delay(100);
   }
}

void float_to_string() {
  sprintf(buffer, "%.2f", display_freq);
}

void menu_change() {
  /*
   * I imagine it like this:
   * 3 submenus that can be cycled between
   * Each has a different intialise routine and loop within the main loop
   * Check the open_menu function for more info
   * 
   * Clicking the encoder initialises the relevant display function and then
   * increments data.menu_state so the next menu is selected on next click
   */
   if (millis() - last_click > 750 && digitalRead(encoder_click) == 0) {
      open_menu(next_menu);
   }
   last_click = millis();
}

void open_menu(int next) {
  // Initialise the appropriate menu screen and set data.menu so the right main loop starts.
  
   if (next == 1) {
    menu = 1;
    // Set Threshold or Toggle Calibration?
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Threshold");
    lcd.setCursor(0, 1);
    lcd.print("Toggle Test Mode");
   }

   else if (next == 2) {
    // Select Threshold Digit
    menu = 2;
    next_menu = 3;
    lcd.clear();
    
    // First, split current threshold into digits
    float thresh = threshold;
    char string[5]; 
    sprintf(string, "%.2f", thresh);
    dp[0] = string[0]; // tens
    dp[1] = string[1]; // units
    dp[2] = string[3]; // 1 dp (string[2] is the decimal point??)
    dp[3] = string[4]; // 2 dp

    // Then print to display
    lcd.setCursor(3, 0);
    lcd.print("Threshold");
    lcd.setCursor(5, 1);
    lcd.print(dp[0]);
    lcd.setCursor(7, 1);
    lcd.print(dp[1]);
    lcd.print(". ");
    lcd.print(dp[2]);
    lcd.setCursor(12, 1);
    lcd.print(dp[3]);
    lcd.setCursor(5, 1);
   }

   else if (next == 3) {
    // Set Threshold
    menu = 3;
    next_menu = 0;
   }

   else if (next == 4) {
    // Toggle Calibration mode
    calibration_mode = !calibration_mode;
    digitalWrite(mux, calibration_mode);
    menu = 3;
    next_menu = 0;
   }

   else {
    next_menu == 1;
   }
}
