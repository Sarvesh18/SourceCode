void setup() {
pinMode(13,OUTPUT) ; //telling Arduino LED is connected to pin 13 and set as outut
  
pinMode(12,INPUT) ; // telling Arduino LED is connected to pin 12 and set as input
-
}

void loop() {
 if (digitalRead(12)==HIGH)
  {
    digitalWrite(13,HIGH); //switch is high glow LED
  }
  else 
  {
    digitalWrite(13,LOW);//switch is low off LED
  }
}
