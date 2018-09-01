
#define f1 13
#define b1 12
#define pwm1 11
#define pwm2 10
#define b2 9
#define f2 8

#define SENSOR_1 2
#define SENSOR_2 3
#define SENSOR_3 4
#define SENSOR_4 5
#define SENSOR_5 6
//#define SENSOR_6 7 


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
 pinMode(SENSOR_1, INPUT);
 pinMode(SENSOR_2, INPUT);
 pinMode(SENSOR_3, INPUT);
 pinMode(SENSOR_4, INPUT);
 pinMode(SENSOR_5, INPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(f1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(pwm2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
forward();
}
void forward()
{
  Serial.print("MOTOR START");
  analogWrite(pwm1, 250);
  analogWrite(pwm2, 250);
  digitalWrite(f1, HIGH);
  digitalWrite(f2, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  delay(50);
  //stop1();
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
