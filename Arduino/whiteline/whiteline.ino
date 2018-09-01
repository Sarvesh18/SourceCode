
#define arll 2
#define arl 3
#define arc 4
#define arr 5
#define arrr 6
#define f1 12
#define b1 13
#define pwm1 10
#define pwm2 11
#define f2 8
#define b2 9
//#define p 100
int l=0;
int c=0;
int r=0;
int ll=0;
int rr=0;
int z=0;
void setup() {
  Serial.begin(9600);
pinMode(arll,INPUT);
pinMode(arl,INPUT);
pinMode(arc,INPUT);
pinMode(arr,INPUT);
pinMode(arrr,INPUT);
pinMode(pwm1,OUTPUT);
pinMode(pwm2,OUTPUT);
pinMode(f1,OUTPUT);
pinMode(b1,OUTPUT);
pinMode(f2,OUTPUT);
pinMode(b2,OUTPUT);// put your setup code here, to run once:
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
 analogWrite(pwm1,0);
analogWrite(pwm2,100);
digitalWrite(f2,HIGH);
delay(20);
straight();
}
void straight()
{
  analogWrite(pwm1,100);
  analogWrite(pwm2,100);
  digitalWrite(f1,HIGH);
digitalWrite(f2,HIGH);
digitalWrite(b1,LOW);
digitalWrite(b2,LOW);

}
void alignright()
{
analogWrite(pwm2,0);
  analogWrite(pwm1,100);
digitalWrite(f1,HIGH);
delay(20);
straight();
}
void right()
{digitalWrite(f2,LOW);
digitalWrite(b1,LOW);
analogWrite(pwm1,100);
analogWrite(pwm2,100);
digitalWrite(f1,HIGH);
digitalWrite(b2,HIGH);
delay(250);
}
void left()
{digitalWrite(f1,LOW);
digitalWrite(b2,LOW);
analogWrite(pwm1,100);
 analogWrite(pwm2,100);
digitalWrite(f2,HIGH);
digitalWrite(b1,HIGH);
delay(250);

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
void movement(int x)
{
switch(x)
 {
  case 00:{stopie();
          Serial.println("STOP");   
          break;}
  /*case 110:{alignright();
          Serial.println("Aligning right");  
          break;}*/
case 11100:{left();
            Serial.println("left"); 
            break;}
case 100:{straight();
          Serial.println("Straight"); 
          break;}
/*ase 1100:{alignleft();
          Serial.println("Aligning left");   
          break;}*/
case 1000:{alignleft();
          Serial.println("Aligning left");   
          break;}
case 10:{alignright();
          Serial.println("Aligning right");   
          break;}
case 111:{right();
          Serial.println("right"); 
          break;}
default:{straight();break;}
 }
}

