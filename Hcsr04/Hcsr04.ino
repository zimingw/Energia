/*
 HC-SR04 Ping distance sensor]
 VCC to arduino 5v GND to arduino GND
 Echo to Arduino pin 13 Trig to Arduino pin 12
 More info at: http://goo.gl/kJ8Gl
 */

#define trigPin 12
#define echoPin 13
#define tonePin 10

void setup() {
  // Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  int duration;
  // int freq;
  float distance;
  int conversion;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 74.07;
  if (distance >= 20 || distance <= 1){
    // Serial.println("Out of range");
    noTone(tonePin);
  }
  else {
    // freq = map(conversion,2,12,500,1200);
    tone(tonePin,distance*40);
    // Serial.print(distance);
    // Serial.println(" in");
  }
  delay(10);
}

