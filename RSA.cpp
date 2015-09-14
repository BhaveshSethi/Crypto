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


void main()
{
	clrscr();
	int i,len,n = p*q;
	char ch=1,ch1;
	cout<<"\n\tRSA ";
	FILE *oFile,*cFile;
	oFile = fopen("test.txt","rb");
	cFile = fopen("cryptRSA.dat","wb");

	cout<<"\n\tEncrypting File Test.txt:\n";
	while((ch=fgetc(oFile))!=EOF)
		cout<<ch;
	cout<<"\n\nEncrypted File:\n";
	fclose(oFile);
	oFile = fopen("test.txt","rb");
	ch=1;
	clock_t c1 = clock();

	while(ch!=EOF)
	{
		ch=fgetc(oFile);
		if(ch==EOF)
			break;
		ch1 = char(power((int)ch,e,n));
		cout<<ch1;
		fputc(ch1,cFile);
	}
	fclose(oFile);
	fclose(cFile);

	cout<<"\n\tEncryption Ends ";
	clock_t c2=clock();
	cout<<"\n\tTime taken is "<<(c2-c1)/CLK_TCK<<" sec";

	cout<<"\n\n\tNow Decrypting\n\t";
	c1=clock();

	oFile = fopen("test1.txt","wb");
	cFile = fopen("cryptRSA.dat","rb");
	ch=1;
	while(ch!=EOF)
	{
		ch=fgetc(cFile);
		if(ch==EOF)
			break;
		ch1 = (char)(power((int)(unsigned char)ch,d,n));
		cout<<ch1;
		fputc(ch1,oFile);
	}
	fclose(oFile);
	fclose(cFile);

	c2 = clock();
	cout<<"\n\tDecrypting done";
	cout<<"\n\tTime taken is "<<(c2-c1)/CLK_TCK<<" sec";

	getch();
}