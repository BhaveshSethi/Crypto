#include<fstream.h>
#include<iomanip.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<bftable.h>

void strToInt(unsigned long int *xL, unsigned long int *xR, unsigned char str[8])
{
	*xL=*xR=0;
	for(int j=0;j<4;j++)
	{
		*xL+=(unsigned long int)(str[j])<<((3-j)*8);
		*xR+=(unsigned long int)(str[j+4])<<((3-j)*8);
	}
}
void blowfish(unsigned char Cstr[8], unsigned char str[8],int mode)
{
	unsigned char strL[4],strR[4];
	int i,j;
	unsigned long int xL,xR,x,y,temp;
	if(!mode)
		strToInt(&xL,&xR,str);
	else
		strToInt(&xL,&xR,Cstr);
	for(i=0;i<16;i++)
	{
		x=y=0;
		if(mode==0)
			xL^=P[i];
		else
			xL^=P[17-i];
		x=xL;
		//cout<<"\n\tx = "<<x;
		for(j=3;j>=0;j--)
		{
			strL[j] = x;
		//	cout<<"\n\tstr["<<j<<"] = "<<strL[j]<<" "<<(int)strL[j];
			x = x >> 8;
		}
		y = ((S[0][strL[0]] + S[1][strL[1]]) ^ S[2][strL[2]]) + S[3][strL[3]];
		//cout<<"\n\t"<<S[0][strL[0]]<<"\n\t"<<S[1][strL[1]]<<"\n\t"<<S[2][strL[2]]<<"\n\t"<<S[3][strL[3]];
		//cout<<"\n\ty = "<<y;
		xR ^= y;
		x=xR;
		/*for(j=3;j>=0;j--)
		{
			strR[j] = x;
			cout<<"\n\tstr["<<j<<"] = "<<strL[j]<<" "<<(int)strL[j];
			x = x >> 8;
		}*/
		temp = xL;
		xL = xR;
		xR = temp;
	}
	temp = xL;
	xL = xR;
	xR = temp;
	if(mode==0)
	{
		xR ^= P[16];
		xL ^= P[17];
	}
	else
	{
		xR ^= P[1];
		xL ^= P[0];
	}
	for(j=3;j>=0;j--)
	{
		if(!mode)
		{
			Cstr[j+4] = xR;
			Cstr[j] = xL;
		}
		else
		{
			str[j+4] = xR;
			str[j] = xL;
		}
		//cout<<"\n\tstr["<<j<<"] = "<<str[j]<<" "<<(int)str[j]<<"\n\tstr["<<j+4<<"] = "<<str[j+4]<<" "<<(int)str[j+4];
		xL = xL >> 8;
		xR = xR >> 8;
	}
}
void print8(char *str)
{
	for(int i=0;i<8;i++)
		cout<<str[i];
}
void main()
{
//	clrscr();
	cout<<"\n\tBlowFish\n\tGenerating Keys";
	int i,j,k=0,flag,val;
	unsigned long int x,kL,kR;
	FILE *oFile, *cFile;
	oFile = fopen("test.txt","rb");        //the file to be encrypted
	char key[20],msg[80],data[8],crypt[8];
	//fstream f;
	//f.open("crypt1.dat",ios::out | ios::trunc);
	cFile = fopen("cryptBF.dat","wb");//crypt file
	strcpy(key,"blowfish");
	cout<<"\n\tEnter Msg \n\t";
//	gets(msg);
//	cout<<msg;
//	cout<<"\n\tMsg is "<<msg<<" of length "<<strlen(msg);
//	msg[8]='\0';
	int len=strlen(key);
	for(i=0;i<18;i++)
	{
		x=0;
		for(j=0;j<=3;j++)
			x += (unsigned long int)(key[(j + k)%len])<<((3-j)*8);
		//cout<<"\n\tk="<<k<<" x="<<x<<" P["<<i<<"]="<<P[i];
		k = (k+4)%len;
		P[i]^=x;
 //		cout<<"\n\tP["<<i<<"]="<<P[i]<<endl;
 //		getch();
	}
//	cout<<"\n\tMsg is ";
//	print8(msg);

	char keyCrypt[8];
	memset(keyCrypt,0,8);
	for(i=0;i<18;i+=2)
	{
		kL=kR=0;
		//cout<<"\n"<<keyCrypt;
		blowfish(keyCrypt,keyCrypt,0);
		strToInt(&kL,&kR,keyCrypt);
		//cout<<" "<<kL<<" "<<kR<<" "<<keyCrypt;
		P[i] = kL;
		P[i+1] = kR;
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<256;j+=2)
		{
			kL=kR=0;
			blowfish(keyCrypt,keyCrypt,0);
			strToInt(&kL,&kR,keyCrypt);
			S[i][j] = kL;
			S[i][j+1] = kR;
		}
	}
//	fi.open("crypt.txt",ios::in | ios::binary);
	len = strlen(msg);
	//memset(Cmsg,0,strlen(Cmsg));
	flag=1;
	fseek(oFile,0,SEEK_SET);
	fseek(cFile,0,SEEK_SET);
	char ch='1';
//	for(i=0;i<len;i+=8)
	len=0;
	while(flag)
	{
		ch = fgetc(oFile);
		j=0;
		//cout<<ch;
		//data[j]=ch;
		while(ch!=EOF)
		{
			cout<<ch;
			data[j++]=ch;
			if(j==8)
				break;
			ch=fgetc(oFile);
		}
//		fi.close();


		//***************************************

		if(j==0)
			break;
		else if(j < 8)
		{
//			for(j=0;j< len -i ;j++)
//				data[j] = msg[i+j];
			flag=0;
			//j++;
			for(;j<8;j++)
				data[j] = 0;
		}  /*
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
		}    */
		blowfish(crypt,data,0);
		//memcpy((Cmsg+strlen(Cmsg)),crypt,8);

		//print8(crypt);
		len+=8;
		for(j=0;j<8;j++)
		{
			val = (unsigned char)crypt[j];
			//f<<setw(4)<<val;
			fputc(val,cFile);
			//cout<<(char)val<<" ";

			//Cmsg[i + j] = crypt[j];
		}
		//cout<<len;
	}
	fclose(cFile);
	fclose(oFile);
	cFile = fopen("cryptBF.dat","rb");
	flag=1;
	oFile = fopen("test1.txt","wb");
	fseek(oFile,0,SEEK_SET);
	fseek(cFile,0,SEEK_SET);
	ch='0';
	len=0;
	while(flag)
	{
		memset(crypt,0,8);
		i=0;
		while(val != EOF)
		{
			val = fgetc(cFile);
			if(val == EOF)
				flag=0;
			else
			{
				crypt[i++] = (unsigned char)val;
				//cout<<(char)val<<" ";
			}
			if(i==8)
				break;
		}     /*
		for(j=0;j<8;j++)
			crypt[j] = Cmsg[i+j];*/
		blowfish(crypt,data,1);
		len+=8;
		if(flag)
		{
			print8(data);
			//cout<<len;
			for(int i=0;i<8;i++)
			{
				if(data[i])
					fputc(data[i],oFile);
			}
		}
	}
	fclose(cFile);
	fclose(oFile);
//	print8(data);fgetc
	cout<<"done";
	getch();
}