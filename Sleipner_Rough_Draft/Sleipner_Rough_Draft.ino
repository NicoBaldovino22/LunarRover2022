//~~~INFO~~~
//This is a basic NON FUNCTIONAL script. Its main purpose is to create the "bones" that will likely
  //be used on future functioning code. This code is also mainly setup to display a forward motion.

//~~~ASSUMPTIONS~~~
//Positive Direction of rotation is toward the forward direction (not accurate to reality, but needs
  //to be adjusted once applied to physical bot.
//Hip Servos have their mid point of their range pointed straight down.
//Knee Servos have their mid point of their range parallel to the thigh.

#include <Servo.h>
const int Delay = 3000;

//Inputs
 //
//Servos
 //Top
  Servo TFRH; //Top Front Right Hip
  Servo TFRK; //Top Front Right Knee
  
  Servo TFLH; //Top Front Left Hip
  Servo TFLK; //Top Front Left Knee
  
  Servo TBRH; //Top Back Right Hip
  Servo TBRK; //Top Back Right Knee
  
  Servo TBLH; //Top Back Left Hip
  Servo TBLK; //Top Back Left Knee
 //Bottom
  Servo BFRH; //Bottom Front Right Hip
  Servo BFRK; //Bottom Front Right Knee
  
  Servo BFLH; //Bottom Front Left Hip
  Servo BFLK; //Bottom Front Left Knee
  
  Servo BBRH; //Bottom Back Right Hip
  Servo BBRK; //Bottom Back Right Knee
  
  Servo BBLH; //Bottom Back Left Hip
  Servo BBLK; //Bottom Back Left Knee
 //Variables
  const int ServoMin = 0;
  const int ServoMax = 270;
  const int MinServoF = 500;
  const int MaxServoF = 2500;
 //Calculated
  const int ServoMid = (ServoMin+ServoMax)/2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  TFRH.attach(11);
  TFRK.attach(10);
  BFRH.attach(9);
  BFRK.attach(5);
  
  TFRH.writeMicroseconds(map(ServoMid+45,ServoMin,ServoMax,MinServoF,MaxServoF));
  TFRK.writeMicroseconds(map(ServoMid+45,ServoMin,ServoMax,MinServoF,MaxServoF));
  BFRH.writeMicroseconds(map(ServoMid,ServoMin,ServoMax,MinServoF,MaxServoF));
  BFRK.writeMicroseconds(map(ServoMid,ServoMin,ServoMax,MinServoF,MaxServoF));

}

void loop() {
  // put your main code here, to run repeatedly:
  //Step 1
  Serial.println("Step 1 Start");
  int NewDeg = map(ServoMid-45,ServoMin,ServoMax,MinServoF,MaxServoF);
  TFRH.writeMicroseconds(NewDeg);
  BFRK.writeMicroseconds(NewDeg);
  NewDeg = map(ServoMid-45,ServoMin,ServoMax,MinServoF,MaxServoF);
  TFRK.writeMicroseconds(NewDeg);
  BFRH.writeMicroseconds(NewDeg);
  //delay(Delay/2);
  NewDeg = map(ServoMid,ServoMin,ServoMax,MinServoF,MaxServoF);
  BFRK.writeMicroseconds(NewDeg);
  BFRH.writeMicroseconds(NewDeg);
  delay(Delay);  
  //Step 2
  Serial.println("Step 2 Start");
  NewDeg = map(ServoMid-120,ServoMin,ServoMax,MinServoF,MaxServoF);
  TFRH.writeMicroseconds(NewDeg);
  NewDeg = map(ServoMid-120,ServoMin,ServoMax,MinServoF,MaxServoF);
  TFRK.writeMicroseconds(NewDeg);
  delay(Delay);
  //Step 3
  Serial.println("Step 3 Start");
  NewDeg = map(ServoMid+45,ServoMin,ServoMax,MinServoF,MaxServoF);
  TFRH.writeMicroseconds(NewDeg);
  delay(Delay/2);
  NewDeg = map(ServoMid+45,ServoMin,ServoMax,MinServoF,MaxServoF);
  TFRK.writeMicroseconds(NewDeg);
  delay(Delay);

  
//  THStep1(TFRH,TFLH,TBRH,TBLH);
//  TKStep1(TFRK,TFLK,TBRK,TBLK);
//  BHStep1(BFRH,BFLH,BBRH,BBLH);
//  BKStep1(BFRK,BFLK,BBRK,BBLK);
//  delay(100);
//  THStep2(TFRH,TFLH,TBRH,TBLH);
//  TKStep2(TFRK,TFLK,TBRK,TBLK);
//  delay(100);
//  THStep3(TFRH,TFLH,TBRH,TBLH);
//  TKStep3(TFRK,TFLK,TBRK,TBLK);
//  delay(100);
}

int THStep1(int FR,int FL,int BR,int BL){ //Top Hip Step 1 (rotate from +45 deg to -45 deg relative to mid)
  int NewDeg = map(ServoMid-45,ServoMin,ServoMax,MinServoF,MaxServoF);
//  FR.writeMicroseconds(NewDeg);
//  FL.writeMicroseconds(NewDeg);
//  BR.writeMicroseconds(NewDeg);
//  BL.writeMicroseconds(NewDeg);
}
int TKStep1(int FR,int FL,int BR,int BL){ //Top Hip Step 1 (rotate from -45 deg to +45 deg relative to mid)
  int NewDeg = map(ServoMid+45,ServoMin,ServoMax,MinServoF,MaxServoF);
//  FR.writeMicroseconds(NewDeg);
//  FL.writeMicroseconds(NewDeg);
//  BR.writeMicroseconds(NewDeg);
//  BL.writeMicroseconds(NewDeg);
}
int BHStep1(int FR,int FL,int BR,int BL){ //Top Hip Step 1 (rotate from +45 deg to -45 deg relative to mid)
  int NewDeg = map(ServoMid+45,ServoMin,ServoMax,MinServoF,MaxServoF);
//  FR.writeMicroseconds(NewDeg);
//  FL.writeMicroseconds(NewDeg);
//  BR.writeMicroseconds(NewDeg);
//  BL.writeMicroseconds(NewDeg);
}
int BKStep1(int FR,int FL,int BR,int BL){ //Top Hip Step 1 (rotate from +45 deg to -45 deg relative to mid)
  int NewDeg = map(ServoMid-45,ServoMin,ServoMax,MinServoF,MaxServoF);
//  FR.writeMicroseconds(NewDeg);
//  FL.writeMicroseconds(NewDeg);
//  BR.writeMicroseconds(NewDeg);
//  BL.writeMicroseconds(NewDeg);
//  delay(50)
//  NewDeg = map(ServoMid,ServoMin,ServoMax,MinServoF,MaxServoF);
//  FR.writeMicroseconds(NewDeg);
//  FL.writeMicroseconds(NewDeg);
//  BR.writeMicroseconds(NewDeg);
//  BL.writeMicroseconds(NewDeg);
}


int THStep2(int FR,int FL,int BR,int BL){ //Top Hip Step 1 (rotate from +45 deg to -45 deg relative to mid)
  int NewDeg = map(ServoMid-60,ServoMin,ServoMax,MinServoF,MaxServoF);
//  FR.writeMicroseconds(NewDeg);
//  FL.writeMicroseconds(NewDeg);
//  BR.writeMicroseconds(NewDeg);
//  BL.writeMicroseconds(NewDeg);
}
int TKStep2(int FR,int FL,int BR,int BL){ //Top Hip Step 1 (rotate from -45 deg to +45 deg relative to mid)
  int NewDeg = map(ServoMid+60,ServoMin,ServoMax,MinServoF,MaxServoF);
//  FR.writeMicroseconds(NewDeg);
//  FL.writeMicroseconds(NewDeg);
//  BR.writeMicroseconds(NewDeg);
//  BL.writeMicroseconds(NewDeg);
}


int THStep3(int FR,int FL,int BR,int BL){ //Top Hip Step 1 (rotate from +45 deg to -45 deg relative to mid)
  int NewDeg = map(ServoMid+45,ServoMin,ServoMax,MinServoF,MaxServoF);
//  FR.writeMicroseconds(NewDeg);
//  FL.writeMicroseconds(NewDeg);
//  BR.writeMicroseconds(NewDeg);
//  BL.writeMicroseconds(NewDeg);
}
int TKStep3(int FR,int FL,int BR,int BL){ //Top Hip Step 1 (rotate from -45 deg to +45 deg relative to mid)
  int NewDeg = map(ServoMid-45,ServoMin,ServoMax,MinServoF,MaxServoF);
//  FR.writeMicroseconds(NewDeg);
//  FL.writeMicroseconds(NewDeg);
//  BR.writeMicroseconds(NewDeg);
//  BL.writeMicroseconds(NewDeg);
}
