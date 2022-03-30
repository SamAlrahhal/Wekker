#define BUZZER 3
#define MICRO 4
#define SW 5
#define SDArtc A3
#define SLKrtc A2
#define VRx A1
#define VRy A0

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(MICRO, INPUT);
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  lcd.print("Welkom");
  Serial.begin(9600);
}

void loop() {
  
}
void Alarm(){
  bool status = false;
  do{
    digitalWrite(BUZZER, HIGH);
    delay(250);
    digitalWrite(BUZZER, LOW);
    delay(250);
  }while(digitalRead(MICRO) != HIGH);
}

