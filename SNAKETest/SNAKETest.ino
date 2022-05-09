
#include <Adafruit_PWMServoDriver.h>  //For usage with PCA9685 (Servo Control)
#include <Wire.h>   //For usage with PCA9685 (Servo Control)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();    //For usage with PCA9685 (Servo Control)

#define SERVOMIN 500    //For usage with PCA9685 (Servo Control) //WARNING
#define SERVOMAX 2500   //For usage with PCA9685 (Servo Control) //WARNING
#define USMIN 2000      //For usage with PCA9685 (Servo Control)
#define USMAX 10000     //For usage with PCA9685 (Servo Control)
#define SERVO_FREQ 50   //For usage with PCA9685 (Servo Control)

uint8_t TA = 0;
uint8_t BA = 1;

uint8_t TB = 2;
uint8_t BB = 3;

uint8_t TC = 4;
uint8_t BC = 5;

uint8_t TD = 6;
uint8_t BD = 7;

const int ServoMinA = 0;
const int ServoMaxA = 180;
const int ServoMid = (ServoMinA +ServoMaxA)/2;

const int XRange = 100;
const int YRange = 30;

const double Speed = 0.025;
const int Offset = 20;

const int ButtPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ButtPin, INPUT);
  pwm.begin();                          //For usage with PCA9685 (Servo Control)
  pwm.setOscillatorFrequency(27000000); //For usage with PCA9685 (Servo Control)
  pwm.setPWMFreq(SERVO_FREQ);           //For usage with PCA9685 (Servo Control)

}

void loop() {
  // put your main code here, to run repeatedly:
  int Butt = digitalRead(ButtPin);
  double n = 0;
  while (Butt == LOW) {
    Serial.println("Start Slither");
    int A = (XRange / 2) * sin(Speed * n);
    int B = (XRange / 2) * sin(Speed * n + Offset);
    int C = (XRange / 2) * sin(Speed * n + Offset * 2);
    int D = (XRange / 2) * sin(Speed * n + Offset * 3);

    int AY = abs(abs((XRange / 2) - A) - YRange);
    int BY = abs(abs((XRange / 2) - B) - YRange);
    int CY = abs(abs((XRange / 2) - C) - YRange);
    int DY = abs(abs((XRange / 2) - D) - YRange);

    Serial.print("AX: ");
    Serial.println(A);
    Serial.print("AY: ");
    Serial.println(AY);

    pwm.writeMicroseconds(TA, map(ServoMid + AY, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(BA, map(ServoMid + A, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));

    pwm.writeMicroseconds(TB, map(ServoMid + BY, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(BB, map(ServoMid + B, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));

    pwm.writeMicroseconds(TC, map(ServoMid + CY, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(BC, map(ServoMid + C, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));

    pwm.writeMicroseconds(TD, map(ServoMid + DY, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(BD, map(ServoMid + D, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));

    n++;
    delay(10);
    Butt = digitalRead(ButtPin);
  }
  pwm.writeMicroseconds(TA, map(ServoMid, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(BA, map(ServoMid, (ServoMid - (XRange / 2)), (ServoMid + (XRange / 2)), SERVOMIN, SERVOMAX));

  pwm.writeMicroseconds(TB, map(ServoMid, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(BB, map(ServoMid, (ServoMid - (XRange / 2)), (ServoMid + (XRange / 2)), SERVOMIN, SERVOMAX));

  pwm.writeMicroseconds(TC, map(ServoMid, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(BC, map(ServoMid, (ServoMid - (XRange / 2)), (ServoMid + (XRange / 2)), SERVOMIN, SERVOMAX));

  pwm.writeMicroseconds(TD, map(ServoMid, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(BD, map(ServoMid, (ServoMid - (XRange / 2)), (ServoMid + (XRange / 2)), SERVOMIN, SERVOMAX));
}
