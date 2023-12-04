#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define FREQUENCY             50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int potWrist = A3;
int potElbow = A2;
int potShoulder = A1;
int potBase = A0;
int hand = 11;
int wrist = 12;
int elbow = 13;
int shoulder = 14;
int base = 15;

#define RECORD_BUTTON_PIN 2
#define PLAY_BUTTON_PIN 3

bool isRecording = false;
bool isPlaying = false;

int pulseWidths[100];
int pulseCount = 0;

void setup() {
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  pinMode(13, INPUT_PULLUP);
  pinMode(RECORD_BUTTON_PIN, INPUT_PULLUP);
  pinMode(PLAY_BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);

  // 인터럽트 설정
  attachInterrupt(digitalPinToInterrupt(RECORD_BUTTON_PIN), recordInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(PLAY_BUTTON_PIN), playInterrupt, FALLING);
}

void loop() {
  if (isRecording) {
    int pulse = 0;
    moveMotor(potWrist, wrist, pulse);
    pulseWidths[pulseCount] = pulse;
    pulseCount++;
  }

  // 다른 동작 수행 가능

  if (isPlaying) {
    playBack();
  }
}

void recordInterrupt() {
  if (!isRecording) {
    isRecording = true;
    pulseCount = 0;
  } else {
    isRecording = false;
  }
  delay(500);  // 버튼 바운스 방지를 위한 딜레이
}

void playInterrupt() {
  if (!isPlaying && pulseCount > 0) {
    isPlaying = true;
    playBack();
  }
  delay(500);  // 버튼 바운스 방지를 위한 딜레이
}

void moveMotor(int controlIn, int motorOut, int &pulseValue) {
  int pulse_wide, pulse_width, potVal;
  potVal = analogRead(controlIn);
  pulse_wide = map(potVal, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  pwm.setPWM(motorOut, 0, pulse_width);
  pulseValue = pulse_width;
}

void playBack() {
  for (int i = 0; i < pulseCount; i++) {
    pwm.setPWM(hand, 0, pulseWidths[i]);
    delay(100);  // 각 펄스 사이의 딜레이, 필요에 따라 조정
  }
  isPlaying = false;
}
