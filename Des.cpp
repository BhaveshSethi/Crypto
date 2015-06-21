//Testing .bat

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>

int PC1[7][8] = {{56,49,41,33,25,17,9,1},
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
int S[8][4][16] = {{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		    {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		    {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
		    {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},

		   {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		    {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		    {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		    {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},

		   {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		    {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		    {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		    {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},

		   {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		    {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		    {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		    {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},

		   {{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		    {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		    {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		    {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},

		   {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		    {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		    {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		    {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},

		   {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		    {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		    {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		    {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},

		   {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		    {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		    {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		    {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}};

int LS[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int P[8][4] = {{16,7,20,21},
	       {29,12,28,17},
	       {1,15,23,26},
	       {5,18,31,10},
	       {2,8,24,14},
	       {32,27,3,9},
	       {19,13,30,6},
	       {22,11,4,25}};

int FP[8][8] = {{40,8,48,16,56,24,64,32},
		{39,7,47,15,55,23,63,31},
		{38,6,46,14,54,22,62,30},
		{37,5,45,13,53,21,61,29},
		{36,4,44,12,52,20,60,28},
		{35,3,43,11,51,19,59,27},
		{34,2,42,10,50,18,58,26},
		{33,1,41,9,49,17,57,25}};

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
void PCkey(int M[7][8], int PM[7][8],int mode)
{
//	printMatrix((int*)&M,7,8);
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
  //	cout<<endl;
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
//	printMatrix((int*)&K,7,8);
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
//	printMatrix((int*)&K,7,8);
	for(j=0;j<48;j++)
	{
		k[i][j/6][j%6] = K[(PC2[j/6][j%6]-1)/8][(PC2[j/6][j%6]-1)%8];
	}
//	printMatrix((int*)&k[i],8,6);
}
void XOR86(int R[8][6],int key[8][6])
{
	for(int i=0;i<8;i++)
		for(int j=0;j<6;j++)
			R[i][j] = (R[i][j] == key[i][j])?0:1;
}
void XOR84(int R[8][4],int key[8][4])
{
	for(int i=0;i<8;i++)
		for(int j=0;j<4;j++)
			R[i][j] = (R[i][j] == key[i][j])?0:1;
}
void main()
{
	clrscr();
	char msg[80],Key[7],Pkey[7],data[8],ch;
	int i,j,l,val,k[16][8][6],len,K[7][8],PK[7][8],M[8][8],PM[8][8],R[8][6],T[8][4],B[8][4],Temp[8][8];
	cout<<"\n\tCrptyo 1.0";
	cout<<"\n\tEnter Your Key:\n\t";
	fstream f;
	f.open("Crypt.txt",ios::out | ios::trunc);
   /*	gets(Key);
	while(strlen(Key) != 7)
	{
		cout<<"\n\tInvalid Key Length -- |k| = 56 bits  -- Enter Again\n\t";
		gets(Key);
	}                   */
	strcpy(Key,"BHAVESH");
	puts(Key);
	strToMatrix(Key,K,7);
	//printMatrix((int*)&K,7,8);
	PCkey(K,PK,0);
	//printMatrix((int*)PK,7,8);
	matrixToStr(Pkey,PK,7);
	cout<<"\n\tReceived: \n\t"<<Pkey;
	for(i=0;i<7;i++)
		cout<<i;
	cout<<"\n\t";
	for(i=0;i<7;i++)
		cout<<Pkey[i];
	cout<<";";
/*	PCkey(PK,K,1);
	matrixToStr(Key,K,7);
	cout<<"\n\tReceived Key: ";*/
	cout<<"\n\tEnter your Message \n\t";
	gets(msg);
     //	strcpy(msg,"hello br");
	len = strlen(msg);
	//TODO 2: implement outer for loop 16 times
	for(i=0;i<16;i++)
	{
		genKey_i(PK,k,i);
      //		cout<<"\n\tOriginal Shifted Key \n";
		//printMatrix((int*)&PK,7,8);
      //		cout<<"\n\tKey "<<i<<":";
      //		printMatrix((int*)&k[i],8,6);
	}
	cout<<"\n\tCrypt Formed\n\t";
	for(i=0;i<len;i+=8)
	{
		if(len - i < 8)
		{
			for(j=0;j< len -i ;j++)
				data[j] = msg[i+j];
			for(;j<8;j++)
				data[j] = 0;
		}
		else
		{
			for(j=0;j<8;j++)
				data[j] = msg[i+j];
		}
	//	cout<<"\n\tData: "<<data;
		strToMatrix(data,M,8);
		PCmsg(M,PM,0);
		PCmsg(PM,M,1);
		//printMatrix((int*)&M,8,8);
		//printMatrix((int*)&PM,8,8);
		matrixToStr(data,PM,8);
	//	cout<<"\n\tReceived Data: ";
	/*	for(int h=0;h<8;h++)
			cout<<data[h];
		cout<<" with length "<<strlen(data)<<endl;
	*/	for(j=0;j<16;j++)
		{
			expand(PM,R);
			//printMatrix((int*)&R,8,6);
			XOR86(R,k[j]);
			//printMatrix((int*)&R,8,6);
			for(l=0;l<8;l++)
			{
				int m = 2*R[l][0] + R[l][5];
				int n = 8*R[l][1] + 4*R[l][2] + 2*R[l][3] + R[l][4];
				int val = S[l][m][n];
				for(int o=0;o<4;o++)
				{
					T[l][3-o] = val%2;
					val/=2;
				}
			}
			//printMatrix((int*)&T,8,4);
			for(l=0;l<32;l++)
    /*B contains R*/		B[l/4][l%4] = T[(P[l/4][l%4]-1)/4][(P[l/4][l%4]-1)%4];
			//printMatrix((int*)&B,8,4);
			for(l=0;l<32;l++)
    /*T contains L*/		T[l/4][l%4] = PM[l/8][l%8];
			//printMatrix((int*)&T,8,4);
			/*T will contain Li-1 xor f(Ri-1,Ki)*/
			XOR84(T,B);
			//printMatrix((int*)&T,8,4);
			for(l=0;l<32;l++)
			{
				PM[l/8][l%8] = PM[(32+l)/8][(32+l)%8];
				PM[(32+l)/8][(32+l)%8] = T[l/4][l%4];
			}
			//printMatrix((int*)&PM,8,8);
     //			printMatrix((int*)&PM,8,8);
     //			cout<<"\n\tPass "<<j+1<<" done!!";
		}
		//printMatrix((int*)&PM,8,8);
		for(l=0;l<32;l++)
		{
			j = PM[l/8][l%8];
			PM[l/8][l%8] = PM[(32+l)/8][(32+l)%8];
			PM[(32+l)/8][(32+l)%8] = j;
		}
		//printMatrix((int*)&PM,8,8);
		for(l=0;l<64;l++)
			M[l/8][l%8] = PM[(FP[l/8][l%8]-1)/8][(FP[l/8][l%8]-1)%8];
		for(l=0;l<64;l++)
			PM[l/8][l%8] = M[l/8][l%8];
		matrixToStr(data,PM,8);
		for(j=0;j<8;j++)
		{
			cout<<data[j];
			val = (unsigned char)data[j];
			f<<setw(4)<<val;                  //setw
		}
	}
	f.close();
	f.open("crypt.txt",ios::in | ios::binary);
	cout<<"\n\n\tNow Deciphering... ";
	i=0;
	f>>val;
	memset(msg,0,sizeof(msg));
	while(!f.eof())
	{
		//cout<<(char)val<<" ";
		msg[i++] = (char)val;
		f>>val;
	}
	len = i;
	cout<<"\n\n\tCrypt of length "<<len<<":\n\t";
	for(i=0;i<len;i++)
		cout<<msg[i];
	//random
	cout<<"\n\n\tPlain Message:\n\t";
	for(i=0;i<len;i+=8)
	{
		for(j=0;j<8;j++)
			data[j] = msg[i+j];
	    //	strToMatrix(data,PM,8);
	    /*	for(l=0;l<64;l++)
			M[(FP[l/8][l%8]-1)/8][(FP[l/8][l%8]-1)%8] = PM[l/8][l%8];
		for(l=0;l<64;l++)
			PM[l/8][l%8] = M[l/8][l%8];
		//printMatrix((int*)&PM,8,8);
		for(j=15;j>=0;j--)
		{

		}    */
		strToMatrix(data,M,8);
		PCmsg(M,PM,0);
		PCmsg(PM,M,1);
		//printMatrix((int*)&M,8,8);
		//printMatrix((int*)&PM,8,8);
		matrixToStr(data,PM,8);
	//	cout<<"\n\tReceived Data: ";
	/*	for(int h=0;h<8;h++)
			cout<<data[h];
		cout<<" with length "<<strlen(data)<<endl;
       */	for(j=0;j<16;j++)
		{
			expand(PM,R);
			//printMatrix((int*)&R,8,6);
			XOR86(R,k[15-j]);
			//printMatrix((int*)&R,8,6);
			for(l=0;l<8;l++)
			{
				int m = 2*R[l][0] + R[l][5];
				int n = 8*R[l][1] + 4*R[l][2] + 2*R[l][3] + R[l][4];
				int val = S[l][m][n];
				for(int o=0;o<4;o++)
				{
					T[l][3-o] = val%2;
					val/=2;
				}
			}
			//printMatrix((int*)&T,8,4);
			for(l=0;l<32;l++)
    /*B contains R*/		B[l/4][l%4] = T[(P[l/4][l%4]-1)/4][(P[l/4][l%4]-1)%4];
			//printMatrix((int*)&B,8,4);
			for(l=0;l<32;l++)
    /*T contains L*/		T[l/4][l%4] = PM[l/8][l%8];
			//printMatrix((int*)&T,8,4);
			/*T will contain Li-1 xor f(Ri-1,Ki)*/
			XOR84(T,B);
			//printMatrix((int*)&T,8,4);
			for(l=0;l<32;l++)
			{
				PM[l/8][l%8] = PM[(32+l)/8][(32+l)%8];
				PM[(32+l)/8][(32+l)%8] = T[l/4][l%4];
			}
			//printMatrix((int*)&PM,8,8);
     //			printMatrix((int*)&PM,8,8);
     //			cout<<"\n\tPass "<<j+1<<" done!!";
		}
		//printMatrix((int*)&PM,8,8);
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
		for(l=0;l<8;l++)
			cout<<data[l];
	}
	f.close();
	getch();
}