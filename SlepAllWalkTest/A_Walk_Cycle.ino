void walk() {
  Serial.println("Step 1: Start");
  Step(0, 0, +45, +45, 20);
  TurnEnd();
  Step(-35, +45, -45, +85, 20);

  Serial.println("Step 2: Start");
  Step(-50, +120, -45, +85, 35);

  TurnStart();

  Serial.println("Step 3: Start");
  Step(+40, -45, -45, +85, 40);
  Step(+25, -45, -45, +85, 35);
}
