#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the I2C LCD, address 0x27, 16 chars, 2 lines
LiquidCrystal_I2C lcd(0x20, 16, 2);

// IR sensor pins
const int IR_IN_PIN = 6;
const int IR_OUT_PIN = 7;

// Variables to store states
int inCount = 0;
int outCount = 0;
int currentCount = 0;

bool inFlag = false;
bool outFlag = false;

void setup() {
  lcd.init();                      // initialize the lcd
  lcd.backlight();                 // turn on the backlight
  pinMode(IR_IN_PIN, INPUT);
  pinMode(IR_OUT_PIN, INPUT);

  lcd.setCursor(0,0);
  lcd.print("IN:0 OUT:0");
  lcd.setCursor(0,1);
  lcd.print("Current:0");

  Serial.begin(9600);
}

void loop() {
  int inState = digitalRead(IR_IN_PIN);
  int outState = digitalRead(IR_OUT_PIN);

  // Check if someone is entering
  if (inState == LOW && !inFlag) {  // assuming IR sensor LOW when blocked
    inCount++;
    currentCount++;
    inFlag = true;
    updateLCD();
    delay(200); // debounce delay
  }
  if (inState == HIGH) {
    inFlag = false;
  }

  // Check if someone is exiting
  if (outState == LOW && !outFlag) {
    outCount++;
    if(currentCount > 0) currentCount--; // prevent negative count
    outFlag = true;
    updateLCD();
    delay(200); // debounce delay
  }
  if (outState == HIGH) {
    outFlag = false;
  }
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("IN:");
  lcd.print(inCount);
  lcd.print(" OUT:");
  lcd.print(outCount);

  lcd.setCursor(0,1);
  lcd.print("Current:");
  lcd.print(currentCount);

  // Also print to Serial Monitor
  Serial.print("IN:");
  Serial.print(inCount);
  Serial.print(" OUT:");
  Serial.print(outCount);
  Serial.print(" Current:");
  Serial.println(currentCount);
}
