#include <Servo.h>

//#define MAX_SIGNAL 2100
#define MIN_SIGNAL 700

int MAX_SIGNAL;

Servo motor;
Servo otor;
Servo tor;
Servo zor;
// PWM signal arduino pin
int ch1 = 0;
int changech1=0;    // Receiver channel 1 pwm value
int a=0;
int b=0;
int c=0;

void setup() {
   pinMode(3, INPUT);
 Serial.println("Program begin...");
  Serial.println("This program will calibrate the ESC.");

  motor.attach(9);
  otor.attach(10);
  tor.attach(11);
  zor.attach(6);

  Serial.begin(9600);
}

void loop() {
  // Read in the length of the signal in microseconds
  changech1 = pulseIn(3, HIGH, 25000);
  if(changech1>ch1)
  {
  MAX_SIGNAL=MAX_SIGNAL+(changech1-ch1);
  motor.writeMicroseconds(MAX_SIGNAL);
  otor.writeMicroseconds(MAX_SIGNAL);
  tor.writeMicroseconds(MAX_SIGNAL);
  zor.writeMicroseconds(MAX_SIGNAL);
  ch1=changech1;
  }
  else if((changech1<ch1))
  {
  MAX_SIGNAL=MAX_SIGNAL-(ch1-changech1);
  motor.writeMicroseconds(MAX_SIGNAL);
  otor.writeMicroseconds(MAX_SIGNAL);
  tor.writeMicroseconds(MAX_SIGNAL);
  zor.writeMicroseconds(MAX_SIGNAL);
    ch1=changech1;}
    
  if (ch1==0)
    {
  motor.writeMicroseconds(MIN_SIGNAL);
  otor.writeMicroseconds(MIN_SIGNAL);
  tor.writeMicroseconds(MIN_SIGNAL);
  zor.writeMicroseconds(MIN_SIGNAL);
  }

  Serial.print("Channel #1: ");
  Serial.println(ch1);

delay(20);
}

