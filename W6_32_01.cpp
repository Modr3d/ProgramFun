#include<stdio.h>
#include<iostream>
using namespace std;

int main()
{
	float GA[3][5],GB[3][5],dA=0,dB=0,Mul[3][3];
	
	printf("Enter Matrix A :\n");
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			cin >> GA[i][j];
			if(j<2)
				GA[i][j+3]=GA[i][j];
		}
	printf("Enter Matrix B :\n");
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			cin >> GB[i][j];
			if(j<2)
				GB[i][j+3]=GB[i][j];
		}
	
	for(int i=0;i<3;i++)
	{
		dA+=(GA[0][i]*GA[1][i+1]*GA[2][i+2]);
		dA-=(GA[2][i]*GA[1][i+1]*GA[0][i+2]);
	}
	printf("\nDetA = %.2f\n",dA);
	for(int i=0;i<3;i++)
	{
		dB+=(GB[0][i]*GB[1][i+1]*GB[2][i+2]);
		dB-=(GB[2][i]*GB[1][i+1]*GB[0][i+2]);
	}
	printf("DetB = %.2f\n",dB);
	
	printf("\nInverse A :\n");
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%.2f",((GA[(j+1)%3][(i+1)%3] * GA[(j+2)%3][(i+2)%3]) - (GA[(j+1)%3][(i+2)%3] * GA[(j+2)%3][(i+1)%3])) / dA);
			printf("\t");
		}
		printf("\n");
	}
	
	printf("Inverse B :\n");
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%.2f",((GB[(j+1)%3][(i+1)%3] * GB[(j+2)%3][(i+2)%3]) - (GB[(j+1)%3][(i+2)%3] * GB[(j+2)%3][(i+1)%3])) / dB);
			printf("\t");
		}
		printf("\n");
	}
	
	printf("\nA + B :\n");
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%.2f\t",GA[i][j]+GB[i][j]);
		}
		printf("\n");
	}
	printf("A - B :\n");
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%.2f\t",GA[i][j]-GB[i][j]);
		}
		printf("\n");
	}
	
	for (int i=0;i<3;i++)
	    for (int j=0;j<3;j++) 
	    {
	    	Mul[i][j] = 0;
	        for (int k=0;k<3;k++)
	            Mul[i][j] += (GA[i][k] * GB[k][j]);
	    }
	            
	printf("A x B :\n");
	for (int i=0;i<3;i++)
	{
	    for (int j=0;j<3;j++)
			printf("%.2f\t",Mul[i][j]);
		printf("\n");
	}
	return 0;
}
