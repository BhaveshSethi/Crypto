#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<iomanip.h>
#include<aestable.h>
#include<time.h>

void SubWord(unsigned char *word, int n, int mode)
{
	int val;
	for(int i=0;i<n;i++)
	{
		val = word[i];
		word[i] = (mode==0)?(unsigned char)AES_S[val]:(unsigned char)inv_S[val];
	}
}

void keyExpansion(unsigned char key[16], unsigned char word[44][4])
{
	unsigned char temp[4],t;
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			word[i][j] = key[4*i + j];

	for(i=4;i<44;i++)
	{
		for(j=0;j<4;j++)
			temp[j] = word[i-1][j];

		if(i%4==0)
		{
			t = temp[0];
			for(j=0;j<3;j++)
				temp[j] = temp[j+1];
			temp[3] = t;
			SubWord(temp,4,0);
			temp[0]^=RC[i/4-1];
		}

		for(j=0;j<4;j++)
			word[i][j] = word[i-4][j] ^ temp[j];
	}
}
void printHex(unsigned char data[16])
{
	cout<<endl;
	for(int i=0;i<16;i++)
		cout<<hex<<(int)data[i]<<dec<<" ";
}
void ShiftRows(char data[16], int mode)
{
	char str[16];
	memset(str,0,16);
	for(int i=0;i<16;i++)
		str[i] = (mode==0)?data[PM[i]]:data[IPM[i]];
	for(i=0;i<16;i++)
		data[i] = str[i];
}
unsigned int gmul(unsigned int a, unsigned int b)
{
	unsigned int p=0;
	int i;
	for(i=0;i<8;i++)
	{
		if(b & 1)
			p^=a;
		a<<=1;
		if(a & 0x100)
			a^=0x11b;
		b>>=1;
	}
	return p;
}
void MixCol(unsigned char data[16])
{
	int i,j;
	unsigned char a[4],b[4],c,h;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			a[j] = data[4*i + j];
			h = (unsigned char)((signed char)data[4*i+j]>>7);
			b[j] = data[4*i  + j]<<1;
			b[j] ^= (0x1B & h);
		}
		data[4*i + 0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
		data[4*i + 1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
		data[4*i + 2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
		data[4*i + 3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
	}
}
void InvMixCol(unsigned char data[16])
{
	int i,j,k;
	unsigned char t[4][4];
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			t[i][j] = 0x00;
			for(k=0;k<4;k++)
				t[i][j] ^= gmul(IMC[i][k],data[j*4+k]);
		}
	}
	for(i=0;i<16;i++)
		data[i] = t[i%4][i/4];
}
void AESEncrypt(char msg[16], char cipher[16], unsigned char w[44][4])
{
	int i,j;
	memset(cipher,0,16);
	for(i=0;i<16;i++)
		cipher[i] = msg[i]^w[i/4][i%4];         //Round 0
	for(j=1;j<=9;j++)
	{
		SubWord(cipher,16,0);
		ShiftRows(cipher,0);
		MixCol(cipher);
		for(i=0;i<16;i++)
			cipher[i] ^= w[4*j + i/4][i%4];
	}
	SubWord(cipher,16,0);
	ShiftRows(cipher,0);
	for(i=0;i<16;i++)
		cipher[i] ^= w[4*j + i/4][i%4];
}
void AESDecrypt(char msg[16], char cipher[16], unsigned char w[44][4])
{
	int i,j;
	memset(msg,0,16);
	for(i=0;i<16;i++)
	{
		msg[i] = cipher[i];
		msg[i] ^= w[40 + i/4][i%4];
	}
	for(i=9;i>=1;i--)
	{
		ShiftRows(msg,1);
		SubWord(msg,16,1);
		for(j=0;j<16;j++)
			msg[j] ^= w[4*i + j/4][j%4];
		InvMixCol(msg);
	}
	ShiftRows(msg,1);
	SubWord(msg,16,1);
	for(i=0;i<16;i++)
		msg[i] ^= w[i/4][i%4];
}
void print16(char *str)
{
	for(int i=0;i<16;i++)
		cout<<str[i];
}

void main()
{
	clrscr();
	cout<<"\n\tAES\n\t";
	int i,j,flag=1,val=1;

	unsigned char key[16] = {0x0f,0x15,0x71,0xc9,0x47,0xd9,0xe8,0x59,0x0c,0xb7,0xad,0xd6,0xaf,0x7f,0x67,0x98};
	unsigned char word[44][4];
	keyExpansion(key,word);

	char data[16],crypt[16],ch;

	FILE *oFile,*cFile;
	oFile = fopen("test.txt","rb");
	cFile = fopen("cryptAES.dat","wb");

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
		AESEncrypt(data,crypt,word);
		for(i=0;i<16;i++)
		{
			j = (unsigned char)crypt[i];
			cout<<(unsigned char)j;
			fputc(j,cFile);
		}
	}
	fclose(oFile);
	fclose(cFile);


	cout<<"\n\tEncryption Ends ";
	clock_t c2=clock();
	cout<<"\n\tTime taken is "<<(c2-c1)/CLK_TCK<<" sec";

	cout<<"\n\n\tNow Decrypting\n\t";
	c1=clock();

	cFile = fopen("cryptAES.dat","rb");
	flag=1;
	oFile = fopen("test1.txt","wb");
	fseek(oFile,0,SEEK_SET);
	fseek(cFile,0,SEEK_SET);

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
		AESDecrypt(data,crypt,word);

		if(flag)
		{
			for(int i=0;i<16;i++)
			{
				if(data[i])
				{
					fputc(data[i],oFile);
					cout<<data[i];
				}
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