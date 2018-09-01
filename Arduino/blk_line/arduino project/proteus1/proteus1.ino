void setup() {
 pinMode(12,OUTPUT); // put your setup code here, to run once:
pinMode(13,OUTPUT);
}

void loop() {
 digitalWrite(12,HIGH);digitalWrite(13,LOW);
 delay(250);
 digitalWrite(12,LOW);
 digitalWrite(13,HIGH);
 delay(250);
//digitalWrite(12,HIGH); // put your main code here, to run repeatedly:

}
