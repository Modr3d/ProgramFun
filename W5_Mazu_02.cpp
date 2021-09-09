#include<stdio.h>
#include<vector>
#include<iostream>
using namespace std;

vector <int> v;

int main()
{
	int n,check;
	scanf("%d",&n);
	char arr[n];
	int count=n;
	
	for(int i=0;i<n;i++)
	{
		cin >> arr[i];
	}
	
	do
	{
		check=0;
		for(int i=0;i<n-1;i++)
		{
			if(arr[i] != 0)
			{
				if(arr[i+1] == 0)
					for(int j=i+1;j<n;j++)
					{
						if(arr[j] != 0)
						{
							if(arr[i] == arr[j])
							{
								arr[i]=0;
								arr[j]=0;
								check++;
								count-=2;
							}
							break;
						}
					}
				else
				{
					if(arr[i] == arr[i+1])
					{
						arr[i]=0;
						arr[i+1]=0;
						check++;
						count-=2;
						i+=2;
					}
				}
			}
		}
	}while(check != 0);
	
	printf("%d\n",count);
	
	if(count > 0)
	{
		for(int i=n-1;i>=0;i--)
		{
			if(arr[i] != 0)
				printf("%c",arr[i]);
		}
	}
	else
		printf("empty");
	
	return 0;
}
