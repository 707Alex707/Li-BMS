//Libarys
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LCD Config
//Sets I2C address and expander pin out
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
double pow_used = 0;


void setup() {
  // put your setup code here, to run once:
  
  //LCD Start Config
  lcd.begin(20,4);
  lcd.backlight();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  double vin = analogRead(16);
  delay(100);
  vin = vin * (5.0 / 1023.0) / (1.0/11.0);

  //Prints Voltage
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Input voltage:" + String(vin) + "V");

  //Toggle LED
  digitalWrite(13, HIGH);

  if(vin > 0.1){
    digitalWrite(12, HIGH);
    double shunti = analogRead(17);// * (5.0/ 1023.0)* (11.0 / 0.1);
    shunti = (shunti * (5.0 / 1023)) / 11.0 / 0.1;

    //Conmpute Power every second
    double power = vin * shunti;
    pow_used = pow_used + power/3600;
    
    
    String svin = String(vin, 3);
    String sshunti = String(shunti, 3);
    String spower = String(power, 3);
    String spow_used = String(pow_used, 4);
    
    //Prints data to lcd
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Input voltage:" + svin + "V");
    lcd.setCursor(0,1);
    lcd.print("Current:" + sshunti + "A");
    lcd.setCursor(0,2);
    lcd.print("Power rt:" + spower + "W");
    lcd.setCursor(0,4);
    lcd.print("Power Con:" + spow_used + "Wh");
  } else {
    digitalWrite(12, LOW);    
    }
    

    delay(450);
    digitalWrite(13, LOW);
    delay(450);

}
