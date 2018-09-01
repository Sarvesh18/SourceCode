void setup() {
 pinMode(9,OUTPUT);
Serial.begin(9600);
}

void loop() {
  for(int i=0;i<35;i++)
 { analogWrite(9,i);
  delay(50);
 }
}
