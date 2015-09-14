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

void DESencrypt(char crypt[8], char data[8], int k[16][8][6])
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
	matrixToStr(crypt,M,8);
}
void DESdecrypt(char crypt[8],char data[8], int k[16][8][6])
{
	int M[8][8],PM[8][8],j,l,R[8][6],T[8][4],B[8][4];
	strToMatrix(crypt,M,8);
	PCmsg(M,PM,0);
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
	matrixToStr(data,M,8);
}