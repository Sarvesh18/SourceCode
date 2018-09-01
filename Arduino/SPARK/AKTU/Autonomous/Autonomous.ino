/*
 HC-SR04 Ping distance sensor:
 VCC to arduino 5v
 GND to arduino GND
 Echo to Arduino pin 7
 Trig to Arduino pin 8
 */
#define LechoPin 2 // Echo Pin
#define LtrigPin 3 // Trigger Pin
#define LLEDPin 4 // Onboard LEFT LED

#define RechoPin 6 // Echo Pin
#define RtrigPin 7 // Trigger Pin
#define RLEDPin 5 // Onboard RIGHT LED

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

void setup() {
  Serial.begin (9600);
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
  pinMode(LLEDPin, OUTPUT); // Use LED indicator (if required)
  pinMode(RLEDPin, OUTPUT); // Use LED indicator (if required)
}

void loop() {
  ultrasonic();
  move1();
  delay(50); //Delay 50ms before next reading.
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

void move1()
{
  if (distanceR >= RminimumRange)
  {
    ch = 'D';
  }
  else if (distanceL >= LminimumRange)
  {
      ch = 'A';
  }
  else
  {
    ch = 'W';
  }


  switch (ch)
  {
    case 'W' :
      {
        forward();
        break;
      }
    case 'D':
      {
        alignright();
        break;
      }
    case 'A':
      {
        alignleft();
        break;
      }
    case 'S':
      {
        stop1();
        break;
      }
  }
}

void forward()
{
  Serial.print("MOTOR START");

  digitalWrite(LLEDPin, LOW);
  digitalWrite(RLEDPin, LOW);
  
  analogWrite(pwm1, 250);
  analogWrite(pwm2, 250);
  digitalWrite(f1, HIGH);
  digitalWrite(f2, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  //stop1();
}

void alignright()
{
  Serial.print("ALIGN RIGHT");
  digitalWrite(RLEDPin, HIGH);
  
  analogWrite(pwm1,250);
  analogWrite(pwm2,250);
  digitalWrite(b2,LOW);
  digitalWrite(f1,LOW);
  digitalWrite(f2,HIGH);
  digitalWrite(b1,HIGH);
  delay(18);
}

void alignleft()
{
  Serial.print("ALIGN LEFT");
  digitalWrite(LLEDPin, HIGH);
  
  analogWrite(pwm1,250);
  analogWrite(pwm2,250);
  digitalWrite(b1,LOW);
  digitalWrite(f2,LOW);
  digitalWrite(f1,HIGH);
  digitalWrite(b2,HIGH);
  delay(18);
}

void stop1()
{
  Serial.print("MOTOR STOP");
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  digitalWrite(f1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(b2, LOW);
}




