#define LED 13
int ll,rr,r,l,c;
void setup() {
pinMode(2,INPUT);  // put your setup code here, to run once
pinMode(3,INPUT); 
pinMode(4,INPUT); 
pinMode(5,INPUT); 
pinMode(6,INPUT); 
Serial.begin(9600);
}

void loop() {
ll= digitalRead(2);
 l=digitalRead(3);
 c=digitalRead(4);
 r=digitalRead(5);
 rr=digitalRead(6);//puts on the led
 Serial.print(ll);
 Serial.print(l);
 Serial.print(c);
 Serial.print(r);
 Serial.println(rr);
// Serial.print(ll);
}
