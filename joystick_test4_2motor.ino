int LeftPow = 9;
int LeftFor = 4;
int LeftRev = 5;
int RightPow = 10;
int RightFor = 6;
int RightRev = 7;
int LeftJoy,RightJoy;
int LeftPower,RightPower;
const double DeadZP = .05;
void setup() {
  Serial.begin(9600);
  pinMode(LeftPow, OUTPUT);
  pinMode(RightPow, OUTPUT);
  pinMode(LeftFor, INPUT);
  pinMode(LeftRev, INPUT);
  pinMode(RightFor, INPUT);
  pinMode(RightRev, INPUT);

  digitalWrite(RightFor, LOW);
  digitalWrite(RightRev,LOW);
  digitalWrite(LeftFor,LOW);
  digitalWrite(LeftRev,LOW);
}

void loop() {
  LeftJoy=analogRead(A1);
  RightJoy=analogRead(A3);
  Serial.print("LeftJoy,RightJoy");
  Serial.print(LeftJoy);
  Serial.print(",");
  Serial.println(RightJoy);

  if (LeftJoy > 512){
    LeftPower=map(LeftJoy,512,1023,178,255);
    digitalWrite(LeftFor, HIGH);
    digitalWrite(LeftRev, LOW);
    }
   else {
    LeftJoy = 1023-LeftJoy;
    LeftPower=map(LeftJoy,512,1023,178,255);
    digitalWrite(LeftFor, LOW);
    digitalWrite(LeftRev,HIGH);   
   }
   if(LeftJoy > (511.5-511.5*DeadZP) && LeftJoy < (511.5+511.5*DeadZP)){
    LeftPower = 0;
    }

  if (RightJoy > 512){
    RightPower=map(RightJoy,512,1023,178,255);
    digitalWrite(RightFor, HIGH);
    digitalWrite(RightRev, LOW);
    }
   else {
    RightJoy = 1023-RightJoy;
    RightPower=map(RightJoy,512,1023,178,255);
    digitalWrite(RightFor, LOW);
    digitalWrite(RightRev,HIGH);   
   }
   if(RightJoy > (511.5-511.5*DeadZP) && RightJoy < (511.5+511.5*DeadZP)){
    RightPower = 0;
    }
   analogWrite(LeftPow,LeftPower);
  Serial.print("LeftPower,RightPower");
  Serial.print(LeftPower);
  Serial.print(",");
  Serial.println(RightPower);
  }

  
  
