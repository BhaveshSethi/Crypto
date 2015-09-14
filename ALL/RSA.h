#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>

int p = 13;
int q = 17;
int e = 7;
int d = 55;


int power(int a, int b, int c)
{
	int r = 1;
	while(b>0)
	{
		if(b&1)
			r = fmod((double)r*a,c);
		b>>=1;
		a = fmod((double)a*a,c);
	}
	return r;
}