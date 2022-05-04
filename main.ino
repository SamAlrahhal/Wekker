#define BUZZER 3
#define MICRO 4
#define switchJOY 5
#define SDArtc A3
#define SLKrtc A2
#define VRx A1
#define VRy A0

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int menuStatus = 0;
int uurUp = 0;
int minUp = 0;

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(MICRO, INPUT);
  pinMode(switchJOY, INPUT);
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  lcd.print("Welkom");
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(switchJOY) == HIGH){
    menuStatus++;
  }

  switch(menuStatus){
    case 1:
      setHour();
      break;
    case 2:
      setMin();
      break;
    case 3:
      save();
      break;

    default:
      Time();
      menuStatus = 0;
      break;
  }
  
}


void Alarm()
{
  bool status = false;
  
  do{
    tone(BUZZER, 500);
    delay(250);
    noTone(BUZZER);
    delay(250);
  }while(digitalRead(MICRO) != HIGH);
}

//display the current time
void Time(){
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
  if (digitalRead(tijdUp) == LOW)
  {
    if (uurUp == 23)
    {
      uurUp = 0;
    }
    else {
      uurUp = uurUp + 1;
    }
  }
  if (digitalRead(tijdDown) == LOW)
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
  if (digitalRead(tijdUp) == LOW)
  {
    if (minUp == 59)
    {
      minUp = 0;
    }
    else {
      minUp = minUp + 1;
    }
  }
  if (digitalRead(tijdDown) == LOW)
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
  RTC.adjust(DateTime(jaarUp, maandUp, dagUp, uurUp, minUp, 0));
  delay(200);
}


