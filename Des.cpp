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
int PC2[8][6] = {{14,17,11,24,1,5},
		 {3,28,15,6,21,10},
		 {23,19,12,4,26,8},
		 {16,7,27,20,13,2},
		 {41,52,31,37,47,55},
		 {30,40,51,45,33,48},
		 {44,49,39,56,34,53},
		 {46,42,50,36,29,32}};
int IP[8][8] = {{58,50,42,34,26,18,10,2},
		{60,52,44,36,28,20,12,4},
		{62,54,46,38,30,22,14,6},
		{64,56,48,40,32,24,16,8},
		{57,49,41,33,25,17,9,1},
		{59,51,43,35,27,19,11,3},
		{61,53,45,37,29,21,13,5},
		{63,55,47,39,31,23,15,7}};

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
void PCmsg(int M[8][8], int PM[8][8],int mode)
{
 //	printMatrix(M,8);
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
		{
			if(mode==0)
				PM[i][j] = M[ (IP[i][j]-1)/8  ][ (IP[i][j]-1)%8  ];
			else
				PM[ (IP[i][j]-1)/8  ][ (IP[i][j]-1)%8  ] = M[i][j];
		}
	cout<<endl;
 //	printMatrix(PM,8);
}

void main()
{
	clrscr();
	char msg[80],Key[7],Pkey[7],data[8],R[4],L[4];
	int i,j,k,len,K[7][8],PK[7][8],M[8][8],PM[8][8];
	cout<<"\n\tCrptyo 1.0";
	cout<<"\n\tEnter Your Key:\n\t";

   /*	gets(Key);
	while(strlen(Key) != 7)
	{
		cout<<"\n\tInvalid Key Length -- |k| = 56 bits  -- Enter Again\n\t";
		gets(Key);
	}                   */
    /*	strcpy(Key,"BHAVESH");
	puts(Key);
	strToMatrix(Key,K);
	PCkey(K,PK,0);
    /*	matrixToStr(Pkey,PK,7);
	cout<<"\n\tReceived: "<<Pkey;
	PCkey(PK,K,1);
	matrixToStr(Key,K,7);
	cout<<"\n\tReceived Key: "<<Key;   */
	cout<<"\n\tEnter your Message ";
	gets(msg);
	len = strlen(msg);
	//TODO 2: implement outer for loop 16 times
	for(i=0;i<len;i+=8)
	{
		if(len - i < 8)
		{
			//TODO 1
		}
		for(j=0;j<8;j++)
			data[j] = msg[i+j];
		cout<<"\n\tData: "<<data;
		strToMatrix(data,M);
		PCmsg(M,PM,0);
		PCmsg(PM,M,1);
		matrixToStr(data,M,8);
		cout<<"\n\tReceived Data: "<<data;
	}
	getch();
}