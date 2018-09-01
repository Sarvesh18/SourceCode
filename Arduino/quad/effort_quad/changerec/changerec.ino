//------------------------------ LIBRARIES -------------------------
#include "I2Cdev.h"
#include "Wire.h"    
#include "MPU6050_6Axis_MotionApps20.h"
#include "MPU6050.h" 

#include "Servo.h"
#include "SPI.h"

//------------------------------ LIBRARIES -------------------------

//Define Variables we'll be connecting to
double Input1;
double Setpoint1;

double Input2;
double Setpoint2;


double Output1;
double Output2;
double Output3;
double Output4;

//Specify the links and initial tuning parameter

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

int bank_val;
int bank_left;
int bank_right;
int pitch_val;
int pitch_bwd;
int pitch_fwd;
int throttle_val;
int thepackage;
const uint64_t pipe_Rx  = 0xE8E8F0F0E1LL;

/*-----( The PACKAGE Array )-----*/
int ch2,ch3,ch4;
  //  1 ==  Throttle
  //  2 ==  Bank
  //  3 ==  Pitch
  //  4 ==  1 = Turn on Radio

/*------(Maximum and Minimum Values)------*/
int m[4];  
int motormax = 130;
int low = 38;
int high = 42;
int low2 = 10;

//========================================================================================================
//========================================      MPU Objects       ========================================
//========================================================================================================
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
//=========================================================================================================
//========================================      End MPU Objects     =======================================
//=========================================================================================================
/*----------------------------------------------------------------------------*/


// ======================================================================================================
// ===============================                   SETUP                  =============================
// =======================================================================================================
void setup()
{
   // SetSampleTime(100);
    Input1 = ypr[1];
    Input2 = ypr[2]; 
 

    //=======================================
    //=====         Radio Setup         =====
    //=======================================
 
      motor1.attach(3); 
      motor2.attach(5); 
      motor3.attach(6);
      motor4.attach(9);
    /*============================================*/
    /*============  End Radio Setup   ============*/
    /*============================================*/
    /*----------------------------------------------------------------------------*/
    //===================================
    //=====       MPU Setup         =====
    //===================================
    Wire.begin();
    mpu.initialize();
    mpu.dmpInitialize();
    mpu.setDMPEnabled(true);
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();

    dmpReady = true;    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    packetSize = mpu.dmpGetFIFOPacketSize();       // get expected DMP packet size for later comparison 
    //==========================================================================================
    //=====      End MPU Setup       ===========================================================
    //==========================================================================================
    /*----------------------------------------------------------------------------*/  
}

//==================================================================================================================================================        
//==========================                        ================================================================================================        
//==========================       Start LOOP       ================================================================================================
//==========================                        ================================================================================================ 
//==================================================================================================================================================        
void loop()
{
  if( radio.available())
  {
    bool done = false;    
    while(!done)
    {
            getposition();
            throttle_val = ch2;  // 0 = Zero      190 = MAX
            bank_val     = ch3;
            pitch_val    = ch4;
            
            throttle_val=map(throttle_val,  1000, 2000, 0,190);
            bank_val=map(bank_val,  1000, 2000, 0,  190);
            pitch_val=map(pitch_val,  1000, 2000, 0,190);
                     
            /*===== Set Datum for PITCH && ROLL ======*/
            yprd[0] = 0; //      Datum Pitch
            yprd[1] = 0; //      Datum Roll
  
            Setpoint1 = 1.14;    // Pitch
            Setpoint2 = -0.55;    // Roll   
    
            /*--------------- BANK ---------------*/
             bank_left  = map(bank_val,  0, 38, 20,  0);
             bank_right = map(bank_val, 42, 80,  0, 20);       
            /*--------------- BANK ---------------*/     

            /*--------------- PITCH ---------------*/
             pitch_bwd  = map(pitch_val,  0, 38, 20,  0);
             pitch_fwd  = map(pitch_val, 42, 80,  0, 20);           
            /*--------------- PITCH ---------------*/
  
  
            
                        
          if( ch2>= 1000)
          {
            //Serial.println("More");
            if(throttle_val <= 50)
            {
              m[0] = throttle_val;
              m[1] = throttle_val;
              m[2] = throttle_val;
              m[3] = throttle_val;   
              motor1.write(m[0]);
              motor2.write(m[1]);
              motor3.write(m[2]);
              motor4.write(m[3]);
            }              
//====================================================================================================================        
//===================================       MOTOR CONTROL      =======================================================
//====================================================================================================================
          if(throttle_val > 50)
          {
// ------------------------------------ ( 1 ALL THROTTLE) ------------------------------------
            if( bank_val >= low && bank_val <= high  &&  pitch_val <= high && pitch_val >= low)
            {   
              m[0] = constrain(throttle_val, 0, motormax);
              m[1] = constrain(throttle_val, 0, motormax);
              m[2] = constrain(throttle_val, 0, motormax);
              m[3] = constrain(throttle_val , 0, motormax); 
              motor1.write(m[0]);
              motor2.write(m[1]);
              motor3.write(m[2]);
              motor4.write(m[3]);  
              getStability();  
            }
    
    
// ------------------------------------ ( 2 BANK RIGHT) ------------------------------------
            if( bank_val >= high  &&   pitch_val >= low && pitch_val <= high)
            {     
              m[0] = constrain((throttle_val + bank_right), 0, motormax);
              m[1] = constrain((throttle_val + bank_right), 0, motormax);
              m[2] = constrain((throttle_val - bank_right), 0, motormax);
              m[3] = constrain((throttle_val - bank_right), 0, motormax);  
              motor1.write(m[0]);
              motor2.write(m[1]);
              motor3.write(m[2]);
              motor4.write(m[3]);    
              getStability();    
            }
    
    
// ------------------------------------ ( 3 BANK LEFT) ------------------------------------
            if( bank_val <= low  &&   pitch_val >= low && pitch_val <= high)
            {     
              m[0] = (constrain((throttle_val - bank_left), 0, motormax));
              m[1] = (constrain((throttle_val - bank_left), 0, motormax));
              m[2] = (constrain((throttle_val + bank_left), 0, motormax));
              m[3] = (constrain((throttle_val + bank_left), 0, motormax));   
              motor1.write(m[0]);
              motor2.write(m[1]);
              motor3.write(m[2]);
              motor4.write(m[3]);    
              getStability();    
            }    
    
    
// ------------------------------------ ( 4 PITCH BWD) ------------------------------------
            if( pitch_val <= low  &&   bank_val >= low && bank_val <= high)
            {     
              m[0] = (constrain((throttle_val + pitch_bwd), 0, motormax));
              m[1] = (constrain((throttle_val - pitch_bwd), 0, motormax));
              m[2] = (constrain((throttle_val - pitch_bwd), 0, motormax));
              m[3] = (constrain((throttle_val + pitch_bwd), 0, motormax));  
              motor1.write(m[0]);
              motor2.write(m[1]);
              motor3.write(m[2]);
              motor4.write(m[3]);    
              getStability();
    
            }
    
    
// ------------------------------------ ( 5 PITCH FWD) ------------------------------------
            if( pitch_val >= high  &&   bank_val >= low && bank_val <= high)
            {
              m[0] = (constrain((throttle_val - pitch_fwd), 0, motormax));
              m[1] = (constrain((throttle_val + pitch_fwd), 0, motormax));
              m[2] = (constrain((throttle_val + pitch_fwd), 0, motormax));
              m[3] = (constrain((throttle_val - pitch_fwd), 0, motormax)); 
              motor1.write(m[0]);
              motor2.write(m[1]);
              motor3.write(m[2]);
              motor4.write(m[3]);    
              getStability();
             }
    
// -----------------------------------------   (Double Logic) ------------------------------------
// ------------------------------------ ( 6 BANK LEFT && PITCH BWD) ------------------------------------
            if( bank_val <= low  &&  pitch_val <= low)
            {
              m[0] = (constrain((throttle_val - bank_left + pitch_bwd), 0, motormax));
              m[1] = (constrain((throttle_val - bank_left - pitch_bwd), 0, motormax));
              m[2] = (constrain((throttle_val + bank_left - pitch_bwd), 0, motormax));
              m[3] = (constrain((throttle_val + bank_left + pitch_bwd), 0, motormax));
              motor1.write(m[0]);
              motor2.write(m[1]);
              motor3.write(m[2]);
              motor4.write(m[3]);    
              getStability();
             }
    
    
// ------------------------------------ ( 7 BANK LEFT && PITCH FWD) ------------------------------------
            if( bank_val <= low  &&  pitch_val >= high)
            {     
              m[0] = (constrain((throttle_val - bank_left - pitch_fwd), 0, motormax));
              m[1] = (constrain((throttle_val - bank_left + pitch_fwd), 0, motormax));
              m[2] = (constrain((throttle_val + bank_left + pitch_fwd), 0, motormax));
              m[3] = (constrain((throttle_val - 10 + bank_left - pitch_fwd), 0, motormax));
              motor1.write(m[0]);
              motor2.write(m[1]);
              motor3.write(m[2]);
              motor4.write(m[3]);  
              getStability();
             }
    
    
// ------------------------------------ ( 8 BANK RIGHT && PITCH FWD) ------------------------------------
            if( bank_val >= high  &&  pitch_val >= high)
            {     
              m[0] = (constrain((throttle_val + bank_right - pitch_fwd), 0, motormax));
              m[1] = (constrain((throttle_val + bank_right + pitch_fwd), 0, motormax));
              m[2] = (constrain((throttle_val - bank_right + pitch_fwd), 0, motormax));
              m[3] = (constrain((throttle_val - 10 - bank_right - pitch_fwd), 0, motormax)); 
              motor1.write(m[0]);
              motor2.write(m[1]);
              motor3.write(m[2]);
              motor4.write(m[3]);   
             getStability();
            }
 
// ------------------------------------ ( 9 BANK RIGHT && PITCH BWD) ------------------------------------
            if( bank_val >= high  &&  pitch_val <= low)
            {
              m[0] = (constrain((throttle_val + bank_right + pitch_fwd), 0, motormax));
              m[1] = (constrain((throttle_val + bank_right - pitch_fwd), 0, motormax));
              m[2] = (constrain((throttle_val - bank_right - pitch_fwd), 0, motormax));
              m[3] = (constrain((throttle_val - 10 - bank_right + pitch_fwd), 0, motormax)); 
              motor1.write(m[0]);
              motor2.write(m[1]);
              motor3.write(m[2]);
              motor4.write(m[3]); 
              getStability();
             }
          } // If Throttle_Val Greater than 50       
      }     // If Pot greater than 700
    }       // While Radio Available
  }         // If Radio Available
  
  else
  {
    //Serial.println("No Radio");
  }
}           // End VOID LOOP
//==================================================================================================================================================        
//==========================                      ==================================================================================================        
//==========================       END LOOP       ==================================================================================================
//==========================                      ==================================================================================================   
//==================================================================================================================================================        





// =====================================================================================================================================================
// ===                       Get Angles Code                    ========================================================================================
// =====================================================================================================================================================
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

//===============================================================================================================================================
//==================================     Stability Algorithm      ===============================================================================
//===============================================================================================================================================
/*--------------------- Pitch ---------------------*/  
void getStability()
{
//=========================== 1 ======*/  // Pitch BWD 
    if( ypr[1] >= (yprd[0] + low2) &&     ypr[2] >= (yprd[1] - low2)  &&  ypr[2] <= (yprd[1] + low2))    
    {
      m[0] = constrain(throttle_val + pitch_bwd - Output1, 0, motormax);
      m[1] = constrain(throttle_val - pitch_bwd + Output1, 0, motormax);
      m[2] = constrain(throttle_val - pitch_bwd + Output1, 0, motormax);
      m[3] = constrain(throttle_val + pitch_bwd - Output1, 0, motormax); 
      motor1.write(m[0]);
      motor2.write(m[1]);
      motor3.write(m[2]);
      motor4.write(m[3]);   
    }   
  
//=========================== 2 ======*/  // Pitch FWD  
    if( ypr[1] <= (yprd[0] - low2) &&     ypr[2] >= (yprd[1] - low2)  &&  ypr[2] <= (yprd[1] + low2) )  
    { 
      m[0] = constrain(throttle_val - pitch_fwd + Output2, 0, motormax);
      m[1] = constrain(throttle_val + pitch_fwd - Output2, 0, motormax);
      m[2] = constrain(throttle_val + pitch_fwd - Output2, 0, motormax);
      m[3] = constrain(throttle_val - pitch_fwd + Output2, 0, motormax); 
      motor1.write(m[0]);
      motor2.write(m[1]);
      motor3.write(m[2]);
      motor4.write(m[3]); 
    }   
  
  
//========================================== Roll =====================*/  
//===================== ====== 3 ======*/  // Roll LEFT
    if( ypr[2] <= (yprd[1] - low2) &&     ypr[1] >= (yprd[0] - low2)  &&  ypr[1] <= (yprd[0] + low2) )   
    {    
      m[0] = constrain(throttle_val - bank_left + Output3, 0, motormax);
      m[1] = constrain(throttle_val - bank_left + Output3, 0, motormax);
      m[2] = constrain(throttle_val + bank_left - Output3, 0, motormax);
      m[3] = constrain(throttle_val + bank_left - Output3, 0, motormax); 
      motor1.write(m[0]);
      motor2.write(m[1]);
      motor3.write(m[2]);
      motor4.write(m[3]); 
    }   
    
//=========================== 4 ======*/  // Roll RIGHT  
    if( ypr[2] >= (yprd[1] + low2) &&     ypr[1] >= (yprd[0] - low2)  &&  ypr[1] <= (yprd[0] + low2) )
    {  
      m[0] = constrain(throttle_val + bank_right - Output4, 0, motormax);
      m[1] = constrain(throttle_val + bank_right - Output4, 0, motormax);
      m[2] = constrain(throttle_val - bank_right + Output4, 0, motormax);
      m[3] = constrain(throttle_val - bank_right + Output4, 0, motormax); 
      motor1.write(m[0]);
      motor2.write(m[1]);
      motor3.write(m[2]);
      motor4.write(m[3]); 
    }   
  
  
//========================================== Pitch & Roll =====================*/    
//================================= 5 ======*/  // Picth Bwd && Roll Right
    if( ypr[1] >= (yprd[0] + low2) &&  ypr[2] >= (yprd[1] + low2) )
    {          
      m[0] = constrain(throttle_val + bank_right + pitch_fwd - Output1 - Output4, 0, motormax);
      m[1] = constrain(throttle_val + bank_right - pitch_fwd + Output1 - Output4, 0, motormax);
      m[2] = constrain(throttle_val - bank_right - pitch_fwd + Output1 + Output4, 0, motormax);
      m[3] = constrain(throttle_val - bank_right + pitch_fwd - Output1 + Output4, 0, motormax); 
      motor1.write(m[0]);
      motor2.write(m[1]);
      motor3.write(m[2]);
      motor4.write(m[3]);
    }   
  
//=========================== 6 ======*/  // Picth Bwd && Roll Left  
    if( ypr[1] >= (yprd[0] + low2) && ypr[2] <= (yprd[1] - low2)) 
    {         
      m[0] = constrain(throttle_val - bank_left + pitch_bwd - Output1 + Output3, 0, motormax);
      m[1] = constrain(throttle_val - bank_left - pitch_bwd + Output1 + Output3, 0, motormax);
      m[2] = constrain(throttle_val + bank_left - pitch_bwd + Output1 - Output3, 0, motormax);
      m[3] = constrain(throttle_val + bank_left + pitch_bwd - Output1 - Output3, 0, motormax);         
      motor1.write(m[0]);
      motor2.write(m[1]);
      motor3.write(m[2]);
      motor4.write(m[3]); 
    }   
  
//=========================== 7 ======*/  // Picth Fwd && Roll Left  
    if( ypr[1] <= (yprd[0] - low2) && ypr[2] <= (yprd[1] - low2) )
    {
         
      m[0] = constrain(throttle_val - bank_left - pitch_fwd + Output2 + Output3, 0, motormax);
      m[1] = constrain(throttle_val - bank_left + pitch_fwd - Output2 + Output3, 0, motormax);
      m[2] = constrain(throttle_val + bank_left + pitch_fwd - Output2 - Output3, 0, motormax);
      m[3] = constrain(throttle_val + bank_left - pitch_fwd + Output2 - Output3, 0, motormax); 
      motor1.write(m[0]);
      motor2.write(m[1]);
      motor3.write(m[2]);
      motor4.write(m[3]); 
    }   
  
//=========================== 8 ======*/  // Picth Fwd && Roll Right  
    if( ypr[1] <= (yprd[0] - low2) &&  ypr[2] >= (yprd[1] + low2) ) 
    {
             
      m[0] = constrain(throttle_val + bank_right - pitch_fwd + Output2 - Output4, 0, motormax);
      m[1] = constrain(throttle_val + bank_right + pitch_fwd - Output2 - Output4, 0, motormax);
      m[2] = constrain(throttle_val - bank_right + pitch_fwd - Output2 + Output4, 0, motormax);
      m[3] = constrain(throttle_val - 10 - bank_right - pitch_fwd + Output2 + Output4, 0, motormax); 
      motor1.write(m[0]);
      motor2.write(m[1]);
      motor3.write(m[2]);
      motor4.write(m[3]);    
    }   


//===================== If Input Angles are Within parameters of Datum
/*
    if( ypr[1] >= (yprd[0] - low2) && ypr[1] <= (yprd[0] + low2)   &&   ypr[2] >= (yprd[1] - low2) && ypr[2] <= (yprd[1] + low2))
    {
      myPID1.Compute();       
      myPID2.Compute();
      myPID3.Compute();
      myPID4.Compute();         
      m[0] = constrain(throttle_val - Output1 + Output2 + Output3 - Output4, 0, motormax);
      m[1] = constrain(throttle_val + Output1 - Output2 + Output3 - Output4, 0, motormax);
      m[2] = constrain(throttle_val + Output1 - Output2 - Output3 + Output4, 0, motormax);
      m[3] = constrain(throttle_val - 10 - Output1 + Output2 - Output3 + Output4, 0, motormax);     
      motor1.write(m[0]);
      motor2.write(m[1]);
      motor3.write(m[2]);
      motor4.write(m[3]); 
    }
    */
}  

