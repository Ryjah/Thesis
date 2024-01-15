#define DRIVER_OUT 5
#define LED_PIN 13

uint32_t periode;
uint8_t dutyCycle;
uint32_t ledTimer;

uint8_t Output_GetDutyCycle(){
  return dutyCycle;  
}

void Output_Init(){
    pinMode(DRIVER_OUT, OUTPUT);
    pinMode(LED_PIN, OUTPUT); 
}

void Output_periode(uint8_t period){
  periode = period;
}

void Output_SetDutyCycle(uint8_t duty){
  dutyCycle = duty;
}

void Output_Handler(){
  uint32_t tOn, tOff;
  if (dutyCycle == 0){
    tOn = 0;
    digitalWrite(DRIVER_OUT, LOW);
    digitalWrite(LED_PIN, LOW);
  } 
  else {tOn = periode * (dutyCycle / 100.0);
  tOff = periode - tOn;
  if
   (millis() - ledTimer < tOn){
   digitalWrite(DRIVER_OUT, HIGH);
   digitalWrite(LED_PIN, HIGH);
   }
   else if 
   (millis() - ledTimer < tOn + tOff){
   digitalWrite(DRIVER_OUT, LOW);
   digitalWrite(LED_PIN, LOW);
   }
   else {
   ledTimer = millis();
   }
  }
}
