#include<stdio.h>
#include<queue>
using namespace std;

int graph[20][20];
bool cgraph[20][20];
	
struct position
{
	int x,y,last;
}pos,temp;

int main()
{
	int x,y,max=-6,n;
	scanf("%d",&n);
	scanf("%d %d",&x,&y);
	
	queue <position> q;
	
	pos.x=y-1; pos.y=x-1; pos.last=-6;
	q.push(pos);
	
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d",&graph[i][j]);
	
	while(!q.empty())
	{
		temp=q.front();
		q.pop();
		if(cgraph[temp.x][temp.y] == 0 && graph[temp.x][temp.y] != 100 && temp.last < graph[temp.x][temp.y])
		{
			cgraph[temp.x][temp.y] = 1;
			if(graph[temp.x][temp.y] > max)
				max = graph[temp.x][temp.y];
			if(temp.x+1 < n)
			{
				pos.x=temp.x+1; pos.y=temp.y; pos.last=graph[temp.x][temp.y];
				q.push(pos);
			}
			if(temp.x-1 >= 0)
			{
				pos.x=temp.x-1; pos.y=temp.y; pos.last=graph[temp.x][temp.y];
				q.push(pos);
			}
			if(temp.y+1 < n)
			{
				pos.x=temp.x; pos.y=temp.y+1; pos.last=graph[temp.x][temp.y];
				q.push(pos);
			}
			if(temp.y-1 >= 0)
			{
				pos.x=temp.x; pos.y=temp.y-1; pos.last=graph[temp.x][temp.y];
				q.push(pos);
			}
		}
	}	
	
	printf("%d",max);
	
	return 0;
}
