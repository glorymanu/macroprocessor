#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define FREQUENCY             50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int potelbow = A3;
int potShoulder_delt = A2;
int potShoulder_side = A1;
int potShoulder_front = A0;

int hand = 11;
int elbow = 12;
int Shoulder_delt = 13;
int Shoulder_side = 14;
int Shoulder_front = 15;

#define MIN_ANGLE 0
#define MAX_ANGLE 180
#define SERVO_NUM 0
#define START_ANGLE 90

// 각 서보 모터의 초기 각도 설정
int startAngleShoulderFront = 130;
int startAngleShoulderSide = 87;
int startAngleShoulderDelt = 330;
int startAngleElbow = 378;

void setup() {
  delay(5000);

  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  pwm.setPWM(hand, 0, 180);  // Set Gripper to 180 degrees (Close Gripper)

  pinMode(13, INPUT_PULLUP);

  Serial.begin(9600);

  // Set servo motor angles to their starting positions
  setServoAngle(Shoulder_front, startAngleShoulderFront);
  setServoAngle(Shoulder_side, startAngleShoulderSide);
  setServoAngle(Shoulder_delt, startAngleShoulderDelt);
  setServoAngle(elbow, startAngleElbow);
}

void moveMotor(int controlIn, int motorOut) {
  int potVal = analogRead(controlIn);
  int pulse_wide = map(potVal, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  int pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  pwm.setPWM(motorOut, 0, pulse_width);
}

void setServoAngle(uint8_t servoNum, int angle) {
  int mappedAngle = map(angle, 0, 180, pwm.getServoMinimum(), pwm.getServoMaximum());
  pwm.setPWM(servoNum, 0, mappedAngle);
}

void loop() {
  moveMotor(potShoulder_delt, Shoulder_delt);
  moveMotor(potelbow, elbow);
  moveMotor(potShoulder_side, Shoulder_side);
  moveMotor(potShoulder_front, Shoulder_front);

  int pushButton = digitalRead(13);
  if (pushButton == LOW) {
    pwm.setPWM(hand, 0, 180);
    Serial.println("Grab");
  } else {
    pwm.setPWM(hand, 0, 90);
    Serial.println("Release");
  }
}
