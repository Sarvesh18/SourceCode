///////////////////////////////////////////////////////*************************PIN DECLARATIONS*******************************//////////////////////////////////////////////////////////////////////////////////////
#define arll 6
#define arl 5
#define arc 4
#define arr 3
#define arrr 2
#define f1 8
#define b1 9
#define pwm1 10
#define pwm2 11
#define f2 12
#define b2 13
////////////////////////////////////////////////////////////////////////////////////////////CONSTANTS//////////////////////////////////////////////////////////////////////////////////////////////////////
int l=0;
int c=0;
int r=0;
int ll=0;
int rr=0;
int z=0;
int y=0;
int bhag=0;
    int n=0,i,j;
    char d;
char ar[501];
///////////////////////////////////////////////////////*************************PIN CHARACTERSTICS*******************************//////////////////////////////////////////////////////////////////////////////////////
void setup() {
pinMode(arll,INPUT);
pinMode(arl,INPUT);
pinMode(arc,INPUT);
pinMode(arr,INPUT);
pinMode(arrr,INPUT);
pinMode(f1,OUTPUT);
pinMode(b1,OUTPUT);
pinMode(f2,OUTPUT);
pinMode(b2,OUTPUT);
pinMode(pwm1,OUTPUT);
pinMode(pwm2,OUTPUT);
}
///////////////////////////////////////////////////////*************************MAIN LOOP*******************************//////////////////////////////////////////////////////////////////////////////////////
void loop() {
  if(bhag==0)
  {
getz();
 movement(z);
  }
  else {
getz();
if(z!=10111&&z!=11011&&z!=11101&&z!=11001&&z!=10011)
{d=ar[i];
traverse(d);i++;}
  }
}
////////////////////////////////////////////////////////////////////////////////FUNCTION TO CHOOSE JUNCTION STEPS///////////////////////////////////////////////////////////////////////////////////////////////////
void inch()
{digitalWrite(pwm1,250);
  digitalWrite(pwm2,250);
  digitalWrite(f1,HIGH);
  digitalWrite(f2,HIGH);
  delay(500);
  digitalWrite(f1,LOW);
  digitalWrite(f2,LOW);
 getz();
 if(y==1)
     {if(z==0)
        { z=3;}
       else {z=11;}}
  else if(y==2)
  {
  if(z==11111)
      {z=2;}
      else {z=11011;}
  }
     
movement(z);
}

////////////////////////////////////////////////////////////////////////////////FUNCTION TO MOVE BOT AHEAD///////////////////////////////////////////////////////////////////////////////////////////////////
void straight()
{
  digitalWrite(pwm1,250);
  digitalWrite(pwm2,250);
digitalWrite(b1,LOW);
digitalWrite(b2,LOW);
digitalWrite(f1,HIGH);
digitalWrite(f2,HIGH);
}
////////////////////////////////////////////////////////////////////////////////FUNCTION TO ALIGN BOT TOWARDS LEFT///////////////////////////////////////////////////////////////////////////////////////////////////
void alignleft()
{
  digitalWrite(f1,LOW);
digitalWrite(f2,HIGH);
digitalWrite(b1,HIGH);
delay(50);
straight();
}
////////////////////////////////////////////////////////////////////////////////FUNCTION TO ALIGN THE BOT TOWARDS RIGHT///////////////////////////////////////////////////////////////////////////////////////////////////
void alignright()
{digitalWrite(pwm1,250);
  digitalWrite(pwm2,250);
digitalWrite(f1,HIGH);
digitalWrite(f2,LOW);
digitalWrite(b2,HIGH);
delay(50);
straight();
}
////////////////////////////////////////////////////////////////////////////////FUNCTION TO TAKE A RIGHT TURN///////////////////////////////////////////////////////////////////////////////////////////////////
void right()
{digitalWrite(pwm1,250);
  digitalWrite(pwm2,250);
  digitalWrite(f2,LOW);
digitalWrite(f1,HIGH);
digitalWrite(b2,HIGH);
delay(200);
digitalWrite(f1,LOW);
digitalWrite(b2,LOW);
straight();
}
////////////////////////////////////////////////////////////////////////////////FUNCTION TO TAKE A LEFT TURN///////////////////////////////////////////////////////////////////////////////////////////////////
void left()
{digitalWrite(pwm1,250);
  digitalWrite(pwm2,250);
digitalWrite(f1,LOW);
digitalWrite(f2,HIGH);
digitalWrite(b1,HIGH);
delay(200);
digitalWrite(f2,LOW);
digitalWrite(b1,LOW);
straight();
}
////////////////////////////////////////////////////////////////////////////////FUNCTION TO TAKE A UTURN///////////////////////////////////////////////////////////////////////////////////////////////////
void uturn()

{digitalWrite(pwm1,250);
  digitalWrite(pwm2,250);
  digitalWrite(b1,LOW);
digitalWrite(b2,LOW);
 digitalWrite(f2,HIGH);
digitalWrite(f1,HIGH);
delay(250);
digitalWrite(f2,LOW);
digitalWrite(f1,LOW);
 
 while(digitalRead(4)!=0)
 { digitalWrite(f2,HIGH);
digitalWrite(b1,HIGH);
 }
digitalWrite(f2,LOW);
digitalWrite(b1,LOW);
straight();
}
///////////////////////////////////////////////////////////////////////////////DECIDING BOT MOVEMENT FIRST MAZE TRAVERSING//////////////////////////////////////////////////////////////////////////////////
void movement(int x)
{
switch(x)
 {
case 11101:{alignright();break;}
case 3:{digitalWrite(f2,LOW);
digitalWrite(b1,LOW);
digitalWrite(f1,LOW);
digitalWrite(b2,LOW);delay(10000);compute();break;}
case 2:{ar[i]='r';i++;right();break;}
case 11000:{y=2;inch();break;}
case 11011:{ar[i]='s';i++;straight();break;}
case 10111:{alignleft();break;}
case 11:{ar[i]='l';i++;left();break;}
case 0:{inch();y=1;break;}
case 11111:{ar[i]='u';i++;uturn();break;}
 default:{straight(); break;}
 }
}
/////////////////////////////////////////////////////////////////////////////////FINDING THE SHORTEST PATH///////////////////////////////////////////////////////////////////////////////////////////////////
char f(char a,char b)
{
    if(a=='r')
    {
        if(b=='r')
        {
            return 's';
        }
        else if(b=='s')
        {
            return 'l';
        }
        else if(b=='l')
            return 'u';
    }

    else if(a=='l')
    {

        if(b=='s')
        {
            return 'r';
        }
        else if(b=='r')
        {
            return 'u';
        }
        else if(b=='l')
            return 's';
    }

    else if  (a=='s')
    {

        if(b=='r')
        {
            return 'l';
        }
        else if(b=='l')
        {
            return 'r';
        }
        else if(b=='s')
            return 'u';
    }
}

void compute()
{
bhag=1;
    for(i=0; i<n; i++)
    {
        while(ar[i]=='u')
        {
          
            d=f(ar[i-1],ar[i+1]);
            ar[i-1]=d;
            for(j=i; j<n-2; j++)
            {
                ar[j]=ar[j+2];
            }
            n=n-2;
            i=i-2;
        }
    }
i=0;
}
/////////////////////////////////////////////////////////////////////////END OF FINDING THE SHORTEST PATH///////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////GETTING IR SENSOR READING///////////////////////////////////////////////////////////////////////////////////////////////////////
void getz()
{
ll=digitalRead(arll);
  l=digitalRead(arl);
 c=digitalRead(arc);
 r=digitalRead(arr);
  rr=digitalRead(arrr);
 z=ll*10000+l*1000+c*100+r*10+rr;
}

//////////////////////////////////////////////////////////////////////////FINAL TRAVERSING OF THE MAZE SOLVING////////////////////////////////////////////////////////////////////////////////////////////
void traverse(char m)
{
switch(d)
{
case 'l':{left();break;}
case 'r':{right();break;}
case 's':{straight();break;}
}
}
