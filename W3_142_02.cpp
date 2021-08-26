#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

int main()
{
	int count=0,s1,s2,s3,set2,set3;
	bool c1,c2,c3,c4,out;
	char c;
	string str;
	cout << "Input Password : ";
	getline(std::cin, str);
	
	for(int i=0;i<str.size();i++)
	{
		if(str[i] != ',')
		{
			if(str[i] >= 'a' && str[i] <='z')
				c1=true;
			if(str[i] >= 'A' && str[i] <='Z')
				c2=true;
			if(str[i] >= '0' && str[i] <='9')
				c3=true;
			if(str[i] == '$' || str[i] =='@' || str[i] == '#')
				c4=true;
		}
		else if(str[i] == ',')
		{
			if(count == 0)
			{
				s1=i; set2=i+1;
				if(c1 == true && c2 == true && c3 == true && c4 == true && (s1 >=6 && s1 <=12))
				{
					for(int j=0;j<i;j++)
						printf("%c",str[j]);
					printf("(Kob) ");
					out=true;
				}
				count++;
			}
			else if(count == 1)
			{
				s2=(i-s1-1); set3=i+1;
				if(c1 == true && c2 == true && c3 == true && c4 == true && (s2 >=6 && s2 <=12) && out == false)
				{
					for(int j=set2;j<i;j++)
						printf("%c",str[j]);
					printf("(Romtham) ");
					out=true;
				}
				count++;
			}
			c1=false,c2=false,c3=false,c4=false;
		}
		if(i == str.size()-1)
		{
			s3=(i-1-s2-s1);
			if(c1 == true && c2 == true && c3 == true && c4 == true && (s3 >=6 && s3 <=12) && out == false)
			{
				for(int j=set3;j<i;j++)
					printf("%c",str[j]);
				printf("(Jojo) ");
			}
		}
	}
	
	return 0;
}
