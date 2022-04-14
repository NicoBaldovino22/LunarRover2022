#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2);

double x_pos;
double y_pos;
const int xJoy = A0;
const int yJoy = A1;
const int LED_PIN = 7;

void setup() {
Serial.begin(38400);
  pinMode(7,OUTPUT);
  pinMode(xJoy, INPUT);
  pinMode(yJoy, INPUT);
}

void loop() {
  x_pos = analogRead(xJoy);
  y_pos = analogRead(yJoy);
  
  if (Serial.available()>0)
  {
      char data= Serial.read();
      switch(data)
      {
        if (x_pos>50){
          digitalWrite(LED_PIN,HIGH);break;
        }
        if (x_pos<50){
          digitalWrite(LED_PIN,LOW);break;
        }
         else {
          default : break;
         }
      }
      Serial.println(data);
  }
  delay(50);
}
