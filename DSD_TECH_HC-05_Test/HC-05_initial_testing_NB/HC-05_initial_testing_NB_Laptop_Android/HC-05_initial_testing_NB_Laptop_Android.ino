#include <SoftwareSerial.h>

//the following will be code needed to operate one single DSD TECH HC-05 Bluetooth module with an Android phone

#define ledPin 7
int state = 0; 

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(38400); // Default communication rate of the Bluetooth signal
}

void loop() {
  if(Serial.available() > 0 ) { // Check whether data is correct or not
    state = Serial.read(); // Reads the data from the serial
  }
  if (state == '0') {
    digitalWrite(ledPin, LOW); // Turn OFF LED
    Serial.println("LED: OFF"); // Send back to the phone or computer
    state = 0;
  }
  else if (state == '1') {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED: ON");
    state = 0;
  }
}
