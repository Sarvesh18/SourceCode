#define arll 2
#define arl 3
#define arc 4
#define arr 5
#define arrr 6
#define f1 8
#define b1 9
//#define pwm1 10
//#define pwm2 11
#define f2 10
#define b2 11
int l=0;
int c=0;
int r=0;
int ll=0;
int rr=0;
int z=0;
void setup() {
pinMode(arll,INPUT);
pinMode(arl,INPUT);
pinMode(arc,INPUT);
pinMode(arr,INPUT);
pinMode(arrr,INPUT);
pinMode(f1,OUTPUT);
pinMode(b1,OUTPUT);
pinMode(f2,OUTPUT);
pinMode(f3,OUTPUT);// put your setup code here, to run once:
}

void loop() {
 ll=digitalRead(arll);
  l=digitalRead(arl);
 c=digitalRead(arc);
 r=digitalRead(arr);
  rr=digitalRead(arrr);
 z=ll*10000+l*1000+c*100+r*10+rr;
 movement(z);
}

void alignleft()
{
digitalWrite(f2,HIGH);
digitalWrite(b1,HIGH);
delay(50);
straight();
}
void straight()
{
  //digitalWrite(pwm1,250);
  //digitalWrite(pwm2,250);
digitalWrite(f1,HIGH);
digitalWrite(f2,HIGH);
digitalWrite(b1,LOW);
digitalWrite(b2,LOW);

}
void alignright()
{//digitalWrite(pwm1,250);
 // digitalWrite(pwm2,250);
digitalWrite(f1,HIGH);
digitalWrite(b2,HIGH);
delay(50);
straight();
}
void right()
{//digitalWrite(pwm1,250);
 // digitalWrite(pwm2,250);
digitalWrite(f1,HIGH);
digitalWrite(b2,HIGH);
delay(250);
digitalWrite(f1,LOW);
digitalWrite(b2,LOW);
straight();
}
void left()
{//digitalWrite(pwm1,250);
  //digitalWrite(pwm2,250);
digitalWrite(f2,HIGH);
digitalWrite(b1,HIGH);
delay(250);
digitalWrite(f2,LOW);
digitalWrite(b1,LOW);
straight();
}

void movement(int x)
{
switch(x)
 {
case 10:{alignright();break;}
case 11100:{left();break;}
case 100:{straight();break;}
case 1000:{alignleft();break;}
case 111:{right();break;}
default:{straight();break;}
 }
}

