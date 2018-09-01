/*
 HC-SR04 Ping distance sensor:
 VCC to arduino 5v
 GND to arduino GND
 Echo to Arduino pin 7
 Trig to Arduino pin 8
 */
#include<SoftwareSerial.h>
SoftwareSerial myserial(4, 5);//RX,TX

#define LechoPin 2 // Echo Pin
#define LtrigPin 3 // Trigger Pin
//#define LLEDPin 4 // Onboard LEFT LED

#define RechoPin 6 // Echo Pin
#define RtrigPin 7 // Trigger Pin
//#define RLEDPin 5 // Onboard RIGHT LED

#define f1 13
#define b1 12
#define pwm1 11
#define pwm2 10
#define b2 9
#define f2 8

char ch;
int LminimumRange = 18; // Maximum range needed
int RminimumRange = 18; // Minimum range needed
long durationL, distanceL; // Duration used to calculate distance
long durationR, distanceR; // Duration used to calculate distance

void setup()
{
  pinMode(pwm1, OUTPUT);
  pinMode(f1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(LtrigPin, OUTPUT);
  pinMode(LechoPin, INPUT);
  pinMode(RtrigPin, OUTPUT);
  pinMode(RechoPin, INPUT);
  Serial.begin(9600);
  myserial.begin(9600);

  while (ch != 'S')
  { if (myserial.available())
    {
      ch = myserial.read();
    }
  }
}

void loop()
{
  if (myserial.available())
  {
    ch = myserial.read();
  }
  switch (ch)
  {
    case 'F' :
      {
        straight();
        break;
      }
    case 'L' :
      {
        left();
        break;
      }
    case 'R' :
      {
        right();
        break;
      }
    case 'B' :
      {
        back();
        break;
      }

    default:
      {
        ultrasonic();
        amove();
      }
  }
  //Delay 50ms before next reading.
}

void ultrasonic()
{
  //The following trigPin/echoPin cycle is used to determine the
  //distance of the nearest object by bouncing soundwaves off of it.

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(LtrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(LtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(LtrigPin, LOW);
  durationL = pulseIn(LechoPin, HIGH);
  distanceL = durationL / 58.2;

  digitalWrite(RtrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(RtrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(RtrigPin, LOW);
  durationR = pulseIn(RechoPin, HIGH);
  distanceR = durationR / 58.2;

  //cm = (duration/2) / 29.1;
  //inches = (duration/2) / 74;

  //Calculate the distance (in cm) based on the speed of sound.speed of sound is approx 343m/s
  //so it will take 29.1 microsecond to travel 1 cm
  //since the distance and duration is twice
  //actual distance=duration/2*29.1

  Serial.println("Successful Read:L & R");
  Serial.println(distanceL);
  Serial.println(distanceR);
}

void amove()
{
  if (distanceL >= LminimumRange && distanceR >= RminimumRange)
  {
    stop1();
  }
  else if (distanceL >= LminimumRange)
  {
    alignleft();
  }
  else if (distanceR >= RminimumRange)
  {
    alignright();
  }
  else
  {
    forward();
  }
}

void straight() //Full Speed
{
  Serial.println("STRAIGHT");
  analogWrite(pwm1, 250);
  analogWrite(pwm2, 250);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(f1, HIGH);
  digitalWrite(f2, HIGH);
}

void forward() //Circular Motion
{
  Serial.println("MOTOR START");
  analogWrite(pwm1, 220);
  analogWrite(pwm2, 250);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(f1, HIGH);
  digitalWrite(f2, HIGH);
}

void back() //Full Speed
{
  Serial.println("BACK");
  analogWrite(pwm1, 220);
  analogWrite(pwm2, 250);
  digitalWrite(f1, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(b2, HIGH);
}

void left()
{
  Serial.println("LEFT");
  ultrasonic();
  if (distanceL >= LminimumRange)
  {
    alignleft();
  }
  else
  {
    analogWrite(pwm1, 200);
    analogWrite(pwm2, 200);
    digitalWrite(f1, LOW);
    digitalWrite(b2, LOW);
    digitalWrite(b1, HIGH);
    digitalWrite(f2, HIGH);
  }
}

void alignright() //Move Left
{
  Serial.println("ALIGN RIGHT");
  analogWrite(pwm1, 180);
  analogWrite(pwm2, 230);
  digitalWrite(b2, LOW);
  digitalWrite(f1, LOW);
  digitalWrite(f2, HIGH);
  digitalWrite(b1, HIGH);
  delay(10);
}

void right()
{
  Serial.println("RIGHT");
  ultrasonic();
  if (distanceR >= RminimumRange)
  {
    alignright();
  }
  else
  {
    analogWrite(pwm1, 200);
    analogWrite(pwm2, 200);
    digitalWrite(f2, LOW);
    digitalWrite(b1, LOW);
    digitalWrite(b2, HIGH);
    digitalWrite(f1, HIGH);
  }
}

void alignleft() //Move Right
{
  Serial.println("ALIGN LEFT");
  analogWrite(pwm1, 230);
  analogWrite(pwm2, 180);
  digitalWrite(b1, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(f1, HIGH);
  digitalWrite(b2, HIGH);
  delay(10);
}

void stop1()
{
  Serial.println("MOTOR STOP");
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  digitalWrite(f1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(b2, LOW);
}




