#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.

//~~~~~~~~~~~~~~~~~~BUTTON LIST~~~~~~~~~~~~~~~~~~
//    All begin with "PSB_" EXCEPT JOYSTICK INPUTS
//    ex: SELECT = PSB_SELECT

//SELECT
//START   
//PAD_UP    = D-Pad Up
//PAD_DOWN  = D-Pad Down
//PAD_LEFT  = D-Pad Left
//PAD_RIGHT = D-Pad Right
//BLUE  = X Button
//GREEN = Triangle Button
//PINK  = Square Button
//RED   = Circle Button
//L3    = Left Stick Click
//R3    = Right Stick Click
//L2    = Left Trigger
//R2    = Right Trigger
//L1    = Left Bumper
//R1    = Right Bumper
//PSS_RX    = Right Joystick X Axis (0 to 256, Rests at 128)
//PSS_RY    = Right Joystick Y Axis (0 to 256, Rests at 128)
//PSS_LX    = Left Joystick X Axis (0 to 256, Rests at 128)
//PSS_LY    = Left Joystick Y Axis (0 to 256, Rests at 128)


//~~~~~~~~~~~~~~~~~~BUTTON INTERACTIONS~~~~~~~~~~~~~~~~~~
//    All begin with "ps2x." and end with "(BUTTON)" where "BUTTON" is the a button mentioned in BUTTON LIST
//    ex: Button = ps2x.Button(BUTTON)

//Button          = Is true (1) as long as button is pressed
//NewButtonState  = Is true (1) when button is pressed or released (changes state)
//ButtonPressed   = Is true (1) when button is pressed
//ButtonReleased  = Is true (1) when button is released
//Analog          = Returns value of button at current time (for reading joysticks)

//When using Serial Moniter, ensure that baud rate is 57600 (Line 52, after void setup)

int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){
 Serial.begin(57600);
 
 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
 error = ps2x.config_gamepad(13,11,10,12, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
    Serial.println("Found Controller, configured successful");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
  
}

void loop() {
 if(error == 1) //skip loop if no controller found
 {
  Serial.println("No Controller Detected");
  return; 
 }
 else { //DualShock Controller

    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select");
    if(ps2x.Button(PSB_START))
      Serial.println("Start");
      
    if(ps2x.Button(PSB_PAD_UP))
      Serial.println("D-Pad Up");
    if(ps2x.Button(PSB_PAD_DOWN))
      Serial.println("D-Pad Down");
    if(ps2x.Button(PSB_PAD_LEFT))
      Serial.println("D-Pad Left");
    if(ps2x.Button(PSB_PAD_RIGHT))
      Serial.println("D-Pad Right");
      
    if(ps2x.Button(PSB_BLUE))
      Serial.println("X");
    if(ps2x.Button(PSB_GREEN))
      Serial.println("Triangle");
    if(ps2x.Button(PSB_PINK))
      Serial.println("Square");
    if(ps2x.Button(PSB_RED))
      Serial.println("Circle");
      
    if(ps2x.Button(PSB_L3))
    {
      Serial.println("Left Stick Click, ");
      Serial.println("Left Stick Position: ");
      Serial.println(ps2x.Analog(PSS_LX), DEC);
      Serial.println(", ");
      Serial.println(ps2x.Analog(PSS_LY), DEC);
    }
    if(ps2x.Button(PSB_R3))
    {
      Serial.println("Right Stick Click, ");
      Serial.println("Right Stick Position: ");
      Serial.println(ps2x.Analog(PSS_RX), DEC);
      Serial.println(", ");
      Serial.println(ps2x.Analog(PSS_RY), DEC);
    }
      
    if(ps2x.Button(PSB_L2))
      Serial.println("Left Trigger");
    if(ps2x.Button(PSB_R2))
      Serial.println("Right Trigger");
      
    if(ps2x.Button(PSB_L1))
      Serial.println("Left Bumper");
    if(ps2x.Button(PSB_R1))
      Serial.println("Right Bumper");
 }
 
 
 delay(50);
     
}
