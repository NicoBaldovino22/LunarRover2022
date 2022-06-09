/*
   How to configure and pair two HC-05 Bluetooth Modules
   by Dejan Nedelkovski, www.HowToMechatronics.com

                   == MASTER CODE ==
*/
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> // RX / TX
SoftwareSerial mySerial(11, 12);
LiquidCrystal_I2C lcd(0x3F,16,2);

int potValue, Received;
int button1, button2, button1R, button2R;
int xJoy1, yJoy1, xJoy2, yJoy2, xJoy1R, yJoy1R, xJoy2R, yJoy2R;
char state;

void setup()
{
  Serial.begin(38400); // Default communication rate of the Bluetooth module
  Serial.println("<Arduino Ready with HC-05 Master>");
  mySerial.begin(38400);
  Serial.println("<BTserial started at 38400");
  lcd.init();
  lcd.backlight();
  lcd.print("Hello LR Team");
}

void loop()
{
  if (mySerial.available())
  {
    state = mySerial.read(); // Reads the data from the BT and writes to Serial
  }
  readingModules();
}

void readingModules()
{
  //Reading the potentiometer
  //potValue = analogRead(A0);
  //int potValueMapped = map(potValue, 0, 1023, 0, 255);
  //mySerial.write(potValueMapped); // Sends potValue to servo motor
/*
  mySerial.write("<");

  //Reading and Mapping Two Joysticks
  xJoy1R = analogRead(A0); //Joystick 1 (Left) X
  xJoy1 = map(xJoy1R, 0, 1023, 0, 255);
  mySerial.write(xJoy1);
  delay(10);

  yJoy1R = analogRead(A1); //Joystick 1 (Left) Y
  yJoy1 = map(yJoy1R, 0, 1023, 0, 255);
  mySerial.write(yJoy1);
  delay(10);

  mySerial.write(">")

  xJoy2R = analogRead(A2); //Joystick 2 (Right) X
  xJoy2 = map(xJoy2R, 0, 1023, 0, 255);
  mySerial.write(xJoy2);
  delay(10);

  yJoy2R = analogRead(A3); //Joystick 2 (Right) Y
  yJoy2 = map(yJoy2R, 0, 1023, 0, 255);
  mySerial.write(yJoy2);
  delay(10);

  //Reading and Mapping Push Buttons on Joys
  button1R = analogRead(A7);
  if (button1R > 0)
  {
    button1 = 1;
    mySerial.write(button1);
    delay(10);
  }
  else if (button1R < 1)
  {
    button1 = 0;
    mySerial.write(button1);
    delay(10);
  }
*/
  button2R = analogRead(A6);
  if (button2R > 0)
  {
    button2 = 0;
    mySerial.write(button2);
    delay(100);
  }
  else if (button2R < 1)
  {
    button2 = 1;
    mySerial.write(button2);
    delay(100);
  }

  //Serial.print("Pot Values: ");
  //Serial.println(potValueMapped,1);
  //Serial.print("BT Command From S: ");
  //Serial.println(state);
  //Serial.print("Button1: ");
  //Serial.println(button1);
  Serial.print("Button2: ");
  Serial.println(button2);
  //Serial.print("xJoy1: ");
  //Serial.println(xJoy1);
  //Serial.print("yJoy1: ");
  //Serial.println(yJoy1);
  //Serial.print("xJoy2: ");
  //Serial.println(xJoy2);
  //Serial.print("yJoy2: ");
  //Serial.println(yJoy2);
  //delay(500);
}