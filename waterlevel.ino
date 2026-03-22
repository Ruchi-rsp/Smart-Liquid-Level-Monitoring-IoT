#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD at I2C address 0x27, 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

// Tank height in cm - adjust as needed
const int tankHeight = 30;

void setup() {
  lcd.init();
  lcd.backlight();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Water Level:");
  delay(2000);
}

void loop() {
  long duration;
  float distance, level;

  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo pulse duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration * 0.0343 / 2;

  // Limit max distance to tank height
  if (distance > tankHeight) distance = tankHeight;

  // Calculate water level
  level = tankHeight - distance;

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level: ");
  lcd.print(level, 1);
  lcd.print(" cm");

  lcd.setCursor(0, 1);
  lcd.print("Tank: ");
  lcd.print((level / tankHeight) * 100, 0);
  lcd.print("% full");

  delay(1000);
}
