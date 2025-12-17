#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD. Address 0x27 is common for I2C LCDs. Adjust if needed.
LiquidCrystal_I2C lcd(0x20, 16, 2);

// Pin Definitions
const int soilSensorPin = A0;  // Analog pin connected to soil sensor
const int relayPin = 7;        // Digital pin connected to relay

// Threshold for soil moisture (0-1023)
const int moistureThreshold = 500; // Adjust according to your soil

void setup() {
  lcd.init();           // Initialize LCD
  lcd.backlight();      // Turn on backlight
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure pump is OFF initially
  Serial.begin(9600);
}

void loop() {
  int soilValue = analogRead(soilSensorPin);
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilValue);

  lcd.setCursor(0, 0);
  lcd.print("Soil Moisture:");
  lcd.setCursor(0, 1);
  lcd.print(soilValue);
  lcd.print("       "); // Clear remaining chars

  if (soilValue < moistureThreshold) {
    // Soil is dry, turn on water pump
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(12, 1);
    lcd.print("ON ");
    Serial.println("Pump ON");
  } else {
    // Soil is wet enough, turn off pump
    digitalWrite(relayPin, LOW);
    lcd.setCursor(12, 1);
    lcd.print("OFF");
    Serial.println("Pump OFF");
  }

  delay(2000); // Update every 2 seconds
}
