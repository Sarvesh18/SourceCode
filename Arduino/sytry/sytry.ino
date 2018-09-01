#define arll 2
#define arl 3
#define arc 4
#define arr 5
#define arrr 6
int ll=0;
int l=0;
int c=0;
int r=0;
int rr=0;
int z=0;
int timer=0;
void setup() {
pinMode(arll,INPUT);
pinMode(arl,INPUT);
pinMode(arc,INPUT);
pinMode(arr,INPUT);
pinMode(arrr,INPUT);// put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
getz();
movement(z);
// put your main code here, to run repeatedly:

}
void inch()
{
  delay(200);
getz();
if(z==0)
{Serial.println("LEFT");}
else if(z=11111)
{Serial.println("STOP");}
else
movement(z);
}

void getz()
{
ll=digitalRead(arll);  
l=digitalRead(arl);
c=digitalRead(arc);
r=digitalRead(arr);
rr=digitalRead(arrr);
z=ll*10000+l*1000+c*100+r*10+rr;
if(ll==1&&l==1)
{ timer=millis();
while(millis()-timer<80)
  {if(digitalRead(arrr)==1&&digitalRead(arr)==1)
{z=11111;}
else z=11100;
  }
}
else if(rr==1&&r==1)
{ timer=millis();
while(millis()-timer<80)
  {if(digitalRead(arll)==1&&digitalRead(arl)==1)
{z=11111;}
else z=111;
  }
}
void movement(int x)
{
switch(x)
{
case 0:{Serial.println("UTURN");break;}
case 100:{Serial.println("STRAIGHT");break;}
case 111:{Serial.println("RIGHT");break;}
case 11100:{inch();break;}
case 1100:{Serial.println("ALIGN LEFT");break;}
case 110:{Serial.println("ALIGN RIGHT");break;}
case 1000:{Serial.println("ALIGN LEFT");break;}
case 10:{Serial.println("ALIGN RIGHT");break;}
case 11111:{inch();break;}
default:{Serial.println("STRAIGHT");break;}
}
}
:stopie();
{
  digitalWrite(b1,LOW);
    digitalWrite(b2,LOW);
      digitalWrite(f1,LOW);
      digitalWrite(f2,LOW);
}

void forward()
{
  digitalWrite(b1,LOW);
    digitalWrite(b2,LOW);
      digitalWrite(f1,HIGH);
      digitalWrite(f2,HIGH);
}
void backward()
{
digitalWrite(f1,LOW);
 digitalWrite(f2,LOW);
 digitalWrite(b1,HIGH);
 digitalWrite(b2,HIGH);
  }
void right()
{
digitalWrite(f1,LOW);
 digitalWrite(b2,LOW);
  while(digitalRead(arrr)!=1)
 {digitalWrite(f2,HIGH);
 digitalWrite(b1,HIGH);}
}
 while(digitalRead(arr)!=1)
 {digitalWrite(f2,HIGH);
 digitalWrite(b1,HIGH);}
}
 while(digitalRead(arc)!=1)
 {digitalWrite(f2,HIGH);
 digitalWrite(b1,HIGH);}
}
void left()
{
  digitalWrite(f2,LOW);
 digitalWrite(b1,LOW);
 while(digitalRead(arll)!=1)
{ digitalWrite(f1,HIGH);
 digitalWrite(b2,HIGH);}
  while(digitalRead(arl)!=1)
{ digitalWrite(f1,HIGH);
 digitalWrite(b2,HIGH);}
  while(digitalRead(arc)!=1)
{ digitalWrite(f1,HIGH);
 digitalWrite(b2,HIGH);}
}

      
