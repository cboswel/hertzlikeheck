#include "hertz.h"

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
int encoder_1;
int encoder_2;
int prev_encoder_a;
int last_click;
float threshold;
float average_freq;
float display_freq;
char buffer[5];

void setup() {
  // put your setup code here, to run once:
  
  // set I/O
  pinMode(mux, OUTPUT);
  pinMode(display_message, OUTPUT);
  pinMode(lcdsda, OUTPUT);
  pinMode(lcdscl, OUTPUT);
  pinMode(encoder_click, INPUT_PULLUP);
  pinMode(encoder_a, INPUT_PULLUP);
  pinMode(encoder_b, INPUT_PULLUP);
  pinMode(sq_wave, INPUT);

  // setup interrupts
  attachInterrupt(digitalPinToInterrupt(sq_wave), new_cycle, RISING);
  attachInterrupt(digitalPinToInterrupt(encoder_a), check_encoder, FALLING);

  // set up the LCD's number of columns and rows:
  lcd.init();
  lcd.backlight();

  // Print a message to the LCD.
  lcd.print("HertzLikeHeck :)");
  // set cursor to column 0, line 1
  lcd.setCursor(0, 1);
  prev_encoder_a = millis();
  last_click = millis();
  prev_time = millis();
  display_freq = 60;
  threshold = 61;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
/**
  if (data.encoder_left == 1) {
    Serial.println(digitalRead(encoder_a));
    data.encoder_left = 0;
  }
  if (data.encoder_right == 1) {
    Serial.println("Right!");
    data.encoder_right = 0;
  }
**/
  menu_change();
  // Menu loops:
  if (menu == 0) {
    // main window stuff
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Freq = ");
    lcd.setCursor(7, 0);
    float_to_string();
    lcd.print(buffer);

    lcd.setCursor(0, 1);
    lcd.print("Thresh = ");
    lcd.setCursor(9, 1);
    float_to_string();
    lcd.print(buffer);
  }
  
  else if (menu == 1) {
    // Threshold or Calibrate menu
    if (encoder_left || encoder_right) {
      if (next_menu == 2) {
        next_menu = 3;
        lcd.setCursor(1, 0);
      }
      else if (next_menu == 3) {
        next_menu = 2;
        lcd.setCursor(0, 0);
      }
      encoder_left = 0;
      encoder_right = 0;
    }
  }
  
  else if (menu == 2) {
    // Choose Threshold Digit
    int position[4] = {5, 7, 10, 12};
    int i = 0;
    if (encoder_left) {
        i--;
        if (i < 0) {
          i = 3;
      }
      encoder_left = 0;
    }
    if (encoder_right) {
      i++;
      if (i > 3) {
        i = 0;
      }
      encoder_right = 0;
    }
    lcd.setCursor(position[i], 1);
    cursorPos = i;
  }

  else if (menu == 3) {
    // Set Threshold Digit
    lcd.noCursor();
    int value = dp[cursorPos];
    if (encoder_left) {
        value--;
        if (value < 0) {
          value = 9;
      }
      encoder_left = 0;
    }
    if (encoder_right) {
      value++;
      if (value > 9) {
        value = 0;
      }
      encoder_right = 0;
    }
    dp[cursorPos] = value;  
    lcd.clear();
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
    lcd.cursor();
  }
    // No loop required to toggle calibration (so no menu 4 loop)
    delay(100);
}
