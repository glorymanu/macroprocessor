#include <Wire.h>
 
#include <Adafruit_PWMServoDriver.h>


#define MIN_PULSE_WIDTH       650
#define MAX_PULSE_WIDTH       2350
#define FREQUENCY             50
 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


int potelbow = A3;
int potShoulder_delt = A2;                        //Assign Potentiometers to pins on Arduino Uno
int potShoulder_side = A1;
int potShoulder_front = A0;


int hand = 11;
int elbow = 12;
int Shoulder_delt = 13;                           //Assign Motors to pins on Servo Driver Board
int Shoulder_side  = 14;
int Shoulder_front = 15;


void setup()
{
  delay(5000);                            // <-- So I have time to get controller to starting position
 
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  pwm.setPWM(11, 0, 90);                  //Set Gripper to 90 degrees (Close Gripper)
 
  pinMode(13,INPUT_PULLUP);
 
  Serial.begin(9600);
}
 
 
void moveMotor(int controlIn, int motorOut)
{
  int pulse_wide, pulse_width, potVal;
 
  potVal = analogRead(controlIn);                                                   //Read value of Potentiometer
 
  pulse_wide = map(potVal, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);                //Map Potentiometer position to Motor
 
  pwm.setPWM(motorOut, 0, pulse_width); //pulse width가 모터 각도 제어 => 각 모터 별로 moveMotor function 만들어주고, 안에 if 문 넣어서, 최대 각도 이상의 각도가 들어가면, 최대 각도에서 멈추도록 설정
 
}
 
void loop()
{
  moveMotor(potShoulder_delt, Shoulder_delt);
 
  moveMotor(potelbow, elbow);
                                                            //Assign Motors to corresponding Potentiometers
  moveMotor(potShoulder_side, Shoulder_side);
 
  moveMotor(potShoulder_front, Shoulder_front);





 
  int pushButton = digitalRead(13);
  if(pushButton == LOW)
  {
    pwm.setPWM(hand, 0, 180);                             //Keep Gripper closed when button is not pressed
    Serial.println("Grab");
  }
  else
  {


    pwm.setPWM(hand, 0, 90);                              //Open Gripper when button is pressed
    Serial.println("Release");
  }
}

