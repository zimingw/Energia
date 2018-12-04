/*
* Launchpad code for SN754410 H-bridge
 * motor driver control.
 * copyright May. 2014, Ziming Wang *
 */
#define trigPin 5
#define echoPin 6

int enablePinRight = 8;
int motorRightReversePin = 9;
int motorRightForwardPin = 10;

int enablePinLeft = 11;
int motorLeftReversePin = 12;
int motorLeftForwardPin = 13;

int ledPin = 14;
int speed_value_motor1;

void setup() {
  Serial.begin(9600);

  pinMode(enablePinRight, OUTPUT);
  pinMode(motorLeftReversePin, OUTPUT); 
  pinMode(motorLeftForwardPin, OUTPUT);

  pinMode(enablePinLeft, OUTPUT);
  pinMode(motorRightReversePin, OUTPUT); 
  pinMode(motorRightForwardPin, OUTPUT);

  pinMode(ledPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH); // status LED is always on
  digitalWrite(enablePinLeft, HIGH);
  digitalWrite(enablePinRight, HIGH);

  speed_value_motor1 = 180; // half speed

  float distance = TestDistanceAhead();

  while(distance < 20)
  {
    ReverseAndTurnSlightly();
    distance = TestDistanceAhead();
  }

  Forward();
}

void Forward()
{
  digitalWrite(motorLeftReversePin, LOW);
  digitalWrite(motorRightReversePin, LOW);
  analogWrite(motorLeftForwardPin, speed_value_motor1); 
  analogWrite(motorRightForwardPin, speed_value_motor1);  
}

float TestDistanceAhead()
{
  int duration;
  // int freq;
  float distance;
  int conversion;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 74.07;
  Serial.println(distance);
  return distance;
}

void ReverseAndTurnSlightly()
{
  //Do more reverse before forward again.
  for(int i=0; i<2500; i++)
  {
    digitalWrite(motorLeftForwardPin, LOW);
    digitalWrite(motorRightForwardPin, LOW);
    analogWrite(motorLeftReversePin, speed_value_motor1); 
    analogWrite(motorRightReversePin, speed_value_motor1 / 4); 
  }
}

