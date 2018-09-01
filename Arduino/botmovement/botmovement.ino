#include"SoftwareSerial.h"
SoftwareSerial Slave=SoftwareSerial(4,5);//rx,tx
#define f1 12
#define b1 13
#define pwm1 10
#define pwm2 11
#define f2 8
#define b2 9
#define sf 2
#define sb 3
char z;

void setup() {
  Serial.begin(9600);
  Slave.begin(9600);
pinMode(pwm1,OUTPUT);
pinMode(pwm2,OUTPUT);
pinMode(f1,OUTPUT);
pinMode(b1,OUTPUT);
pinMode(f2,OUTPUT);
pinMode(b2,OUTPUT);
pinMode(sf,OUTPUT);
pinMode(sb,OUTPUT);// put your setup code here, to run once:
}

void loop() {
if(Slave.available())
 z=Slave.read();
 movement(z);
}


void back()
{
  analogWrite(pwm1,200);
  analogWrite(pwm2,200);
  digitalWrite(f1,LOW);
digitalWrite(f2,LOW);
digitalWrite(b1,HIGH);
digitalWrite(b2,HIGH);

}

void straight()
{
  analogWrite(pwm1,200);
  analogWrite(pwm2,200);
  digitalWrite(f1,HIGH);
digitalWrite(f2,HIGH);
digitalWrite(b1,LOW);
digitalWrite(b2,LOW);

}

void right()
{digitalWrite(f2,LOW);
analogWrite(pwm1,200);
analogWrite(pwm2,200);
digitalWrite(f1,HIGH);
digitalWrite(b2,HIGH);
delay(100);
digitalWrite(f1,LOW);
digitalWrite(b2,LOW);
}
void left()
{digitalWrite(f1,LOW);
analogWrite(pwm1,200);
 analogWrite(pwm2,200);
digitalWrite(f2,HIGH);
digitalWrite(b1,HIGH);
delay(100);
digitalWrite(f2,LOW);
digitalWrite(b1,LOW);
}
void stopie()
{
analogWrite(pwm1,0);
 analogWrite(pwm2,0);
  digitalWrite(f2,LOW);
digitalWrite(b1,LOW);
digitalWrite(f1,LOW);
digitalWrite(b2,LOW);
}
void up()
{
stopie();
digitalWrite(sf,HIGH);
delay(50);
digitalWrite(sf,LOW);
}
void down()
{
stopie();
digitalWrite(sb,HIGH);
delay(50);
digitalWrite(sb,LOW);
}
void movement(char x)
{
switch(x)
 {
case 'a':{left();
            Serial.println("left"); 
            break;}
case 'w':{straight();
          Serial.println("Straight"); 
          break;}

case 'd':{right();
          Serial.println("Right"); 
          break;}
case 's':{back();
          Serial.println("Back");
        break;}
case 'u':{up();
          Serial.println("Servo up");
        break;}
case 'l':{down();
          Serial.println("Servo down");
        break;}
default:{stopie();break;}
 }
}

