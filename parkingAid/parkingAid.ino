const int RED = 12;
const int BLUE = 13;
const int GREEN = 14;
const int TONE = 8;

#include "pitches.h"

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(TONE, OUTPUT);
  
  digitalWrite(RED, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(GREEN, LOW);
}

void loop()
{
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  unsigned long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(3, OUTPUT);// attach pin 3 to Trig
  digitalWrite(3, LOW);
  delayMicroseconds(2);
  digitalWrite(3, HIGH);
  delayMicroseconds(5);
  digitalWrite(3, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode (7, INPUT);//attach pin 4 to Echo
  duration = pulseIn(7, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  digitalWrite(RED, cm < 80 ? HIGH : LOW);
  digitalWrite(GREEN, cm > 200 ? HIGH : LOW);
  digitalWrite(BLUE, cm >=80 && cm <= 200 ? HIGH: LOW);
  
  if (cm < 100) {
    int noteDuration = 1000/4;
    tone(TONE, NOTE_D6 , noteDuration);
  }
 
  Serial.print(inches);
  Serial.print(", ");
  Serial.println(cm);
 
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
