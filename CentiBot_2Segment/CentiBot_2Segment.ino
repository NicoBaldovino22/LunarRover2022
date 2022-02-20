

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


#define MIN_PULSE_WIDTH 500
#define MAX_PULSE_WIDTH 2500
#define FREQUENCY 50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//Input (Joystick)
const int XJoy = A0;
const int YJoy = A1;
const int SW = A2;
//Output (Servos)
const int LServo = 15;
const int RServo = 14;
double xpos;
double ypos;
int Lservopos;
int Rservopos;
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
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
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
  int Lpulse_wide,Lpulse_width;
  int Rpulse_wide,Rpulse_width;
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

  Lpulse_wide = map(Lservopos, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  Rpulse_wide = map(Rservopos, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  
  Lpulse_width = int(float(Lpulse_wide) / 1000000 * FREQUENCY * 4096);
  Rpulse_width = int(float(Rpulse_wide) / 1000000 * FREQUENCY * 4096);
  
  pwm.setPWM(LServo, 0, Lpulse_width);
  pwm.setPWM(RServo, 0, Rpulse_width);

  delay(0);
}
