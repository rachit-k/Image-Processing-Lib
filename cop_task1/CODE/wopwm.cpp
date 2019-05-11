#include <iostream>
#include "mklib.h"
#include "openblaslib.h"
#include "pthmult.h"
#include <chrono>

using namespace std;

void wopwm(float** X,float**Y,int a,int b,float** L,int flag)
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
    
    float D[b][b];
    for(int i=0;i<b;i++)/*reversing kernel*/
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
    float s=0;
    if(flag==0)
    {
        mklib(Z,W,V,(a-b+1)*(a-b+1),b*b,1);
    }
    else if(flag==1)
    {
        openblaslib(Z,W,V,(a-b+1)*(a-b+1),b*b,1);
    }
    else if(flag==2)
    {
        pthmult(Z,W,V,(a-b+1)*(a-b+1),b*b,1);
    }
    else
    {
   // auto t1=std::chrono::high_resolution_clock::now();
    for(int i=0;i<(a-b+1)*(a-b+1);i++)/*calclating elements of output matrix*/
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
    //auto t2=std::chrono::high_resolution_clock::now();
    //cout<<(t2-t1).count()<<endl;
    }
    for(int i=0;i<a-b+1;i++)/*Storing output in 2D matrix*/
    {
        for(int j=0;j<a-b+1;j++)
        {
            L[i][j]=V[((a-b+1)*i)+j][0];
        }
    }

}