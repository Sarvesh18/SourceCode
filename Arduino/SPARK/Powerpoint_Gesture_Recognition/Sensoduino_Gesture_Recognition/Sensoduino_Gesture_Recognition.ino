// Replace sensor numbers with Names

//#include<SoftwareSerial.h>
//SoftwareSerial myserial(3, 4);
#define f1 12
#define b1 13
#define pwm1 10
#define pwm2 11
#define f2 8
#define b2 9
#define sf 6
#define sb 7
char ch;
float x, y, z;


#define START_CMD_CHAR '>'
#define END_CMD_CHAR '\n'
#define DIV_CMD_CHAR ','

//SoftwareSerial mySerial(3, 2);

#define DEBUG 1 // Set to 0 if you don't want serial output of sensor data

String inText;
float value0, value1, value2;

void setup() {
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(f1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(sf, OUTPUT);
  pinMode(sb, OUTPUT);
  //Serial.begin(9600);
  //myserial.begin(9600);

  Serial.begin(115200); // The default speed of the HC-05  Bluetooth serial modules
  Serial.println("Android Sensor Type No: ");
  Serial.println("1- ACCELEROMETER  (m/s^2 - X,Y,Z)");
  Serial.println("3- ORIENTATION (Yaw, Pitch, Roll)");
  Serial.println("4- GYROSCOPE (rad/sec - X,Y,Z)");
  Serial.println("16- GYROSCOPE_UNCALIBRATED (rad/sec - X,Y,Z)");
  Serial.flush();
}

void loop()
{
  Serial.flush();
  int inCommand = 0;
  int sensorType = 0;
  unsigned long logCount = 0L;

  char getChar = ' ';  //read serial

  // wait for incoming data
  if (Serial.available() < 1) return; // if serial empty, return to loop().

  // parse incoming command start flag
  getChar = Serial.read();
  if (getChar != START_CMD_CHAR) return; // if no command start flag, return to loop().

  // parse incoming pin# and value
  sensorType = Serial.parseInt(); // read sensor typr
  logCount = Serial.parseInt();  // read total logged sensor readings
  value0 = Serial.parseFloat();  // 1st sensor value
  value1 = Serial.parseFloat();  // 2rd sensor value if exists
  value2 = Serial.parseFloat();  // 3rd sensor value if exists


  x = value0;
  y = value1;
  z = value2;

    move1(x, y);
    delay(10);
  
}

void move1(float x, float y)
{

  if (x<-5.0&&y>-1)
  {
    ch = 'W';
  }//Forward
  else if (x>5.0&&y>-1)
  {
    ch = 'S'; //Backward
  }
  else if (y<-4.0&&x>-1)
  {
    ch = 'U'; //Left
  }
  else if (y>4.0&&x>-1)
  {
    ch = 'L'; //Right
  }
  else
  {
    ch = 'T'; //Stop
  }
  /*//else if ()
  {
    //ch = 'A'; //Left
  }
  //else if ()
  {
    //ch = 'D'; //Right
  }*/

  switch (ch)
  {
    case 'W' :
      {
        start();
        break;
      }
    case 'D':
      {
        right();
        break;
      }
    case 'A':
      {
        left();
        break;
      }
    case 'S':
      {
        back();
        break;
      }
    case 'T':
      {
        stop1();
        break;
      }
    case 'U':
      {
        digitalWrite(sb, LOW);
        digitalWrite(sf, HIGH);
        break;
      }
    case 'L':
      {
         digitalWrite(sf, LOW);
        digitalWrite(sb, HIGH);
        break;
      }
  }
}

void start()
{
  Serial.print("MOTOR START");
  analogWrite(pwm1, 200);
  analogWrite(pwm2, 200);
  digitalWrite(f1, HIGH);
  digitalWrite(f2, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  delay(50);
  //stop1();
}

void right()
{
  Serial.print("MOTOR RIGHT");
  analogWrite(pwm1, 200);
  analogWrite(pwm2, 200);
  digitalWrite(f1, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(f2, HIGH);
  digitalWrite(b2, LOW);
  delay(20);
  //stop1();
}

void left()
{
  Serial.print("MOTOR LEFT");
  analogWrite(pwm1, 200);
  analogWrite(pwm2, 200);
  digitalWrite(f1, HIGH);
  digitalWrite(b1, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(b2, HIGH);
  delay(20);
  //stop1();
}

void back()
{
  Serial.print("MOTOR BACK");
  analogWrite(pwm1, 200);
  analogWrite(pwm2, 200);
  digitalWrite(f1, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(b1, HIGH);
  digitalWrite(b2, HIGH);
  delay(50);
  //stop1();
}

void stop1()
{
  Serial.print("MOTOR STOP");
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  digitalWrite(f1, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(f2, LOW);
  digitalWrite(b2, LOW);
}

void upper() 
{
  digitalWrite(sf, HIGH);
  digitalWrite(sb, LOW);
}


void lower() 
{
  digitalWrite(sf, LOW);
  digitalWrite(sb, HIGH);
}

