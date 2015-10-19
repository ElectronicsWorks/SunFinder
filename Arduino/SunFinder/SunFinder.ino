
#define LAT 45.421389
#define LON -75.691667
#define TZ -5

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include "Sun.h"

RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20 chars and 4 line display
Sun sun(LAT, LON, TZ);

void setup()
{
  lcd.init();                      // initialize the lcd 
 rtc.begin();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("Arduino Tracker");
  if (! rtc.isrunning()) {
    rtc.adjust(DateTime(2014, 11, 17, 15, 15, 0));
    lcd.setCursor(0, 1);
    lcd.print("Reset Date");
  }
}

void loop()
{
  DateTime now = rtc.now();
  lcd.setCursor(0, 1);
  String d = "Date: " ;
  d = d + now.year() + "/" + now.month()+ "/" + now.day()+ "   ";
  lcd.print(d);
  
  lcd.setCursor(0, 2);
  String t = "Time: " ;
  t = t + now.hour() + ":" + now.minute()+ ":" + now.second() + "     ";
  lcd.print(t);
  
  sun.calcSun(now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  if (sun.ItsDark())
  {
    lcd.setCursor(0,3);
    lcd.print("It's dark           ");
  }
  else
  {
  String s = "Sun: ";
  s = s + sun.azimuth() + " " + sun.elevation();
  lcd.setCursor(0,3);
  lcd.print(s);
  }

  delay(3000);
}
