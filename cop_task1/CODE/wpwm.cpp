#include <iostream>
#include "mklib.h"
#include "openblaslib.h"
#include "pthmult.h"
#include <chrono>

using namespace std;

void wpwm(float** X,float** Y,int a,int b,int ps, float** L, int flag)
{
   
    int f=2*ps;
    int q=a-b+1;
    float O[a+f][a+f];/*Decleration of matrix will be used for padding of input matrix*/
    for(int i=0;i<(a+f);i++)
    {
        for(int j=0;j<(a+f);j++)
        {
            O[i][j]=0;
        }
    }
    for(int i=0;i<a;i++)/*Storing data into padded matrix*/
    {
        for(int j=0;j<a;j++)
        {
            O[i+ps][j+ps]=X[i][j];
        }
    }

    float **Z=new float*[(a-b+1+f)*(a-b+1+f)];
    for(int i=0;i<(a-b+1+f)*(a-b+1+f);i++)
    {
        Z[i]=new float[b*b];
    }
    float **W=new float*[b*b];
    for(int i=0;i<(b*b);i++)
    {
        W[i]=new float[1];
    }    

    for(int i=0;i<(a-b+1+f);i++)/*construction of matrix which will be used in multiplication for calculating convolution*/
    {
        for(int j=0;j<(a-b+1+f);j++)
        {
            for(int k=0;k<b*b;k++)
            {
                int t=k/b;
                Z[(a-b+1+f)*i+(j)][k]=O[i+t][j+k-t*b];
            }
        }
    }
    
    float D[b][b];/*Taking image of kernel about it's centre*/
   for(int i=0;i<b;i++)
    {
        for(int j=0;j<b;j++)
        {
            D[i][j]=Y[b-1-i][b-1-j];
        }
    }
    for(int i=0;i<b;i++)
    {
        for(int j=0;j<b;j++)
        {
            Y[i][j]=D[i][j];
        }
    }
    for(int i=0;i<b;i++)/*Converting kernel into matrix which will be used for multiplication for calculating convolution*/
    {
        for(int j=0;j<b;j++)
        {
            W[b*i+j][0]=Y[i][j];
        }
    }
    float **V=new float*[(a-b+1+f)*(a-b+1+f)];
    for(int i=0;i<(a-b+1+f)*(a-b+1+f);i++)
    {
        V[i]=new float[1];
    }
    float s=0;
    if(flag==0)
    {
        mklib(Z,W,V,(a-b+1+f)*(a-b+1+f),b*b,1);
    }
    else if(flag==1)
    {
        openblaslib(Z,W,V,(a-b+1+f)*(a-b+1+f),b*b,1);
    }
    else if(flag==2)
    {
        pthmult(Z,W,V,(a-b+1+f)*(a-b+1+f),b*b,1);
    }
    else
    {
        for(int i=0;i<(a-b+1+f)*(a-b+1+f);i++)/*Matrix multiplication for finding element of output matrix*/
        {
            s=0;
            for(int j=0;j<b*b;j++)
            {
                for(int k=0;k<1;k++)
                {
                    s=s+Z[i][j]*W[j][k];
                }
            }
            V[i][0]=s;
        }
    }
    
    for(int i=0;i<a-b+1+f;i++)/*Storing output data in matrix of true dimension*/
    {
        for(int j=0;j<a-b+f+1;j++)
        {
            L[i][j]=V[((a-b+1+f)*i)+j][0];
        }
    }
    
}
