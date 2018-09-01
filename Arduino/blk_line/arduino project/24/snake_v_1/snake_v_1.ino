
int inita0=analogRead(A0);
int inita1=analogRead(A1);
int inita2=analogRead(A2);
int inita3=analogRead(A3);
#include<openGLCD.h>
void setup() {
  // put your setup code here, to run once:
GLCD.Init();//initialize the glcd
GLCD.ClearScreen();//clear the glcd
GLCD.SelectFont(System5x7);//select the glcd font
Serial.begin(9600);//start the serial communication
GLCD.SetDot(0,32,BLACK);
GLCD.SetDot(1,32,BLACK);
GLCD.SetDot(2,32,BLACK);
GLCD.SetDot(3,32,BLACK);
GLCD.SetDot(4,32,BLACK);//display the snake
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);//initialize siwtches for input
}

void loop() {
  // put your main code here, to run repeatedly:


int curra0=analogRead(A0);
int curra1=analogRead(A1);
int curra2=analogRead(A2);
int curra3=analogRead(A3);
int i=5;
int j=0;

while(inita0==curra0&&inita1==curra1&&inita2==curra2&&inita3==curra3)
{

GLCD.SetDot(i,32,BLACK);
GLCD.SetDot(j,32,WHITE);  
i++;  
j++;

if(i==127)
i=0;
if(j==127)
j=0;
delay(500);
curra0=analogRead(A0);
curra1=analogRead(A1);
curra2=analogRead(A2);
curra3=analogRead(A3);
}
foodx=random(0,127);
foody=random(0,63);

}
