const int pingout=7;
const int pingin=8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pingout,OUTPUT);
  pinMode(pingin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, inches, cm;
  int microSec1=2;
  int microSec2=5;
  int pingDelayTime=100;
  
  digitalWrite(pingout,LOW);
  delayMicroseconds(2);

  digitalWrite(pingout,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingout,LOW);

  duration = pulseIn(pingin,HIGH);
  inches = microSecToInches(duration);
  cm=microSecToCm(duration);
  Serial.print(inches);
  Serial.print("in,");
  Serial.print(cm);
  Serial.print("cm,");
  Serial.println();
  delay(pingDelayTime);
  }
  long microSecToInches(long microseconds){
    return microseconds/74/2;
  }
  long microSecToCm(long microseconds){
    return microseconds/29/2;
  }
