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

//When using Serial Moniter, ensure that baud rate is 57600 (after void setup)

int error; 
byte type;
byte vibrate;


const int MFLF = 9; //Front Left Forward
const int MFLR = 6; //Front Left Reverse
//const int MFLP; //Front Left Power

const int MFRF = 5; //Front Right Forward
const int MFRR = 3; //Front Right Reverse
//const int MFRP; //Front Right Power

//const int MBLF; //Back Left Forward
//const int MBLR; //Back Left Reverse
//const int MBLP; //Front Left Power

//const int MBRF; //Back Right Forward
//const int MBRR; //Back Right Reverse
//const int MBRP; //Front Left Power
#define PI 3.1415926535897932384626433832795
#define sgn(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0))   //funtion for determining Sign of value (Circle Output -> Square Output)
const double DeadZ = .05;   //sets deadzone, percentage of of the entire joystick range that will be read as neutral



void setup(){
 Serial.begin(9600);
 
 pinMode(MFLF,INPUT);   //Defining pins
 pinMode(MFLR,INPUT);
 //pinMode(MFLP,OUTPUT);

 pinMode(MFRF,INPUT);
 pinMode(MFRR,INPUT);
 //pinMode(MFRP,OUTPUT);

 //pinMode(MBLF,INPUT);
 //pinMode(MBLR,INPUT);
 //pinMode(MBLP,OUTPUT);

// pinMode(MBRF,INPUT);
// pinMode(MBRR,INPUT);
// pinMode(MBRP,OUTPUT);


 digitalWrite(MFLF,HIGH);   //setting initial conditions for motor directs
 digitalWrite(MFLR,LOW);

 digitalWrite(MFRF,HIGH);
 digitalWrite(MFRR,LOW);

 //digitalWrite(MBLF,HIGH);
 //digitalWrite(MBLR,LOW);

 //digitalWrite(MBRF,HIGH);
 //digitalWrite(MBRR,LOW);

 
 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
 error = ps2x.config_gamepad(13,11,10,12, false, false);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
   Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
   Serial.println("holding L1 or R1 will print out the analog stick values.");
   Serial.println("Go to www.billporter.info for updates and to report bugs.");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   Serial.println(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        //Serial.println("Unknown Controller type");
       break;
       case 1:
        //Serial.println("DualShock Controller Found");
       break;
       case 2:
         //Serial.println("GuitarHero Controller Found");
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
  double Offset;  //defining variables for calculations
    Offset = (-45*PI)/180;  //Offset in radians (to translate joystick input to motor outputs)
  double LXin;    // X and Y Square Input
  double LYin;  
  double LUin;    // U and V Circle Input
  double LVin;
  double LUout;   // U and V Circle Output
  double LVout;
  double LXout;   // X and Y Square Output
  double LYout;
  double Lout;    // Left and Right Side Final Output
  double Rout;

    ps2x.read_gamepad(false, vibrate);    //necessary to read ps2 controller

    
    LXin = ps2x.Analog(PSS_LX);   //Reads the input from the left joystick
    LYin = ps2x.Analog(PSS_LY);   // 0 - 256

    
      Serial.print("Input: ");      //NOT NECESSARY, wrote to help with debugging
      Serial.print(LXin, 0);
      Serial.print(", ");
      Serial.println(LYin, 0);      //END NOT NECESSARY
 
    LYin = 256-LYin;    //Original Code was under assumption that Y was 256 at top position, not 0
                          //so this reverses the Y input to match my assumption
                            //4 Wheeler Controls Excel Sheet: (Input -> Mod. Input)
    
    if(LXin > (128-128*DeadZ) && LXin < (128+128*DeadZ))    //If input is within dead zone percentage, then reads it as exactly at 128, 128
      LXin = 128;
    if(LYin > (128-128*DeadZ) && LYin < (128+128*DeadZ))
      LYin = 128;
    
    if(LXin == 128 && LYin == 128)    //If the input is at 128 (neutral position), then skips calculation
    {
      Lout = 128;
      Rout = 128;
    }
    else    //Begining of calculation
    {
    LXin = (LXin-128)/128;    //Changes Square input from 0 to 256, to -1 to 1
    LYin = (LYin-128)/128;      //4 Wheeler Controls Excel Sheet: (Mod. Input -> Square Input)

    LUin = LXin * sqrt(1-(0.5*sq(LYin)));   //Calculates Circle Input using http://squircular.blogspot.com/2015/09/mapping-circle-to-square.html
    LVin = LYin * sqrt(1-(0.5*sq(LXin)));     //4 Wheeler Controls Excel Sheet: (Square Input -> Circle Input)

    LUout = (LUin*cos(Offset))-(LVin*sin(Offset));    //Offsets Input by 45 degrees using https://en.wikipedia.org/wiki/Rotation_matrix
    LVout = (LUin*sin(Offset))+(LVin*cos(Offset));      //4 Wheeler Controls Excel Sheet: (Circle Input -> Circle Output)

    if(sq(LUout) >= sq(LVout))                        //Calculates X's Square Output using http://squircular.blogspot.com/2015/09/elliptical-arc-mapping.html
      LXout = sgn(LUout)*sqrt(sq(LUout)+sq(LVout));     //4 Wheeler Controls Excel Sheet: (Circle Output -> Square Output)
    else
      LXout = sgn(LVout)*(LUout/LVout)*sqrt(sq(LUout)+sq(LVout));

    if(LVout == 0)                                    //Calculates Y's Square Output using http://squircular.blogspot.com/2015/09/elliptical-arc-mapping.html
      LYout = 0;                                        //Fringe case where when LVout = 0, #div/0 err occurs 
    else if(sq(LUout) >= sq(LVout))                       //4 Wheeler Controls Excel Sheet: (Circle Output -> Square Output)
      LYout = sgn(LUout)*(LVout/LUout)*sqrt(sq(LUout)+sq(LVout));
    else
      LYout = sgn(LVout)*sqrt(sq(LUout)+sq(LVout));

    Lout = (LXout*128)+128;   //Changes Square Output from -1 to 1, to 0 to 256
    Rout = (LYout*128)+128;     //4 Wheeler Controls Excel Sheet: (Square Output -> Output)

    if(Lout <= 1.5 || Rout <= 1.5)  //Output needs to be reversed if output is reverse
    {                                 //Added after realising mistake where when in reverse, 
      if(Lout < 250 || Rout < 250)      //Rover would reverse in wrong direction
      {
        Rout = (LXout*128)+128;
        Lout = (LYout*128)+128;
      }
    }
    }
    Serial.println("Output: ");   //NOT NECESSARY, wrote to help with debugging
    Serial.println(Lout, 1);
    Serial.println(", ");
    Serial.println(Rout, 1);    //END NOT NECESSARY
  
    if(Lout > 128)              //Sets outputs based on L/Rout
    {                             //Power can be set based on value of L/Rout
      digitalWrite(MFLF,HIGH);      //"Square Output" may be better for calculating Power
      digitalWrite(MFLR,LOW);
    }
    else if(Lout == 128)
    {
      digitalWrite(MFLF,LOW);
      digitalWrite(MFLR,LOW);
    }
    else
    {
      digitalWrite(MFLF,LOW);
      digitalWrite(MFLR,HIGH);
    }

    if(Rout > 128)
    {
      digitalWrite(MFRF,HIGH);
      digitalWrite(MFRR,LOW);
    }
    else if(Rout == 128)
    {
      digitalWrite(MFRF,LOW);
      digitalWrite(MFRR,LOW);
    }
    else
    {
      digitalWrite(MFRF,LOW);
      digitalWrite(MFRR,HIGH);
    }
 
 
 }  
 delay(50);
  
}
