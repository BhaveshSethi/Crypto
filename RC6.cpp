#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<math.h>
#include<time.h>

const int w = 32, r = 20, b = 16;
const unsigned long P = 0xB7E15163, Q = 0x9E3779B9;

unsigned long Ror(unsigned long X, int places)
{
	return X>>places|X<<(32-places);
}
unsigned long Rol(unsigned long X, int places)
{
	return X<<places|X>>(32-places);
}
void keySched(char k[16], unsigned long S[2*r+4])
{
	unsigned long L[4],i,j;
	for(i=0;i<4;i++)
	{
		L[i]=0;
		for(j=0;j<4;j++)
				L[i] += (unsigned long)((int)k[4*i + j])<<(8*j);
	}
	S[0] = P;
	for(i=1;i<=2*r+3;i++)
		S[i] = S[i-1]+Q;
	unsigned long A,B;
	A=B=i=j=0;
	int v = (4>(2*r+4))?12:3*(2*r+4);
	for(int s=1;s<=v;s++)
	{
		A = S[i] = Rol((S[i] + A + B),3);
		B = L[j] = Rol((L[j] + A + B),(A+B)&31);
		i = (i+1)%(2*r+4);
		j = (j+1)%4;
	}
}

void RC6Encrypt(char C[16], char M[16], unsigned long S[2*r+4])
{
	unsigned long A[4],t,u;
	int i,j;
	for(i=0;i<4;i++)
	{
		A[i]=0;
		for(j=0;j<4;j++)
			A[i] += (unsigned long)((int)(unsigned char)M[4*i+j])<<(8*j);
	}
	A[1]+=S[0];
	A[3]+=S[1];
	for(i=1;i<=r;i++)
	{
		t = Rol((A[1]*(A[1]*2 + 1)),5);
		u = Rol((A[3]*(A[3]*2 + 1)),5);
		A[0] = Rol((A[0]^t),u&31) + S[2*i];
		A[2] = Rol((A[2]^u),t&31) + S[2*i+1];
		t=A[0];
		A[0]=A[1];
		A[1]=A[2];
		A[2]=A[3];
		A[3]=t;
	}
	A[0] = A[0]+S[2*r + 2];
	A[2] = A[2]+S[2*r + 3];
	for(i=0;i<16;i++)
	{
		C[i] = (unsigned char)A[i/4];
		A[i/4]>>=8;
	}
}
void RC6Decrypt(char C[16], char M[16], unsigned long S[2*r+4])
{
	unsigned long A[4],t,u;
	int i,j;
	for(i=0;i<4;i++)
	{
		A[i]=0;
		for(j=0;j<4;j++)
			A[i] += (unsigned long)((int)(unsigned char)C[4*i+j])*pow(2,8*j);
	}
	A[2]-=S[2*r + 3];
	A[0]-=S[2*r + 2];
	for(i=r;i>=1;i--)
	{
		t=A[0];
		A[0]=A[3];
		A[3]=A[2];
		A[2]=A[1];
		A[1]=t;
		u = Rol((A[3]*(A[3]*2 + 1)),5);
		t = Rol((A[1]*(A[1]*2 + 1)),5);
		A[2] = Ror((A[2] - S[2*i + 1]),t&31) ^ u;
		A[0] = Ror((A[0] - S[2*i]),u&31) ^ t;
	}
	A[3] = A[3] - S[1];
	A[1] = A[1] - S[0];
	for(i=0;i<16;i++)
	{
		M[i] = (unsigned char)A[i/4];
		A[i/4]>>=8;
	}
}

void print16(char *str)
{
	for(int i=0;i<16;i++)
		cout<<str[i];
}


void main()
{
	clrscr();
	int i,flag=1,j,val=1;
	cout<<"\n\tRC6";
	char key[16],data[16],crypt[16],ch;
	unsigned long S[2*r+4];
	strcpy(key,"0123456789012345");
	cout<<"\n\tChosen key is ";
	for(i=0;i<16;i++)
		cout<<key[i];
	keySched(key,S);
	FILE *oFile,*cFile;
	oFile = fopen("test.txt","rb");
	cFile = fopen("cryptRC6.dat","wb");

	cout<<"\n\tEncrypting File Test.txt:\n";
	while((ch=fgetc(oFile))!=EOF)
		cout<<ch;
	cout<<"\n\nEncrypted File:\n";
	fclose(oFile);
	oFile = fopen("test.txt","rb");

	clock_t c1 = clock();

	while(flag)
	{
		ch=fgetc(oFile);
		i=0;
		while(ch!=EOF)
		{
			data[i++]=ch;
			if(i==16)
				break;
			ch=fgetc(oFile);
		}
		if(i==0)
			break;
		else if(i<16)
		{
			flag=0;
			for(;i<16;i++)
				data[i]=0;
		}
		RC6Encrypt(crypt,data,S);
		for(i=0;i<16;i++)
		{
			j = (unsigned char)crypt[i];
			cout<<(unsigned char)j;
			fputc(j,cFile);
		}
	}
	fclose(oFile);
	fclose(cFile);






	cFile = fopen("cryptRC6.dat","rb");
	flag=1;
	oFile = fopen("test1.txt","wb");
	fseek(oFile,0,SEEK_SET);
	fseek(cFile,0,SEEK_SET);
	cout<<"\n\tEncryption Ends ";
	clock_t c2=clock();
	cout<<"\n\tTime taken is "<<(c2-c1)/CLK_TCK<<" sec";

	cout<<"\n\n\tNow Decrypting\n\t";
	c1=clock();

	while(flag)
	{
		memset(crypt,0,16);
		i=0;
		while(val != EOF)
		{
			val = fgetc(cFile);
			if(val == EOF)
				flag=0;
			else
				crypt[i++] = (unsigned char)val;
			if(i==16)
				break;
		}
		RC6Decrypt(crypt,data,S);

		if(flag)
		{
			print16(data);
			for(int i=0;i<16;i++)
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