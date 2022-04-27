/*
   How to configure and pair two HC-05 Bluetooth Modules
   by Dejan Nedelkovski, www.HowToMechatronics.com

                   == MASTER CODE ==
*/

#define ledPin 8
#include <SoftwareSerial.h> // RX / TX
SoftwareSerial mySerial(10,11);

int state = 0;
int potValue = 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  Serial.println("Arduino Ready with HC-05 Master");
  mySerial.begin(38400);
  Serial.println("BTserial started at 38400");  
}

void loop() 
{
  if (mySerial.available())
  {
    state = mySerial.read();
    ; // Reads the data from the BT and writes to Serial 
  }
   
  //Serial.println(state);

  // Controlling the LED
  if (state == '1') 
  {
    digitalWrite(ledPin, HIGH); // LED ON
    state = 0;
  }
  if (state == '0') 
  {
    digitalWrite(ledPin, LOW); // LED OFF
    state = 0;
  }
  
  // Reading the potentiometer
  potValue = analogRead(A1);
  int potValueMapped = map(potValue, 0, 1023, 0, 255);
  mySerial.write(potValueMapped); // Sends potValue to servo motor

  Serial.print("Pot Values: ");
  Serial.println(potValueMapped,1);
  Serial.print("BT Command: ");
  Serial.println(state,1);
  delay(10);
}
