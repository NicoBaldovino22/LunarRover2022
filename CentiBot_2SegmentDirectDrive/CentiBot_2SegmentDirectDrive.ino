

#include <Servo.h>

//Input (Joystick)
const int XJoy = A0;
const int YJoy = A1;
const int SW = A2;
//Output (Servos)
Servo HServo;
Servo VServo;
double xpos;
double ypos;
int Hservopos;
int Vservopos;

//Joystick Variables
//Variable
const int JoyMin = 0;
const int JoyMax = 1024;
//Calculated
const int JoyMid = (JoyMin+JoyMax)/2;

//Servo Variables
//Variable
const int ServoMin = 0;
const int ServoMax = 270;
const int MaxServoF = 2500;
const int MinServoF = 500;
const int HRange = 90; //Horizontal Range of motion in degrees
const int VRange = 90; //Vertical Range of motion in degrees
//Calculated
const int HMin = ((ServoMax-ServoMin)/2)-(HRange/2);
const int HMax = ((ServoMax-ServoMin)/2)+(HRange/2);
const int VMin = ((ServoMax-ServoMin)/2)-(VRange/2);
const int VMax = ((ServoMax-ServoMin)/2)+(VRange/2);

//Motor Variables
//Variable
const int For = 22;
const int Rev = 23;
const int Pow = 11;

const double DeadZP = .10;  //Deadzone percentage




void setup() {
 Serial.begin(9600);
  // put your setup code here, to run once:
  HServo.attach(10);
  HServo.writeMicroseconds((MaxServoF+MinServoF)/2);
  VServo.attach(11);
  VServo.writeMicroseconds((MaxServoF+MinServoF)/2);
  pinMode(XJoy, INPUT);     // X position of Joystick, 0 to 1023                 
  pinMode(YJoy, INPUT);     // Y position of Joystick, 0 to 1023
//  pinMode(Pow, OUTPUT);
//  pinMode(For, INPUT);
//  pinMode(Rev, INPUT);

//  digitalWrite(For, HIGH);
//  digitalWrite(Rev, LOW);
//  analogWrite(Pow, 255);

}

void loop() {
  // put your main code here, to run repeatedly:
  xpos = analogRead(XJoy);
  ypos = analogRead(YJoy);

 
  if(xpos > (JoyMid-JoyMid*DeadZP) && xpos < (JoyMid+JoyMid*DeadZP))  //Dead Zone Application
  {
    xpos = JoyMid;  
  }
  if(ypos > (JoyMid-JoyMid*DeadZP) && ypos < (JoyMid+JoyMid*DeadZP))  //Dead Zone Application
  {
    ypos = JoyMid;  
  }
    
  Serial.print("Joystick Position (x,y): ");
  Serial.print(xpos,1);
  Serial.print(", ");
  Serial.println(ypos,1);
  
  Hservopos = map(xpos,JoyMin,JoyMax,HMin,HMax);
  Vservopos = map(ypos,JoyMin,JoyMax,VMin,VMax);
  
  Serial.print("Servo Position (H,V): ");
  Serial.print(Hservopos);
  Serial.print(", ");
  Serial.println(Vservopos);
  
  Hservopos = map(Hservopos,ServoMin,ServoMax,MinServoF,MaxServoF);
  Vservopos = map(Vservopos,ServoMin,ServoMax,MinServoF,MaxServoF);

    
  HServo.writeMicroseconds(Hservopos);
  VServo.writeMicroseconds(Vservopos);

}
