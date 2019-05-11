#include <iostream>
#include <pthread.h>
#include <chrono>

using namespace std;

int a,b,c,size=0;
float** M1;
float** M2;
float** M3;


void *mul(void *arg)
{
    int r=size++;
    if(a%2==0)
    {
    for(int i=0;i<a/2;i++)
    for (int j = 0; j < b; j++)
    {
        for (int l = 0; l < c; l++)
        {
            M3[(r*(a/2))+i][l] += M1[(r*(a/2))+i][j] * M2[j][l];
        }
    }
    }
    else
    {
        for(int i=0;i<(a/2)+1;i++)
            for (int j = 0; j < b; j++)
            {
                for (int l = 0; l < c; l++)
                {
                    M3[(r*(a/2))+i][l] += M1[(r*(a/2))+i][j] * M2[j][l];
                }
            }
    }  
}

void pthmult(float** Z,float** W,float** V,int z,int x,int l)
{
    a=z;
    b=x;
    c=l;

    pthread_t threads[2];
    
    M1 = (float **) malloc(a * sizeof(float *));
    M2 = (float **) malloc(b * sizeof(float *));
    M3 = (float **) malloc(a * sizeof(float *));
    for(int i=0;i < a;i++)
    {
        M1[i] = (float *) malloc(b * sizeof(float));
    }
    for(int i=0;i < b;i++)
    {
        M2[i] = (float *) malloc(c * sizeof(float));
    }
    for(int i=0;i <a; i++)
    {
        M3[i] = (float *) malloc(c * sizeof(float));
    }
    
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<b;j++)
        {
            M1[i][j]=Z[i][j];
        }
    }
    
    for(int i=0;i<b;i++)
    {
        for(int j=0;j<c;j++)
        {
            M2[i][j]=W[i][j];
        }
    }
    
    int* pt ;
    //auto t1=std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, mul, (void*)(pt));
    }
    
    for (int i = 0; i < 2 ; i++) {
        pthread_join(threads[i], NULL);
    }
   // auto t2=std::chrono::high_resolution_clock::now();
   // cout<<(t2-t1).count()<<endl;
  
    if(a%2==1)
    {
        for(int i=0;i<b;i++)
        {
            M3[int (a/2)][i]=(M3[int (a/2)][i])/2;
        }
    }

    
    
    for(int i=0;i<a;i++)
    {
        for(int j=0;j<c;j++)
        {
            V[i][j]=M3[i][j];
        }
    }
}
