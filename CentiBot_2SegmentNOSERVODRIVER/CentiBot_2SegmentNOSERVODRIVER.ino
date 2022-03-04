

#include <Servo.h>

//Input (Joystick)
const int XJoy = A0;
const int YJoy = A1;
const int SW = A2;
//Output (Servos)
Servo LServo;
Servo RServo;
double xpos;
double ypos;
int Lservopos;
int Rservopos;
const int ServoRate = 20;
const int ServoMin = 0;
const int ServoMax = 270;
const int MaxServoF = 2500;
const int MinServoF = 500;

const int For = 22;
const int Rev = 23;
const int Pow = 11;

const double DeadZP = .10;




void setup() {
 Serial.begin(9600);
  // put your setup code here, to run once:
  RServo.attach(11);
  RServo.write(ServoMax/2);
  LServo.attach(10);
  LServo.write(ServoMax/2);
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
  
  if(abs(xpos-511.5)>abs(ypos-511.5))
  {
    Lservopos = map(abs(xpos-511.5),0,511.5,90,180);
    Rservopos = map(abs(xpos-511.5),0,511.5,90,180);
    if(xpos > 511.5)
      Lservopos = 180-Lservopos;
    else
      Rservopos = 180-Rservopos;
  }
  else
  {
    Lservopos = map(abs(ypos-511.5),0,511.5,90,180);
    if(ypos>511.5)
      Lservopos = 180-Lservopos;
    Rservopos = Lservopos;
  }
  Serial.print("Servo Position (L,R): ");
  Serial.print(Lservopos);
  Serial.print(", ");
  Serial.println(Rservopos);

  Rservopos = abs(Rservopos-180);

  Rservopos = Rservopos+45;
  Lservopos = Lservopos+45;
  
  Lservopos = map(Lservopos,0,270,MinServoF,MaxServoF);
  Rservopos = map(Rservopos,0,270,MinServoF,MaxServoF);

    
  LServo.writeMicroseconds(Lservopos);
  RServo.writeMicroseconds(Rservopos);

  delay(1|0);
}
