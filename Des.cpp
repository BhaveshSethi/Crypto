//Testing .bat

#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>

int PC1[7][8] = { {56,49,41,33,25,17,9,1},
		 {50,42,34,26,18,10,2,51},
		 {43,35,27,19,11,3,52,44},
		 {36,55,47,39,31,23,15,7},
		 {54,46,38,30,22,14,6,53},
		 {45,37,29,21,13,5,28,20},
		 {12,4,8,32,16,40,48,24 }};
void strToMatrix(char *str,int M[][8])
{
	int n = strlen(str),i,j,ch;
	for(i=0;i<n;i++)
	{
		ch = str[i];
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
void printMatrix(int M[][8], int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<8;j++)
			cout<<M[i][j];
		cout<<endl;
	}
}
void PCkey(int M[7][8], int PM[7][8],int mode)
{
	//printMatrix(M,7);
	for(int i=0;i<7;i++)
		for(int j=0;j<8;j++)
		{
			if(mode==0)
				PM[i][j] = M[ (PC1[i][j]-1)/8  ][ (PC1[i][j]-1)%8  ];
			else
				PM[ (PC1[i][j]-1)/8  ][ (PC1[i][j]-1)%8  ] = M[i][j];
		}
	cout<<endl;
	//printMatrix(PM,7);
}

void main()
{
	clrscr();
	char msg[80],Key[7],Pkey[7];
	int i,j,t,M[7][8],PM[7][8];
	cout<<"\n\tCrptyo 1.0";
	cout<<"\n\tEnter Your Key:\n\t";
	/*
	gets(Key);
	while(strlen(Key) != 7)
	{
		cout<<"\n\tInvalid Key Length -- |k| = 56 bits  -- Enter Again\n\t";
		gets(Key);
	}
	*/
	strcpy(Key,"BHAVESH");
	puts(Key);
	strToMatrix(Key,M);
	PCkey(M,PM,0);
	matrixToStr(Pkey,PM,7);
	cout<<"\n\tReceived: "<<Pkey;
	PCkey(PM,M,1);
	matrixToStr(Key,M,7);
	cout<<"\n\tReceived Key: "<<Key;
	getch();
}