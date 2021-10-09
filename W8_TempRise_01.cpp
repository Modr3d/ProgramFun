#include<stdio.h>

int graph[20][20],max=-6,n;
bool cgraph[20][20];

void walk(int x,int y,int last)
{
	if(cgraph[x][y] == 0 && graph[x][y] != 100 && last < graph[x][y])
	{
		cgraph[x][y] = 1;
		if(graph[x][y] > max)
			max = graph[x][y];
		if(x+1 < n)
			walk(x+1,y,graph[x][y]);
		if(x-1 >= 0)
			walk(x-1,y,graph[x][y]);
		if(y+1 < n)
			walk(x,y+1,graph[x][y]);
		if(y-1 >= 0)
			walk(x,y-1,graph[x][y]);
	}
}

int main()
{
	int x,y;
	scanf("%d",&n);
	scanf("%d %d",&x,&y);
	
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&graph[i][j]);
	
	walk(y-1,x-1,-6);
	
	printf("%d",max);
	
	return 0;
}
