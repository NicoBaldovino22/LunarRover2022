
#include <Servo.h>

const int XJoy = A0;
const int YJoy = A1;
const int SW = A2;
Servo XServo;
Servo YServo;
double xpos;
double ypos;
int Xservopos;
int Yservopos;
const int ServoRate = 20;
const int ServoMin = 0;
const int ServoMax = 180;

const int For = 22;
const int Rev = 23;
const int Pow = 11;

const double DeadZP = .10;




void setup() {
 Serial.begin(9600);
  // put your setup code here, to run once:
  XServo.attach(11);
  XServo.write(ServoMax/2);
  YServo.attach(10);
  YServo.write(ServoMax/2);
  pinMode(XJoy, INPUT);     // X position of Joystick, 0 to 1023                 
  pinMode(YJoy, INPUT);     // Y position of Joystick, 0 to 1023
  Xservopos = ServoMax/2;
  Yservopos = ServoMax/2;
  pinMode(Pow, OUTPUT);
  pinMode(For, INPUT);
  pinMode(Rev, INPUT);

  digitalWrite(For, HIGH);
  digitalWrite(Rev, LOW);
  analogWrite(Pow, 255);

}

void loop() {
  // put your main code here, to run repeatedly:
  xpos = analogRead(XJoy);
  ypos = analogRead(YJoy);

 
  if(xpos > (511.5-511.5*DeadZP) && xpos < (511.5+511.5*DeadZP))  //Dead Zone Application
  {
    xpos = 511.5;  
  }
  if(ypos > (511.5-511.5*DeadZP) && ypos < (511.5+511.5*DeadZP))  //Dead Zone Application
  {
    ypos = 511.5;  
  }
    
  Serial.print("Joystick Position (x,y): ");
  Serial.print(xpos,1);
  Serial.print(", ");
  Serial.println(ypos,1);
  
  if(xpos > 512 && Xservopos <= ServoMax)
  {
    Xservopos = Xservopos + ServoRate;
    if(Xservopos > ServoMax) Xservopos = ServoMax;
  }
  else if(xpos < 511 && Xservopos >= ServoMin)
  {
    Xservopos = Xservopos - ServoRate;
    if(Xservopos < ServoMin) Xservopos = ServoMin;
  }
  if(ypos > 512 && Yservopos <= ServoMax)
  {
    Yservopos = Yservopos + ServoRate;
    if(Yservopos > ServoMax) Yservopos = ServoMax;
  }
  else if(ypos < 511 && Yservopos >= ServoMin)
  {
    Yservopos = Yservopos - ServoRate;
    if(Yservopos < ServoMin) Yservopos = ServoMin;
  }
  
  Serial.print("Servo Position (x,y): ");
  Serial.print(Xservopos);
  Serial.print(", ");
  Serial.println(Yservopos);
  
  XServo.write(Xservopos);
  YServo.write(Yservopos);
  delay(100);
}
