#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

int main()
{
	bool check;
	int graph[4][4];
	string s;
	
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			cin >> graph[i][j];
			
	rewind(stdin);
	getline(cin,s);
	
	for(int i=0;i<s.size();i++)
	{
		if(s[i] == 'L')
		{
			do
			{
				check=0;
				for(int j=3;j>0;j--)
				{
					for(int k=0;k<4;k++)
					{
						if((graph[k][j] == graph[k][j-1]  && graph[k][j] != 0 && graph[k][j-1] != 0)|| (graph[k][j-1] == 0 && graph[k][j] != 0))
						{
							graph[k][j-1]+=graph[k][j];
							graph[k][j]=0;
							check=1;
						}
					}
				}
			}while(check != false);
		}
		else if(s[i] == 'R')
		{
			do
			{
				check=0;
				for(int j=0;j<3;j++)
				{
					for(int k=0;k<4;k++)
					{
						if((graph[k][j] == graph[k][j+1]  && graph[k][j] != 0 && graph[k][j+1] != 0)|| (graph[k][j+1] == 0 && graph[k][j] != 0))
						{
							graph[k][j+1]+=graph[k][j];
							graph[k][j]=0;
							check=1;
						}
					}
				}
			}while(check != false);
		}
		else if(s[i] == 'U')
		{
			do
			{
				check=0;
				for(int j=3;j>0;j--)
				{
					for(int k=0;k<4;k++)
					{
						if((graph[j][k] == graph[j-1][k]  && graph[j-1][k] != 0 && graph[j][k] != 0)|| (graph[j-1][k] == 0 && graph[j][k] != 0))
						{
							graph[j-1][k]+=graph[j][k];
							graph[j][k]=0;
							check=1;
						}
					}
				}
			}while(check != false);
		}
		else if(s[i] == 'D')
		{
			do
			{
				check=0;
				for(int j=0;j<3;j++)
				{
					for(int k=0;k<4;k++)
					{
						if((graph[j][k] == graph[j+1][k]  && graph[j+1][k] != 0 && graph[j][k] != 0)|| (graph[j+1][k] == 0 && graph[j][k] != 0))
						{
							graph[j+1][k]+=graph[j][k];
							graph[j][k]=0;
							check=1;
						}
					}
				}
			}while(check != false);
		}
	}
	
	printf("Result : ");
	printf("\n");
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
			cout << graph[i][j] << "\t";
		printf("\n");
	}
	return 0;
}
