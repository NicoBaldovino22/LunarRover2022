
#include <PS2X_lib.h>
#include <Servo.h>
//PS2 Stuff
PS2X ps2x; // create PS2 Controller Class
int error = 0; 
byte type = 0;
byte vibrate = 0;


//Output (Servos)
Servo HServo;
Servo VServo;
double lxpos;
double lypos;
double rxpos;
double rypos;
int Hservopos;
int Vservopos;

//Joystick Variables
//Variable
const int JoyMin = 0;
const int JoyMax = 256;
//Calculated
const int JoyMid = (JoyMin+JoyMax)/2;

//Servo Variables
//Variable
const int HServoPin = 5;
const int VServoPin = 6;
const int ServoMin = 0;
const int ServoMax = 270;
const int MaxServoF = 2500;
const int MinServoF = 500;
const int HRange = 90; //Horizontal Range of motion in degrees
const int VRange = 40; //Vertical Range of motion in degrees
//Calculated
const int HMin = ((ServoMax-ServoMin)/2)-(HRange/2);
const int HMax = ((ServoMax-ServoMin)/2)+(HRange/2);
const int VMin = ((ServoMax-ServoMin)/2)-(VRange/2);
const int VMax = ((ServoMax-ServoMin)/2)+(VRange/2);

//Motor Variables
//Variable
const int FFor = 7;
const int FRev = 8;
const int FPow = 3;
const int BFor = 2;
const int BRev = 4;
const int BPow = 9;
int Pow;

const double DeadZP = .10;  //Deadzone percentage



void setup() {
 Serial.begin(57600);
  
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
  
  
  HServo.attach(HServoPin);
  HServo.writeMicroseconds((MaxServoF+MinServoF)/2);
  VServo.attach(VServoPin);
  VServo.writeMicroseconds((MaxServoF+MinServoF)/2);
  pinMode(FPow, OUTPUT);
  pinMode(FFor, INPUT);
  pinMode(FRev, INPUT);

  digitalWrite(FFor, LOW);
  digitalWrite(FRev, LOW);
  analogWrite(FPow, 255);
  
  pinMode(BPow, OUTPUT);
  pinMode(BFor, INPUT);
  pinMode(BRev, INPUT);

  digitalWrite(BFor, LOW);
  digitalWrite(BRev, LOW);
  analogWrite(BPow, 255);


}

void loop() {
 if(error == 1) //skip loop if no controller found
  return;
 else {

    ps2x.read_gamepad(false, vibrate);    //necessary to read ps2 controller
    rxpos = ps2x.Analog(PSS_RX);
    rypos = ps2x.Analog(PSS_RY);
    lypos = ps2x.Analog(PSS_LY);
    lxpos = ps2x.Analog(PSS_LX);

      
    lxpos = DeadZone(lxpos,DeadZP,JoyMid);
    lypos = DeadZone(lypos,DeadZP,JoyMid);
    rxpos = DeadZone(rxpos,DeadZP,JoyMid);
    rypos = DeadZone(rypos,DeadZP,JoyMid);

    Serial.print("Joystick Position (x,y): ");
    Serial.print(rxpos,1);
    Serial.print(", ");
    Serial.println(lypos,1);

    //Begin Servo Control
    Hservopos = map(rxpos,JoyMin,JoyMax,HMin,HMax);
    Vservopos = map(rypos,JoyMin,JoyMax,VMin,VMax);
    
    Serial.print("Servo Position (H,V): ");
    Serial.print(Hservopos);
    Serial.print(", ");
    Serial.println(Vservopos);
    
    Hservopos = map(Hservopos,ServoMin,ServoMax,MinServoF,MaxServoF);
    Vservopos = map(Vservopos,ServoMin,ServoMax,MinServoF,MaxServoF);
  
      
    HServo.writeMicroseconds(Hservopos);
    VServo.writeMicroseconds(Vservopos);
    
    //Begin Motor Control
    Pow = (abs(lypos-JoyMid)*2);
    Serial.println(Pow);
    analogWrite(FPow,Pow);
    analogWrite(BPow,Pow);
    
    if(lypos > JoyMid){
      digitalWrite(FFor, HIGH);
      digitalWrite(FRev, LOW);
      
      digitalWrite(BFor, HIGH);
      digitalWrite(BRev, LOW);
      Serial.println("Reverse");
    }
    else{
      digitalWrite(FFor, LOW);
      digitalWrite(FRev, HIGH);
      
      digitalWrite(BFor, LOW);
      digitalWrite(BRev, HIGH);
      Serial.println("Forward");
      
    }
    Serial.print(map(analogRead(BPow),0,1023,0,255));
    Serial.print(", ");
    Serial.print(digitalRead(BFor));
    Serial.print(", ");
    Serial.println(digitalRead(BRev));
    }
  
  //delay(200);
}


int DeadZone(int Value,double ZP,int Mid){
  if(Value > (Mid-Mid*(ZP/2)) && Value < (Mid+Mid*(ZP/2)))  //Dead Zone Application
  {
    return Mid;  
  }
  else{
    return Value;
  }
}
