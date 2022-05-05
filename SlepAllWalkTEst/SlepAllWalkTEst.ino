#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <Servo.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 500
#define SERVOMAX 2500
#define USMIN 2000
#define USMAX 10000
#define SERVO_FREQ 50

bool FIRST = true;

 Servo Waist;
 const int WaistPin = 3;

 uint8_t SFL = 0;
 uint8_t SFR = 1;
 uint8_t SBL = 2;
 uint8_t SBR = 3;
 
 uint8_t EFL = 4;
 uint8_t EFR = 5;
 uint8_t EBL = 6;
 uint8_t EBR = 7;
 
 uint8_t HFL = 8;
 uint8_t HFR = 9;
 uint8_t HBL = 10;
 uint8_t HBR = 11;
 
 uint8_t KFL = 12;
 uint8_t KFR = 13;
 uint8_t KBL = 14;
 uint8_t KBR = 15;
 
 int SFLOff = 0;
 int SFROff = -7;
 int SBLOff = -5;
 int SBROff = -2;
 
 int EFLOff = 0;
 int EFROff = -5;
 int EBLOff = +5;
 int EBROff = 0;
 
 int HFLOff = 0;
 int HFROff = 0;
 int HBLOff = 0;
 int HBROff = 0;
 
 int KFLOff = 0;
 int KFROff = -5;
 int KBLOff = +7;
 int KBROff = 0;
 
  int ps, pe, ph, pk;

  double Agressivness = .15;

  const int TurnRange = 20;
 
 
 const int ServoAngleMin = 0;
 const int ServoAngleMax = 270;
 const int ServoAngleMid = (ServoAngleMin+ServoAngleMax)/2;
 const int DELAY = 100;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("All Walk Test");

  Waist.attach(WaistPin);
  Waist.writeMicroseconds(map(ServoAngleMid,ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));  

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  delay(DELAY);
  //Power for joystick
  pinMode(A0,INPUT);

  //Step(0,0,0,0,0);
  //delay(DELAY);
  Step(+25,-45,-45,+85,0);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int XJoy = analogRead(A0

  int YJoy = analogRead(A1);
  if(YJoy <= 20){
    walk(XJoy,YJoy);
    }
}
  
void walk(int X,int Y){
  Serial.println("Step 1: Start");
  Step(0,0,+45,+45,20);
  TurnEnd(X);
  Step(-35,+45,-45,+85,20);
  
  Serial.println("Step 2: Start");
  Step(-50,+120,-45,+85,35);
  
  TurnStart(X);
  
  Serial.println("Step 3: Start");
  Step(+40,-45,-45,+85,40);  
  Step(+25,-45,-45,+85,35);
}

void TurnStart(int x){
  int angle = map(x,0,1023,(135-(TurnRange/2)),(135+(TurnRange/2)));  
  Waist.writeMicroseconds(map(angle,ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
}

void TurnEnd(int x){
  Waist.writeMicroseconds(map(ServoAngleMid,ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));  
}

void Step(int s, int e,int h, int k, int iter){
  if(FIRST == false)
  {
    Serial.println("Non-First Step");
  for(int i = 0; i <= iter; i++){
    ps = Smooth(ps,s);
    pe = Smooth(pe,e);
    ph = Smooth(ph,h);
    pk = Smooth(pk,k);
    Shoulder(ps);
    Elbow(pe);
    Hip(ph);
    Knee(pk);
    delay(10);
    }
  ps = s;
  pe = e;
  ph = h;
  pk = k;
  }
  else
  {
    Serial.println("First Step");
    Shoulder(s);
    Elbow(e);
    Hip(h);
    Knee(k);
    ps = s;
    pe = e;
    ph = h;
    pk = k;
    FIRST = false;
  }
}

float Smooth(int prev, int next){
  return ((next*(Agressivness))+(prev*(1-Agressivness)));
}

void Shoulder(int NewDeg){
    //Serial.print(NewDeg);
    //Serial.print(", ");
  pwm.writeMicroseconds(SFL,map(ServoAngleMid-(NewDeg+SFLOff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(SFR,map(ServoAngleMid+(NewDeg+SFROff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(SBL,map(ServoAngleMid-(NewDeg+SBLOff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(SBR,map(ServoAngleMid+(NewDeg+SBROff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
}
void Elbow(int NewDeg){
    //Serial.print(NewDeg);
    //Serial.print(", ");
  pwm.writeMicroseconds(EFL,map(ServoAngleMid-(NewDeg+EFLOff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(EFR,map(ServoAngleMid-(NewDeg+EFROff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(EBL,map(ServoAngleMid-(NewDeg+EBLOff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(EBR,map(ServoAngleMid-(NewDeg+EBROff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
}
void Hip(int NewDeg){
    //Serial.print(NewDeg);
    //Serial.print(", ");
  pwm.writeMicroseconds(HFL,map(ServoAngleMid+(NewDeg+HFLOff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(HFR,map(ServoAngleMid+(NewDeg+HFROff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(HBL,map(ServoAngleMid+(NewDeg-HBLOff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(HBR,map(ServoAngleMid+(NewDeg+HBROff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
}
void Knee(int NewDeg){
    //Serial.println(NewDeg);
  pwm.writeMicroseconds(KFL,map(ServoAngleMid+(NewDeg+KFLOff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(KFR,map(ServoAngleMid+(NewDeg-KFROff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(KBL,map(ServoAngleMid+(NewDeg+KBLOff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
  pwm.writeMicroseconds(KBR,map(ServoAngleMid+(NewDeg+KBROff),ServoAngleMin,ServoAngleMax,SERVOMIN,SERVOMAX));
}
