char c;
void setup()
{
Serial.begin(9600);
}
void loop()
{c=Serial.read();
if(c=='a')//||Serial.read=='a')
{Serial.println("LEFT");}
else if(c=='s')//||Serial.read=='S')
{Serial.println("DOWN");}
else if(c=='d')//||Serial.read=='D')
{Serial.println("RIGHT");}
else if(c=='w')//||Serial.read=='W')
{Serial.println("UP");}
}
