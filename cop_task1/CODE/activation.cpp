#include <math.h>
using namespace std;

void activation(float **A,int a, int b,int flag) 
{
	if(flag==0)	//relu
	{
		for(int i=0;i<a;i++)
		{
			for(int j=0;j<b;j++)
			{
				if(A[i][j]<0)
					A[i][j]=0;
			}
		}
	}
	else	//tanh
	{
		for(int i=0;i<a;i++)
		{
			for(int j=0;j<b;j++)
			{
				A[i][j]=tanh(A[i][j]);
			}
		}
	}
}