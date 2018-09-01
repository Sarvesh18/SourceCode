#include<SPI.h>
#include<SoftwareSerial.h>
SoftwareSerial myserial(4, 5);//RX-TX,TX-RX
int Xread;
int Yread;
int Zread;
int Xrest;
int Yrest;
int Zrest;
int S;
double Gx;
double Gy;
double Gz;
int sensorpinX = A1;
int sensorpinY = A2;
int sensorpinZ = A3;
void setup() {
  // put your setup code here, to run once:
  pinMode(sensorpinX, INPUT);
  pinMode(sensorpinY, INPUT);
  pinMode(sensorpinZ, INPUT);
  Serial.begin(9600);
  myserial.begin(9600);
  Read();
  Check();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (S > 18)
  {
    myserial.write("F");
    Serial.println("Forward");
    Read();
    Check();
    while (S > 10)
    {
      Check();
      delay(1000);
    }
  }
  else if (S < -18)
  {
    myserial.write("B");
    Serial.println("Backward");
    Read();
    Check();
    while (S < -10)
    {
      Check();
      delay(1000);
    }
  }
  else
  {
    myserial.write("");
    Serial.println("No Reading");
    Check();
  }

  //Gx = Xread / 67.584; // Conversion; see notes below
  /*Note that a conversion factor is needed to change the analog value recorded by the
  sensor before displaying the angular acceleration corresponding to the analog value.*/
  //Serial.print("Gyroscope X: ");
  //Serial.println(Gx);
  delay(50);
}

void Read()
{
  // Do not touch the sensor for 2 seconds
  Xrest = analogRead(sensorpinX);//Reads the rest value in the X direction
  Yrest = analogRead(sensorpinY);//Reads the rest value in the Y direction
  Zrest = analogRead(sensorpinZ);//Reads the rest value in the Z direction
  Serial.println(Xrest);//Prints the rest value
  Serial.println(Yrest);//Prints the rest value
  Serial.println(Zrest);//Prints the rest value
}

void Check()
{
  Xread = analogRead(sensorpinX) - Xrest;// Subtract the rest value
  Yread = analogRead(sensorpinY) - Yrest;// Subtract the rest value
  Zread = analogRead(sensorpinZ) - Zrest;// Subtract the rest value
  /*
  Serial.print("X:");
  Serial.print(Xread);
  Serial.print("\tY:");
  Serial.print(Yread);
  Serial.print("\tZ:");
  Serial.println(Zread);
  */
  S = Xread + Yread + Zread;
  Serial.println(S);
}

