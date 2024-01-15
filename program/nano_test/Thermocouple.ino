#include <SPI.h>
 
#define MAX6675_CS   10
#define MAX6675_SO   11
#define MAX6675_SCK  12

uint32_t thermocoupleTimer;
float thermocoupleData;

void Thermocouple_Init() 
{
  pinMode(MAX6675_CS, OUTPUT);
  pinMode(MAX6675_SO, INPUT);
  pinMode(MAX6675_SCK, OUTPUT);
}
 
void Thermocouple_Handler() {
  if(millis() - thermocoupleTimer >= 500){
    thermocoupleData = readThermocouple();
    thermocoupleTimer = millis();
  }
}
float Thermocouple_GetTemperature(){
  return thermocoupleData;
}
 
float readThermocouple() {
  uint16_t v;
  
  digitalWrite(MAX6675_CS, LOW);
 
  // Read in 16 bits,
  //  15    = 0 always
  //  14..2 = 0.25 degree counts MSB First
  //  2     = 1 if thermocouple is open circuit  
  //  1..0  = uninteresting status
  
  v = shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);
  v <<= 8;
  v |= shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);
  
  digitalWrite(MAX6675_CS, HIGH);
  if (v & 0x4) 
  {    
    // Bit 2 indicates if the thermocouple is disconnected
    return NAN;     
  }
 
  // The lower three bits (0,1,2) are discarded status bits
  v >>= 3;
 
  // The remaining bits are the number of 0.25 degree (C) counts
  return v*0.25;
}
