#include<stdio.h>

bool graph[8][8];

void tile(int x,int y,int type,bool first)
{
	if(x >= 0 && x < 8 && y >= 0 && y < 8)
	{
		graph[x][y]=1;
		if(first == 1)
		{
			tile(x-1,y,1,0);
			tile(x-1,y+1,2,0);
			tile(x,y+1,3,0);
			tile(x+1,y+1,4,0);
			tile(x+1,y,5,0);
			tile(x+1,y-1,6,0);
			tile(x,y-1,7,0);
			tile(x-1,y-1,8,0);
		}
		else
		{
			if(type == 1 && x-1 > 0)
			{
				tile(x-1,y,1,0);
			}
			else if(type == 2 && x-1 > 0 && y+1 < 8)
			{
				tile(x-1,y+1,2,0);
			}
			else if(type == 3 && y+1 < 8)
			{
				tile(x,y+1,3,0);
			}
			else if(type == 4 && x+1 < 8 && y+1 < 8)
			{
				tile(x+1,y+1,4,0);
			}
			else if(type == 5 && x+1 < 8)
			{
				tile(x+1,y,5,0);
			}
			else if(type == 6 && x+1 < 8 && y-1 > 0)
			{
				tile(x+1,y-1,6,0);
			}
			else if(type == 7 && y-1 > 0)
			{
				tile(x,y-1,7,0);
			}
			else if(type == 8 && x-1 > 0 && y-1 > 0)
			{
				tile(x-1,y-1,8,0);
			}
		}
	}
};

int main()
{
	int n,a,b,count=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d %d",&a,&b);
		a--; b--;
		tile(a,b,0,true);
	}
	
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			if(graph[i][j] == false)
				count++;
					
	printf("%d",count);
	
	return 0;
}
