
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include <Servo.h>
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

//void esc_calibrate();
//void motors();
//void gyro();

MPU6050 mpu;
#define OUTPUT_READABLE_YAWPITCHROLL
#define MIN_SIGNAL 700
#define int_SIGNAL 800
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;
float yaw,pitch,roll,pitchc,rollc;
int u1,u2,d1,d2,a1,a2,b1,b2;
int MAX_SIGNAL;
int j,i,c=0;
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

//declaring motors
Servo up1, up2,down1,down2;

//receiver parameters
int ch1 = 0,changech1=0;

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

void setup() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(115200);
    mpu.initialize();// initialize device
    devStatus = mpu.dmpInitialize();
    mpu.setXGyroOffset(80);
    mpu.setYGyroOffset(-37);
    mpu.setZGyroOffset(-34);
    mpu.setZAccelOffset(1718);
    if (devStatus == 0) {
        mpu.setDMPEnabled(true);
        attachInterrupt(0, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();
        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    } 
    pinMode(LED_PIN, OUTPUT);// configure LED for output
    pinMode(3, INPUT);
    up1.attach(6);
    up2.attach(9);
    down1.attach(10);
    down2.attach(11);
    u1=u2=d1=d2=a1=a2=b1=b2=MAX_SIGNAL;
}

void loop() {
    //MAX_SIGNAL=MAX_SIGNAL-200;
  changech1 = pulseIn(3, HIGH, 25000);
  if(changech1>ch1)
  {
  MAX_SIGNAL=MAX_SIGNAL+((changech1-ch1));
  up1.writeMicroseconds(MAX_SIGNAL);
  up2.writeMicroseconds(MAX_SIGNAL);
  down1.writeMicroseconds(MAX_SIGNAL);
  down2.writeMicroseconds(MAX_SIGNAL);
  ch1=changech1;
  }
  else if((changech1<ch1))
  {
  MAX_SIGNAL=MAX_SIGNAL-((ch1-changech1));
  up1.writeMicroseconds(MAX_SIGNAL);
  up2.writeMicroseconds(MAX_SIGNAL);
  down1.writeMicroseconds(MAX_SIGNAL);
  down2.writeMicroseconds(MAX_SIGNAL);
    ch1=changech1;}
    
    if (ch1==0 )
    {
       up1.writeMicroseconds(MIN_SIGNAL);
       up2.writeMicroseconds(MIN_SIGNAL);
       down1.writeMicroseconds(MIN_SIGNAL);
       down2.writeMicroseconds(MIN_SIGNAL);
  }
if (!dmpReady) return;// if programming failed, don't try to do anything
    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
    }
  // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();
    fifoCount = mpu.getFIFOCount();// get current FIFO count
    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
        mpu.resetFIFO();// reset so we can continue cleanly
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & 0x02) {
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();// wait for correct available data length, should be a VERY short wait
        mpu.getFIFOBytes(fifoBuffer, packetSize);// read a packet from FIFO
        fifoCount -= packetSize;// track FIFO count here in case there is > 1 packet available (this lets us immediately read more without waiting for an interrupt)
        #ifdef OUTPUT_READABLE_YAWPITCHROLL
            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            Serial.print("ypr\t");
            Serial.print(ypr[0] * 180/M_PI);
            Serial.print("\t");
            Serial.print(ypr[1] * 180/M_PI);
            Serial.print("\t");
            Serial.println(ypr[2] * 180/M_PI);
        #endif
        blinkState = !blinkState;// blink LED to indicate activity
        digitalWrite(LED_PIN, blinkState);
    }
//1st loop is for throttle
  
  //now the controlling of the gyro
 pitch= ypr[1] * 180/M_PI;
 roll=ypr[2] * 180/M_PI;

for(int i=0;i<10;)
{ changech1 = pulseIn(3, HIGH, 25000);
  if(changech1!=ch1)
  {
    break;
  }
  if(pitch<3.95&&roll>-1.30)
  {c=0;
    for(int j=0;j<10;)
  {c++;
    d2=d2+10;
    down2.writeMicroseconds(d2);
    if((pitch<4.15)&&(pitch>3.95)&&(roll<-1.30)&&(roll>1.50))
    {
      break;
    }
    else if(c==4)
    break;
  }
  }
  else if((pitch>4.15)&&(roll>-1.30))
  {c=0;
    for(int j=0;j<10;)
  {c++;
    d1=d1+10;
    down1.writeMicroseconds(d1);
    if((pitch<4.15)&&(pitch>3.95)&&(roll<-1.30)&&(roll>1.50))
    {
      break;
    }
       else if(c==4)
    break;
  }
  }
  else if((pitch>4.15)&&(roll<1.50))
  {c=0;
     for(int j=0;j<10;)
  {c++;
    u1=u1+10;
    up1.writeMicroseconds(u1);
    if((pitch<4.15)&&(pitch>3.95)&&(roll<-1.30)&&(roll>1.50))
    {
      break;
    }
       else if(c==4)
    break;
  }
  }
else if((pitch<3.95)&&(roll<-1.50))
{c=0;
  
     for(int j=0;j<10;)
  {
    c++;
    u2=u2+10;
    up2.writeMicroseconds(u2);
    if((pitch<4.15)&&(pitch>3.95)&&(roll<-1.30)&&(roll>1.50))
    {
      break;
    }
    else if(c==4)
    break;
  }
}
    else if(((pitch-4.05)<3)&&(roll>0))
    {c=0;
      
     for(int j=0;j<10;)
  {c++;
    d1=1+10;
  d2=d2+10;
    down1.writeMicroseconds(d1);
    down2.writeMicroseconds(d2);
    
    if((pitch<4.15)&&(pitch>3.95)&&(roll<-1.30)&&(roll>1.50))
    {
      break;
    }
    else if(c==4)
    break;
  }
    }
  
  else if(((4.05-pitch)<3)&&(roll<0))
  {
    c=0;
    for(int j=0;j<10;)
  {c++;
    u1=u1+10;
  u2=u2+10;
   up1.writeMicroseconds(u1);
    up2.writeMicroseconds(u2);
    
    if((pitch<4.15)&&(pitch>3.95)&&(roll<-1.30)&&(roll>1.50))
    {
      break;
    }
    else if(c==4)
    break;
  }
    }
    else if((pitch>0)&&((-1.40-roll)<3))
    {c=0;
    for(int j=0;j<10;)
  {c++;
    u1=u1+10;
  d1=d1+10;
    up1.writeMicroseconds(u1);
    down1.writeMicroseconds(d1);
    
    if((pitch<4.15)&&(pitch>3.95)&&(roll<-1.30)&&(roll>1.50))
    {
      break;
    }
    else if(c==4)
    break;
  }
    }
    else if((pitch<0)&&((roll-(-1.40))<3))
    {c=0;
    for(int j=0;j<10;)
  {c++;
    u2=u2+10;
  d2=d2+10;
    up2.writeMicroseconds(u2);
    down2.writeMicroseconds(d2);
    
    if((pitch<4.15)&&(pitch>3.95)&&(roll<-1.30)&&(roll>1.50))
    {
      break;
    }
    else if(c==4)
    break;
  }
    }
    
} 
}


