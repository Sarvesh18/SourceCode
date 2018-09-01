int c=0;
void setup()
{
pinMode(2,OUTPUT);  
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);  
}


void loop()
{
  c++;
  if (c!=0)
  switch(c)
       {
case 1: {
         digitalWrite(3,HIGH);
         digitalWrite(4,HIGH);
         digitalWrite(5,HIGH);
         digitalWrite(8,HIGH);
         break;
          }
case 2: {
         digitalWrite(2,HIGH);
         digitalWrite(6,HIGH);
         digitalWrite(9,HIGH);
         //digitalWrite(8,HIGH);
         break;
          }
case 3: {
         digitalWrite(2,HIGH);
         digitalWrite(6,HIGH);
         digitalWrite(9,HIGH);
         //digitalWrite(8,HIGH);
         break;
}
case 4: {
         digitalWrite(3,HIGH);
         digitalWrite(4,HIGH);
         digitalWrite(7,HIGH);
         digitalWrite(8,HIGH);
         break;
          }
case 5: {
         digitalWrite(3,HIGH);
         digitalWrite(4,HIGH);
         digitalWrite(5,HIGH);
         digitalWrite(6,HIGH);
         digitalWrite(2,HIGH);
         digitalWrite(7,HIGH);
         digitalWrite(9,HIGH);
         digitalWrite(8,HIGH);
         break;
          }
case 6: {
         digitalWrite(6,HIGH);
         //digitalWrite(6,HIGH);
         //digitalWrite(9,HIGH);
         //digitalWrite(8,HIGH);
         break;
          }
case 7: {
         digitalWrite(5,HIGH);
         digitalWrite(7,HIGH);
         //digitalWrite(9,HIGH);
         //digitalWrite(8,HIGH);
         break;
}
case 8: {
         digitalWrite(3,HIGH);
         digitalWrite(4,HIGH);
         digitalWrite(2,HIGH);
         digitalWrite(8,HIGH);
         digitalWrite(9,HIGH);
         break;
          }

case 9: {
         digitalWrite(3,HIGH);
         digitalWrite(4,HIGH);
         digitalWrite(5,HIGH);
         digitalWrite(8,HIGH);
         break;
          }
case 10: {
         digitalWrite(2,HIGH);
         digitalWrite(6,HIGH);
         digitalWrite(9,HIGH);
         //digitalWrite(8,HIGH);
         break;
          }
case 11: {
         digitalWrite(2,HIGH);
         digitalWrite(6,HIGH);
         digitalWrite(9,HIGH);
         //digitalWrite(8,HIGH);
         break;
}
case 12: {
         digitalWrite(3,HIGH);
         digitalWrite(4,HIGH);
         digitalWrite(7,HIGH);
         digitalWrite(8,HIGH);
         c=0;
         break;
          }

 default : {
             digitalWrite(3,HIGH);
         digitalWrite(4,HIGH);
         digitalWrite(5,HIGH);
         digitalWrite(6,HIGH);
         digitalWrite(7,HIGH);
         digitalWrite(8,HIGH);
         digitalWrite(9,HIGH);
         digitalWrite(2,HIGH);         
 }        
}
 delay(3.3333); 
digitalWrite(2,LOW);
digitalWrite(3,LOW);
digitalWrite(4,LOW);
digitalWrite(5,LOW);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
digitalWrite(9,LOW);
  
  
}
