#define ph 2
#define buz 3
#define ALCOHOL_SENSOR_PIN A0
#define PULSE_SENSOR_PIN A1
#include<SoftwareSerial.h>
SoftwareSerial ss(6, 7);
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
char py_rx, zig_rx;

// TODO: Alcohol detection threshold (adjust based on MQ-3 calibration)
const int ALCOHOL_THRESHOLD = 400;
int alcohol_level = 0;

// TODO: Pulse rate monitoring (bpm calculation)
int pulse_rate = 0;
void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  lcd.begin(16, 2);
  lcd.print("helmet section");
  pinMode(ph, INPUT_PULLUP);
  pinMode(buz, OUTPUT);
  digitalWrite(buz, LOW);
  delay(1000);
}

void loop() {
  serialEvent();
  lcd.clear();
  
  // Read alcohol sensor (MQ-3)
  alcohol_level = analogRead(ALCOHOL_SENSOR_PIN);
  
  if (digitalRead(ph) == 0) {
    Serial.write("A");
    lcd.print("WEAR HELMET");
    
    // TODO: Check alcohol level - prevent ignition if alcohol detected
    if (alcohol_level > ALCOHOL_THRESHOLD) {
      lcd.setCursor(0, 1);
      lcd.print("ALCOHOL ALERT");
      digitalWrite(buz, HIGH);
      delay(500);
      digitalWrite(buz, LOW);
    }
  }
  else
  {
    lcd.print("PLS WEAR HELMET");
  }
  delay(100);
}
void serialEvent() {
  while (Serial.available() > 0) {
    zig_rx = Serial.read();
    switch (zig_rx) {
      case 'B':
        lcd.setCursor(4, 0);
        lcd.print("left side");
        lcd.setCursor(0, 1);
        lcd.print("vehicle detected"); delay(2000);
        digitalWrite(buz, HIGH);
        delay(1000);
        digitalWrite(buz, LOW);
        break;
      case 'C':
        lcd.setCursor(4, 0);
        lcd.print("back side");
        lcd.setCursor(0, 1);
        lcd.print("vehicle detected"); delay(2000);
        digitalWrite(buz, HIGH);
        delay(1000);
        digitalWrite(buz, LOW);
        break;
      case 'D':
        lcd.setCursor(4, 0);
        lcd.print("right side");
        lcd.setCursor(0, 1);
        lcd.print("vehicle detected"); delay(2000);
        digitalWrite(buz, HIGH);
        delay(1000);
        digitalWrite(buz, LOW);
        break;
    }
  }
  while  (ss.available() > 0) {
    py_rx = ss.read();
    if (py_rx == 'E') {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("DROWSINESS DETECTED");
      Serial.write("F");
      digitalWrite(buz, HIGH);
      delay(1000);
      digitalWrite(buz, LOW);
      py_rx = 'X';
      break;
    }
  }
}
