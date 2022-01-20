const int For = 8;
const int Rev = 9;
const int PWM = 13;

void setup() {
 Serial.begin(57600);
  // put your setup code here, to run once:
  pinMode(For, INPUT);    //defines pins
  pinMode(Rev, INPUT);
  pinMode(PWM, OUTPUT);

  digitalWrite(For, LOW);    //sets initial direction condition
  digitalWrite(Rev, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  double Powr;    //defines variable power
  for (double i = 0; i <= 6.28; i = i+.628) //cycles i through ~2Pi in ~10 steps
    {
    Powr = ((cos(i)*0.25)+0.75)*255;      //calculates power, ranges from 50 to 100% power (50% is ~min to move motor)
    analogWrite(PWM, Powr);                 //max power is always 255, min is 0
    double powPct = (Powr / 255) * 100;   //calculates percentage of power
    Serial.print("Power is at: ");        //prints the power, for debugging
    Serial.print(powPct,0);
    Serial.println("%");
    delay(500);                           //delays function by 0.5 second
    }
  if(digitalRead(For) == HIGH){           //turns off motor and changes motor direction
    analogWrite(PWM,0);
    digitalWrite(For, LOW);
    digitalWrite(Rev, HIGH);
    Serial.println("Direction Switched to Reverse");
    }
  else{
    analogWrite(PWM,0);
    digitalWrite(For, HIGH);
    digitalWrite(Rev, LOW);
    Serial.println("Direction Switched to Forward");
  }
    delay(2000);    //delays function by 2 seconds to ensure motor stops spinning (may be unnecessary)
}
