#include<stdio.h>
#include<vector>
#include<iostream>
using namespace std;

vector <int> v;

int main()
{
	int n,count;
	char c;
	
	
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		cin >> c;
		v.push_back(c);
	}
	
	do
	{
		count=0;
		for(int i=0;i<v.size()-1 && v.size() > 0;i++)
		{
			if(v[i] == v[i+1])
			{
				v.erase(v.begin()+i);
				v.erase(v.begin()+i);
				i-=2;
				count++;
			}
		}
	}while(count != 0);
	
	printf("%d\n",v.size());
	
	if(v.size() != 0)
		for(int i=v.size()-1;i>=0;i--)
		{
			printf("%c",v[i]);	
		}
	else
		printf("empty");
		
	return 0;
}
