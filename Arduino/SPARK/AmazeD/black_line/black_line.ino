///////////////////////////////////////////////////////*************************PIN DECLARATIONS*******************************//////////////////////////////////////////////////////////////////////////////////////
#define arll 2
#define arl 3
#define arc 4
#define arr 5
#define arrr 6
#define f1 9
#define b1 8
#define pwm1 10
#define pwm2 11
#define f2 13
#define b2 12
////////////////////////////////////////////////////////////////////////////////////////////CONSTANTS//////////////////////////////////////////////////////////////////////////////////////////////////////
int l = 0;
int c = 0;
int r = 0;
int ll = 0;
int rr = 0;
int z = 0;
/////////////////////////////////////////////////////
int y = 0;
int n = 0, i, j;
char d;
///////////////////////////////////////////////////////*************************PIN CHARACTERSTICS*******************************//////////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(arll, INPUT);
  pinMode(arl, INPUT);
  pinMode(arc, INPUT);
  pinMode(arr, INPUT);
  pinMode(arrr, INPUT);
  pinMode(f1, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(f2, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  Serial.begin(9600);
}
///////////////////////////////////////////////////////*************************MAIN LOOP*******************************//////////////////////////////////////////////////////////////////////////////////////
void loop() {
  getz();
  movement(z);
}
////////////////////////////////////////////////////////////////////////////////FUNCTION TO MOVE BOT AHEAD///////////////////////////////////////////////////////////////////////////////////////////////////
void stopie()
{
  Serial.print("stop");
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(f1, LOW);
  digitalWrite(f2, LOW);
}
void straight()
{
  Serial.print("straight");
  analogWrite(pwm1, 100);
  analogWrite(pwm2, 100);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(f1, HIGH);
  digitalWrite(f2, HIGH);
}
////////////////////////////////////////////////////////////////////////////////FUNCTION TO ALIGN BOT TOWARDS LEFT///////////////////////////////////////////////////////////////////////////////////////////////////
void alignright()
{
  Serial.print("align right");
  analogWrite(pwm1, 100);
  analogWrite(pwm2, 100);
  digitalWrite(b2, LOW);
  digitalWrite(f1, LOW);
  digitalWrite(f2, HIGH);
  digitalWrite(b1, HIGH);
  delay(10);
  straight();
}
////////////////////////////////////////////////////////////////////////////////FUNCTION TO ALIGN THE BOT TOWARDS RIGHT///////////////////////////////////////////////////////////////////////////////////////////////////
void alignleft()
{
  Serial.print("align left");
  analogWrite(pwm1, 100);
  analogWrite(pwm2, 100);
  digitalWrite(f2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(f1, HIGH);
  digitalWrite(b2, HIGH);
  delay(10);
  straight();
}
////////////////////////////////////////////////////////////////////////////////FUNCTION TO TAKE A RIGHT TURN///////////////////////////////////////////////////////////////////////////////////////////////////
void right()
{
  Serial.print("right");
  straight();
  delay(50);
  digitalWrite(b2, LOW);
  digitalWrite(b1, LOW);
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 100);
  digitalWrite(f2, HIGH);
  digitalWrite(f1, LOW);
  delay(250);
  digitalWrite(f2, LOW);
  straight();
}
////////////////////////////////////////////////////////////////////////////////FUNCTION TO TAKE A LEFT TURN///////////////////////////////////////////////////////////////////////////////////////////////////
void left()
{ Serial.print("left");
  straight();
  delay(50);
  digitalWrite(b2, LOW);
  digitalWrite(b1, LOW);
  analogWrite(pwm1, 100);
  analogWrite(pwm2, 0);
  digitalWrite(f1, HIGH);
  digitalWrite(f2, LOW);
  delay(250);
  digitalWrite(f1, LOW);
  straight();
}
///////////////////////////////////////////////////////////////////////////////DECIDING BOT MOVEMENT FIRST MAZE TRAVERSING//////////////////////////////////////////////////////////////////////////////////
void movement(int x)
{
  switch (x)
  {
    case 10: {
        alignleft();
        break;
      }
    case 110: {
        alignleft();
        break;
      }
    case 111: {
        left();
        break;
      }
    case 100: {
        straight();
        break;
      }
    case 1000: {
        alignright();
        break;
      }
    case 1100 : {
        alignright();
        break;
      }
    case 11100: {
        right();
        break;
      }
      case 11111: {
        right();//TURN RIGHT AT NODE
      }
    default : straight();
  }
}
////////////////////////////////////////////////////////////////////////GETTING IR SENSOR READING///////////////////////////////////////////////////////////////////////////////////////////////////////
void getz()
{
  ll = digitalRead(arll);
  l = digitalRead(arl);
  c = digitalRead(arc);
  r = digitalRead(arr);
  rr = digitalRead(arrr);
  z = ll * 10000 + l * 1000 + c * 100 + r * 10 + rr;
  Serial.println(z);
}

