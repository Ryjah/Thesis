float setpoint;
float setkp = 0;
float setki = 0;
float setkd = 0;

void setup(){
  Output_Init();
  Display_Init();
  Serial_Init();
  Thermocouple_Init();
}


void loop(){
  Thermocouple_Handler();
  PID_Koefisien(setkp, setki , setkd, 1);
  PID_Calculate(setpoint, Thermocouple_GetTemperature());
  
  int d;
  d = PID_ReadResult();
  if(d < 0){d = 0;}
  else if(d > 100){d = 100;}

  Output_SetDutyCycle(d);                  //Nilai Duty Cycle %    (PWM)
  Output_periode(1000);                    

  Output_Handler();
  Display_Handler();
  Serial_Handler();
}

void SetSetpoint(float sp){
  setpoint = sp;
}
void SetKp(float kp){
  setkp = kp;
}
void SetKi(float ki){
  setki = ki;
}
void SetKd(float kd){
  setkd = kd;
}

float GetSetpoint(){
  return setpoint;
}
