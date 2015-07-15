#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>

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
		//cout<<hex<<L[i]<<endl;
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

void RC6(char C[16], char M[16], unsigned long S[2*r+4])
{
	unsigned long A[4],t,u;
	int i,j;
	for(i=0;i<4;i++)
	{
		A[i]=0;
		for(j=0;j<4;j++)
			A[i] += (unsigned long)((int)M[4*i+j])<<(8*j);
	}
	A[1]+=S[0];
	A[3]+=S[1];
	for(i=1;i<=r;i++)
	{
		t = Rol(A[1]*(A[1]<<1 + 1),5);
		u = Rol(A[3]*(A[3]<<1 + 1),5);
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

void main()
{
	clrscr();
	int i;
	cout<<"\n\tRC6";
	char key[16],msg[16],crypt[16];
	unsigned long S[2*r+4];
	strcpy(key,"0123456789012345");
	memset(key,0,16);
	cout<<"\n\tChosen key is ";
	puts(key);
	cout<<"\n\tMsg is ";
	memset(msg,0,16);
	for(i=0;i<16;i++)
		cout<<hex<<(int)msg[i];
	keySched(key,S);
	RC6(crypt,msg,S);
	cout<<"\n\tEncrypted Msg is ";
	for(i=0;i<16;i++)
		cout<<endl<<hex<<(int)(unsigned char)crypt[i];
	getch();
}