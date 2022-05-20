#include <Adafruit_PWMServoDriver.h>  //For usage with PCA9685 (Servo Control)
#include <Wire.h>   //For usage with PCA9685 (Servo Control)
#include <Servo.h>  //For direct control of servos (waist as of 5/4/22)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();    //For usage with PCA9685 (Servo Control)

#define SERVOMIN 500    //For usage with PCA9685 (Servo Control)
#define SERVOMAX 2500   //For usage with PCA9685 (Servo Control)
#define USMIN 2000      //For usage with PCA9685 (Servo Control)
#define USMAX 10000     //For usage with PCA9685 (Servo Control)
#define SERVO_FREQ 50   //For usage with PCA9685 (Servo Control)

bool FIRST = true;    //Used for defining previous servo positions for smoothing function for the first iteration of the step function

Servo Waist;    //Defines "Waist" as servo using <Servo.h>
const int WaistPin = 3;   //Defines Waist Pin
const int WaistOffset = -5;

uint8_t SFL = 0;    //Shoulder, Front/Back, Left/Right
uint8_t SFR = 1;    //Defines servo for control with PCA9685
uint8_t SBL = 2;
uint8_t SBR = 3;

uint8_t EFL = 4;    //Elbow, Front/Back, Left/Right
uint8_t EFR = 5;    //Defines servo for control with PCA9685
uint8_t EBL = 6;
uint8_t EBR = 7;

uint8_t HFL = 8;    //Hip, Front/Back, Left/Right
uint8_t HFR = 9;    //Defines servo for control with PCA9685
uint8_t HBL = 10;
uint8_t HBR = 11;

uint8_t KFL = 12;   //Knee, Front/Back, Left/Right
uint8_t KFR = 13;   //Defines servo for control with PCA9685
uint8_t KBL = 14;
uint8_t KBR = 15;

int SFLOff = 0;     //Defines Offset to be used in Leg/Arm Functions
int SFROff = -7;
int SBLOff = -5;
int SBROff = -2;

int EFLOff = 0;     //Defines Offset to be used in Leg/Arm Functions
int EFROff = -5;
int EBLOff = +5;
int EBROff = 0;

int HFLOff = 0;     //Defines Offset to be used in Leg/Arm Functions
int HFROff = 0;
int HBLOff = 0;
int HBROff = 0;

int KFLOff = 0;     //Defines Offset to be used in Leg/Arm Functions
int KFROff = -5;
int KBLOff = 0;
int KBROff = 0;

double ps, pe, ph, pk;   //Intiates previous Shoulder, Elbow, Hip, and Knee servo angle for use in step & smoothing function

const float AttackMin = 0.05;   //Defines Attack min and max for usage in Smoothing Function
const float AttackMax = 0.15;

const int TurnRange = 25;   //Defines Turning Range (degrees) to be used in Turning Function


const int ServoAngleMin = 0;    //Defines Servo Angle Info (degrees)
const int ServoAngleMax = 270;
const int ServoAngleMid = (ServoAngleMin + ServoAngleMax) / 2;

const int JoystickMin = 0;      //Defines Joystick input info
const int JoystickMax = 1023;
const int JoystickMid = (JoystickMin + JoystickMax) / 2;
const int XJoyPin = A0;   //Defines X Axis of Joystick Pin
const int YJoyPin = A1;   //Defines Y Axis of Joystick Pin
const int JoyPower = 13;

const double DeadZonePercentage = .20;    //Defines percentage that reads as neutral in DeadZone Function (about dead center of joystick)

const int SStep0 = +30;
const int EStep0 = -60;
const int HStep0 = -45;
const int KStep0 = +78;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("All Walk Test");

  Waist.attach(WaistPin);
  Waist.writeMicroseconds(map(ServoAngleMid, ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));

  pwm.begin();                          //For usage with PCA9685 (Servo Control)
  pwm.setOscillatorFrequency(27000000); //For usage with PCA9685 (Servo Control)
  pwm.setPWMFreq(SERVO_FREQ);           //For usage with PCA9685 (Servo Control)

  pinMode(XJoyPin, INPUT);
  pinMode(YJoyPin, INPUT);
  pinMode(JoyPower, OUTPUT);
  digitalWrite(JoyPower, HIGH);

  //Step(0,0,0,0);
  Step(SStep0, EStep0, HStep0, KStep0);
  //delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int XJoy = analogRead(XJoyPin);
  int YJoy = analogRead(YJoyPin);

  XJoy = DeadZone(XJoy, DeadZonePercentage, JoystickMid);
  YJoy = DeadZone(YJoy, DeadZonePercentage, JoystickMid);
  //Serial.println(XJoy);
  //Serial.println(YJoy);
  
  if (XJoy > JoystickMid+JoystickMid/1.5 || XJoy < JoystickMid-JoystickMid/1.5) {
    turn();
  }
  if (YJoy > JoystickMid + JoystickMid/1.5) {
    walk();
    Serial.println();
    Serial.println("End Walk Cycle");
    Serial.println();
  }
  if (YJoy < JoystickMid - JoystickMid/1.5) {
    reverse();
    Serial.println();
    Serial.println("End Reverse Cycle");
    Serial.println();
  }

}
