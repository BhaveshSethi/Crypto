//Testing .bat

#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>
#include<destable.h>

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
	f.open("crypt.txt",ios::out | ios::trunc);
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
	//gets(msg);
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
	ifstream fi;
	fi.open("test.txt",ios::in | ios::binary);
	int flag=1;
	cout<<"\n\tCrypt Formed\n\t";
//	for(i=0;i<len;i+=8)
	while(flag)
	{
		//***************************************
		//Reading and Encrypting a file

		fi>>ch;
		j=0;
		//cout<<ch;
		data[j]=ch;
		while(!fi.eof())
		{
			fi>>ch;
			//cout<<ch;
			data[++j]=ch;
			if(j==7)
				break;
		}
//		fi.close();


		//***************************************

		if(j < 7)
		{
//			for(j=0;j< len -i ;j++)
//				data[j] = msg[i+j];
			flag=0;
			j++;
			for(;j<8;j++)
				data[j] = 0;
		}
/*		else
		{
			for(j=0;j<8;j++)
				data[j] = msg[i+j];
		}
*/	//	cout<<"\n\tData: "<<data;
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
			//cout<<data[j];
			val = (unsigned char)data[j];
			f<<setw(4)<<val;
//			f<<data[j];
		}
	}
	fi.close();
	f.close();
	f.open("crypt.txt",ios::in | ios::binary);
	flag=1;
	cout<<"\n\n\tNow Deciphering... ";
/*	i=0;
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
*/	cout<<"\n\n\tPlain Message:\n\t";
//	for(i=0;i<len;i+=8)
	while(flag)
	{
		memset(data,0,8);
		i=0;
		while(!f.eof())
		{
			f>>val;
			data[i++] = (char)val;
			if(f.eof())
				flag=0;
			if(i==8)
				break;
		}
	    /*	for(j=0;j<8;j++)
			data[j] = msg[i+j];
	  */  //	strToMatrix(data,PM,8);
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
	       //	for(l=0;l<8;l++)
	       //		cout<<data[l];
	}
	cout<<"done";
	f.close();
	getch();
}