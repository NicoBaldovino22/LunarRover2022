
#include <Adafruit_PWMServoDriver.h>  //For usage with PCA9685 (Servo Control)
#include <Wire.h>   //For usage with PCA9685 (Servo Control)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();    //For usage with PCA9685 (Servo Control)

#define SERVOMIN 500    //For usage with PCA9685 (Servo Control) //WARNING
#define SERVOMAX 2500   //For usage with PCA9685 (Servo Control) //WARNING
#define USMIN 2000      //For usage with PCA9685 (Servo Control)
#define USMAX 10000     //For usage with PCA9685 (Servo Control)
#define SERVO_FREQ 50   //For usage with PCA9685 (Servo Control)

uint8_t FV = 0;
uint8_t FH = 1;
uint8_t BH = 2;
uint8_t BV = 3;

const int ServoMinDeg = 0;
const int ServoMaxDeg = 270;
const int ServoMidDeg = (ServoMinDeg + ServoMaxDeg) / 2;

const int VRange = 90;
const int HRange = 135;

const int XJoyPin = A2;
const int YJoyPin = A1;

const int JoyMin = 0;
const int JoyMax = 1023;
const int JoyMid = (JoyMin + JoyMax) / 2;

const double Attack = .15;
float HSmooth;
float VSmooth;
float HPrev;
float VPrev;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(XJoyPin, INPUT);
  pinMode(YJoyPin, INPUT);
  pwm.begin();                          //For usage with PCA9685 (Servo Control)
  pwm.setOscillatorFrequency(27000000); //For usage with PCA9685 (Servo Control)
  pwm.setPWMFreq(SERVO_FREQ);           //For usage with PCA9685 (Servo Control)

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  HPrev = ServoMidDeg;
  VPrev = ServoMidDeg;
}

void loop() {
  // put your main code here, to run repeatedly:


  int XJoy = analogRead(XJoyPin);
  int YJoy = analogRead(YJoyPin);

  Serial.print("XJoy: ");
  Serial.println(XJoy);
  Serial.print("YJoy: ");
  Serial.println(YJoy);

  int VDeg = map(YJoy, JoyMin, JoyMax, (ServoMidDeg - (VRange / 2)), (ServoMidDeg + (VRange / 2)));
  int HDeg = map(XJoy, JoyMin, JoyMax, (ServoMidDeg - (HRange / 2)), (ServoMidDeg + (HRange / 2)));
  /*
    int VDeg = ServoMidDeg;
    int HDeg = ServoMidDeg;
  */
  Serial.print("VDeg: ");
  Serial.println(VDeg);
  Serial.print("HDeg: ");
  Serial.println(HDeg);

  HSmooth = (HDeg * Attack) + (HPrev * (1 - Attack));
  VSmooth = (VDeg * Attack) + (VPrev * (1 - Attack));
  HPrev = HSmooth;
  VPrev = VSmooth;

  pwm.writeMicroseconds(FV, map(VSmooth, ServoMinDeg, ServoMaxDeg, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(FH, map(HSmooth, ServoMinDeg, ServoMaxDeg, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(BH, map(HSmooth, ServoMinDeg, ServoMaxDeg, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(BV, map(VSmooth, ServoMinDeg, ServoMaxDeg, SERVOMIN, SERVOMAX));
  delay(10);
}
