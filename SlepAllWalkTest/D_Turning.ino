void TurnStart(int x) {
  int angle = map(x, 0, 1023, (135 - (TurnRange / 2)), (135 + (TurnRange / 2)));
  Waist.writeMicroseconds(map(angle, ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
}

void TurnEnd(int x) {
  Waist.writeMicroseconds(map(ServoAngleMid, ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
}
