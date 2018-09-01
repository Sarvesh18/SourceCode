#define LED 13

void setup() {
pinMode(LED,OUTPUT);  // put your setup code here, to run once

}

void loop() {
 digitalWrite(LED,HIGH);//puts on the led
 delay(100);//waiting time for a loop (delay)
digitalWrite(LED,LOW);// puts off the led
delay(100);
}
