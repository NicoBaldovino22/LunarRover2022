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
int button1, button2;
int xJoy1, yJoy1, xJoy2, yJoy2;
char state;

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
 while (BTSerial.available() >= 6)
 {
    xJoy1 = BTSerial.read();
    yJoy1 = BTSerial.read();
    xJoy2 = BTSerial.read();
    yJoy2 = BTSerial.read();
    button1 = BTSerial.read();
    button2 = BTSerial.read();
 }
 S1.write(xJoy1);
 S2.write(yJoy1);
 
 // Reading the BTSerial()
 Serial.print("Button1: ");
 Serial.println(button1);
 Serial.print("Button2: ");
 Serial.println(button2);
 Serial.print("xJoy1: ");
 Serial.println(xJoy1);
 Serial.print("yJoy1: ");
 Serial.println(yJoy1);
 Serial.print("xJoy2: ");
 Serial.println(xJoy2);
 Serial.print("yJoy2: ");
 Serial.println(yJoy2);
 delay(500);
}
