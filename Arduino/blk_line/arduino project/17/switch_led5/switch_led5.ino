int c=0;
void setup() {
pinMode(13,INPUT);//input pin switch
pinMode(9,OUTPUT);//output pin led_1
pinMode(10,OUTPUT);//output pin led_2
pinMode(11,OUTPUT);//output pin led_3
pinMode(12,OUTPUT);//output pin led_4
pinMode(8,OUTPUT);//output pin led _5
//Serial.begin(9600);//start serial communication
}

void loop() {
  if(digitalRead(13)==HIGH)
  {//Serial.print("Switch is pressed");// display if switch is pressed
  c++;
  //Serial.println(c);//diasplay value of count  c++;
}
  if(c==1)
  {digitalWrite(8,HIGH);}//glow led 1
  //Serial.println("LED8 is high");}//display which led is high
else  if(c==2)
  {digitalWrite(9,HIGH);}//glow led 1 and 2
   //Serial.println("LED9 is high");}//display which led is high
 else if(c==3)
  {digitalWrite(10,HIGH);//glow led 1,2 and 3
   }//display which led is high
  else if(c==4)
  {digitalWrite(11,HIGH);//glow lead 1,2,3 and 4
 }//display which led is 
else if(c==5)
{digitalWrite(9,HIGH);
digitalWrite(10,HIGH);
digitalWrite(11,HIGH);
digitalWrite(12,HIGH);
digitalWrite(8,HIGH);
delay(499);
digitalWrite(9,LOW);
digitalWrite(10,LOW);
digitalWrite(11,LOW);
digitalWrite(12,LOW);
digitalWrite(8,LOW);
delay(499);
}
else 
{c=0;
  digitalWrite(9,LOW);
digitalWrite(10,LOW);
digitalWrite(11,LOW);
digitalWrite(12,LOW);
digitalWrite(8,LOW);
}

delay(500);
}

