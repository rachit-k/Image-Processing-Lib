#include <math.h>
using namespace std;

void subsampling(float **A, int a, int n, float **B,int flag)
{
	int t=a/n; 	//dimension of each small box=txt
	if(flag==0)//maxpooling
	{
		for(int i=0;i<n;i++)
		{
			for(int j=0; j<n;j++)
			{
				B[i][j]=A[t*i][t*j];	//initialising B to the first element of each box
			}
		}
		for(int k=0;k<n;k++)
		{
			for(int l=0;l<n;l++)
			{
				for(int i=0; i<t; i++)
				{
					for(int j=0;j<t; j++)
					{
						if(A[i+t*k][j+t*l]>B[k][l])
							B[k][l]=A[i+t*k][j+t*l];			
					}
				}
			}
		}
	}
	else	//avgpooling
	{
		for(int k=0;k<n;k++)
		{
			for(int l=0;l<n;l++)
			{
				float temp=0.0;
				for(int i=0; i<t; i++)
				{
					for(int j=0;j<t; j++)
					{
						temp=temp+A[i+t*k][j+t*l];			
					}
				}
				temp=temp/(t*t);
				B[k][l]=temp;

			}
		}
	}
}