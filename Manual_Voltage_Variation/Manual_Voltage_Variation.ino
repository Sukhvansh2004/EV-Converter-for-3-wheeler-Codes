#define OUTPUT_P 9
#define THROTTLE A0
#define DIR A1

int data = 180;
void setup() {
  // Begin serial communication at your desired baud rate
  Serial.begin(38400);
  pinMode(OUTPUT_P, OUTPUT);
  pinMode(THROTTLE, INPUT);
  pinMode(DIR, INPUT);
}

void loop() {
  // Check if there's data available on the serial buffer

  // if (Serial.available() > 0) {
  //       data = Serial.parseFloat();
        // Serial.print("Received float data: ");
        // Serial.println(data);
  // }
  // if (data >0) {
    analogWrite(OUTPUT_P, data);
    Serial.print("Writing ");
    Serial.println(data);
  // }
  // Add a delay to avoid overwhelming the serial communication
  // float val = analogRead(THROTTLE);
  // int dir = analogRead(DIR);
  // Serial.println(dir);
  delay(40);
}
