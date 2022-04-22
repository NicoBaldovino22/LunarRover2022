/*
 * How to configure and pair two HC-05 Bluetooth Modules
 * by Dejan Nedelkovski, www.HowToMechatronics.com
 * 
 *                 == SLAVE CODE ==
 */
 
#include <Servo.h>
#define button 8
#define TxOut 7
#define RxIn 6
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(RxIn, TxOut);

Servo S1;
int state = 0;
int buttonState = 0;

void setup() {
  pinMode(button, INPUT);
  S1.attach(9);
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
    Serial.write(state);
 }
 //Serial.println(state);
 
 // Controlling the servo motor
 S1.write(state);
 
 // Reading the button
 buttonState = digitalRead(button);
 Serial.print("BT Command: ");
 Serial.println(state);
 Serial.print("Butt State: ");
 Serial.println(buttonState);
 delay(10);
}
