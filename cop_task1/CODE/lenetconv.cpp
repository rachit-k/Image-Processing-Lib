#include <iostream>
#include "openblaslib.h"

using namespace std;

void lenetconv(float** X,float**Y,int a,int b,float** L)
{
    int q=a-b+1;
    float **Z=new float*[(a-b+1)*(a-b+1)];
    for(int i=0;i<(a-b+1)*(a-b+1);i++)
    {
        Z[i]=new float[b*b];
    }
    float **W=new float*[b*b];
    for(int i=0;i<(b*b);i++)
    {
        W[i]=new float[1];
    }

    for(int i=0;i<a-b+1;i++)/*Storing elements from input matrix into matrix which wil be used for multiplication*/
    {
        for(int j=0;j<a-b+1;j++)
        {
            for(int k=0;k<b*b;k++)
            {
                int t=k/b;
                Z[(a-b+1)*i+(j)][k]=X[i+t][j+k-t*b];
            }
        }
    }
    
    for(int i=0;i<b;i++)/*converting kernel into other matrix which will be multiply by another matrix for calculating convolution*/
    {    
        for(int j=0;j<b;j++)
        {
            W[b*i+j][0]=Y[i][j];
        }
    } 
    float **V=new float*[(a-b+1)*(a-b+1)];
    for(int i=0;i<(a-b+1)*(a-b+1);i++)
    {
        V[i]=new float[1];
    } 

    openblaslib(Z,W,V,(a-b+1)*(a-b+1),b*b,1);

    for(int i=0;i<a-b+1;i++)/*Storing output in 2D matrix*/
    {
        for(int j=0;j<a-b+1;j++)
        {
            L[i][j]=V[((a-b+1)*i)+j][0];
        }
    }

}