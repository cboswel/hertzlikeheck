#include <LiquidCrystal.h>

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
  float threshold;
  float average_freq;
  // etc, etc....
};

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

void setup() {
  // put your setup code here, to run once:
  
  // set I/O
  pinMode(mux, OUTPUT);
  pinMode(display_message, OUTPUT);
  pinMode(lcdRegSel, OUTPUT);
  pinMode(lcdEnable, OUTPUT);
  pinMode(lcdRegSel, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(encoder_click, INPUT);
  pinMode(encoder_scroll, INPUT);
  pinMode(sq_wave, INPUT);

  // setup interrupts
  attachInterrupt(digitalPinToInterrupt(sq_wave), new_cycle, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder_click), menu_change, RISING);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("HertzLikeHeck :)");
  // set cursor to column 0, line 1
  lcd.setCursor(0, 1);
}

void new_cycle() {
  // This runs when a rising edge square wave arrives. What should happen?
}

int sanity_check() {
  // This can be used to check that values aren't erroneous, e.g. frequency is 1000000000 or 0 or something
  int error_code = 0;
  return error_code;
}

void check_encoder() {
   // check whether encoder was moved, and queue up a moved flag if so
   if (digitalRead(encoder_scroll) < data.encoder_scroll_value) {
    data.encoder_scroll_value = digitalRead(encoder_scroll);
    data.encoder_left = 1;
   }
   else if (digitalRead(encoder_scroll) > data.encoder_scroll_value) {
    data.encoder_scroll_value = digitalRead(encoder_scroll);
    data.encoder_right = 1;
   }
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
   
  open_menu(data.next_menu);
}

void open_menu(int next) {
  // Initialise the appropriate menu screen and set data.menu so the right main loop starts.
  
   if (next == 1) {
    data.menu = 1;
    // Set Threshold or Toggle Calibration?
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Threshold");
    lcd.setCursor(0, 1);
    lcd.print("Toggle Test Mode");
   }

   else if (next == 2) {
    // Select Threshold Digit
    data.menu = 2;
    data.next_menu = 3;
    lcd.clear();
    
    // First, split current threshold into digits
    float thresh = data.threshold;
    char string[5]; 
    sprintf(string, "%.2f", thresh);
    data.dp[0] = string[0]; // tens
    data.dp[1] = string[1]; // units
    data.dp[2] = string[3]; // 1 dp (string[2] is the decimal point??)
    data.dp[3] = string[4]; // 2 dp

    // Then print to display
    lcd.setCursor(3, 0);
    lcd.print("Threshold");
    lcd.setCursor(5, 1);
    lcd.print(data.dp[0]);
    lcd.setCursor(7, 1);
    lcd.print(data.dp[1]);
    lcd.print(". ");
    lcd.print(data.dp[2]);
    lcd.setCursor(12, 1);
    lcd.print(data.dp[3]);
    lcd.setCursor(5, 1);
   }

   else if (next == 3) {
    // Set Threshold
    data.menu = 3;
    data.next_menu = 0;
   }

   else if (next == 4) {
    // Toggle Calibration mode
    data.calibration_mode = !data.calibration_mode;
    digitalWrite(mux, data.calibration_mode);
    data.menu = 3;
    data.next_menu = 0;
   }

   else {
    data.next_menu == 1;
   }
}

void loop() {
  // put your main code here, to run repeatedly:

  check_encoder();
  
  // Menu loops:
  if (data.menu == 0) {
    // main window stuff
  }
  
  else if (data.menu == 1) {
    // Threshold or Calibrate menu
    if (data.encoder_left || data.encoder_right) {
      if (data.next_menu == 2) {
        data.next_menu = 3;
        lcd.setCursor(1, 0);
      }
      else if (data.next_menu == 3) {
        data.next_menu = 2;
        lcd.setCursor(0, 0);
      }
      data.encoder_left = 0;
      data.encoder_right = 0;
    }
  }
  
  else if (data.menu == 2) {
    // Choose Threshold Digit
    int position[4] = {5, 7, 10, 12};
    int i = 0;
    if (data.encoder_left) {
        i--;
        if (i < 0) {
          i = 3;
      }
      data.encoder_left = 0;
    }
    if (data.encoder_right) {
      i++;
      if (i > 3) {
        i = 0;
      }
      data.encoder_right = 0;
    }
    lcd.setCursor(position[i], 1);
    data.cursorPos = i;
  }

  else if (data.menu == 3) {
    // Set Threshold Digit
    lcd.noCursor();
    int value = data.dp[data.cursorPos];
    if (data.encoder_left) {
        value--;
        if (value < 0) {
          value = 9;
      }
      data.encoder_left = 0;
    }
    if (data.encoder_right) {
      value++;
      if (value > 9) {
        value = 0;
      }
      data.encoder_right = 0;
    }
    data.dp[data.cursorPos] = value;  
    lcd.clear();
    lcd.print("Threshold");
    lcd.setCursor(5, 1);
    lcd.print(data.dp[0]);
    lcd.setCursor(7, 1);
    lcd.print(data.dp[1]);
    lcd.print(". ");
    lcd.print(data.dp[2]);
    lcd.setCursor(12, 1);
    lcd.print(data.dp[3]);
    lcd.setCursor(5, 1);
    lcd.cursor();
  }
    // No loop required to toggle calibration (so no menu 4 loop)
    delay(100);
}
