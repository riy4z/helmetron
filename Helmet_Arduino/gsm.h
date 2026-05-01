#ifndef GSM_H
#define GSM_H

#include <SoftwareSerial.h>

extern SoftwareSerial ss;

inline void send_sms(const String &number, const String &message)
{
  ss.println("AT");
  delay(1000);
  ss.println("AT+CMGF=1");
  delay(1000);
  ss.print("AT+CMGS=\"+91");
  ss.print(number);
  ss.print("\"\r");
  delay(1000);
  ss.print(message);
  ss.write(26);
  delay(5000);
}

#endif
