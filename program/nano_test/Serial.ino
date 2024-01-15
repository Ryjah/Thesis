uint32_t serialTimer;
uint32_t serialRxTimer;
char serialRxBuffer[22];
uint8_t serialRxPtr;

void Serial_Init(){
  Serial.begin(115200);
}
void Serial_Handler(){
  if(Serial.available()){
    char data = 0;
    memset(serialRxBuffer, 0, 22);
    serialRxPtr = 0;
    serialRxTimer = millis();
    do{
      if(Serial.available() && serialRxPtr < 20){
        data = Serial.read();
        serialRxBuffer[serialRxPtr++] = data;
      }
    }while(data != '\n' && millis() - serialRxTimer < 1000);
  }
  if(serialRxPtr > 0){
    if(strncmp(serialRxBuffer, "SP:", 3) == 0){
      SetSetpoint(atof(serialRxBuffer + 3));
      PID_Reset();
    }
    if(strncmp(serialRxBuffer, "KP:", 3) == 0){
      SetKp(atof(serialRxBuffer + 3));
      PID_Reset();
    }
    if(strncmp(serialRxBuffer, "KI:", 3) == 0){
      SetKi(atof(serialRxBuffer + 3));
      PID_Reset();
    }
    if(strncmp(serialRxBuffer, "KD:", 3) == 0){
      SetKd(atof(serialRxBuffer + 3));
      PID_Reset();
    }
    if(strncmp(serialRxBuffer, "RST", 3) == 0){
      SetKp(0);
      SetKi(0);
      SetKd(0);
      PID_Reset();
    }
    memset(serialRxBuffer, 0, 22);
    serialRxPtr = 0;
  }
  
  if (millis() - serialTimer >= 1000){
    Serial.println(Thermocouple_GetTemperature());
    serialTimer = millis();
  }
}
