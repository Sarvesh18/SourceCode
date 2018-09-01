int c=0;
int s=0;
void setup() {
pinMode(6,INPUT);//input pin switch_1
pinMode(7,INPUT);//input pin switch_2
pinMode(8,OUTPUT);//output pin led_1
pinMode(9,OUTPUT);//output pin led_2
pinMode(10,OUTPUT);//output pin led_3
pinMode(11,OUTPUT);//output pin led_4
pinMode(12,OUTPUT);//output pin led _5
pinMode(13,OUTPUT);//output pin led_6
Serial.begin(9600);//start serial communication
}

void loop() {
  if(c==8||s==8)
  {s=0;c=0;}
else  if(digitalRead(6)==HIGH)
  {c++;}else if(digitalRead(7)==HIGH)
{s++;}
if(c!=0)
 switch(c)
{case 1:{digitalWrite(8,HIGH);break;}//high led_8 when switch_1 pressed 1 time
case 2:{digitalWrite(9,HIGH);break;}//high led_9 when switch_1 pressed 2 times
case 3:{digitalWrite(10,HIGH);break;}//high led_10 when switch_1 pressed 3 times
case 4:{digitalWrite(10,LOW);break;}//low led_10 when switch_1 pressed 4times
case 5:{digitalWrite(9,LOW);break;}//low led_9 when switch_1 pressed 5 times
  
default :{ s=0;
   digitalWrite(11,LOW);
    digitalWrite(12,LOW);
     digitalWrite(13,LOW);
  Serial.print ("Left thumb Wins");
        digitalWrite(8,HIGH);
        digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);
    delay(50);
    digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
    delay(50);
}
}
if(s!=0)
switch(s)
{case 1:{digitalWrite(11,HIGH);break;}//high 11 when switch_2 pressed 1 time
case 2:{digitalWrite(12,HIGH);break;}//high 12 when switch_2 pressed 2 times
case 3:{digitalWrite(13,HIGH);break;}//high 13 when switch_2 pressed 3 times
case 4:{digitalWrite(13,LOW);break;}//low 13 when switch_2 pressed 4 times
case 5:{digitalWrite(12,LOW);break;}//low 12 when switch_2 pressed 5 times
default:{c=0;
   digitalWrite(8,LOW);
    digitalWrite(9,LOW);
     digitalWrite(10,LOW);
  Serial.print("Right Thumb Wins");
  digitalWrite(11,HIGH);
        digitalWrite(12,HIGH);
      digitalWrite(13,HIGH);
    delay(50);
    digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
    delay(50);
}
}
delay(150);
}

