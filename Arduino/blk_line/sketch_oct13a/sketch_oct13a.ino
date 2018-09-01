int ch,ch1,ch2,ch3,ch4;
void setup() {
  pinMode(8,INPUT);
  pinMode(7,INPUT);
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  pinMode(4,INPUT);// put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
ch=digitalRead(8); 
Serial.print(ch);
ch1=digitalRead(7); 
Serial.print(ch1);
ch2=digitalRead(6); 
Serial.print(ch2);
ch3=digitalRead(5); 
Serial.print(ch3);
ch4=digitalRead(4); 
Serial.println(ch4);
// put your main code here, to run repeatedly:

}
