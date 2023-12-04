#define angle_limit_delt 515
#define angle_upper_limit_elbow 496
#define angle_lower_limit_elbow 177
#define angle_upper_limit_side 515
#define angle_lower_limit_side 87
#define angle_limit_front 274




void moveMotor_front(int controlIn, int motorOut) {
  int pulse_wide, pulse_width, potVal;

  potVal = analogRead(controlIn);  //Read value of Potentiometer


  pulse_wide = map(potVal, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);  //Map Potentiometer position to Motor


  if (pulse_width < angle_limit_delt) {
    pwm.setPWM(motorOut, 0, pulse_width);  //pulse width가 모터 각도 제어 => 각 모터 별로 moveMotor function 만들어주고, 안에 if 문 넣어서, 최대 각도 이상의 각도가 들어가면, 최대 각도에서 멈추도록 설정
  } else if (pulse_width >= angle_limit_delt) {
    pwm.setPWM(motorOut, 0, angle_limit_delt);
  }
}


void moveMotor_side(int controlIn, int motorOut) {
  int pulse_wide, pulse_width, potVal;

  potVal = analogRead(controlIn);  //Read value of Potentiometer


  pulse_wide = map(potVal, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);  //Map Potentiometer position to Motor


  if (pulse_width > angle_lower_limit_side & pulse_width < angle_upper_limit_side) {
    pwm.setPWM(motorOut, 0, pulse_width);  //pulse width가 모터 각도 제어 => 각 모터 별로 moveMotor function 만들어주고, 안에 if 문 넣어서, 최대 각도 이상의 각도가 들어가면, 최대 각도에서 멈추도록 설정
  } 
  else if (pulse_width <= angle_lower_limit_side) {
    pwm.setPWM(motorOut, 0, angle_lower_limit_side);
  } 
  else if (pulse_width >= angle_upper_limit_side) {
    pwm.setPWM(motorOut, 0, angle_upper_limit_side);
  }
}

void moveMotor_delt(int controlIn, int motorOut) {
  int pulse_wide, pulse_width, potVal;

  potVal = analogRead(controlIn);  //Read value of Potentiometer


  pulse_wide = map(potVal, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);  //Map Potentiometer position to Motor


  if (pulse_width < angle_limit_delt) {
    pwm.setPWM(motorOut, 0, pulse_width);  //pulse width가 모터 각도 제어 => 각 모터 별로 moveMotor function 만들어주고, 안에 if 문 넣어서, 최대 각도 이상의 각도가 들어가면, 최대 각도에서 멈추도록 설정
  } else if (pulse_width >= angle_limit_delt) {
    pwm.setPWM(motorOut, 0, angle_limit_delt);
  }
}

void moveMotor_elbow(int controlIn, int motorOut) {
  int pulse_wide, pulse_width, potVal;

  potVal = analogRead(controlIn);  //Read value of Potentiometer


  pulse_wide = map(potVal, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);  //Map Potentiometer position to Motor


    if (pulse_width > angle_lower_limit_elbow & pulse_width < angle_upper_limit_elbow) {
    pwm.setPWM(motorOut, 0, pulse_width);  //pulse width가 모터 각도 제어 => 각 모터 별로 moveMotor function 만들어주고, 안에 if 문 넣어서, 최대 각도 이상의 각도가 들어가면, 최대 각도에서 멈추도록 설정
  } 
  else if (pulse_width <= angle_lower_limit_elbow) {
    pwm.setPWM(motorOut, 0, angle_lower_limit_elbow);
  } 
  else if (pulse_width >= angle_upper_limit_elbow) {
    pwm.setPWM(motorOut, 0, angle_upper_limit_elbow);
  }
}

//정확한 건 pwm.setPWM definition 확인해서 짜보기
