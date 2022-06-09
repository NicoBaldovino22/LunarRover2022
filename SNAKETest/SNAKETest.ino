
#include <Adafruit_PWMServoDriver.h>  //For usage with PCA9685 (Servo Control)
#include <Wire.h>   //For usage with PCA9685 (Servo Control)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();    //For usage with PCA9685 (Servo Control)

#define SERVOMIN 500    //For usage with PCA9685 (Servo Control) //WARNING
#define SERVOMAX 2500   //For usage with PCA9685 (Servo Control) //WARNING
#define USMIN 2000      //For usage with PCA9685 (Servo Control)
#define USMAX 10000     //For usage with PCA9685 (Servo Control)
#define SERVO_FREQ 50   //For usage with PCA9685 (Servo Control)

uint8_t ServoA = 0;
uint8_t ServoB = 1;
uint8_t ServoC = 2;
uint8_t ServoD = 3;
uint8_t ServoE = 4;
uint8_t ServoF = 5;
uint8_t ServoG = 6;
uint8_t ServoH = 7;

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
    int E = (XRange / 2) * sin(Speed * n + Offset * 4);
    int F = (XRange / 2) * sin(Speed * n + Offset * 5);
    int G = (XRange / 2) * sin(Speed * n + Offset * 6);
    int H = (XRange / 2) * sin(Speed * n + Offset * 7);

    pwm.writeMicroseconds(ServoA, map(ServoMid + A, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(ServoB, map(ServoMid + B, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(ServoC, map(ServoMid + C, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(ServoD, map(ServoMid + D, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(ServoE, map(ServoMid + E, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(ServoF, map(ServoMid + F, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(ServoG, map(ServoMid + G, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    pwm.writeMicroseconds(ServoH, map(ServoMid + H, ServoMinA, ServoMaxA, SERVOMIN, SERVOMAX));
    n++;
    
    delay(10);
    Butt = digitalRead(ButtPin);
  }
}
