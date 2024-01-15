#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

uint32_t displayTimer;

void Display_Init(){
  lcd.begin();
}

void Display_Handler(){
  if(millis() - displayTimer >= 1000){
    lcd.setCursor(0,0);
    lcd.print("  Temp.    Pwr."); 
    lcd.setCursor(0,1);
    lcd.print(Thermocouple_GetTemperature(),2);
    lcd.print("|");
    lcd.print(GetSetpoint(), 0);
    lcd.print("  ");
    lcd.setCursor(12,1);
    lcd.print(Output_GetDutyCycle());
    lcd.print("%  ");
    displayTimer = millis();
  }
}
