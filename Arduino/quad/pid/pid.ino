class compute
{int P,I,D,integral;
float error,cons=0,dt,t_now;
float tpre=0,kp,ki,kd,las=0,actual;
public:
void constant()
{error=actual;
  if(t_now>tpre)
dt=t_now-tpre;  
else
dt=-t_now+tpre;  
P=error*kp;
if(integral<100)
integral=integral+error*dt;
else
{
integral=0;
integral=integral+error*dt;
}
I=integral*ki;
if (las>actual)
D=(las-actual)/dt*kd;
else
D=(-las+actual)/dt*kd;
}
cons=P+I+D;
tpre=t_now;
las=actual;
};
