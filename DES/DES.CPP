#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>
#include<destable.h>
#include<time.h>

void strToMatrix(char *str,int M[][8],int n)
{
	int i,j,ch;
	for(i=0;i<n;i++)
	{
		ch = (int)((unsigned char)str[i]);
		for(j=0;j<8;j++)
		{
			M[i][7-j] = ch%2;
			ch/=2;
		}
	}
}
void matrixToStr(char *str, int M[][8],int n)
{
	int val,i,j;
	for(i=0;i<n;i++)
	{
		val=0;
		for(j=0;j<8;j++)
		{
			val = val*2 + M[i][j];
		}
		str[i] = (char)val;
	}
}
void printMatrix(int *M, int m, int n)
{
	int i,j;
	cout<<endl;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
			cout<<M[i*n + j];
		cout<<endl;
	}
}
void PCkey(int K[7][8], int PK[7][8],int mode)
{
	for(int i=0;i<7;i++)
		for(int j=0;j<8;j++)
		{
			if(mode==0)
				PK[i][j] = K[ (PC1[i][j]-1)/8  ][ (PC1[i][j]-1)%8  ];
			else
				PK[ (PC1[i][j]-1)/8  ][ (PC1[i][j]-1)%8  ] = K[i][j];
		}
}
void PCmsg(int M[8][8], int PM[8][8],int mode)
{
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{
			if(mode==0)
				PM[i][j] = M[ (IP[i][j]-1)/8  ][ (IP[i][j]-1)%8  ];
			else
				PM[ (IP[i][j]-1)/8  ][ (IP[i][j]-1)%8  ] = M[i][j];
		}
}

void expand(int M[8][8],int R[8][6])
{
	for(int i=0;i<48;i++)
		R[i/6][i%6] = M[(32+E[i/6][i%6]-1)/8][(32+E[i/6][i%6]-1)%8];
}

void genKey_i(int K[7][8],int k[16][8][6],int i)
{
	int t[4]={K[0][0],K[0][1],K[3][4],K[3][5]};
	for(int j=0;j < 28-LS[i];j++)
	{
		K[j/8][j%8] = K[(j+ LS[i])/8][(j+ LS[i])%8];
		K[(j+28)/8][(j+28)%8] = K[(j+28+ LS[i])/8][(j+28+ LS[i])%8];
	}
	for(;j<28;j++)
	{
		K[j/8][j%8] = t[j+LS[i]-28];
		K[(j+28)/8][(j+28)%8] = t[j+LS[i]-26];
	}
	for(j=0;j<48;j++)
	{
		k[i][j/6][j%6] = K[(PC2[j/6][j%6]-1)/8][(PC2[j/6][j%6]-1)%8];
	}
}
void XOR86(int R[8][6],int key[8][6])
{
	for(int i=0;i<8;i++)
		for(int j=0;j<6;j++)
			R[i][j] = R[i][j] ^ key[i][j];
}
void XOR84(int R[8][4],int key[8][4])
{
	for(int i=0;i<8;i++)
		for(int j=0;j<4;j++)
			R[i][j] = R[i][j] ^ key[i][j];
}

void DESencrypt(char data[8], int k[16][8][6])
{
	int M[8][8],PM[8][8],j,l,R[8][6],T[8][4],B[8][4];
	strToMatrix(data,M,8);
	PCmsg(M,PM,0);
	for(j=0;j<16;j++)
	{
		expand(PM,R);
		XOR86(R,k[j]);
		for(l=0;l<8;l++)
		{
			int m = 2*R[l][0] + R[l][5];
			int n = 8*R[l][1] + 4*R[l][2] + 2*R[l][3] + R[l][4];
			int val = DES_S[l][m][n];
			for(int o=0;o<4;o++)
			{
				T[l][3-o] = val%2;
				val/=2;
			}
		}
		for(l=0;l<32;l++)
			B[l/4][l%4] = T[(DES_P[l/4][l%4]-1)/4][(DES_P[l/4][l%4]-1)%4];
		for(l=0;l<32;l++)
			T[l/4][l%4] = PM[l/8][l%8];
		XOR84(T,B);
		for(l=0;l<32;l++)
		{
			PM[l/8][l%8] = PM[(32+l)/8][(32+l)%8];
			PM[(32+l)/8][(32+l)%8] = T[l/4][l%4];
		}
	}
	for(l=0;l<32;l++)
	{
		j = PM[l/8][l%8];
		PM[l/8][l%8] = PM[(32+l)/8][(32+l)%8];
		PM[(32+l)/8][(32+l)%8] = j;
	}
	for(l=0;l<64;l++)
		M[l/8][l%8] = PM[(FP[l/8][l%8]-1)/8][(FP[l/8][l%8]-1)%8];
	for(l=0;l<64;l++)
		PM[l/8][l%8] = M[l/8][l%8];
	matrixToStr(data,PM,8);
}
void DESdecrypt(char data[8], int k[16][8][6])
{
	int M[8][8],PM[8][8],j,l,R[8][6],T[8][4],B[8][4];
	strToMatrix(data,M,8);
	PCmsg(M,PM,0);
	matrixToStr(data,PM,8);
	for(j=0;j<16;j++)
	{
		expand(PM,R);
		XOR86(R,k[15-j]);
		for(l=0;l<8;l++)
		{
			int m = 2*R[l][0] + R[l][5];
			int n = 8*R[l][1] + 4*R[l][2] + 2*R[l][3] + R[l][4];
			int val = DES_S[l][m][n];
			for(int o=0;o<4;o++)
			{
				T[l][3-o] = val%2;
				val/=2;
			}
		}
		for(l=0;l<32;l++)
			B[l/4][l%4] = T[(DES_P[l/4][l%4]-1)/4][(DES_P[l/4][l%4]-1)%4];
		for(l=0;l<32;l++)
			T[l/4][l%4] = PM[l/8][l%8];
		XOR84(T,B);
		for(l=0;l<32;l++)
		{
			PM[l/8][l%8] = PM[(32+l)/8][(32+l)%8];
			PM[(32+l)/8][(32+l)%8] = T[l/4][l%4];
		}
	}
	for(l=0;l<32;l++)
	{
		j = PM[l/8][l%8];
		PM[l/8][l%8] = PM[(32+l)/8][(32+l)%8];
		PM[(32+l)/8][(32+l)%8] = j;
	}
	for(l=0;l<64;l++)
		M[l/8][l%8] = PM[(FP[l/8][l%8]-1)/8][(FP[l/8][l%8]-1)%8];
	for(l=0;l<64;l++)
		PM[l/8][l%8] = M[l/8][l%8];
	matrixToStr(data,PM,8);
}
void main()
{
	clrscr();
	char msg[80],Key[7],Pkey[7],data[8],ch;
	int i,val,k[16][8][6],j,K[7][8],PK[7][8];
	cout<<"\n\tDES.CPP";
	strcpy(Key,"BHAVESH");
	strToMatrix(Key,K,7);
	PCkey(K,PK,0);
	for(i=0;i<16;i++)
		genKey_i(PK,k,i);
	int flag=1;

	FILE *oFile,*cFile;
	oFile = fopen("test.txt","rb");
	cFile = fopen("crypt.dat","wb");

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
		j=0;
		while(ch!=EOF)
		{
			data[j++]=ch;
			if(j==8)
				break;
			ch=fgetc(oFile);
		}
		if(i==0)
			break;

		else if(j < 8)
		{
			flag=0;
			for(;j<8;j++)
				data[j] = 0;
		}
		DESencrypt(data,k);
		for(j=0;j<8;j++)
		{
			cout<<data[j];
			val = (unsigned char)data[j];
			fputc(val,cFile);
		}
	}
	fclose(oFile);
	fclose(cFile);
	cout<<"\n\tEncryption Ends ";
	clock_t c2=clock();
	cout<<"\n\tTime taken is "<<(c2-c1)/CLK_TCK<<" sec";

	cout<<"\n\n\tNow Decrypting \n\tDecrypted File:\n";
	c1=clock();

	cFile = fopen("crypt.dat","rb");
	flag=1;
	oFile = fopen("test1.txt","wb");
	fseek(oFile,0,SEEK_SET);
	fseek(cFile,0,SEEK_SET);

	val=1;

	while(flag)
	{
		memset(data,0,8);
		i=0;
		while(val!=EOF)
		{
			val = fgetc(cFile);
			if(val==EOF)
				flag=0;
			else
				data[i++] = (unsigned char)val;
			if(i==8)
				break;
		}
		if(!flag)
			break;
		DESdecrypt(data,k);
		for(int l=0;l<8;l++)
		{
			cout<<data[l];
			if(data[l])
				fputc(data[l],oFile);
		}
	}
	fclose(oFile);
	fclose(cFile);
	c2 = clock();
	cout<<"\n\tDecrypting done";
	cout<<"\n\tTime taken is "<<(c2-c1)/CLK_TCK<<" sec";

	getch();
}