 // SNAKE GAME DEVELOPED BY T.R.E.E.S.
 // IN MANUAL CONFIGURATION CHANGE EN_PIN FROM A4 TO 12
  
  
#include <openGLCD.h>    // REQUIRED HEADERS FOR GLCD JHD12864
#include <bitmaps/snake.h>
#include <bitmaps/snake1.h>
#include <bitmaps/trees.h>

int left;
int right;
int up;
int down;
int x=64;
int y=32;
int len=5;        //length=5 ( small squares of 4x4 pixels to mimic the shape of the snake)
int dir=0;
int lost;
int foodx;
int foody;
int score=0;
int newfood=1;
int Speed=4;          // speed can be varied from 0(max speed) to 5(min speed)       
int highscore=0;
int posadd[]={0,0};
int posx[100];
int posy[100];
void initi();

void setup()
{
  GLCD.Init(NON_INVERTED);   
  GLCD.ClearScreen();     
  GLCD.SelectFont(System5x7);
  Serial.begin(9600);
  pinMode(A5,INPUT);    //y-axis
  pinMode(A4,INPUT);   //x-axis
  initi();
}
void loop()
{
  GLCD.ClearScreen(); 
  GLCD.CursorTo(1,0);   
  int x=analogRead(A4);
  int y=analogRead(A5);
  
 Serial.print("x");    // TOO SEE X & Y CO-ORDINATES, NEEDED TO CALIBRATE THE DIRECTION
 Serial.print(x);
 Serial.print('\t');
 Serial.print("y");
 Serial.println(y);
 
 // FOOD DISTRIBUTION IN SPACE
 
  if(newfood==1)
  {
  int repeat=0;
  do
  {
  foodx=random(0,124);
  foody=random(0,60);
  if(foodx%4!=0)
  {
    foodx+=4-(foodx%4);
  }
  if(foody%4!=0)
  {
    foody+=4-(foody%4);
  }
  
  /*Serial.println(foodx);
  Serial.println(foody);*/
  
     for(int i=0;i<len-1;i++)
    {
      if(foodx==posx[i] && foody==posx[i])
      {
      repeat=1;
      }
    }
  } 
  
  while(repeat==1);
  newfood=0;
  }
  
     //INPUTS: CASE 0: FOR CONTROLLING SNAKE, CASE 1: GAME LOST IF SNAKE TOUCHES ITSELF
	 
  switch(lost)
  {
    case 0:
    // left1 DIRECTION
    
// initial left direction

if((  (x>=405 && x<=445)  &&  (y>=355 && y<=390)  ) && dir==0)     //up
{
dir=3;
}
else if((  (x>=350 && x<=380)  &&  (y>=298 && y<=342)  ) && dir==0)  //right
{
dir=0;
}
else if((  (x>=345 && x<=398)  &&  (y>=410 && y<=449)  ) && dir==0)  //left
{
dir=0;
}
else if((  (x>=295 && x<=335)  &&  (y>=365 && y<=380)  ) && dir==0)  //down
{
dir=1;
}


//initial up direction


if((  (x>=405 && x<=445)  &&  (y>=355 && y<=390)  )&& dir==3)       //up  
{
dir=3;
}
else if((  (x>=350 && x<=380)  &&  (y>=298 && y<=342)  ) && dir==3)   //right
{
dir=2;
}
else if((  (x>=345 && x<=398)  &&  (y>=410 && y<=449)  ) && dir==3)   //left
{
dir=0;
}
else if((  (x>=295 && x<=335)  &&  (y>=365 && y<=380)  ) && dir==3)    //down
{
dir=3;
}


//initial right direction


if((  (x>=405 && x<=445)  &&  (y>=355 && y<=390)  ) && dir==2)    //up
{
dir=3;
}
else if((  (x>=350 && x<=380)  &&  (y>=298 && y<=342)  ) && dir==2)   //right
{
dir=2;
}
else if((  (x>=345 && x<=398)  &&  (y>=410 && y<=449)  ) && dir==2)    //left
{
dir=2;
}
else if((  (x>=295 && x<=335)  &&  (y>=365 && y<=380)  ) && dir==2)     //down
{
dir=1;
}


//initial down direction


if((  (x>=405 && x<=445)  &&  (y>=355 && y<=390)  ) && dir==1)    //up
{
dir=1;
}
else if((  (x>=350 && x<=380)  &&  (y>=298 && y<=342)  ) && dir==1)    //right
{
dir=2;
}
else if((  (x>=345 && x<=398)  &&  (y>=410 && y<=449)  ) && dir==1)    //left
{
dir=0;
}
else if((  (x>=295 && x<=335)  &&  (y>=365 && y<=380)  ) && dir==1)    //down
{
dir=1;
}

    // OUTPUT
  for(int i=0;i<len;i++)
  {
  GLCD.DrawRect(posx[i], posy[i], 2, 2, BLACK);
  GLCD.DrawRect(foodx,foody, 1, 1, BLACK);
  }
    // MOVE
  for(int i=0;i<(len-1);i++)
  {
    posadd[0]=posx[0];
    posadd[1]=posy[0];
     posx[i]=posx[i+1];
     posy[i]=posy[i+1];          
  }
   // CHANGING DIRECTIONS
  switch(dir)
  {
    case 0:
    posx[len-1]-=4;
    break;
    case 1:
    posy[len-1]+=4;
    break;
    case 2:
    posx[len-1]+=4;
    break;
    case 3:
    posy[len-1]-=4;
    break;
  }
   //NO WALLS MODE SO NO DISPLAY EDGE LIMIT
  
  if(posx[len-1]<0) 
  {
    posx[len-1]=124;
  }
    if(posx[len-1]>127) 
  {
    posx[len-1]=0;
  }
  if(posy[len-1]>63)
  {
    posy[len-1]=0;
  }
  if(posy[len-1]<0) 
  {
    posy[len-1]=60;
  }
  for(int i=0;i<len-1;i++)
  {
    if(posx[len-1]==posx[i] && posy[len-1]==posy[i])
    {
      lost=1;
    }    
  }
  
 //EAT
  if(posx[len-1]==foodx && posy[len-1]==foody)
  {
    newfood=1;
    len++;
    for(int i=(len-1);i>=1;i--)
    {
     posx[i]=posx[i-1];
     posy[i]=posy[i-1];          
    }
    posx[0]=posadd[0];
    posy[0]=posadd[1];
  }
  
  delay(50*(Speed+1));
  GLCD.ClearScreen();
    
  break;
    
	//SCORE CALCULATING AFTER LOSING
  case 1:
  
     score=(len-5);     //*(6-Speed)/2; 
     if(highscore<score)
     {
     highscore=score; 
     GLCD.DrawString("New HighScore!",gTextfmt_center,gTextfmt_center); 
     delay(2000);
     }
    
    GLCD.ClearScreen();
    GLCD.Puts("Game over :(");
    GLCD.CursorTo(1,2);
    GLCD.Puts("SCORE:");
    GLCD.PrintNumber(score);
    delay(3000);
    GLCD.ClearScreen(); 
    lost=0;
	newfood=1;
    initi();
    break;
  }
}

//INITIAL STATE : SNAKE STARTS FROM THE MIDDLE OF THE SCREEN DEFINED BY BELOW CO-ORDINATES. 
//IF NO INITIALISATION IS PROVIDED IT WILL START FROM TOP right1 DIRECTING TO TOP left1 (dir=0); 

void initi()
{
      posx[0]=64;
      posx[1]=60;
      posx[2]=56;
      posx[3]=52;
      posx[4]=48;
      posy[0]=32;
      posy[1]=32;
      posy[2]=32;
      posy[3]=32;
      posy[4]=32;
      dir=0;
      len=5;
      newfood=1;
}

