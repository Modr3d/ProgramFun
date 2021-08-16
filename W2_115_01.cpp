#include<stdio.h>
#include<iostream>
using namespace std;

bool graph2[1001][1001];
int graph[1001][1001],a,b,x,y;

int search(int a,int b,int graph[1001][1001])
{
	graph2[a][b]=1;
	
	if(graph2[a][b+1] != 1 && graph[a][b+1] == 0 && b+1<y)
		search(a,b+1,graph);
	if(graph2[a+1][b] != 1 && graph[a+1][b] == 0 && a+1<x)
		search(a+1,b,graph);
	if(graph2[a][b-1] != 1 && graph[a][b-1] == 0 && b-1 >=0)
		search(a,b-1,graph);
	if(graph2[a-1][b] != 1 && graph[a-1][b] == 0 && a-1 >=0)
		search(a-1,b,graph);
};

int main()
{
	scanf("%d %d",&x,&y);

	for(int i=0;i<x;i++)
		for(int j=0;j<y;j++)
			cin >> graph[i][j];
			
	search(0,0,graph);
	
	if(graph2[x-1][y-1] == 1)
		printf("Yes");
	else
		printf("No");
	
	return 0;
}
