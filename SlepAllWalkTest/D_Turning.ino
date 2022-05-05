void TurnStart() {
  int X = analogRead(XJoyPin);
  int x = DeadZone(X, DeadZonePercentage, JoystickMid);
  int angle = map(x, JoystickMin, JoystickMax, (135 - (TurnRange / 2)), (135 + (TurnRange / 2)));
  Waist.writeMicroseconds(map(angle, ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
}

void TurnEnd() {
  Waist.writeMicroseconds(map(ServoAngleMid, ServoAngleMin, ServoAngleMax, SERVOMIN, SERVOMAX));
}
