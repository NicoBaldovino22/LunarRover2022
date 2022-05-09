/*
 * How to configure and pair two HC-05 Bluetooth Modules
 * by Dejan Nedelkovski, www.HowToMechatronics.com
 * 
 *                 == SLAVE CODE ==
 */
 
#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);

Servo S1;
Servo S2;
int serv1x, serv1y, serv2x, serv2y;
int state[6];

void setup() 
{
  S1.attach(9);
  S2.attach(7);
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  Serial.println("Arduino Ready with HC-05 Slave");
  BTSerial.begin(38400);
  Serial.println("BTserial started at 38400");  
}

void loop() 
{
 while (BTSerial.available())
 {
    state[6] = BTSerial.read();
 }
 //S1.write(state);
 //S2.write(state);
 //Serial.println(serv2x);
 
 // Reading the BTSerial()
 Serial.print("BT State 1: ");
 Serial.println(state[4]);
 delay(100);
 
 //Serial.print("Servo 1x: ");
 //Serial.println(serv1x);
 //Serial.print("Servo 1y: ");
 //Serial.println(serv1y);
 //Serial.print("Servo 2x: ");
 //Serial.println(serv2x);
 //Serial.print("Servo 2y: ");
 //Serial.println(serv2y);
 //delay(1000);
}
