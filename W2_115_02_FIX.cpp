#include<stdio.h>
#include<iostream>
#include<queue>
using namespace std;

struct info{
	int a,b;	
	
}temp,temp2;

int main()
{
	int x,y;
	queue <info> s;
	
	scanf("%d %d",&x,&y);
	int graph[x][y];
	bool graph2[x][y];

	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			cin >> graph[i][j];
	
	temp.a = 0; temp.b = 0;
	s.push(temp);
	
	while(s.empty() != 1)
	{
		temp = s.front();
		s.pop();
		
		if(graph2[temp.a][temp.b] != 1)
		{
			graph2[temp.a][temp.b] = 1;
			if(graph[temp.a+1][temp.b] != 1 && temp.a+1 <x)
			{
				temp2.a=temp.a+1;
				temp2.b=temp.b;
				s.push(temp2);
			}
			if(graph[temp.a-1][temp.b] != 1 && temp.a-1 >=0)
			{
				temp2.a=temp.a-1;
				temp2.b=temp.b;
				s.push(temp2);
			}
			if(graph[temp.a][temp.b+1] != 1 && temp.b+1 <y)
			{
				temp2.a=temp.a;
				temp2.b=temp.b+1;	
				s.push(temp2);
			}
			if(graph[temp.a][temp.b-1] != 1 && temp.b-1 >=0)
			{
				temp2.a=temp.a;
				temp2.b=temp.b-1;
				s.push(temp2);
			}
		}
	}
	
	if(graph2[x-1][y-1] == 1)
		printf("Yes");
	else
		printf("No");

	return 0;
}
