//------------------------------ LIBRARIES -------------------------
#include "I2Cdev.h"
#include "Wire.h"    
#include "MPU6050_6Axis_MotionApps20.h"
#include "MPU6050.h" 

#include "Servo.h"
//#include "SPI.h"
//#include "RF24.h"

#define MAX_SIGNAL 1000
#define MIN_SIGNAL 900

#include "PID_v1.h"
//------------------------------ LIBRARIES -------------------------

void constant();
void esc_calibrate();

//Define Variables we'll be connecting to
double Input1;
double Setpoint1;

double Input2;
double Setpoint2;

double Input3;
double Setpoint3;
double Input4;
double Setpoint4;
//void SetSampleTime(int);
double Output;
double Output1=0;
double Output2=0;
double Output3=0;
double Output4=0;

//Specify the links and initial tuning parameters

Servo up1;
Servo up2;
Servo down1;
Servo down2;

int bank_val;
int bank_left;
int bank_right;
int pitch_val;
int pitch_bwd;
int pitch_fwd;
int throttle_val;
int throttle_val2;
int thepackage;

int changech1=0;
int changech2=0;
int changech3=0;
int changech4=0;

//pinMode(3,INPUT);
//pinMode(4,INPUT);
//pinMode(5,INPUT);

//RF24 radio (7,8);  //RF24 radio(CE_PIN, CSN_PIN);
//const uint64_t pipe_Rx  = 0xE8E8F0F0E1LL;

/*-----( The PACKAGE Array )-----*/
//int package_Rx[4];
  //  1 ==  Throttle
  //  2 ==  Bank
  //  3 ==  Pitch
  //  4 ==  1 = Turn on Radio

/*------(Maximum and Minimum Values)------*/
double error1=0;
double error2=0;
double error3=0;
double error4=0;
double k=3;
int m[4];  
int motormax = 190;
int low = 0;
int high = 0;
int low2 = 2;
//int SampleTime = 1000; //1 sec


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
void setup()
{
  //esc_calibrate();
    
    Input1 = ypr[1];
    Input2 = ypr[2]; 
    Serial.begin(9600);

    //=======================================
    //=====         motor Setup         =====
    //=======================================
      up1.attach(6); 
      up2.attach(9); 
      down1.attach(10);
      down2.attach(11);
      esc_calibrate();
    
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
//esc_calibrate();

}

//==================================================================================================================================================        
//==========================                        ================================================================================================        
//==========================       Start LOOP       ================================================================================================
//==========================                        ================================================================================================ 
//==================================================================================================================================================        
void loop()
{
  
 // SetSampleTime(100);
  changech2 = pulseIn(3, HIGH, 25000);
   // bool done = false;    
   // while(!done)
   // {
            changech3 = pulseIn(4, HIGH, 25000);
            changech4 = pulseIn(5, HIGH, 25000);
            getposition();
            throttle_val = changech2;//package_Rx[0];  // 0 = Zero      190 = MAX
            bank_val     = changech3;//package_Rx[1];
            pitch_val    = changech4;//package_Rx[2];
                     
            /*===== Set Datum for PITCH && ROLL ======*/
            yprd[0] = 0; //      Datum Pitch
            yprd[1] = 0; //      Datum Roll
  
           Setpoint2= Setpoint1 = -0.4;    // Pitch
            Setpoint3=Setpoint4 = -0.63;    // Roll   

            throttle_val = map(throttle_val,1110, 1900, 0,  170);
            bank_val     = map(bank_val, 1120, 1850, 0,  80);
            pitch_val    = map(pitch_val, 1120, 1850, 0,  80);

Serial.print(pitch_val); 
Serial.print('\t'); 
Serial.println(bank_val);         
            Output1    = map(Output1, 0, 500, 0,  40);
            Output2    = map(Output2, 0, 500, 0,  40);
            Output3    = map(Output3, 0, 500, 0,  40);
            Output4    = map(Output4, 0, 500, 0,  40);
           
            /*--------------- BANK ---------------*/
             bank_left  = map(bank_val,  0, 38, 20,  0);
             bank_right = map(bank_val, 42, 80,  0, 20);       
            /*--------------- BANK ---------------*/     

            /*--------------- PITCH ---------------*/
             pitch_bwd  = map(pitch_val,  0, 38, 20,  0);
             pitch_fwd  = map(pitch_val, 42, 80,  0, 20);           
            /*--------------- PITCH ---------------*/
                        
         if( changech2 >= 800)
          {
            //Serial.println("More");
            if(throttle_val <= 40)
            {
              m[0] = throttle_val;
              m[1] = throttle_val;
              m[2] = throttle_val;
              m[3] = throttle_val;   
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);
            }              
//====================================================================================================================        
//===================================       MOTOR CONTROL      =======================================================
//====================================================================================================================
//Serial.print(throttle_val);
//Serial.print('\t');
          if(throttle_val > 40)
          {//Serial.println(throttle_val);
// ------------------------------------ ( 1 ALL THROTTLE) ------------------------------------
            if( changech2>800)//bank_val >= low && bank_val <= high  &&  pitch_val <= high && pitch_val >= low)
            {   
              m[0] = constrain(throttle_val, 0, motormax);
              m[1] = constrain(throttle_val, 0, motormax);
              m[2] = constrain(throttle_val, 0, motormax);
              m[3] = constrain(throttle_val, 0, motormax); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);
   /*           Serial.print(m[0]);  
              Serial.print('\t');  
              Serial.print(m[1]);  
              Serial.print('\t');  
              Serial.print(m[2]);  
              Serial.print('\t');  
              Serial.println(m[3]);  */
              getStability();  
            }
    
    
// ------------------------------------ ( 2 BANK RIGHT) ------------------------------------
            if( bank_val >= high  &&   pitch_val >= low && pitch_val <= high)
            {     
              m[0] = constrain((throttle_val + bank_right), 0, motormax);
              m[1] = constrain((throttle_val - bank_right), 0, motormax);
              m[2] = constrain((throttle_val - bank_right), 0, motormax);
              m[3] = constrain((throttle_val + bank_right), 0, motormax);  
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);    
              
              getStability();    
            }
    
    
// ------------------------------------ ( 3 BANK LEFT) ------------------------------------
            if( bank_val <= low  &&   pitch_val >= low && pitch_val <= high)
            {     
              m[0] = (constrain((throttle_val - bank_left), 0, motormax));
              m[1] = (constrain((throttle_val + bank_left), 0, motormax));
              m[2] = (constrain((throttle_val + bank_left), 0, motormax));
              m[3] = (constrain((throttle_val - bank_left), 0, motormax));   
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);  

              getStability();    
            }    
    
    
// ------------------------------------ ( 4 PITCH BWD) ------------------------------------
            if( pitch_val <= low  &&   bank_val >= low && bank_val <= high)
            {     
              m[0] = (constrain((throttle_val + pitch_bwd), 0, motormax));
              m[1] = (constrain((throttle_val + pitch_bwd), 0, motormax));
              m[2] = (constrain((throttle_val - pitch_bwd), 0, motormax));
              m[3] = (constrain((throttle_val - pitch_bwd), 0, motormax));  
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);     

              
              getStability();
    
            }
    
    
// ------------------------------------ ( 5 PITCH FWD) ------------------------------------
            if( pitch_val >= high  &&   bank_val >= low && bank_val <= high)
            {
              m[0] = (constrain((throttle_val - pitch_fwd), 0, motormax));
              m[1] = (constrain((throttle_val - pitch_fwd), 0, motormax));
              m[2] = (constrain((throttle_val + pitch_fwd), 0, motormax));
              m[3] = (constrain((throttle_val + pitch_fwd), 0, motormax)); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);

              getStability();
             }
    
// -----------------------------------------   (Double Logic) ------------------------------------
// ------------------------------------ ( 6 BANK LEFT && PITCH BWD) ------------------------------------
            if( bank_val <= low  &&  pitch_val <= low)
            {
              m[0] = (constrain((throttle_val - bank_left + pitch_bwd), 0, motormax));
              m[1] = (constrain((throttle_val + bank_left + pitch_bwd), 0, motormax));
              m[2] = (constrain((throttle_val + bank_left - pitch_bwd), 0, motormax));
              m[3] = (constrain((throttle_val - bank_left - pitch_bwd), 0, motormax));
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);   

              
              getStability();
             }
    
    
// ------------------------------------ ( 7 BANK LEFT && PITCH FWD) ------------------------------------
            if( bank_val <= low  &&  pitch_val >= high)
            {     
              m[0] = (constrain((throttle_val - bank_left - pitch_fwd), 0, motormax));
              m[1] = (constrain((throttle_val + bank_left - pitch_fwd), 0, motormax));
              m[2] = (constrain((throttle_val + bank_left + pitch_fwd), 0, motormax));
              m[3] = (constrain((throttle_val - bank_left + pitch_fwd), 0, motormax));
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);

              getStability();
             }
    
    
// ------------------------------------ ( 8 BANK RIGHT && PITCH FWD) ------------------------------------
            if( bank_val >= high  &&  pitch_val >= high)
            {     
              m[0] = (constrain((throttle_val + bank_right - pitch_fwd), 0, motormax));
              m[1] = (constrain((throttle_val - bank_right - pitch_fwd), 0, motormax));
              m[2] = (constrain((throttle_val - bank_right + pitch_fwd), 0, motormax));
              m[3] = (constrain((throttle_val + bank_right + pitch_fwd), 0, motormax)); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);   

              
             getStability();
            }
 
// ------------------------------------ ( 9 BANK RIGHT && PITCH BWD) ------------------------------------
            if( bank_val >= high  &&  pitch_val <= low)
            {
              m[0] = (constrain((throttle_val + bank_right + pitch_bwd), 0, motormax));
              m[1] = (constrain((throttle_val - bank_right + pitch_bwd), 0, motormax));
              m[2] = (constrain((throttle_val - bank_right - pitch_bwd), 0, motormax));
              m[3] = (constrain((throttle_val + bank_right - pitch_bwd), 0, motormax)); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);  
              getStability();
             }
          } // If Throttle_Val Greater than 50       
      }    
       else      if( changech2 ==0)
          {
              m[0] = constrain(throttle_val, 0, 180);
              m[1] = constrain(throttle_val, 0, 180);
              m[2] = constrain(throttle_val, 0, 180);
              m[3] = constrain(throttle_val, 0, 180); 
              up1.write(0);
              up2.write(0);
              down1.write(0);
              down2.write(0);
            //Serial.println(m[0]); 
          }             // If Pot greater than 700
          // While Radio Available
         /* Serial.print(ypr[1]);
          Serial.print('\t');
          Serial.println(ypr[2]);*/
          //esc_calibrate();

}           // End VOID LOOP
//==================================================================================================================================================        
//============================================================================================================================        
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
{constant();
getposition();
//=========================== 1 ======*/  // Pitch if BWD 
   if( ypr[1] >= (yprd[0] + low2)&&    ypr[2] >= (yprd[1] - low2)  &&  ypr[2] <= (yprd[1] + low2))    
    {constant();
     getposition();
      Output1+=error1*k;
      Output4=0;
      Output3=0;
      Output2=0;
      m[0] = constrain(throttle_val - Output1, 0, motormax);
      m[1] = constrain(throttle_val - Output1, 0, motormax);
      m[2] = constrain(throttle_val + Output1, 0, motormax);
      m[3] = constrain(throttle_val + Output1, 0, motormax); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);    
              
    }   
  
//=========================== 2 ======  // Pitch if FWD  
    if( ypr[1] <= (yprd[0] - low2) &&    ypr[2] >= (yprd[1] - low2)  &&  ypr[2] <= (yprd[1] + low2) )  
    {constant();
getposition();
      Output2+=error2*k;
     Output3=0;
     Output4=0;
     Output1=0;
     // myPID2.Compute();    
      m[0] = constrain(throttle_val  + Output2, 0, motormax);
      m[1] = constrain(throttle_val + Output2, 0, motormax);
      m[2] = constrain(throttle_val  - Output2, 0, motormax);
      m[3] = constrain(throttle_val  - Output2, 0, motormax); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);  
              
    }   
  
 
//========================================== Roll =====================*/  
//===================== ====== 3 ======*/  // Roll if LEFT
   if( ypr[2] <= (yprd[1] - low2) &&     ypr[1] >= (yprd[0] - low2)  &&  ypr[1] <= (yprd[0] + low2) )   
    {
      constant();
getposition();
      Output3=error3*k;
    Output4=0;
    Output2=0;
    Output1=0;
     // myPID3.Compute();     
      m[0] = constrain(throttle_val  + Output3, 0, motormax);
      m[1] = constrain(throttle_val - Output3, 0, motormax);
      m[2] = constrain(throttle_val  - Output3, 0, motormax);
      m[3] = constrain(throttle_val  + Output3, 0, motormax); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);
              Serial.print(Output3);
              Serial.print('\t');
                
    }   
    
//=========================== 4 ======  // Roll RIGHT  
    if( ypr[2] >= (yprd[1] + low2) )//&&     ypr[1] >= (yprd[0] - low2)  &&  ypr[1] <= (yprd[0] + low2) )
    {
      constant();
getposition();
      Output4+=error4*k;
     Output3=0;
     Output2=0;
     Output1= 0; 
      m[0] = constrain(throttle_val  - Output4, 0, motormax);
      m[1] = constrain(throttle_val + Output4, 0, motormax);
      m[2] = constrain(throttle_val  + Output4, 0, motormax);
      m[3] = constrain(throttle_val  - Output4, 0, motormax); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);  

              
    }   
  

//========================================== Pitch & Roll =====================   
//================================= 5 ======  // Picth if  Bwd && Roll if Right
    if( ypr[1] >= (yprd[0] + low2) &&  ypr[2] >= (yprd[1] + low2) )
    {
      constant();
getposition();
      Output1+=error1*k;
      Output4+=error4*k;
    Output3=0;
    Output2=0;
                
      m[0] = constrain(throttle_val - Output1 - Output4, 0, motormax);
      m[1] = constrain(throttle_val -  Output1 + Output4, 0, motormax);
      m[2] = constrain(throttle_val + Output1 + Output4, 0, motormax);
      m[3] = constrain(throttle_val  + Output1 - Output4, 0, motormax); 

              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);  
               

    }   
  
//=========================== 6 ======  // Picth if Bwd && Roll if Left  
    if( ypr[1] >= (yprd[0] + low2) && ypr[2] <= (yprd[1] - low2)) 
    {
      constant();
getposition();
      Output1+=error1*k;
      Output3+=error3*k;
    Output4=0;
    Output2=0;
     // myPID1.Compute();       
     // myPID3.Compute();          
      m[0] = constrain(throttle_val - Output1 + Output3, 0, motormax);
      m[1] = constrain(throttle_val  - Output1 - Output3, 0, motormax);
      m[2] = constrain(throttle_val  + Output1 - Output3, 0, motormax);
      m[3] = constrain(throttle_val  + Output1 + Output3, 0, motormax);  
             
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);  
              
    }   
  
//=========================== 7 ====== // Picth if Fwd && Roll if Left  
    if( ypr[1] <= (yprd[0] - low2) && ypr[2] <= (yprd[1] - low2) )
    {
      constant();
getposition();
      Output2+=error2*k;
      Output3+=error3*k;
    Output4=0;
    Output1=0;
   //   myPID2.Compute();       
   //   myPID3.Compute();        
      m[0] = constrain(throttle_val  + Output2 + Output3, 0, motormax);
      m[1] = constrain(throttle_val + Output2 - Output3, 0, motormax);
      m[2] = constrain(throttle_val  - Output2 - Output3, 0, motormax);
      m[3] = constrain(throttle_val - Output2 + Output3, 0, motormax); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);   
    }   
  
//=========================== 8 ======  // Picth  if Fwd && Roll if Right  
    if( ypr[1] <= (yprd[0] - low2) &&  ypr[2] >= (yprd[1] + low2) ) 
    {
      constant();
getposition();
      Output2+=error2*k;
      Output4+=error4*k;
    Output1=0;
    Output3=0;
  //    myPID2.Compute();       
    //  myPID4.Compute();        
      m[0] = constrain(throttle_val  + Output2 - Output4, 0, motormax);
      m[1] = constrain(throttle_val + Output2 + Output4, 0, motormax);
      m[2] = constrain(throttle_val  - Output2 + Output4, 0, motormax);
      m[3] = constrain(throttle_val  - Output2 - Output4, 0, motormax); 
              up1.write(m[0]);
              up2.write(m[1]);
              down1.write(m[2]);
              down2.write(m[3]);  
    }   



}  
void constant()
{if(ypr[1]>Setpoint1)
  error1=ypr[1]-Setpoint1;//pitch error positive
  else
  {error2=Setpoint1-ypr[1];}//pitch error negative
  if(ypr[2]>Setpoint2)
  error4=-Setpoint2+ypr[2];//roll error positive
  else
  {error3=Setpoint2-ypr[2];}//roll error negative
  }
  
 void esc_calibrate()
 {
 
              up1.writeMicroseconds(MAX_SIGNAL);
              up2.writeMicroseconds(MAX_SIGNAL);
              down1.writeMicroseconds(MAX_SIGNAL);
              down2.writeMicroseconds(MAX_SIGNAL);  
              delay(100);

            //  Serial.println(MAX_SIGNAL);
              up1.writeMicroseconds(MIN_SIGNAL);
              up2.writeMicroseconds(MIN_SIGNAL);
              down1.writeMicroseconds(MIN_SIGNAL);
              down2.writeMicroseconds(MIN_SIGNAL);  
 }
