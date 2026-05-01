#include "gsm.h"

SoftwareSerial ss(A0, A1); // RX, TX

#define RELAY_PIN 9
#define IGNITION_ENABLE 1
#define IGNITION_DISABLE 0

#include<Servo.h>
Servo first_servo;

#include <ultrasonic.h>
ULTRASONIC U1;
ULTRASONIC U2;

#define TRIGGER1 2
#define TRIGGER2 4

#define ECHO1 3
#define ECHO2 5

#define PM_P1 13
#define PM_N1 12

#define VIB_PIN 6

int cm1;
int cm2;
int VIB_status;
int data_s = 0;
int count = 0;
void setup() {
  Serial.begin(9600);
  U1.begin(TRIGGER1, ECHO1);
  U2.begin(TRIGGER2, ECHO2);
  pinMode(PM_P1, OUTPUT);
  pinMode(PM_N1, OUTPUT);
  digitalWrite(PM_P1, LOW);
  digitalWrite(PM_N1, LOW);
  pinMode(VIB_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, IGNITION_DISABLE);
  ss.begin(9600);
  first_servo.attach(11);
  first_servo.write(90);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  do
  {
    serialEvent();
  }
  while (data_s == 0);
  
  cm1 = U1.ultra();
  cm2 = U2.ultra();
  Serial.println(cm1);
  Serial.println(cm2);

  VIB_status = digitalRead(VIB_PIN);
  if (VIB_status == 1)
  {
    Serial.println("DD");
    digitalWrite(PM_P1, LOW);
    digitalWrite(PM_N1, LOW);
    //any mobile number here
    send_sms("8888888888", "RIYAS MET WITH AN ACCIDENT");
  }
  else
  {
    digitalWrite(PM_P1, HIGH);
    digitalWrite(PM_N1, LOW);
  }
  if (cm1 < 10)
  {
    digitalWrite(PM_P1, LOW);
    digitalWrite(PM_N1, LOW);
  }
  while (count == 20)
  {
    cm2 = U2.ultra();
    first_servo.write(90);
    if (cm2 < 10)
    {
      Serial.write('B');
    }
    delay(1000);
    first_servo.write(0);
    if (cm2 < 10)
    {
      Serial.write('B');
    }
    delay(1000);
    first_servo.write(90);
    delay(1000);
    first_servo.write(180);
    if (cm2 < 10)
    {
      Serial.write('C');
    }
    delay(1000);
    first_servo.write(90);
    if (cm2 < 10)
    {
      Serial.write('E');
    }
    count = 0;
  }
  count++;
  delay(500);
}
void serialEvent()
{
  while (Serial.available() > 0)
  {
    char inchar = Serial.read();
    switch (inchar)
    {
      case 'A':  data_s = 1;
        digitalWrite(PM_P1, HIGH);
        digitalWrite(PM_N1, LOW);
        break;
      case 'F':
        digitalWrite(PM_P1, LOW);
        digitalWrite(PM_N1, LOW);
        //your number
        send_sms("8888888888", "DROWSINESS DETECTED");
        break;
    }
  }
}
