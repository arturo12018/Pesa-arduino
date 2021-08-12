#include "LiquidCrystal.h"
#include "HX711.h"

HX711 scale(10, 9);
float calibration_factor = 48100; 
float units;
float ounces;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
   Serial.begin(9600);
   scale.set_scale();
  scale.tare();  
  long zero_factor = scale.read_average();
  lcd.begin(16, 2);
  lcd.print("Su maleta pesa");
}

void loop() {
  scale.set_scale(calibration_factor);
  units = scale.get_units(), 10;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  lcd.setCursor(0, 1);
  lcd.print(units); 
   Serial.println();
  delay(100);
    if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
  
}
