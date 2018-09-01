#include"SoftwareSerial.h"
SoftwareSerial b=SoftwareSerial(4,5);//rx,tx
char a;
void setup()
{
Serial.begin(9600);
  b.begin(9600);
pinMode(13,OUTPUT);
pinMode(9,OUTPUT);
digitalWrite(9,HIGH);
}
void loop()
{
if(b.available())
  a=b.read();
if(a=='h')
digitalWrite(13,HIGH);
if(a=='l')
digitalWrite(13,LOW);
}
