#include <Servo.h>
#include "I2Cdev.h"
#include "Wire.h"    
#include "MPU6050_6Axis_MotionApps20.h"
#include "MPU6050.h" 

//#define MAX_SIGNAL 2100
#define MIN_SIGNAL 700

double Setpoint1;
double Setpoint2;

int motormax = 190;

int low2 = 2;
int m[4];
double Output1=0;
double Output2=0;
double Output3=0;
double Output4=0;

int throttle_val;

double error1=0;
double error2=0;
double error3=0;
double error4=0;
double k=3;

int MAX_SIGNAL=0;

void motors();
void esc();
void 

Servo up;
Servo left;
Servo right;
Servo down;

// PWM signal arduino pin
int ch1 = 0;
int changech1=0;    // Receiver channel 1 pwm value
/*------ MPU control/status vars ------*/
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
float yprd[2];          // [pitch, roll]        Datum position

volatile bool mpuInterrupt = false;   // indicates whether MPU interrupt pin has gone high
void dmpDataReady()
{
  mpuInterrupt = true;
}

void setup() {
 //pinMode(3, INPUT);

      up.attach(6); 
      right.attach(9); 
      down.attach(10);
      left.attach(11);
      esc();

    Wire.begin();
    mpu.initialize();
    mpu.dmpInitialize();
    mpu.setDMPEnabled(true);
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    dmpReady = true;    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    packetSize = mpu.dmpGetFIFOPacketSize();
    
  Serial.begin(9600);
}

void loop() 
{
   yprd[0]=0;
   yprd[1]=0;
   getposition();
   // Read in the length of the signal in microseconds
  changech1 = pulseIn(3, HIGH, 25000);
  
throttle_val=changech1;

  Output1    = map(Output1, 0, 500, 0,  150);
  Output2    = map(Output2, 0, 500, 0,  150);
  Output3    = map(Output3, 0, 500, 0,  150);
  Output4    = map(Output4, 0, 500, 0,  150);
            
  Setpoint1 = 0;
  Setpoint2 = 0;

  if( throttle_val>800)
            {   
              m[0] = throttle_val;
              m[1] = 0;//throttle_val;
              m[2] = throttle_val;
              m[3] = 0;//throttle_val; 
              motors();
            }
            getStability(); 
  
  if (throttle_val==0)
    {
              m[0] = MIN_SIGNAL;
              m[1] = MIN_SIGNAL;
              m[2] = MIN_SIGNAL;
              m[3] = MIN_SIGNAL; 
motors();
  }

delay(20);
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

void getStability()
{//constant();
getposition();
//=========================== 1 ======*/  // Pitch if BWD 
 if ( ypr[1] >= (yprd[0] + low2) &&  ypr[2] >= (yprd[1] + low2) )
    {
      constant();
      Output1=Output1+error1*k;
      Output4=Output1+error4*k;
      Output3=0;
      Output2=0;          
      m[0] =(throttle_val - Output1 - Output4+20);
      m[1] = 0;//(throttle_val -  Output1 + Output4;
      m[2] = (throttle_val + Output1 + Output4);
      m[3] = 0;//(throttle_val  + Output1 - Output4); 
      motors();
    }
 if( ypr[1] <= (yprd[0] - low2) && ypr[2] <= (yprd[1] - low2) )
    {
      constant();
      Output2=Output1+error2*k;
      Output3=Output1+error3*k;
      Output4=0;
      Output1=0;
      m[0] = (throttle_val  + Output2 + Output3);
      m[1] = 0;//(throttle_val + Output2 - Output3);
      m[2] = (throttle_val  - Output2 - Output3+20);
      m[3] = 0;//(throttle_val - Output2 + Output3); 
      motors(); 
    }   
    Serial.print(Output1);
    Serial.print('\t');
    Serial.print(Output2);
    Serial.print('\t');
    Serial.print(Output3);
    Serial.print('\t');
    Serial.println(Output1);
}
void constant()
{
  if(ypr[1]>Setpoint1)
  error1=ypr[1]-(Setpoint1);//pitch error positive
  else
  {
    error2=Setpoint1-ypr[1];
    }//pitch error negative
  if(ypr[2]>Setpoint2)
  error4=-Setpoint2+ypr[2];//roll error positive
  else
  {
    error3=Setpoint2-ypr[2];
    }//roll error negative
}
void motors()
{
  up.writeMicroseconds(m[0]);
  right.writeMicroseconds(0);//m[1]);
  down.writeMicroseconds(m[2]);
  left.writeMicroseconds(0);//m[3]);
}
void esc()
{
              m[0] = 1000;
              m[1] = 1000;
              m[2] = 1000;
              m[3] = 1000;
              motors();

              delay(200);

              m[0] = 700;
              m[1] = 700;
              m[2] = 700;
              m[3] = 700;
              motors();
}

