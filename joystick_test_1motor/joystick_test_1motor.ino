#include <Servo.h>
Servo servo1;
Servo servo2;
const int xJoy = A1;                                               
const int yJoy = A0;                                               
double x_pos;
double y_pos; 
const int servo1_pin = 3;
const int servo2_pin = 5;   
//double initial_positionx = 90;
//double initial_positiony = 90;
int x = 90;
int y = 90;

void setup ( ) {
Serial.begin (9600) ;
servo1.attach (servo1_pin);
servo2.attach (servo2_pin);
//servo1.write (initial_positionx);
//servo2.write (initial_positiony);
pinMode (xJoy, INPUT) ;                     
pinMode (yJoy, INPUT) ;                      
}

void loop ( ) {
  x_pos = analogRead (xJoy) ;    // X position of Joystick, 0 to 1023, with 508 being at rest. Controlling Tiankongrc Digital Servo (360 degree)
  y_pos = analogRead (yJoy) ;    // Y position of Joystick, 0 to 1023, with 508 being at rest. Controlling MicroServo 9g (180 degree)                  

  Serial.print("Joystick Position (x,y): ");
  Serial.print(x_pos);
  Serial.print(", ");
  Serial.println(y_pos);

  if (x_pos < 400)
  {
    x = 180;
    servo1.write(x);
  }
  else if (x_pos > 600)
  {
    x = 0;
    servo1.write(x);
  }
  else
  {
    x = 90;
    servo1.write(x);
  }

  
  if (y_pos > 550)
  {
    y = 0;
  }
  else if (y_pos < 500)
  {
    y = 180;
  }
  else
  {
    y = 90;
  }
  servo2.write(y); 
     
  Serial.print("Output (x,y): ");
  Serial.print(x);
  Serial.print(", ");
  Serial.println(y);
}
