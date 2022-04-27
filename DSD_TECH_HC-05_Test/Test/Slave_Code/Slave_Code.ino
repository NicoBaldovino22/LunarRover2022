/*
 * How to configure and pair two HC-05 Bluetooth Modules
 * by Dejan Nedelkovski, www.HowToMechatronics.com
 * 
 *                 == SLAVE CODE ==
 */
 
#include <Servo.h>
#define button 8
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);

Servo S1;
Servo S2;
int state = 0;
int buttonState = 0;

void setup() 
{
  pinMode(button, INPUT);
  S1.attach(9);
  S2.attach(7);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  Serial.println("Arduino Ready with HC-05 Slave");
  BTSerial.begin(38400);
  Serial.println("BTserial started at 38400");  
}

void loop() 
{
 if (BTSerial.available())
 {
    state = BTSerial.read(); // Reads the data from the BT and writes to Serial
    S1.write(state);
    S2.write(state);
 }
 //Serial.println(state);
 
 // Reading the button
 buttonState = digitalRead(button);
 Serial.print("BT Command: ");
 Serial.println(state);
 Serial.print("Butt State: ");
 BTSerial.write(buttonState);
 Serial.println(buttonState);
 delay(10);
}
