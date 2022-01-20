const int For = 9;
const int Rev = 8;
const int PWM = 13;

void setup() {
 Serial.begin(57600);
  // put your setup code here, to run once:
  pinMode(For, INPUT);
  pinMode(Rev, INPUT);
  pinMode(PWM, OUTPUT);

  digitalWrite(For, HIGH);
  digitalWrite(Rev, LOW);
  
}

void loop() {
  analogWrite(PWM,255);
}
