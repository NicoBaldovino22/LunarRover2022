float Smooth(int prev, int next) {
  int Y = analogRead(YJoyPin);                                          //reads Y Joytick (forward/backward)
  int y = DeadZone(Y, DeadZonePercentage, JoystickMid);                 //applies deadzone function 
  y = JoystickMax - y;                                                  //WARNING!!! only needed when forward approaches 0 (inverts value)
  int Attack = map(y, JoystickMid, JoystickMax, AttackMin, AttackMax);  //Maps the users input to the attack percentage based on min/max
  return ((next * (Attack)) + (prev * (1 - Attack)));                   //ACTUAL SMOOTHING FUNCTION, based on James Burton video (How To Make Robots Move Smoothly | Arduino Tutorial, Aug. 2021)
}
