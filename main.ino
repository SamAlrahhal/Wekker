
int ledPin = 6;
void setup() {
pinMode(ledPin, OUTPUT);
}

void loop() {
  for(int i = 0; i < 255; i++){
    analogWrite(ledPin, i);
    delay(25);
  }
}
