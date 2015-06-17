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
int E[8][6] = {{32,1,2,3,4,5},
	       {4,5,6,7,8,9},
	       {8,9,10,11,12,13},
	       {12,13,14,15,16,17},
	       {16,17,18,19,20,21},
	       {20,21,22,23,24,25},
	       {24,25,26,27,28,29},
	       {28,29,30,31,32,1}};
int LS[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

void strToMatrix(char *str,int M[][8],int n)
{
	int i,j,ch;
	for(i=0;i<n;i++)
	{
		ch = (int)((unsigned char)str[i]);
       //		cout<<"\n\tChar "<<str[i]<<" has a value "<<ch;
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
	 //	cout<<"\n\tChar "<<str[i]<<" has a value "<<val;
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
//	cout<<"\n\tK:\n\t";
//	printMatrix(K,7);
//	cout<<"\n\t_________";
//	cout<<"\n\tt:\n\t";
//	printMatrix(t,7);
//	cout<<"\n\t_________";
	for(j=0;j<48;j++)
	{
		k[i][j/6][j%6] = K[(PC2[j/6][j%6]-1)/8][(PC2[j/6][j%6]-1)%8];
	}
}
void main()
{
	clrscr();
	char msg[80],Key[7],Pkey[7],data[8],L[4];
	int i,j,k[16][8][6],len,K[7][8],PK[7][8],M[8][8],PM[8][8],R[8][6];
	cout<<"\n\tCrptyo 1.0";
	cout<<"\n\tEnter Your Key:\n\t";

   /*	gets(Key);
	while(strlen(Key) != 7)
	{
		cout<<"\n\tInvalid Key Length -- |k| = 56 bits  -- Enter Again\n\t";
		gets(Key);
	}                   */
	strcpy(Key,"BHAVESH");
	puts(Key);
	strToMatrix(Key,K,7);
	PCkey(K,PK,0);
//	printMatrix(PK,7);
	matrixToStr(Pkey,PK,7);
	cout<<"\n\tReceived: "<<Pkey;
	for(i=0;i<7;i++)
		cout<<Pkey[i];
	cout<<";";
/*	PCkey(PK,K,1);
	matrixToStr(Key,K,7);
	cout<<"\n\tReceived Key: ";*/
	cout<<"\n\tEnter your Message ";
     //	gets(msg);
	strcpy(msg,"hello br");
	len = strlen(msg);
	//TODO 2: implement outer for loop 16 times
	for(i=0;i<16;i++)
	{
		genKey_i(K,k,i);
		cout<<"\n\tKey "<<i<<":";
		for(int i1=0;i1<8;i1++)
		{
			cout<<"\n\t";
			for(int j1=0;j1<6;j1++)
				cout<<k[i][i1][j1];
		}
	}
	for(i=0;i<len;i+=8)
	{
		if(len - i < 8)
		{
			//TODO 1
		}
		for(j=0;j<8;j++)
			data[j] = msg[i+j];
		cout<<"\n\tData: "<<data;
		strToMatrix(data,M,8);
		PCmsg(M,PM,0);
		PCmsg(PM,M,1);
	   //	printMatrix(M,8);
	   //	printMatrix(PM,8);
		matrixToStr(data,PM,8);
		cout<<"\n\tReceived Data: ";
		for(int h=0;h<8;h++)
			cout<<data[h];
		cout<<" with length "<<strlen(data)<<endl;
		for(j=0;j<16;j++)
		{
			expand(PM,R);
		}
	}
	getch();
}