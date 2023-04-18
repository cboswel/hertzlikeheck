#include "hertz.h"

struct Data data;

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
  data.prev_encoder_a = millis();
  data.last_click = millis();
  data.prev_time = millis();
  data.display_freq = 60;
  data.threshold = 61;
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
  if (data.menu == 0) {
    // main window stuff
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Freq = ");
    lcd.setCursor(7, 0);
    float_to_string();
    lcd.print(data.buffer);

    lcd.setCursor(0, 1);
    lcd.print("Thresh = ");
    lcd.setCursor(9, 1);
    float_to_string();
    lcd.print(data.buffer);
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
