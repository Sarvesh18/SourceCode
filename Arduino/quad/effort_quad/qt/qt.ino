#include <Servo.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

MPU6050 mpu(0x69); //AD0=High


//MPU control/status vars 
bool dmpReady = false; 
uint8_t mpuIntStatus;  //actual interrupt status byte 
uint8_t deviceStatus; //device status , 0 = success , 
uint16_t packetSize; //expected DMP packet size (defult 42) -- ?
uint16_t fifoCount; //count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO buffer storage 

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector





volatile bool mpuInterrupt = false;
//void dmpDataReady() {
//  mpuInterrupt = true;
//}


// put your setup code here, to run once:
//#define MAX_SIGNAL 2100
#define MIN_SIGNAL 700
//#define MOTOR_PIN 3
int roll,pitch;
int MAX_SIGNAL;
int signal;
Servo right;
Servo left;
Servo up;
Servo down;
//int rcPin = 10; // PWM signal arduino pin
int ch1 = 0,changech1=0;
int ch3 = 1534,changech3=1534;
int ch4 = 1540,changech4=1540;// Receiver channel 1 pwm value
int a=0;
int b=0;
int c=0;

void setup() {
 pinMode(3,INPUT); 
  pinMode(5, INPUT);
  pinMode(4,INPUT);
 Serial.println("Program begin...");
  Serial.println("This program will calibrate the ESC.");

  left.attach(6);
  up.attach(10);
  right.attach(11);
  down.attach(9);

//join I2C bus 
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 48; // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
  //initialize serial communication
  Serial.begin(115200);
  while(!Serial); //common for Leonardo issues

  //initialize the mpu 
  Serial.println("Call MPU6050 Lib to initialize devices...");
  mpu.initialize(); //initialize I2C device by using MPU6050 library 

  //verify connection
  Serial.println("Tesing device connections");
  Serial.println(mpu.testConnection() ? F("MPU6050 connection test successed ") : F("MPU6050 connection test failed"));

//  //wait for begin , uncomment if we need wait user interruption
//  Serial.println("Press any button to begin");
//  while (Serial.available() && Serial.read()); // empty buffer
//  while (!Serial.available());                 // wait for data
//  while (Serial.available() && Serial.read()); // empty buffer again


  //load and configure DMP 
  Serial.println("initializing DMP"); 
  deviceStatus = mpu.dmpInitialize(); //use MPU6050 library to inilisalize the dmp 

 //feed offsets 
  mpu.setXGyroOffset(30);
  mpu.setYGyroOffset(4);
  mpu.setZGyroOffset(11);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  //make sure it works 
  if (deviceStatus == 0) {
    Serial.println("DMP initialization success, now enable DMP for use");
    //turn on DMP 
    mpu.setDMPEnabled(true); //use MPU6050 library to enable DMP)

    //wait for first interrup . currently just leave it false automatically 
    mpuInterrupt == false; 

    //let main llop know it's ok to use DMP, set dmpRead flag to ture 
    dmpReady = true;
    Serial.println("DMP is ready to use.");

    //get expected DMP packet size for later comparison 
    packetSize = mpu.dmpGetFIFOPacketSize();
  } else {
    //ERROR! , device status !=0 when initializing DMP
    Serial.print("DMP initialization failed when using MPU6050 library:");
    if (deviceStatus == 1) {
      Serial.println(" intial memory load failed");
    } else if (deviceStatus == 2) {
      Serial.println(" failed to update DMP configuration");
    } else {
      Serial.print(" unknow error with code: ");
      Serial.println(deviceStatus);
    }
}
}


int ticket = 1;
void printOnlyOnce (String message){
  if (ticket == 1){
   Serial.println(message);
   ticket = 0 ;
  } else {
    return;
  }
}

void loop() {
  // Read in the length of the signal in microseconds
  changech1 = pulseIn(5, HIGH, 25000);
  {if(changech1>ch1)
  {
    MAX_SIGNAL=MAX_SIGNAL+(changech1-ch1);
    right.writeMicroseconds(MAX_SIGNAL);
  left.writeMicroseconds(MAX_SIGNAL);
  up.writeMicroseconds(MAX_SIGNAL);
  down.writeMicroseconds(MAX_SIGNAL);
  ch1=changech1;
  }
  else if(changech1<ch1)
  {
    MAX_SIGNAL=MAX_SIGNAL-(ch1-changech1);
    right.writeMicroseconds(MAX_SIGNAL);
  left.writeMicroseconds(MAX_SIGNAL);
  up.writeMicroseconds(MAX_SIGNAL);
  down.writeMicroseconds(MAX_SIGNAL);              //throttle from channel 2
    ch1=changech1;}
    
  if (ch1==0&&ch3==1536&&ch4==1540&&ch3==1534&&ch4==1541)
    {
       right.writeMicroseconds(MIN_SIGNAL);
  left.writeMicroseconds(MIN_SIGNAL);
  up.writeMicroseconds(MIN_SIGNAL);
  down.writeMicroseconds(MIN_SIGNAL);
  }
signal=MAX_SIGNAL;
  Serial.print("Channel #1: ");
  Serial.println(ch1);
   changech4 = pulseIn(4, HIGH, 25000);
   if(changech4>ch4)
   {down.writeMicroseconds(signal+(changech4-ch4));
     up.writeMicroseconds(signal-(changech4-ch4));
     right.writeMicroseconds(signal+(changech4-ch4));
     left.writeMicroseconds(signal-(changech4-ch4));     
   ch4=changech4;}
else if(changech4<ch4)
{down.writeMicroseconds(signal-(changech4-ch4));
     up.writeMicroseconds(signal+(-changech4+ch4));
  right.writeMicroseconds(signal-(-changech4+ch4));
left.writeMicroseconds(signal+(-changech4+ch4));
ch4=changech4;
}
  changech3 = pulseIn(3, HIGH, 25000);
   if(changech3>ch3)
   {right.writeMicroseconds(signal+(changech3-ch3));
     left.writeMicroseconds(signal-(changech3-ch3));
     up.writeMicroseconds(signal+(changech3-ch3));
     down.writeMicroseconds(signal-(changech3-ch3));
   ch3=changech3;}
else if(changech3<ch3)
{left.writeMicroseconds(signal+(changech3-ch3));
     right.writeMicroseconds(signal-(changech3-ch3));
     up.writeMicroseconds(signal-(changech3-ch3));
down.writeMicroseconds(signal+(changech3-ch3));
ch3=changech3;
}
 //if DMP not ready don't do anything 
  if (!dmpReady) {
    printOnlyOnce("MAIN LOOP: DMP disabled");
    return;
  } else {

    //testing overflow 
    if (fifoCount == 1024) {
      mpu.resetFIFO();
      Serial.println("FIFO overflow");
    } else {


    //wait for enough avaliable data length
    while (fifoCount < packetSize) {
      //waiting until get enough
      fifoCount = mpu.getFIFOCount();
    }


    //read this packet from FIFO buffer 
    mpu.getFIFOBytes(fifoBuffer,packetSize);

    //track FIFO count here is more then one packeage avalible 

    //reset fifo count 
    fifoCount -= packetSize ;
    Serial.println(fifoCount);

    if (fifoCount > 2) {
        ////// clear fifo buffer 
    }
    //display stage 
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
roll=ypr[2]*180/M_PI;
pitch=ypr[1]*180/M_PI;
}
  }
if(roll>0)
{
down.writeMicroseconds(MAX_SIGNAL-(roll*100));
     up.writeMicroseconds(MAX_SIGNAL+(roll*100));
  right.writeMicroseconds(MAX_SIGNAL-(roll*100));
left.writeMicroseconds(MAX_SIGNAL+(roll*100));
}
else if(roll<0)
{
down.writeMicroseconds(MAX_SIGNAL+(roll*100));
     up.writeMicroseconds(MAX_SIGNAL-(roll*100));
  right.writeMicroseconds(MAX_SIGNAL+(roll*100));
left.writeMicroseconds(MAX_SIGNAL-(roll*100));
}
if(pitch>3)
{
down.writeMicroseconds(MAX_SIGNAL+((pitch-3)*100));
     up.writeMicroseconds(MAX_SIGNAL-((pitch-3)*100));
  right.writeMicroseconds(MAX_SIGNAL-((pitch-3)*100));
left.writeMicroseconds(MAX_SIGNAL+((pitch-3)*100));
}
else if(pitch<3)
{
down.writeMicroseconds(MAX_SIGNAL-((3-pitch)*100));
     up.writeMicroseconds(MAX_SIGNAL+((3-pitch)*100));
  right.writeMicroseconds(MAX_SIGNAL+((3-pitch)*100));
cleft.writeMicroseconds(MAX_SIGNAL-((3-pitch)*100));
}
delay(20);
  }
}
