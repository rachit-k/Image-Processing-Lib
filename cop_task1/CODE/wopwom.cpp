#include <iostream>
using namespace std;

void wopwom(float** X,float** Y,int a,int b, float** Z)
{
    int q=(b-1)/2,s;
    float W[b][b],Q[a][a]; /*decleration of two matrices will be used for reversing kernl about centre and storing output matrix respectively*/
    for(int i=0;i<b;i++)  /*for reverseing the kernel matrix*/
    {
        for(int j=0;j<b;j++)
        {
            W[i][j]=Y[b-i-1][b-1-j];
        }
    }
    
    for(int i=0;i<b;i++)/*Stroing changed kernel in input kernel*/
    {
        for(int j=0;j<b;j++)
        {
            Y[i][j]=W[i][j];
        }
    }
    
    for(int i=0;i<a;i++)/*calculation of elements of output matrix*/
    {
        for(int j=0;j<a;j++)
        {
            s=0;
            for(int l=0;l<b;l++)
            {
                for(int k=0;k<b;k++)
                {
                    if((i+b-1)<a)
                    {
                        if((j+b-1)<a)
                        {
                            s=s+X[i+l][j+k]*Y[l][k];
                        }
                    }
                }
            }
            Q[i][j]=s;
        }
    }
    
    for(int i=0;i<a-b+1;i++)/*storing output in Z*/
    {
        for(int j=0;j<a-b+1;j++)
        {
            Z[i][j]=Q[i][j];
        }
    }
    
}
