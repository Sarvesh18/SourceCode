#include "I2Cdev.h"
#include "Wire.h"    
#include "MPU6050_6Axis_MotionApps20.h"
#include "MPU6050.h" 
#include "Servo.h"

Servo up1;
Servo up2;
Servo down1;
Servo down2;
int changech2=0;
int motormax=150;//motor maximum speed is set to 150
float set_pitch = -0.4;//reference values for pitch
float set_roll  = -0.63;//reference values for roll
float a;//another reference for pitch
float b;//another reference for roll
float low  =-1;
float high =1;
int throttle_val;
int m[4];

void stability();
void getposition();

bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes      Currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
MPU6050 mpu;

/*------ Orientation/motion vars ------*/
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container

volatile bool mpuInterrupt = false;   // indicates whether MPU interrupt pin has gone high
void dmpDataReady()
{
  mpuInterrupt = true;
}

void setup()
{
  Serial.begin(9600);
      up1.attach(6); 
      up2.attach(9); 
      down1.attach(10);
      down2.attach(11);

       Wire.begin();
    mpu.initialize();
    mpu.dmpInitialize();
    mpu.setDMPEnabled(true);
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    dmpReady = true;    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    packetSize = mpu.dmpGetFIFOPacketSize();       // get expected DMP packet size for later comparison 
void getposition();
}

void loop()
{
 changech2 = pulseIn(3, HIGH, 25000);
 
 throttle_val = changech2;
 getposition();
  throttle_val = map(throttle_val,1110, 2000, 0,  190);
  //condition if the quad is moving bckwrd
  Serial.println(ypr[1]);
  if(changech2>800)
  {
              m[0] = constrain(throttle_val, 0, motormax);
              m[1] = constrain(throttle_val, 0, motormax);
              m[2] = constrain(throttle_val, 0, motormax);
              m[3] = constrain(throttle_val, 0, motormax); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);
              stability();
 }
else if(changech2<800)
{
              up1.write(0);
              up2.write(0);
              down1.write(0);
              down2.write(0);
  }
}

void getposition()
{
    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize)
    {
    }
    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();
  
    // get Current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ( (mpuIntStatus & 0x10) || fifoCount == 1024)
    {
      mpu.resetFIFO();        // reset so we can continue cleanly
    } 
  
    else if (mpuIntStatus & 0x02)
    {     
      while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();   // wait for correct available data length, should be a VERY short wait
      mpu.getFIFOBytes(fifoBuffer, packetSize);                        // read a packet from FIFO

      // track FIFO count here in case there is > 1 packet available
      // (this lets us immediately read more without waiting for an interrupt)
      fifoCount -= packetSize;

      /*===== display Euler ANGLES in DEGREES ======*/
      mpu.dmpGetQuaternion      (&q, fifoBuffer);
      mpu.dmpGetGravity         (&gravity, &q);
      mpu.dmpGetYawPitchRoll    (ypr, &q, &gravity);    
      ypr[1] = ypr[1] * 180/M_PI;  // Pitch
      ypr[2] = ypr[2] * 180/M_PI;  // Roll  
  }
}
void stability()
{
   if(ypr[1]>set_pitch || ypr[1]>high)
   {
    while(!(high>a<set_pitch))
         {    
          a=ypr[1];
              m[0] = constrain(throttle_val-20, 0, motormax);
              m[1] = constrain(throttle_val-20, 0, motormax);
              m[2] = constrain(throttle_val+20, 0, motormax);
              m[3] = constrain(throttle_val+20, 0, motormax); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);
              //Serial.println(a);
         }
  }
  else if(ypr[1]<set_pitch && ypr[1]<low)
  {
    while(high>b<set_pitch)
    {b=ypr[1];
              m[0] = constrain(throttle_val+20, 0, motormax);
              m[1] = constrain(throttle_val+20, 0, motormax);
              m[2] = constrain(throttle_val-20, 0, motormax);
              m[3] = constrain(throttle_val-20, 0, motormax); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);
              //Serial.println(a);
              
    }
  }
}
