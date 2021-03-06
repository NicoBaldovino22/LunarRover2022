/*
   How to configure and pair two HC-05 Bluetooth Modules
   by Dejan Nedelkovski, www.HowToMechatronics.com

                   == MASTER CODE ==
*/

#include <SoftwareSerial.h> // RX / TX
SoftwareSerial mySerial(11,12);

int state, potValue;
int button1, button2, button1R, button2R;
int xJoy1, yJoy1, xJoy2, yJoy2, xJoy1R, yJoy1R, xJoy2R, yJoy2R;

void setup() 
{
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  Serial.println("<Arduino Ready with HC-05 Master>");
  mySerial.begin(38400);
  Serial.println("<BTserial started at 38400");  
}

void loop() 
{
  if (mySerial.available())
  {
    state = mySerial.read(); // Reads the data from the BT and writes to Serial 
  }
   
  //Serial.println(state);
  
  // Reading the potentiometer
  //potValue = analogRead(A0);
  //int potValueMapped = map(potValue, 0, 1023, 0, 255);
  //mySerial.write(potValueMapped); // Sends potValue to servo motor

  //Reading and Mapping Joysticks
  xJoy1R = analogRead(A1); //Joystick 1 (Left) X
  xJoy1 = map(xJoy1R, 0, 1023, 0, 255);
  mySerial.write(xJoy1);

  yJoy1R = analogRead(A2); //Joystick 1 (Left) Y
  yJoy1 = map(yJoy1R, 0, 1023, 0, 255);
  mySerial.write(yJoy1);
  
  xJoy2R = analogRead(A3); //Joystick 2 (Right) X
  xJoy2 = map(xJoy2R, 0, 1023, 0, 255);
  mySerial.write(xJoy2);
    
  yJoy2R = analogRead(A4); //Joystick 2 (Right) Y
  yJoy2 = map(yJoy2R, 0, 1023, 0, 255);
  mySerial.write(yJoy2);

  //Reading and Mapping Push Buttons on Joys
  button1R = analogRead(A6);
  if (button1R > 0)
  {
    button1 = 1;
    mySerial.write(button1);
  }
  else if (button1R < 1)
  {
    button1 = 0;
    mySerial.write(button1);
  }
  
  button2R = analogRead(A5);
  if (button2R > 0)
  {
    button2 = 1;
    mySerial.write(button2);
  }
  else if (button2R < 1)
  {
    button2 = 0;
    mySerial.write(button2);
  }
  
  //Serial.print("Pot Values: ");
  //Serial.println(potValueMapped,1);
  Serial.print("BT Command From S: ");
  Serial.println(state,1);
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
  delay(1000);
}
