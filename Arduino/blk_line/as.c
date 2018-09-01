#include<stdio.h>
#include<string.h>
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
main()
{
    int n=0,i,j,k;
    char a[200];
    char c;
    scanf("%s",&a);
    n=strlen(a);

    for(i=0; i<n; i++)
    {
        while(a[i]=='u')
        {
            c=f(a[i-1],a[i+1]);
            a[i-1]=c;
            for(j=i; j<n-2; j++)
            {
                a[j]=a[j+2];
            }
            n=n-2;
            i=i-2;
          for(k=0; k<n; k++)
    {
        printf("%c",a[k]);
    }
    printf("\n");
        }
    }
    for(i=0; i<n; i++)
    {
        printf("%c",a[i]);
    }
}

