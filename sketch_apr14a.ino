//Line Tracking IO define
#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

const uint8_t maxspeeda = 180;
const uint8_t maxspeedb = 180;
const uint8_t basespeeda = 120;
const uint8_t basespeedb = 120;

float Ki = 0.01;
float Kp = 0.0005;
float Kd = 0.1;
int P, I, D;
int lastError = 0;
int motorspeed, motorspeeda, motorspeedb;

void forward(int a, int b) {
  analogWrite(ENA, a); //left side
  analogWrite(ENB, b); //right side
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go forward!");
}

void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT);
  pinMode(4, INPUT);
  pinMode(2, INPUT);
}

void loop() {
  int position;

  if (LT_L) {
    position = -1500;
  }
  else if (LT_L && LT_M){
    position = -750;
  }
  else if (LT_M) {
    position = 0;
  }
    else if (LT_R && LT_M){
    position = 750;
  }
  else if (LT_R) {
    position = 1500;
  }
  int error = 0 - position;

  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;
  motorspeed = P * Kp + I * Ki + D * Kd;

  motorspeeda = basespeeda + motorspeed;
  motorspeedb = basespeedb - motorspeed;

  if (motorspeeda > maxspeeda) {
    motorspeeda = maxspeeda;
  }
  if (motorspeedb > maxspeedb) {
    motorspeedb = maxspeedb;
  }
  if (motorspeeda < 0) {
    motorspeeda = 0;
  }
  if (motorspeedb < 0) {
    motorspeedb = 0;
  }
  //Serial.print(motorspeeda);Serial.print(" ");Serial.println(motorspeedb);
  forward(motorspeedb, motorspeeda);
}
