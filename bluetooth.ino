void moveMotor(int controlIn, int motorOut, int &pulseValue)
{
  int pulse_wide, pulse_width, potVal;
  
  potVal = analogRead(controlIn);// Potentiometer의 값을 읽어옵니다.
  
  pulse_wide = map(potVal, 800, 240, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  // Potentiometer의 값을 일정 범위로 매핑하고, 서보 모터의 펄스 폭을 계산합니다.
  pulse_width = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  // 펄스 폭을 주파수와 12비트 값으로 변환합니다.
  pwm.setPWM(motorOut, 0, pulse_width);
  // 서보 모터를 지정된 펄스 폭으로 이동시킵니다.
  pulseValue = pulse_width;  // pulseValue 변수에 펄스 폭 저장
}
int pulseValue = 0;  // 코드1에서 전송된 펄스 폭을 저장할 변수

//RECORDING
#define RECORD_BUTTON_PIN 2  // 녹화 버튼에 연결된 핀 번호
#define PLAY_BUTTON_PIN 3    // 재생 버튼에 연결된 핀 번호

bool isRecording = false;
bool isPlaying = false;

int pulseWidths[1000];  // 펄스 폭 값을 저장할 배열, 적절한 크기로 조정하세요.
int pulseCount = 0;     // 저장된 펄스의 개수

void setup() {
  pinMode(RECORD_BUTTON_PIN, INPUT_PULLUP);
  pinMode(PLAY_BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // 녹화 버튼 처리
  if (digitalRead(RECORD_BUTTON_PIN) == LOW) {
    if (!isRecording) {
      // 녹화 시작
      isRecording = true;
      pulseCount = 0;  // 녹화를 시작할 때 저장된 펄스 수 초기화
    } else {
      // 녹화 중지
      isRecording = false;
    }
    delay(500);  // 버튼 바운스 방지를 위한 딜레이
  }

  // 재생 버튼 처리
  if (digitalRead(PLAY_BUTTON_PIN) == LOW) {
    if (!isPlaying && pulseCount > 0) {
      // 재생 시작
      isPlaying = true;
      for (int i = 0; i < pulseCount; i++) {
        pwm.setPWM(motorOut, 0, pulseWidths[i]);  // 저장된 펄스를 재생
        delay(100);  // 각 펄스 사이의 딜레이, 필요에 따라 조정
      }
      isPlaying = false;  // 재생 완료
    }
    delay(500);  // 버튼 바운스 방지를 위한 딜레이
  }

  if (isRecording) {
    int pulse = 0;
    moveMotor(potWrist, wrist, pulse);
    pulseWidths[pulseCount] = pulse;
    pulseCount++;
  }
  
  
}
