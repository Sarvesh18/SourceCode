#include<SoftwareSerial.h>
SoftwareSerial myserial(4, 5);//RX-TX,TX-RX
#define echoPin 6 // Echo Pin
#define trigPin 7 // Trigger Pin

char ch;
int minimumRange = 18; // Maximum range needed
long duration, distance; // Duration used to calculate distance

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  myserial.begin(9600);
    ultrasonic();
}


void loop()
{

  if (distance <= minimumRange)
  {
    myserial.write("F");
    Serial.println("Successful Forward");
    ultrasonic();
    while(distance > minimumRange)
    {
      Serial.println("Stop");
      ultrasonic();
    }
  }
  else
  {
    myserial.write("");
    Serial.println("No Reading");
    ultrasonic();
  }
}

void ultrasonic()
{
  //The following trigPin/echoPin cycle is used to determine the
  //distance of the nearest object by bouncing soundwaves off of it.

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  //cm = (duration/2) / 29.1;
  //inches = (duration/2) / 74;

  //Calculate the distance (in cm) based on the speed of sound.speed of sound is approx 343m/s
  //so it will take 29.1 microsecond to travel 1 cm
  //since the distance and duration is twice
  //actual distance=duration/2*29.1

  Serial.println("Successful Read:");
  Serial.println(distance);
}
