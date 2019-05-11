#include <iostream>
using namespace std;

void wpwom(float** X,float** Y,int a,int b,int ps, float** Z)
{
    int q=(b-1)/2,s,p=2*ps;
    float W[b][b],Q[a+p][a+p],M[a+p][a+p];/*Decleration of matrices for storing data in process*/
    for(int i=0;i<a+p;i++)
    {
        for(int j=0;j<a+p;j++)
        {
            M[i][j]=0;
        }
    }
    for(int i=0;i<a;i++)/*increase in size of inpit matrix with padding*/
    {
        for(int j=0;j<a;j++)
        {
            M[i+ps][j+ps]=X[i][j];
        }
    }
    for(int i=0;i<b;i++)/*tking image of kernel about centre*/
    {
        for(int j=0;j<b;j++)
        {
            W[i][j]=Y[b-i-1][b-1-j];
        }
    }
    
    for(int i=0;i<b;i++)
    {
        for(int j=0;j<b;j++)
        {
            Y[i][j]=W[i][j];
        }
    }
    
    for(int i=0;i<a+p;i++)/*Calcuation of convolution*/
    {
        for(int j=0;j<a+p;j++)
        {
            s=0;
            for(int l=0;l<b;l++)
            {
                for(int k=0;k<b;k++)
                {
                    if((i+b-1)<a+p)
                    {
                        if((j+b-1)<a+p)
                        {
                            s=s+M[i+l][j+k]*Y[l][k];
                        }
                    }
                }
            }
            Q[i][j]=s;
        }
    }
    
    for(int i=0;i<a-b+1+p;i++)/*Stroing output into Z*/
    {
        for(int j=0;j<a-b+p+1;j++)
        {
            Z[i][j]=Q[i][j];
        }
    }
    
}
