#include<stdio.h>
#include<iostream>
using namespace std;
int matrix[100][100];
bool SqrC(int mat[][100],int num)
{
	int sumtl=0,sumbr=0;
	for(int i=0;i<num;i++)
	{
		sumtl+=mat[i][i];
		sumbr+=mat[i][num-i-1];
	}
	if(sumtl != sumbr)
		return false;
	
	int sumr,sumc;
	for(int i=0;i<num;i++)
	{
		sumr=0; sumc=0;
		for(int j=0;j<num;j++)
		{
			sumr+=mat[i][j];
			sumc+=mat[j][i];
		}
		if(sumr != sumc || sumr != sumtl)
		return false;
	}
	
	return true;
}

int main()
{
	int n;
	printf("Input Size of Square : ");
	scanf("%d",&n);
	
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			cin >> matrix[i][j];

	if( SqrC(matrix,n) == true)
		printf("Yes");
	else
		printf("No");
	
	return 0;
}
