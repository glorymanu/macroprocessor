#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PULSE_WIDTH 650
#define MAX_PULSE_WIDTH 2350
#define FREQUENCY 50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int potBase = A0; 
int potShoulder = A1;
int potElbow = A2;
int potWrist = A3;

int base = 11;
int shoulder = 12;
int elbow = 13;
int wrist = 14;
int hand = 15;

void setup() 
{
  delay(5000); 
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  pwm.setPWM(15, 0, 90); // Set Gripper to 90 degrees (Close Gripper)
  pinMode(13, INPUT_PULLUP);
  Serial.begin(9600);
}

void moveMotor(int controlIn, int motorOut)
{
  int pulse_wide, pulse_width, potVal;
  potVal = analogRead(controlIn); 
  pulse_wide = map(potVal, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  pwm.setPWM(motorOut, 0, pulse_width);


// Print the motor angle to Serial for Serial Plotter
  Serial.print(motorOut);
  Serial.print(": ");
  Serial.println(map(potVal, 0, 1023, 0, 180)); // Assuming 0-180 degree range
}

void loop() 
{
  moveMotor(potBase, base);
  moveMotor(potShoulder, shoulder);
  moveMotor(potElbow, elbow);
  moveMotor(potWrist, wrist);

  int pushButton = digitalRead(13);
  if(pushButton == LOW)
  {
    pwm.setPWM(hand, 0, 180); // Keep Gripper closed when button is not pressed
    Serial.println("Grab");
  }
  else
  {
    pwm.setPWM(hand, 0, 90); // Open Gripper when button is pressed
    Serial.println("Release");
  }
}
