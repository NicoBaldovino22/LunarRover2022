

#include <Servo.h>
#include <EasyTransfer.h>

//Input (Joystick)
const int XJoy = A0;
const int YJoy = A1;
const int SW = A2;
//Output (Servos)
Servo HServo;
Servo VServo;
double xpos;
double ypos;
int Hservopos;
int Vservopos;

//Joystick Variables
//Variable
const int JoyMin = 0;
const int JoyMax = 1023;
//Calculated
const int JoyMid = (JoyMin+JoyMax)/2;

//Servo Variables
//Variable
const int HServoPin = 10;
const int VServoPin = 11;
const int ServoMin = 0;
const int ServoMax = 270;
const int MaxServoF = 2500;
const int MinServoF = 500;
const int HRange = 30; //Horizontal Range of motion in degrees
const int VRange = 30; //Vertical Range of motion in degrees
//Calculated
const int HMin = ((ServoMax-ServoMin)/2)-(HRange/2);
const int HMax = ((ServoMax-ServoMin)/2)+(HRange/2);
const int VMin = ((ServoMax-ServoMin)/2)-(VRange/2);
const int VMax = ((ServoMax-ServoMin)/2)+(VRange/2);

//Motor Variables
//Variable
const int For = 22;
const int Rev = 23;
const int Pow = 11;

const double DeadZP = .10;  //Deadzone percentage



//create object
EasyTransfer ET; 

struct RECEIVE_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t lxpos;
  int16_t lypos;
  int16_t rxpos;
  int16_t rypos;
};

//give a name to the group of data
RECEIVE_DATA_STRUCTURE ControllerOutput;
void setup() {
 Serial.begin(38400);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc. 
  ET.begin(details(ControllerOutput), &Serial);
  
  HServo.attach(HServoPin);
  HServo.writeMicroseconds((MaxServoF+MinServoF)/2);
  VServo.attach(VServoPin);
  VServo.writeMicroseconds((MaxServoF+MinServoF)/2);
//  pinMode(Pow, OUTPUT);
//  pinMode(For, INPUT);
//  pinMode(Rev, INPUT);

//  digitalWrite(For, HIGH);
//  digitalWrite(Rev, LOW);
//  analogWrite(Pow, 255);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(ET.receiveData()){
    xpos = ControllerOutput.rxpos;
    ypos = ControllerOutput.rypos;
  
    Serial.print("Joystick Position (x,y): ");
    Serial.print(xpos,1);
    Serial.print(", ");
    Serial.println(ypos,1);
    
    Hservopos = map(xpos,JoyMin,JoyMax,HMin,HMax);
    Vservopos = map(ypos,JoyMin,JoyMax,VMin,VMax);
    
    Serial.print("Servo Position (H,V): ");
    Serial.print(Hservopos);
    Serial.print(", ");
    Serial.println(Vservopos);
    
    Hservopos = map(Hservopos,ServoMin,ServoMax,MinServoF,MaxServoF);
    Vservopos = map(Vservopos,ServoMin,ServoMax,MinServoF,MaxServoF);
  
      
    HServo.writeMicroseconds(Hservopos);
    VServo.writeMicroseconds(Vservopos);
  }
  else{
    Serial.println("Not Connected to Controller");
    
    xpos = ControllerOutput.rxpos;
    ypos = ControllerOutput.rypos;
  
    Serial.print("Received Input (x,y): ");
    Serial.print(ControllerOutput.rxpos,1);
    Serial.print(", ");
    Serial.println(ControllerOutput.rypos,1);
  }
  delay(50);
}
