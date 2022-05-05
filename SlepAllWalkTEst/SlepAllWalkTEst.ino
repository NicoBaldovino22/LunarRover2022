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

double AttackMin = .05;
double AttackMax = .15;

const int TurnRange = 20;


const int ServoAngleMin = 0;
const int ServoAngleMax = 270;
const int ServoAngleMid = (ServoAngleMin + ServoAngleMax) / 2;
const int DELAY = 100;

const int JoystickMin = 0;
const int JoystickMax = 1023;
const int JoystickMid = (JoystickMin + JoystickMax) / 2;

const double DeadZonePercentage = .10;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("All Walk Test");

  Waist.attach(WaistPin);
  Waist.writeMicroseconds(map(ServoAngleMid, ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  delay(DELAY);
  //Power for joystick
  pinMode(A0, INPUT);

  //Step(0,0,0,0,0);
  Step(+25, -45, -45, +85, 0);
  //delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int XJoy = analogRead(A0);
  int YJoy = analogRead(A1);

  XJoy = DeadZone(XJoy, DeadZonePercentage, JoystickMid);
  YJoy = DeadZone(YJoy, DeadZonePercentage, JoystickMid);

  if (YJoy <= JoystickMid) {
    walk(XJoy, YJoy);
  }
}
