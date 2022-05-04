#define BUZZER 3
#define MICRO 4
#define switchJOY 5
#define SDArtc A3
#define SLKrtc A2
#define VRx A1
#define VRy A0

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
RTC_DS1307 RTC;

int menuStatus;
int alarmStatus = 0;
int uurUp;
int minUp;
int alarmHours = 0, alarmMin = 0;


void setup() {
  lcd.begin(16, 2, LCD_5x8DOTS);
  lcd.backlight();
  lcd.clear();  
  printAllOff();
  pinMode(BUZZER, OUTPUT);
  pinMode(MICRO, INPUT);
  pinMode(switchJOY, INPUT_PULLUP);
  printAllOff();

  Serial.begin(9600);
  Wire.begin();
  RTC.begin();

    if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // Set the date and time at compile time
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  // RTC.adjust(DateTime(__DATE__, __TIME__)); //removing "//" to adjust the time
    // The default display shows the date and time
    
  menuStatus = 0;
}

void loop() {
  if(digitalRead(switchJOY) == LOW){
    menuStatus++;
  }
  if (analogRead(VRx)<=300) //beide knoppen te gelijk induwen voor alarm in te stellen
  {
    SetUurAlarm();
    SetMinuutAlarm();
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("ALARM:");
    lcd.setCursor(5, 1);
    lcd.print(alarmHours, DEC);
    lcd.print(":");
    lcd.print(alarmMin, DEC);
    delay(1000);
    lcd.clear();
  }
  switch(menuStatus){
    case 0: 
    Time(); Alarm(); break;
    case 1:
      setHour();
      break;
    case 2:
      setMin();
      break;
    case 3:
      save();delay(500);menuStatus = 0; break;

    default: 
    Serial.print("Fout in het systeem");
  }
  delay(100);
}



//display the current time
void Time(){
  lcd.clear();
    DateTime now = RTC.now();

  lcd.setCursor(0, 0);
  lcd.print("Tijd : ");

  if (now.hour() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.hour(), DEC);
  uurUp = now.hour();
  lcd.print(":");

  if (now.minute() <= 9)
  {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  minUp = now.minute();

}

void setHour()
{
  lcd.clear();
  DateTime now = RTC.now();
  if (analogRead(VRy) >= 700)
  {
    if (uurUp == 23)
    {
      uurUp = 0;
    }
    else {
      uurUp = uurUp + 1;
    }
  }
  if (analogRead(VRy) <= 300)
  {
    if (uurUp == 0)
    {
      uurUp = 23;
    }
    else {
      uurUp = uurUp - 1;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("Zet uren: ");
  lcd.setCursor(0, 1);
  lcd.print(uurUp, DEC);
  delay(200);
}
void setMin()
{
    lcd.clear();
  if (analogRead(VRy) >= 700)
  {
    if (minUp == 59)
    {
      minUp = 0;
    }
    else {
      minUp = minUp + 1;
    }
  }
  if (analogRead(VRy) <= 300)
  {
    if (minUp == 0)
    {
      minUp = 59;
    }
    else {
      minUp = minUp - 1;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("Zet MIN: ");
  lcd.setCursor(0, 1);
  lcd.print(minUp, DEC);
  delay(200);
}
void save()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Opslagen ");
  lcd.setCursor(0, 1);
  lcd.print("Bezig");
  RTC.adjust(DateTime(0, 0, 0, uurUp, minUp, 0));
  delay(200);
}
void SetUurAlarm() {
  while (digitalRead(switchJOY) == HIGH)
  {
    lcd.clear();
    if (analogRead(VRy) >= 700)
    {
      if (alarmHours == 23)
      {
        alarmHours = 0;
      }
      else {
        alarmHours = alarmHours + 1;
      }
    }
    if (analogRead(VRy) <= 300)
    {
      if (alarmHours == 0)
      {
        alarmHours = 23;
      }
      else {
        alarmHours = alarmHours - 1;

      }
    }
    lcd.setCursor(0, 0);
    lcd.print("Zet alarm uur");
    lcd.setCursor(0, 1);
    lcd.print(alarmHours, DEC);
    delay(200);
  }
  delay(200);
}
void SetMinuutAlarm() {
  while (digitalRead(switchJOY) == HIGH)
  {
    lcd.clear();
    if (analogRead(VRy) >= 700)
    {
      if (alarmMin == 59)
      {
        alarmMin = 0;
      }
      else {
        alarmMin = alarmMin + 1;
      }
    }
    if (analogRead(VRy) <= 300)
    {
      if (alarmMin == 0)
      {
        alarmMin = 59;
      }
      else {
        alarmMin = alarmMin - 1;

      }
    }
    lcd.setCursor(0, 0);
    lcd.print("Zet alarm Min");
    lcd.setCursor(0, 1);
    lcd.print(alarmMin, DEC);
    delay(200);
  }
  delay(200);
}
void printAllOn() {
  lcd.setCursor(0, 2);
  lcd.print("Alarm: ");

  if (alarmHours <= 9)
  {
    lcd.print("0");
  }
  lcd.print(alarmHours, DEC);
  lcd.print(":");
  
  if (alarmMin <= 9)
  {
    lcd.print("0");
  }
  lcd.print(alarmMin, DEC);

}
void printAllOff() {
  lcd.setCursor(0, 2);
  lcd.print("Alarm: Uit");
}

void Alarm()
{
  static bool status = false;
  if(analogRead(VRx)>=700)
    {alarmStatus++;
    }
  if(alarmStatus == 0)
      {printAllOff();
      }
   if(alarmStatus == 1)
   {
    printAllOn();

    DateTime now = RTC.now();
    if((now.hour() == alarmHours) && (now.minute() == alarmMin)){
        do{
    tone(BUZZER, 500);
    delay(250);
    noTone(BUZZER);
    delay(250);
  }while(digitalRead(MICRO) != HIGH || analogRead(VRx) >=700);
    }
   }
   if(alarmStatus == 2)
   {
    alarmStatus =0;
   }
   delay(200);

}