#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

int p = 13;
int q = 17;
int e = 7;
int d = 55;


int power(int a, int b, int c)
{
	int r = 1;
	while(b>0)
	{
		//cout<<"\n"<<a<<" "<<b<<" "<<c<<" "<<r;
		if(b&1)
			r = fmod((double)r*a,c);
		b>>=1;
		a = fmod((double)a*a,c);
	}
//	cout<<endl<<r;
	return r;
}


void main()
{
	clrscr();
	int i,len,n = p*q;
	char ch=1,ch1;
	cout<<"\n\tRSA ";
	FILE *oFile,*cFile;
	oFile = fopen("test.txt","rb");
	cFile = fopen("cryptRSA.dat","wb");

	cout<<"\n\tEncrypting..";

	while(ch!=EOF)
	{
		ch=fgetc(oFile);
		if(ch==EOF)
			break;
		ch1 = char(power((int)ch,e,n));
		//cout<<ch;
		fputc(ch1,cFile);
	}
	fclose(oFile);
	fclose(cFile);

	cout<<"\n\tDone\n\tNow Deciphering.. ";
	oFile = fopen("test1.txt","wb");
	cFile = fopen("cryptRSA.dat","rb");
	ch=1;
	while(ch!=EOF)
	{
		ch=fgetc(cFile);
		if(ch==EOF)
			break;
		ch1 = (char)(power((int)(unsigned char)ch,d,n));
		//cout<<ch1;
		fputc(ch1,oFile);
	}
	fclose(oFile);
	fclose(cFile);

	cout<<"\n\tDone";

	getch();
}