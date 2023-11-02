#include<SoftwareSerial.h>
#include<Servo.h>

int a = 0;
SoftwareSerial bt(2,3); // rx,tx of arduino
Servo myservo;

void setup() {
  bt.begin(9600);
  Serial.begin(9600);
  myservo.attach(9);
}

void loop() {
  while(bt.available()>0){
    int x = bt.read();
    if(x>=48 && x<=57){
       x = x - 48;
       a = 10*a + x;
    }
    if(x =='\n'){
      if(x<=180){
        myservo.attach(9);
        myservo.write(a);
        delay(500);
        myservo.detach();
      }
      Serial.println(a);
      a = 0;
    }
  }
}