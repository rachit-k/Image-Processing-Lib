#include "/opt/OpenBLAS-develop/cblas.h"
#include <chrono>
#include <iostream>
using namespace std;

void openblaslib(float** Z, float** W, float** V, int m, int p, int n)
{
	double *A=new double[m*p];
	double *B=new double[p*n];
	double *C=new double[m*n];
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<p;j++)
		{
			A[i*p+j]=Z[i][j];
		}
	}
	for(int i=0;i<p;i++)
	{
		for(int j=0;j<n;j++)
		{
			B[i*n+j]=W[i][j];
		}
	}
	//auto t1=std::chrono::high_resolution_clock::now();
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, p, 1.0, A, p, B, n, 0.0, C, n);
	//auto t2=std::chrono::high_resolution_clock::now();
	//cout<<(t2-t1).count()<<endl;
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			V[i][j]=C[i*n+j];
		}
	}	
}