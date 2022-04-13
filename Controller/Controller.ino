//Joystick Variables
//Variables
const int LXJoy = A5;
const int LYJoy = A4;
const int RXJoy = A1;
const int RYJoy = A0;
const int LJoyMin = 0;
const int LJoyMax = 1023;
const int RJoyMin = 0;
const int RJoyMax = 1023;
const double DeadZP = .07;  //Deadzone percentage
//Calculated
const int LJoyMid = (LJoyMin+LJoyMax)/2;
const int RJoyMid = (RJoyMin+RJoyMax)/2;

#include <EasyTransfer.h>

//create object
EasyTransfer ET; 
struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t lxpos;
  int16_t lypos;
  int16_t rxpos;
  int16_t rypos;
};
//give a name to the group of data
SEND_DATA_STRUCTURE ControllerOutput;

void setup() {
  Serial.begin(38400);
  //start the library, pass in the data details and the name of the serial port. Can be Serial, Serial1, Serial2, etc.
  ET.begin(details(ControllerOutput), &Serial);
  
  pinMode(LXJoy, INPUT);
  pinMode(LYJoy, INPUT);
  pinMode(RXJoy, INPUT);
  pinMode(RYJoy, INPUT);
}

void loop() {
  int lxpos,lypos,rxpos,rypos;
  lxpos = analogRead(LXJoy);
  lypos = analogRead(LYJoy);
  rxpos = analogRead(RXJoy);
  rypos = analogRead(RYJoy);

  lxpos = DeadZone(lxpos,DeadZP,LJoyMid);
  lypos = DeadZone(lypos,DeadZP,LJoyMid);
  rxpos = DeadZone(rxpos,DeadZP,RJoyMid);
  rypos = DeadZone(rypos,DeadZP,RJoyMid);
  
  //Serial.write(lxpos,lypos,rxpos,rypos);
  
  Serial.print("LX, LY, RX, RY: ");
  Serial.print(lxpos);
  Serial.print(", ");
  Serial.print(lypos);
  Serial.print(", ");
  Serial.print(rxpos);
  Serial.print(", ");
  Serial.println(rypos);

  ControllerOutput.lxpos = lxpos;
  ControllerOutput.lypos = lypos;
  ControllerOutput.rxpos = rxpos;
  ControllerOutput.rypos = rypos;
  //send the data
  ET.sendData();
  
    Serial.print("Received Input (x,y): ");
    Serial.print(ControllerOutput.rxpos,1);
    Serial.print(", ");
    Serial.println(ControllerOutput.rypos,1);
  delay(100);
}

int DeadZone(int Value,double ZP,int Mid){
  if(Value > (Mid-Mid*(ZP/2)) && Value < (Mid+Mid*(ZP/2)))  //Dead Zone Application
  {
    return Mid;  
  }
  else{
    return Value;
  }
}
