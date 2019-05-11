#include <math.h>
using namespace std;

void probability(float *A, int a, int flag)
{
	if(flag==0)	//sigmoid
	{
		for(int i=0;i<a;i++)
		{
			A[i]=1/(1+exp(-1*A[i]));
		}
	}
	else	//softmax
	{
		float t=0.0;
		for(int i=0;i<a;i++)
		{
			t=t+ exp(A[i]);	//calculating denominator
		}
		for(int i=0;i<a;i++)
		{
			A[i]=(exp(A[i]))/(t);
		}
	}
} 