int p[10]={0,0,0,0,0,0,0,0,0,0},i=0;
int r[10]={0,0,0,0,0,0,0,0,0,0},j=0;
int k,avgp=0,avgr=0;
while(p[9]==0)
{
  r[j]=ypr[2];
  p[i]=ypr[1];
  i++;
  j++;
}
if(p[9]!=0&&r[9]!=0)
{
for(k=0;k<10;k++)
{
avgp+=p[k];
avgr+=r[k];
}
avgp/=10;
avgr/=10;
for(k=0;k<10;k++)
{
r[k]=p[k]=0;
}
i=j=0;
}
