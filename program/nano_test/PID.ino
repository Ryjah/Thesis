float kp, ki, kd, ts;
float se, de, le, u;
uint32_t pidTimer;

void PID_Koefisien(float Kp, float Ki, float Kd, float Ts){
  kp = Kp;
  ki = Ki;
  kd = Kd;
  ts = Ts;
}

void PID_Reset(){
  se = 0;
  de = 0;
  le = 0;
  u = 0;
  pidTimer = millis();
}

float PID_ReadResult(){
  return u;
}

void PID_Calculate (float sp, float av){
  if (millis() - pidTimer >= ts * 1000){
    float e = sp - av;
  
    // Delta error
    de = e - le;
  
    // rumus PID
    u = (kp * e) + (ki * se * ts) + (kd * de / ts);
  
    // Integral Error
    se = se + e;
  
    // Nilai Error sebelumnya
    le = e;

    pidTimer = millis();
  }
  
}
