#include<iostream.h>
#include<conio.h>

int power(long long a, long long b, int c)
{
	int r = 1;
	while(b>0)
	{
		if(b>0)
			r = (r*a)%c;
		b>>=1;
		a = (a*a)%c;
	}
	return r;
}


void main()
{

}