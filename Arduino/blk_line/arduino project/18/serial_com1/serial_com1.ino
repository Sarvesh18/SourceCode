void setup() {
  // instruct arduino to start serial communication
  Serial.begin(9600);//9600 is baud rate(speed of transmission and recieving)
//9600 bits/sec
}

void loop() {
  // instruct arduino to print "hello world"
Serial.write("Hello World") ;
}
