void Shoulder(int NewDeg) {
  //Serial.print(NewDeg);
  //Serial.print(", ");
  
  pwm.writeMicroseconds(SFL, map(ServoAngleMid - (NewDeg + SFLOff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(SFR, map(ServoAngleMid + (NewDeg + SFROff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(SBL, map(ServoAngleMid - (NewDeg + SBLOff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(SBR, map(ServoAngleMid + (NewDeg + SBROff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  
}
void Elbow(int NewDeg) {
  //Serial.print(NewDeg);
  //Serial.print(", ");
  
  pwm.writeMicroseconds(EFL, map(ServoAngleMid - (NewDeg + EFLOff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(EFR, map(ServoAngleMid - (NewDeg + EFROff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(EBL, map(ServoAngleMid - (NewDeg + EBLOff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(EBR, map(ServoAngleMid - (NewDeg + EBROff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  
}
void Hip(int NewDeg) {
  //Serial.print(NewDeg);
  //Serial.print(", ");
  
  pwm.writeMicroseconds(HFL, map(ServoAngleMid + (NewDeg + HFLOff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(HFR, map(ServoAngleMid + (NewDeg + HFROff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(HBL, map(ServoAngleMid + (NewDeg - HBLOff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(HBR, map(ServoAngleMid + (NewDeg + HBROff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  
}
void Knee(int NewDeg) {
  //Serial.println(NewDeg);
  
  pwm.writeMicroseconds(KFL, map(ServoAngleMid + (NewDeg + KFLOff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(KFR, map(ServoAngleMid + (NewDeg - KFROff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(KBL, map(ServoAngleMid + (NewDeg + KBLOff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  pwm.writeMicroseconds(KBR, map(ServoAngleMid + (NewDeg + KBROff), ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
  
}
