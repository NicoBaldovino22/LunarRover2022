
#include <Servo.h>

const int XJoy = A1;
const int YJoy = A0;
Servo ExServo;
double xpos;
double ypos;
int servopos;
const int ServoRate = 20;
const int ServoMin = 0;
const int ServoMax = 360;

const double DeadZP = .10;




void setup() {
 Serial.begin(9600);
  // put your setup code here, to run once:
  ExServo.attach(11);
  ExServo.write(180);
  pinMode(XJoy, INPUT);     // X position of Joystick, 0 to 1023                 
  pinMode(YJoy, INPUT);     // Y position of Joystick, 0 to 1023
  servopos = 180;
  pinMode(12, OUTPUT);
  digitalWrite(12,HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  xpos = analogRead(XJoy);
  ypos = analogRead(YJoy);

 
  if(xpos > (511.5-511.5*DeadZP) && xpos < (511.5+511.5*DeadZP))  //Dead Zone Application
  {
    xpos = 511.5;  
  }
    
  Serial.print("Joystick Position (x): ");
  Serial.println(xpos,1);
  //Serial.print(", ");
  //Serial.println(ypos,0);
  
  if(xpos > 512 && servopos <= ServoMax)
  {
    servopos = servopos + ServoRate;
    if(servopos > ServoMax) servopos = ServoMax;
  }
  else if(xpos < 511 && servopos >= ServoMin)
  {
    servopos = servopos - ServoRate;
    if(servopos < ServoMin) servopos = ServoMin;
  }
  
  Serial.print("Servo Position: ");
  Serial.println(servopos);
  
  ExServo.write(servopos);
  delay(200);
}
