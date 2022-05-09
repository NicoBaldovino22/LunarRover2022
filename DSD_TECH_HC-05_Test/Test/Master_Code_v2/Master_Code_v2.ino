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
  Serial.println("Arduino Ready with HC-05 Master");
  mySerial.begin(38400);
  Serial.println("BTserial started at 38400");  
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
  //Joystick 1 (Right) X
  xJoy1R = analogRead(A1);
  xJoy1 = map(xJoy1R, 0, 1023, 0, 255);
  if (xJoy1 < 10)
  {
    xJoy1 = 0;
  }
  else if (xJoy1 > 245)
  {
    xJoy1 = 255;
  }
  else if (120 < xJoy1 < 135)
  {
    xJoy1 = 125;
  }
  else
  {
    xJoy1 = map(xJoy1R, 0, 1023, 0, 255);
  }
  mySerial.write(xJoy1);
  
  //Joystick 1 (Right) Y
  yJoy1R = analogRead(A2); 
  yJoy1 = map(yJoy1R, 0, 1023, 0, 255);
  if (yJoy1 < 10)
  {
    yJoy1 = 0;
  }
  else if (yJoy1 > 245)
  {
    yJoy1 = 255;
  }
  else if (120 < yJoy1 < 135)
  {
    yJoy1 = 125;
  }
  else
  {
    yJoy1 = map(yJoy1R, 0, 1023, 0, 255);
  }
  mySerial.write(yJoy1);
  
  //Joystick 2 (Left) X
  xJoy2R = analogRead(A3);
  xJoy2 = map(xJoy2R, 0, 1023, 0, 255);
  if (xJoy2 < 10)
  {
    xJoy2 = 0;
  }
  else if (xJoy2 > 245)
  {
    xJoy2 = 255;
  }
  else if (120 < xJoy2 < 135)
  {
    xJoy2 = 125;
  }
  else
  {
    xJoy2 = map(xJoy2R, 0, 1023, 0, 255);
  }
  mySerial.write(xJoy2);

  //Joystick 2 (Left) Y
  yJoy2R = analogRead(A4);
  yJoy2 = map(yJoy2R, 0, 1023, 0, 255);
  if (yJoy2 < 10)
  {
    yJoy2 = 0;
  }
  else if (yJoy2 > 245)
  {
    yJoy2 = 255;
  }
  else if (120 < yJoy2 < 135)
  {
    yJoy2 = 125;
  }
  else
  {
    yJoy2 = map(yJoy2R, 0, 1023, 0, 255);
  }
  mySerial.write(yJoy2);

  //Reading and Mapping Push Buttons on Joys
  //L3
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

  //R3
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
