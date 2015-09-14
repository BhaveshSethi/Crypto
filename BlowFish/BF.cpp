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
void main()
{
	clrscr();
	cout<<"\n\tBlowFish\n\t";
	int i,j,flag,val;
	FILE *oFile, *cFile;
	oFile = fopen("test.txt","rb");
	char key[20],msg[80],data[8],crypt[8];
	cFile = fopen("cryptBF.dat","wb");
	strcpy(key,"summers");
	expandKey(key,P);

	flag=1;
	fseek(oFile,0,SEEK_SET);
	fseek(cFile,0,SEEK_SET);
	char ch='1';
	cout<<"\n\tEncrypting File Test.txt:\n";
	while((ch=fgetc(oFile))!=EOF)
		cout<<ch;
	cout<<"\n\nEncrypted File:\n";
	fclose(oFile);
	oFile = fopen("test.txt","rb");
	clock_t c1 = clock();
	while(flag)
	{
		ch = fgetc(oFile);
		j=0;
		while(ch!=EOF)
		{
			data[j++]=ch;
			if(j==8)
				break;
			ch=fgetc(oFile);
		}
		if(j==0)
			break;
		else if(j < 8)
		{
			flag=0;
			for(;j<8;j++)
				data[j] = 0;
		}
		blowfish(crypt,data,0);

		for(j=0;j<8;j++)
		{
			val = (unsigned char)crypt[j];
			fputc(val,cFile);
			cout<<(unsigned char)val;
		}
	}
	fclose(cFile);
	fclose(oFile);
	cout<<"\n\tEncryption Ends ";
	clock_t c2 = clock();
	cout<<"\n\tTime taken is "<<(c2-c1)/CLK_TCK<<" sec";

	cFile = fopen("cryptBF.dat","rb");
	flag=1;
	oFile = fopen("test1.txt","wb");
	fseek(oFile,0,SEEK_SET);
	fseek(cFile,0,SEEK_SET);
	ch='0';
	c1=clock();
	cout<<"\n\n\tNow Decrypting \n\tDecrypted File:\n";
	while(flag)
	{
		memset(crypt,0,8);
		i=0;
		while(val != EOF)
		{
			val = fgetc(cFile);
			if(val == EOF)
				flag=0;
			else
			{
				crypt[i++] = (unsigned char)val;
			}
			if(i==8)
				break;
		}
		blowfish(crypt,data,1);
		if(flag)
		{
			print8(data);
			for(int i=0;i<8;i++)
			{
				if(data[i])
					fputc(data[i],oFile);
			}
		}
	}
	fclose(cFile);
	fclose(oFile);

	c2 = clock();
	cout<<"\n\tDecrypting done";
	cout<<"\n\tTime taken is "<<(c2-c1)/CLK_TCK<<" sec";
	getch();
}