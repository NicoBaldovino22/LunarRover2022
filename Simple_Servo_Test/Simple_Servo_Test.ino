const int XJoy = A1;
const int YJoy = A0;
const int servo = 11;
double xpos;
double ypos;
int servopos;
const int ServoRate = 10;

const double DeadZP = .10;

void setup() {
 Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(servo, OUTPUT);
  pinMode(XJoy, INPUT);     // X position of Joystick, 0 to 1023                 
  pinMode(YJoy, INPUT);     // Y position of Joystick, 0 to 1023

}

void loop() {
  // put your main code here, to run repeatedly:
  xpos = analogRead(XJoy);
  ypos = analogRead(YJoy);

 
  if(xpos > (511.5-511.5*DeadZP) && xpos < (511.5+511.5*DeadZP))  //Dead Zone Application
  {
    xpos = 511.5;  
  }
    
  Serial.print("Joystick Position (x): ");
  Serial.println(xpos,1);
  //Serial.print(", ");
  //Serial.println(ypos,0);
  
  if(xpos > 512 && servopos <= 255)
  {
    servopos = servopos + ServoRate;
    if(servopos > 255) servopos = 255;
  }
  else if(xpos < 511 && servopos >= 0)
  {
    servopos = servopos - ServoRate;
    if(servopos < 0) servopos = 0;
  }
  
  Serial.print("Servo Position: ");
  Serial.println(servopos);
  
  analogWrite(servo, servopos);
  delay(200);
}
