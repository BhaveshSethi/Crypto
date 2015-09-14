#include<fstream.h>
#include<iomanip.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<bftable.h>
#include<time.h>

void strToInt(unsigned long int *xL, unsigned long int *xR, unsigned char str[8])
{
	*xL=*xR=0;
	for(int j=0;j<4;j++)
	{
		*xL+=(unsigned long int)(str[j])<<((3-j)*8);
		*xR+=(unsigned long int)(str[j+4])<<((3-j)*8);
	}
}
void blowfish(unsigned char Cstr[8], unsigned char str[8],int mode)
{
	unsigned char strL[4],strR[4];
	int i,j;
	unsigned long int xL,xR,x,y,temp;
	if(!mode)
		strToInt(&xL,&xR,str);
	else
		strToInt(&xL,&xR,Cstr);
	for(i=0;i<16;i++)
	{
		x=y=0;
		if(mode==0)
			xL^=P[i];
		else
			xL^=P[17-i];
		x=xL;
		for(j=3;j>=0;j--)
		{
			strL[j] = x;
			x = x >> 8;
		}
		y = ((S[0][strL[0]] + S[1][strL[1]]) ^ S[2][strL[2]]) + S[3][strL[3]];
		xR ^= y;
		x=xR;
		temp = xL;
		xL = xR;
		xR = temp;
	}
	temp = xL;
	xL = xR;
	xR = temp;
	if(mode==0)
	{
		xR ^= P[16];
		xL ^= P[17];
	}
	else
	{
		xR ^= P[1];
		xL ^= P[0];
	}
	for(j=3;j>=0;j--)
	{
		if(!mode)
		{
			Cstr[j+4] = xR;
			Cstr[j] = xL;
		}
		else
		{
			str[j+4] = xR;
			str[j] = xL;
		}
		xL = xL >> 8;
		xR = xR >> 8;
	}
}
void print8(char *str)
{
	for(int i=0;i<8;i++)
		cout<<str[i];
}
void expandKey(char key[20],unsigned long int P[18])
{
	int len=strlen(key),i,j,k=0;
	unsigned long int x,kL,kR;
	for(i=0;i<18;i++)
	{
		x=0;
		for(j=0;j<=3;j++)
			x += (unsigned long int)(key[(j + k)%len])<<((3-j)*8);
		k = (k+4)%len;
		P[i]^=x;
	}
	char keyCrypt[8];
	memset(keyCrypt,0,8);
	for(i=0;i<18;i+=2)
	{
		kL=kR=0;
		blowfish(keyCrypt,keyCrypt,0);
		strToInt(&kL,&kR,keyCrypt);
		P[i] = kL;
		P[i+1] = kR;
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<256;j+=2)
		{
			kL=kR=0;
			blowfish(keyCrypt,keyCrypt,0);
			strToInt(&kL,&kR,keyCrypt);
			S[i][j] = kL;
			S[i][j+1] = kR;
		}
	}
}