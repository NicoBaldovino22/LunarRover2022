#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;
const int ledYel = 3;
const int ledRed = 5;
const int ledBlu = 6;
const int ledGrn = 9;

void setup(){
 Serial.begin(57600);
 pinMode(ledYel,OUTPUT);
 pinMode(ledRed,OUTPUT);
 pinMode(ledBlu,OUTPUT);
 pinMode(ledGrn,OUTPUT);
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
  return; 
 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
    if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
         Serial.println("Start is being held");
    if(ps2x.Button(PSB_SELECT))
         Serial.println("Select is being held");
         
         
     if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }   
    
    if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
    {
     
       
         
        if(ps2x.Button(PSB_L3))
         Serial.println("L3 pressed");
        if(ps2x.Button(PSB_R3))
         Serial.println("R3 pressed");
        if(ps2x.Button(PSB_L2))
         Serial.println("L2 pressed");
        if(ps2x.Button(PSB_R2))
         Serial.println("R2 pressed");
         
    }   
         
    
    if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
         {
         Serial.println("Circle just pressed");
         digitalWrite(ledRed, HIGH);
         }
         
    if(ps2x.ButtonReleased(PSB_RED))             //will be TRUE if button was JUST released
         {
         Serial.println("Circle just released");
         digitalWrite(ledRed,LOW);
         }        
         
    if(ps2x.ButtonPressed(PSB_PINK))             //will be TRUE if button was JUST pressed
         {
         Serial.println("Square just pressed");
         digitalWrite(ledYel, HIGH);
         }
         
    if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
         {
         Serial.println("Square just released");
         digitalWrite(ledYel,LOW);
         }

    
    if(ps2x.ButtonPressed(PSB_BLUE))             //will be TRUE if button was JUST pressed
         {
         Serial.println("Cross just pressed");
         digitalWrite(ledBlu, HIGH);
         }
         
    if(ps2x.ButtonReleased(PSB_BLUE))             //will be TRUE if button was JUST released
         {
         Serial.println("Cross just released");
         digitalWrite(ledBlu,LOW);
         }

        
    if(ps2x.ButtonPressed(PSB_GREEN))             //will be TRUE if button was JUST pressed
         {
         Serial.println("Triangle just pressed");
         digitalWrite(ledGrn, HIGH);
         }
         
    if(ps2x.ButtonReleased(PSB_GREEN))             //will be TRUE if button was JUST released
         {
         Serial.println("Triangle just released");
         digitalWrite(ledGrn,LOW);
         }

    
    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
    {
        Serial.print("Stick Values:");
        Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_LX), DEC); 
        Serial.print(",");
        Serial.print(ps2x.Analog(PSS_RY), DEC); 
        Serial.print(",");
        Serial.println(ps2x.Analog(PSS_RX), DEC); 
    } 
    
    
 }
 
 
 delay(50);
     
}
