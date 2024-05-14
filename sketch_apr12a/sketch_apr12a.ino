#define THROTTLE A1
#define STATE_1 2
#define STATE_2 3
#define STATE_3 4

#define STATE_F 8
#define STATE_R 9

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
  pinMode(STATE_1, INPUT);
  pinMode(STATE_2, INPUT);
  pinMode(STATE_3, INPUT);
  pinMode(STATE_F, INPUT);
  pinMode(STATE_R, INPUT);

}

void loop() {
  int s1 = digitalRead(STATE_1);
  int s2 =  digitalRead(STATE_2);
  int s3 =  digitalRead(STATE_3);

  int f = digitalRead(STATE_F);
  int r = digitalRead(STATE_R);

  float t = analogRead(THROTTLE) * (5.0 / 1023.0);

  Serial.print("THROTTLE: ");
  Serial.println(t);
  
  Serial.print("F: ");
  Serial.println(f);
  Serial.print("R: ");
  Serial.println(r);
  
  Serial.print("STATE 1: ");
  Serial.println(s1);
  Serial.print("STATE 2: ");
  Serial.println(s2);
  Serial.print("STATE 3: ");
  Serial.println(s3);
  
  delay(1000);
}
