#include <LiquidCrystal.h>

LiquidCrystal lcd(0,1,2,3,4,5);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();
  lcd.print("Hello Professor");
}

void loop() {
  // put your main code here, to run repeatedly:

}
