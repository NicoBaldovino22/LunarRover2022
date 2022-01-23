const int XJoy = A1;
const int YJoy = A0;
const int LinAct = 6;
const int LinFor = 7;
const int LinRev = 8;
double xpos;
double ypos;
const double DeadZP = .05;
double LinActPow;
int Dir = 0;  // 0 = Neutral, 1 = Forward, 2 = Reverse


void setup() {
 Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(LinAct, OUTPUT);
  pinMode(LinFor, INPUT);
  pinMode(LinRev, INPUT);
  pinMode(XJoy, INPUT);     // X position of Joystick, 0 to 1023                 
  pinMode(YJoy, INPUT);     // Y position of Joystick, 0 to 1023 

  digitalWrite(LinFor, LOW);
  digitalWrite(LinRev, LOW);
  
}

void loop() {
  xpos = analogRead(XJoy);
  ypos = analogRead(YJoy);

  Serial.print("Joystick Position (x,y): ");
  Serial.print(xpos,0);
  Serial.print(", ");
  Serial.println(ypos,0);

  if(xpos > 511.5)
  {
    LinActPow = map(xpos,512,1023,178,255);
    digitalWrite(LinFor, HIGH);
    digitalWrite(LinRev, LOW);
    Dir = 1;
  }
  else
  {
    xpos = 1023 - xpos;
    LinActPow = map(xpos,512,1023,178,255);
    digitalWrite(LinFor, LOW);
    digitalWrite(LinRev, HIGH);
    Dir = 2;
  }
  
  if(xpos > (511.5-511.5*DeadZP) && xpos < (511.5+511.5*DeadZP))
  {
    LinActPow = 0;  
    Dir = 0;
  }  
  analogWrite(LinAct,LinActPow);
  
  if(Dir == 0)
    Serial.println("NEUTRAL");
  else if(Dir == 1)
    Serial.println("FORWARD");
  else
    Serial.println("REVERSE");
    
  Serial.print("Linear Actuator Power: ");
  Serial.print((LinActPow/255)*100);
  Serial.println("%");
  
  Serial.println("");
  Serial.println("");

  delay(200);
}
