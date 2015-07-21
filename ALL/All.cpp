#include<aes.h>
#include<blowfish.h>
#include<des.h>
#include<rc6.h>
#include<rsa.h>

typedef struct Node
{
	int info;
	struct Node *next;
}node;

void main()
{
	clrscr();
	int i,flag,j,length,val,count=0;
	char ch,ch1,data[16],crypt[16];

	unsigned char AES_key[16] = {0x0f,0x15,0x71,0xc9,0x47,0xd9,0xe8,0x59,0x0c,0xb7,0xad,0xd6,0xaf,0x7f,0x67,0x98};
	unsigned char AES_word[44][4];
	keyExpansion(AES_key,AES_word);

	char BF_key[20];
	strcpy(BF_key,"blowfish");
	expandKey(BF_key,P);

	char DES_key[7],DES_Pkey[7];
	int K[7][8],PK[7][8],DES_k[16][8][6];
	strcpy(DES_key,"BHAVESH");
	strToMatrix(DES_key,K,7);
	PCkey(K,PK,0);
	matrixToStr(DES_Pkey,PK,7);
	for(i=0;i<16;i++)
		genKey_i(PK,DES_k,i);

	char RC6_key[16];
	unsigned long RC6_S[2*r+4];
	strcpy(RC6_key,"0123456789012345");
	keySched(RC6_key,RC6_S);

	int n=p*q;

	cout<<"\n\tWelcome to all.cpp";

	//change the file below to change original file
	char filename[10]="testy.txt";

	FILE *oFile,*cFile;
	node *top,*np;
	top=NULL;

	int choice1=0,choice2;
	do
	{
		HERE:
		cout<<"\n\tEnter Choice\n\t1. Encrypt\n\t2. Decrypt\n\t3. Exit ";
		cin>>choice1;
		if(choice1==3)
			break;
		switch(choice1)
		{
			case 1:
				if(top==NULL)
				{
					oFile = fopen(filename,"rb");
					cFile = fopen("cryptALL.dat","wb");
				}
				else
				{
					oFile = fopen("cryptALL.dat","rb");
					cFile = fopen("temp.dat","wb");
				}
				break;
			case 2:
				if(top == NULL)
				{
					cout<<"\n\tBad Choice";
					goto HERE;
				}
				if(top->next == NULL)
				{
					cFile = fopen("test1.txt","wb");
					oFile = fopen("cryptALL.dat","rb");
				}
				else
				{
					oFile = fopen("cryptALL.dat","rb");
					cFile = fopen("temp.dat","wb");
				}
				break;
			default:
				cout<<"\n\tBad Choice";
				goto HERE;
		}
		THERE:
		cout<<"\n\tEnter Choice for Algo\n\t1. AES\t2. BlowFish\n\t3. DES  4.RC6  5.RSA ";
		cin>>choice2;
		flag=1;
		if(choice2<0 || choice2>5)
		{
			cout<<"\n\tBad Choice";
			goto THERE;
		}
		switch(choice1)
		{
			case 1:
				np = new node();
				np->info = choice2;
				np->next = NULL;
				if(top==NULL)
					top=np;
				else
				{
					np->next = top;
					top = np;
				}
				break;
			case 2:
				if(top->info != choice2)
				{
					cout<<"\n\tBad Choice";
					goto THERE;
				}
				else if(top->next != NULL)
				{
					np = top;
					top = top->next;
					delete(np);
				}
				else
				{
					delete(top);
					top = NULL;
				}
				break;
		}
		cout<<"\n";
		ch='1';
		if(choice2==5)
		{
			while(ch!=EOF)
			{
				ch=fgetc(oFile);
				if(ch==EOF)
					break;
				ch1 = (choice1==1)?(char(power((int)ch,e,n))):(char)(power((int)(unsigned char)ch,d,n));
				cout<<ch1;
				fputc(ch1,cFile);
			}
		}
		else if(choice1 == 1)
		{
			val=1;
			if(choice2==1 || choice2==4)
				length=16;
			else
				length=8;
			while(flag)
			{
				i=0;

				while(val != EOF)
				{
					val = fgetc(oFile);
					if(val == EOF)
						flag=0;
					else
						data[i++] = (unsigned char)val;
					if(i==length)
						break;
				}
				if(i==0)
					break;
				else if(i<length)
				{
					flag=0;
					for(;i<length;i++)
						data[i]=0;
				}
				switch(choice2)
				{
					case 1:
						AESEncrypt(data,crypt,AES_word);
						break;
					case 2:
						blowfish(crypt,data,0);
						break;
					case 3:
						DESencrypt(crypt,data,DES_k);
						break;
					case 4:
						RC6Encrypt(crypt,data,RC6_S);
						break;
				}
				for(i=0;i<length;i++)
				{
					cout<<(unsigned char)crypt[i];
					j = (unsigned char)crypt[i];
					fputc(j,cFile);
				}
			}
		}
		else
		{
			fseek(oFile,0,SEEK_SET);
			fseek(cFile,0,SEEK_SET);

			val=1;
			if(choice2==1 || choice2==4)
				length=16;
			else
				length=8;
			while(flag)
			{
				i=0;
				while(val != EOF)
				{
					val = fgetc(oFile);
					if(val == EOF)
						flag=0;
					else
						crypt[i++] = (unsigned char)val;
					if(i==length)
						break;
				}
				if(i==0)
					break;
				else if(i<length)
				{
					flag=0;
					for(;i<length;i++)
						crypt[i]=0;
				}
				switch(choice2)
				{
					case 1:
						AESDecrypt(data,crypt,AES_word);
						break;
					case 2:
						blowfish(crypt,data,1);
						break;
					case 3:
						DESdecrypt(crypt,data,DES_k);
						break;
					case 4:
						RC6Decrypt(crypt,data,RC6_S);
						break;
				}
				for(i=0;i<length;i++)
				{
					cout<<(unsigned char)data[i];
					j = (unsigned char)data[i];
					fputc(j,cFile);
				}
			}
		}
		fclose(oFile);
		fclose(cFile);
		if((top->next!=NULL && choice1==1) || (top!=NULL && choice1==2))
		{
			remove("cryptALL.dat");
			rename("temp.dat","cryptALL.dat");
		}
		if(top!=NULL)
		{
			cout<<"\n\tLayers: ";
			for(np=top;np!=NULL;np=np->next)
				switch(np->info)
				{
					case 1:
						cout<<"->AES";
						break;
					case 2:
						cout<<"->BF";
						break;
					case 3:
						cout<<"->DES";
						break;
					case 4:
						cout<<"->RC6";
						break;
					case 5:
						cout<<"->RSA";
				}
		}
	}while(1);
}