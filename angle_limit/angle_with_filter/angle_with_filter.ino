#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define FREQUENCY 50

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

const int numReadings = 5; // 이동 평균을 위한 읽기 횟수
int readings[numReadings]; // 포텐셔미터에서의 읽기 값
int readIndex = 0;         // 읽기 배열의 인덱스
int total = 0;             // 읽은 값들의 총합

void setup()
{
  delay(5000);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  pwm.setPWM(11, 0, 90);
  pinMode(13, INPUT_PULLUP);
  Serial.begin(9600);

  // 초기 읽기 값으로 배열을 초기화합니다.
  for (int i = 0; i < numReadings; i++)
  {
    readings[i] = analogRead(potShoulder_delt);
    total += readings[i];
  }
}

int getFilteredPotValue(int controlIn)
{
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(controlIn);
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;

  return total / numReadings;
}

void moveMotor(int controlIn, int motorOut)
{
  int potVal = getFilteredPotValue(controlIn);

  int pulse_wide = map(potVal, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  int pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);

  pwm.setPWM(motorOut, 0, pulse_width);
}

void loop()
{
  moveMotor(potShoulder_delt, Shoulder_delt);
  moveMotor(potelbow, elbow);
  moveMotor(potShoulder_side, Shoulder_side);
  moveMotor(potShoulder_front, Shoulder_front);

  int pushButton = digitalRead(13);
  if (pushButton == LOW)
  {
    pwm.setPWM(hand, 0, 180);
    Serial.println("Grab");
  }
  else
  {
    pwm.setPWM(hand, 0, 90);
    Serial.println("Release");
  }
}
//
