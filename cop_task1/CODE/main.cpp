#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include "activation.h"
#include "subsampling.h"
#include "probability.h"
#include "wpwm.h"
#include "wpwom.h"
#include "wopwm.h"
#include "wopwom.h"
#include "mklib.h"
#include "openblaslib.h"
#include "pthmult.h"
#include "lenetconv.h"

using namespace std;
int main(int argc, char** argv)
{ 
	ifstream fin;
	if(strcmp(argv[1],"activation")==0)
	{	
		if(argc!=6)
		{
			cout<<"Input should be of the form: activation relu/tanh matrix.txt number_of_rows_in_matrix number_of_columns_in_matrix"<<endl;
			return 0;
		}
		int a=stoi(argv[4]);
		float **A =new float*[a];
		int b=stoi(argv[5]);
		if((a<=0)||(b<=0))
		{
			cout<<"number of rows and columns of a matrix should be greater than 0"<<endl;
			return 0;
		}
		for(int i=0;i<a;i++)
		{
			A[i]=new float[b];
		}
		fin.open(argv[3]);
		if (!fin)
        	throw std::runtime_error("file not found");
		int i=0;
		int j=0;
		while((!fin.eof())&&(j<b))
		{
			fin>>A[i][j];
				i++;
			if(i==a)
			{
				j++;
				i=0;
			}
		}
		fin.close();
		int flag=1;
		if(strcmp(argv[2],"relu")==0)
			flag=0;
		else if(strcmp(argv[2],"tanh")==1)
			{
				cout<<"Invalid subfunction input "<<argv[2]<<"\n Valid inputs: relu, tanh"<<endl;
				return 0;
			}
		activation(A,a,b,flag);
		for(int i=0;i<a;i++)
		{
			for(int j=0;j<b;j++)
			{
				cout<<A[i][j]<<" ";
			}
			cout<<"\n";
		}
	}
	else if(strcmp(argv[1],"subsampling")==0)
	{
		if(argc!=6)
		{
			cout<<"Input should be of the form: subsampling maxpooling/avgpooling matrix.txt number_of_rows_in_input_matrix number_of_rows_in_output_matrix"<<endl;
			return 0;
		}
		int a=stoi(argv[4]);
		int b=stoi(argv[5]);
		if((a<=0)||(b<=0))
		{
			cout<<"size of a matrix should be greater than 0"<<endl;
			return 0;
		}
		float **A =new float*[a];
		for(int i=0;i<a;i++)
		{
			A[i]=new float[a];
		}
		float **B =new float*[b];
		for(int i=0;i<b;i++)
		{
			B[i]=new float[b];
		}
		fin.open(argv[3]);
		if (!fin)
        	throw std::runtime_error("file not found");
		int i=0;
		int j=0;
		while((!fin.eof())&&(j<a))
		{
			fin>>A[i][j];			
			i++;
			if(i==a)
			{
				j++;
				i=0;
			}
		}
		fin.close();
		int flag=1;
		if(strcmp(argv[2],"maxpooling")==0)
			flag=0;
		else if(strcmp(argv[2],"avgpooling")==1)
			{
				cout<<"Invalid subfunction input "<<argv[2]<<"\n Valid inputs: maxpooling, avgpooling"<<endl;
				return 0;
			}
		subsampling(A,a,b,B,flag);	
		for(int i=0;i<b;i++)
		{
			for(int j=0;j<b;j++)
			{
				cout<<B[i][j]<<" ";
			}
			cout<<"\n";
		}		
	}
	else if(strcmp(argv[1],"convolution_withoutpadding")==0)
	{
		if(argc!=6)
		{
			cout<<"Input should be of the form: convolution_withoutpadding matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows"<<endl;
			return 0;
		}
		int a=stoi(argv[3]);
		int b=stoi(argv[5]);
		if(a<b)
		{
			cout<<"kernel size should be less than the size of the matrix"<<endl;
			return 0;
		}
		if((a<=0)||(b<=0))
		{
			cout<<"size of a matrix should be greater than 0"<<endl;
			return 0;
		}
		float **A =new float*[a];		
		for(int i=0;i<a;i++)
		{
			A[i]=new float[a];
		}
		float **B =new float*[b];		
		for(int i=0;i<b;i++)
		{
			B[i]=new float[b];
		}
		fin.open(argv[2]);
		if (!fin)
        	throw std::runtime_error("file not found");
		int i=0;
		int j=0;
		while((!fin.eof())&&(j<a))
		{
			fin>>A[i][j];			
			i++;
			if(i==a)
			{
				j++;
				i=0;
			}
		}
		fin.close();
		fin.open(argv[4]);
		if (!fin)
        	throw std::runtime_error("file not found");
		i=0;
		j=0;
		while((!fin.eof())&&(j<b))
		{
			fin>>B[i][j];			
			i++;
			if(i==b)
			{
				j++;
				i=0;
			}
		}
		fin.close();
		float** Z=new float* [a-b+1];
    	for(int i=0;i<a-b+1;i++)
    	{
        	Z[i]=new float [a-b+1];
    	}
    	wopwom(A,B,a,b,Z);
    	for(int i=0;i<a-b+1;i++)
    	{
    		for(int j=0;j<a-b+1;j++)
    		{
    			cout<<Z[i][j]<<" ";
    		}
    		cout<<"\n";
    	}
	}
	else if(strcmp(argv[1],"convolution_withoutpadding_matrixmult")==0)
	{
		if(argc!=7)
		{
			cout<<"Input should be of the form: convolution_withoutpadding_matrixmult matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows method_of_computing_mult"<<endl;
			return 0;
		}
		int a=stoi(argv[3]);
		int b=stoi(argv[5]);
		if(a<b)
		{
			cout<<"kernel size should be less than the size of the matrix"<<endl;
			return 0;
		}
		if((a<=0)||(b<=0))
		{
			cout<<"size of a matrix should be greater than 0"<<endl;
			return 0;
		}
		float **A =new float*[a];		
		for(int i=0;i<a;i++)
		{
			A[i]=new float[a];
		}
		float **B =new float*[b];		
		for(int i=0;i<b;i++)
		{
			B[i]=new float[b];
		}
		fin.open(argv[2]);
		if (!fin)
        	throw std::runtime_error("file not found");
		int i=0;
		int j=0;
		while((!fin.eof())&&(j<a))
			{
				fin>>A[i][j];			
				i++;
				if(i==a)
				{
					j++;
					i=0;
				}
			}
		fin.close();
		fin.open(argv[4]);
		if (!fin)
        	throw std::runtime_error("file not found");
		i=0;
		j=0;
		while((!fin.eof())&&(j<b))
			{
				fin>>B[i][j];			
				i++;
				if(i==b)
				{
					j++;
					i=0;
				}
			}
		fin.close();
		float**  L=new float* [a-b+1];
	    for(int i=0;i<a-b+1;i++)
	    {
	        L[i]=new float [a-b+1];
	    }
	    int flag=0;
	    if(strcmp(argv[6],"mkl")==0)
	    {
	    	;
	    }
	    else if(strcmp(argv[6],"openblas")==0)
	    {
	    	flag=1;
	    }
	    else if(strcmp(argv[6],"pthread")==0)
	    {
	    	flag=2;
	    }
	    else if(strcmp(argv[6],"manual")==0)
	    {
	    	flag=3;
	    }
	    else
	    {
	    	cout<<"Invalid multiplication method. Valid inputs are: openblas, mkl, pthread, manual";
	    	return 0;
	    }
    	wopwm(A,B,a,b,L,flag);
    	for(int i=0;i<a-b+1;i++)
    	{
    		for(int j=0;j<a-b+1;j++)
    		{
    			cout<<L[i][j]<<" ";
    		}
    		cout<<"\n";
    	}
	}

	else if(strcmp(argv[1],"convolution_withpadding")==0)
	{
		if(argc!=7)
		{
			cout<<"Input should be of the form: convolution_withpadding padsize matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows"<<endl;
			return 0;
		}
		int a=stoi(argv[4]);
		int b=stoi(argv[6]);
		int pad=stoi(argv[2]);
		if(a<b)
		{
			cout<<"kernel size should be less than the size of the matrix"<<endl;
			return 0;
		}
		if((a<=0)||(b<=0))
		{
			cout<<"size of a matrix should be greater than 0"<<endl;
			return 0;
		}
		if(pad<0)
		{
			cout<<"padding size cannot be a negative number"<<endl;
			return 0;
		}
		float **A =new float*[a];		
		for(int i=0;i<a;i++)
		{
			A[i]=new float[a];
		}
		float **B =new float*[b];		
		for(int i=0;i<b;i++)
		{
			B[i]=new float[b];
		}
		fin.open(argv[3]);
		if (!fin)
        	throw std::runtime_error("file not found");
		int i=0;
		int j=0;
		while((!fin.eof())&&(j<a))
		{
			fin>>A[i][j];			
			i++;
			if(i==a)
			{
				j++;
				i=0;
			}
		}		
		fin.close();
		fin.open(argv[5]);
		if (!fin)
        	throw std::runtime_error("file not found");
		i=0;
		j=0;
		while((!fin.eof())&&(j<b))
		{
			fin>>B[i][j];			
			i++;
			if(i==b)
			{
				j++;
				i=0;
			}
		}
		fin.close();
    	int p=2*pad;
    	float**  Z=new float* [a-b+1+p];
	    for(int i=0;i<a-b+1+p;i++)
	    {
	        Z[i]=new float [a-b+1+p];
	    }
    	wpwom(A,B,a,b,pad,Z);
    	for(int i=0;i<a-b+1+p;i++)
    	{
    		for(int j=0;j<a-b+1+p;j++)
    		{
    			cout<<Z[i][j]<<" ";
    		}
    		cout<<"\n";
    	}
	}
	else if(strcmp(argv[1],"convolution_withpadding_matrixmult")==0)
	{
		if(argc!=8)
		{
			cout<<"Input should be of the form: convolution_withpadding_matrixmult padsize matrix1.txt matrix1_numrows matrix2.txt matrix2_numrows method_of_computing_mult"<<endl;
			return 0;
		}
		int a=stoi(argv[4]);
		int b=stoi(argv[6]);
		int pad=stoi(argv[2]);
		if(a<b)
		{
			cout<<"kernel size should be less than the size of the matrix"<<endl;
			return 0;
		}
		if((a<=0)||(b<=0))
		{
			cout<<"size of a matrix should be greater than 0"<<endl;
			return 0;
		}
		if(pad<0)
		{
			cout<<"padding size cannot be a negative number"<<endl;
			return 0;
		}
		float **A =new float*[a];		
		for(int i=0;i<a;i++)
		{
			A[i]=new float[a];
		}
		float **B =new float*[b];		
		for(int i=0;i<b;i++)
		{
			B[i]=new float[b];
		}
		fin.open(argv[3]);
		if (!fin)
        	throw std::runtime_error("file not found");
		int i=0;
		int j=0;
		while((!fin.eof())&&(j<a))
		{
			fin>>A[i][j];			
			i++;
			if(i==a)
			{
				j++;
				i=0;
			}
		}
		fin.close();
		fin.open(argv[5]);
		if (!fin)
        	throw std::runtime_error("file not found");
		i=0;
		j=0;
		while((!fin.eof())&&(j<b))
		{
			fin>>B[i][j];			
			i++;
			if(i==b)
			{
				j++;
				i=0;
			}
		}
		fin.close();
    	int f=2*pad;
    	float**  L=new float* [a-b+1+f];
	    for(int i=0;i<a-b+1+f;i++)
	    {
	        L[i]=new float [a-b+1+f];
	    }
	    int flag=0;
	    if(strcmp(argv[7],"mkl")==0)
	    {
	    	;
	    }
	    else if(strcmp(argv[7],"openblas")==0)
	    {
	    	flag=1;
	    }
	    else if(strcmp(argv[7],"pthread")==0)
	    {
	    	flag=2;
	    }
	    else if(strcmp(argv[7],"manual")==0)
	    {
	    	flag=3;
	    }
	    else
	    {
	    	cout<<"Invalid multiplication method. Valid inputs are: openblas, mkl, pthread, manual";
	    	return 0;
	    }
    	wpwm(A,B,a,b,pad,L,flag);
    	for(int i=0;i<a-b+1+f;i++)
    	{
    		for(int j=0;j<a-b+1+f;j++)
    		{
    			cout<<L[i][j]<<" ";
    		}
    		cout<<"\n";
    	}
	}


	else if(strcmp(argv[1],"probability")==0)
	{
		if(argc!=5)
		{
			cout<<"Input should be of the form: probability sigmoid/softmax vector.txt size_of_vector"<<endl;
			return 0;
		}
		int a=stoi(argv[4]);
		if(a<=0)
		{
			cout<<"size of a vector should be greater than 0"<<endl;
			return 0;
		}
		float *A =new float [a];
		int i=0;
		fin.open(argv[3]);
		if (!fin)
        	throw std::runtime_error("file not found");
		while((!fin.eof())&& (i<a))
		{
			fin>>A[i];
			i++;
		}
		fin.close();
		int flag=1;
		if(strcmp(argv[2],"sigmoid")==0)
			flag=0;
		else if(strcmp(argv[2],"softmax")==1)
			{
				cout<<"Invalid subfunction input "<<argv[2]<<"\n Valid inputs: sigmoid, softmax"<<endl;
				return 0;
			}
		probability(A,a,flag);	
		for(int i=0;i<a;i++)
			cout<<A[i]<<" ";
		cout<<endl;
	}

	else if(strcmp(argv[1],"lenet")==0)
	{
		if(argc!=3)
		{
			cout<<"Input should be of the form: lenet input.txt"<<endl;
			return 0;
		}

		float **I =new float*[28];		//I is the input matrix (I=input)
		for(int i=0;i<28;i++)
		{
			I[i]=new float[28];
		}

		float ***Kernel1 =new float**[20];		
		for(int i=0;i<20;i++)
		{
			Kernel1[i]=new float*[5];
			for(int j=0;j<5;j++)
			{
				Kernel1[i][j]=new float[5];
			}
		}
		
		float ***C1 =new float**[20];		//C1 is the result after conv_1
		for(int i=0;i<20;i++)
		{
			C1[i]=new float*[24];
			for(int j=0;j<24;j++)
			{
				C1[i][j]=new float[24];
			}
		}

		float *Bias1=new float[20];

		fin.open(argv[2]);
		if (!fin)
        	throw std::runtime_error("file not found");
		int i=0;
		int j=0;
		while((!fin.eof())&&(j<28))
		{
			fin>>I[j][i];			
			i++;
			if(i==28)
			{
				j++;
				i=0;
			}
		}
		fin.close();

		fin.open("conv1.txt");
		if (!fin)
        	throw std::runtime_error("file not found");
		i=0;
		j=0;
		int k=0;
		while((!fin.eof())&&(k<40))		//input for Kernel1 and Bias1
		{
			if(k>=20)
			{
				fin>>Bias1[k-20];
				k++;
			}
			else
			{
				fin>>Kernel1[k][j][i];
				i++;
				if(i==5)
				{
					j++;
					if(j==5)
					{
						k++;
						j=0;
					}
					i=0;
				}
			}
		}
		fin.close();
		
		for(int i=0;i<20;i++)
		{
			lenetconv(I,Kernel1[i],28,5,C1[i]);
		}	
		for(int i=0;i<20;i++)
		{
			for(int j=0;j<24;j++)
			{
				for(int k=0;k<24;k++)
				{
					C1[i][j][k]=C1[i][j][k] + Bias1[i];
				}
			}
		}
		//Conv_1 completed (in C1)

		float ***A1 =new float**[20];		// A1 is the output matrix after pool_1 (A=answer) 
		for(int i=0;i<20;i++)
		{
			A1[i]=new float*[12];
			for(int j=0;j<12;j++)
			{
				A1[i][j]=new float[12];
			}
		}
		for(int i=0;i<20;i++)
		{
			subsampling(C1[i],24,12,A1[i],0);
		}
	
		//pool_1 completed(in A1)

		float ****Kernel2 =new float***[50];		
		for(int i=0;i<50;i++)
		{
			Kernel2[i]=new float**[20];
			for(int j=0;j<20;j++)
			{
				Kernel2[i][j]=new float*[5];
				for(int k=0;k<5;k++)
				{
					Kernel2[i][j][k] =new float[5];
				}
			}
		}

		float *Bias2=new float[50];

		float ****C2_temp =new float***[50];		//C2_temp is the intermediate matrix for C2
		for(int i=0;i<50;i++)
		{
			C2_temp[i]=new float**[20];
			for(int j=0;j<20;j++)
			{
				C2_temp[i][j]=new float*[8];
				for(int k=0;k<8;k++)
				{
					C2_temp[i][j][k] =new float[8];
				}
			}
		}

		float ***C2 =new float**[50];		//C2 is the result after conv_2
		for(int i=0;i<50;i++)
		{
			C2[i]=new float*[8];
			for(int j=0;j<8;j++)
			{
				C2[i][j]=new float[8];
			}
		}

		fin.open("conv2.txt");
		if (!fin)
        	throw std::runtime_error("file not found");
		i=0;
		j=0;
		k=0;
		int l=0;
		while((!fin.eof())&&(l<100))		//input for Kernel2 and Bias2
		{
			if(l>=50)
			{
				fin>>Bias2[l-50];
				l++;
			}
			else
			{
				fin>>Kernel2[l][k][j][i];
				i++;
				if(i==5)
				{
					j++;
					if(j==5)
					{
						k++;
						if(k==20)
						{
							l++;
							k=0;
						}
						j=0;
					}
					i=0;
				}
			}
		}
		fin.close();

		for(int i=0;i<50;i++)
		{
			for(int j=0;j<20;j++)
			{
				lenetconv(A1[j],Kernel2[i][j],12,5,C2_temp[i][j]);
			}
		}	

		for(int i=0;i<50;i++)
		{
			for(int k=0;k<8;k++)
			{
				for(int l=0;l<8;l++)
				{
					for(int j=0;j<20;j++)
					{
						C2[i][k][l]=C2[i][k][l] + C2_temp[i][j][k][l];
					}
					C2[i][k][l]=C2[i][k][l]+Bias2[i];
				}
			}
		}

		//Conv_2 completed(in C2)	

		float ***A2 =new float**[50];		// A2 is the output matrix after pool_2 (A=answer) 
		for(int i=0;i<50;i++)
		{
			A2[i]=new float*[4];
			for(int j=0;j<4;j++)
			{
				A2[i][j]=new float[4];
			}
		}	

		for(int i=0;i<50;i++)
		{
			subsampling(C2[i],8,4,A2[i],0);
		}	

		//pool_2 completed(in A2)

		float ****Kernel3 =new float***[500];		
		for(int i=0;i<500;i++)
		{
			Kernel3[i]=new float**[50];
			for(int j=0;j<50;j++)
			{
				Kernel3[i][j]=new float*[4];
				for(int k=0;k<4;k++)
				{
					Kernel3[i][j][k] =new float[4];
				}
			}
		}

		float *Bias3=new float[500];

		float ****C3_temp =new float***[500];		//C3_temp is the intermediate matrix for C3
		for(int i=0;i<500;i++)
		{
			C3_temp[i]=new float**[50];
			for(int j=0;j<50;j++)
			{
				C3_temp[i][j]=new float*[1];
				for(int k=0;k<8;k++)
				{
					C3_temp[i][j][k] =new float[1];
				}
			}
		}

		float ***C3 =new float**[500];		//C3 is the result after fc_1
		for(int i=0;i<500;i++)
		{
			C3[i]=new float*[1];
			for(int j=0;j<1;j++)
			{
				C3[i][j]=new float[1];
			}
		}
		fin.open("fc1.txt");
		if (!fin)
        	throw std::runtime_error("file not found");

		i=0;
		j=0;
		k=0;
		l=0;
		while((!fin.eof())&&(l<1000))		//input for Kernel2 and Bias2
		{
			if(l>=500)
			{
				fin>>Bias3[l-500];
				l++;
			}
			else
			{
				fin>>Kernel3[l][k][j][i];
				i++;
				if(i==4)
				{
					j++;
					if(j==4)
					{
						k++;
						if(k==50)
						{
							l++;
							k=0;
						}
						j=0;
					}
					i=0;
				}
			}
		}
		fin.close();

		for(int i=0;i<500;i++)
		{
			for(int j=0;j<50;j++)
			{
				lenetconv(A2[j],Kernel3[i][j],4,4,C3_temp[i][j]);
			}
		}	

		for(int i=0;i<500;i++)
		{
			for(int k=0;k<1;k++)
			{
				for(int l=0;l<1;l++)
				{
					for(int j=0;j<50;j++)
					{	
						C3[i][k][l]=C3[i][k][l] + C3_temp[i][j][k][l];
					}
					C3[i][k][l]=C3[i][k][l]+Bias3[i];
				}
			}
		}	

		for(int i=0; i<500;i++)
		{
			activation(C3[i],1,1,0);
		}	

		//fc1_completed in C3


		float ****Kernel4 =new float***[10];		
		for(int i=0;i<10;i++)
		{
			Kernel4[i]=new float**[500];
			for(int j=0;j<500;j++)
			{
				Kernel4[i][j]=new float*[1];
				for(int k=0;k<1;k++)
				{
					Kernel4[i][j][k] =new float[1];
				}
			}
		}

		float *Bias4=new float[10];

		float ****C4_temp =new float***[10];		//C4_temp is the intermediate matrix for C4
		for(int i=0;i<10;i++)
		{
			C4_temp[i]=new float**[500];
			for(int j=0;j<500;j++)
			{
				C4_temp[i][j]=new float*[1];
				for(int k=0;k<8;k++)
				{
					C4_temp[i][j][k] =new float[1];
				}
			}
		}

		float *C4 =new float[10];		//C4 is the result after fc_2

		fin.open("fc2.txt");
		if (!fin)
        	throw std::runtime_error("file not found");
		i=0;
		j=0;
		k=0;
		l=0;
		while((!fin.eof())&&(l<20))		//input for Kernel2 and Bias2
		{
			if(l>=10)
			{
				fin>>Bias4[l-10];
				l++;
			}
			else
			{
				fin>>Kernel4[l][k][j][i];
				i++;
				if(i==1)
				{
					j++;
					if(j==1)
					{
						k++;
						if(k==500)
						{
							l++;
							k=0;
						}
						j=0;
					}
					i=0;
				}
			}
		}
		fin.close();

		for(int i=0;i<10;i++)
		{
			for(int j=0;j<500;j++)
			{
				lenetconv(C3[j],Kernel4[i][j],1,1,C4_temp[i][j]);
			}
		}	

		for(int i=0;i<10;i++)
		{
			for(int k=0;k<1;k++)
			{
				for(int l=0;l<1;l++)
				{
					for(int j=0;j<500;j++)
					{
						C4[i]=C4[i] + C4_temp[i][j][k][l];
					}
					C4[i]=C4[i]+Bias4[i];
				}
			}
		}

		float *C5 =new float[10];
		for(int i=0;i<10;i++)
		{		
			C5[i]=C4[i];	
		}

		probability(C4,10,1);
		float temp=-1.0;
		int f=-1;
		for(int j=0;j<5;j++)
		{
			for(int i=0;i<10;i++)
			{
				if(temp<C4[i])
				{
					temp=C4[i];
					f=i;
				}
			}
			cout<<"CPU_TOP:"<<endl<<C4[f]*100<<" class "<<f<<" output "<<C5[f]<<endl;
			C4[f]=-1.0;	
			temp=-1.0;
		}

	

	}
	else
	{
		cout<<"Invalid function input "<<argv[1]<<"\n Valid function inputs: convolution_withoutpadding, convolution_withpadding, convolution_withoutpadding_matrixmult, convolution_withpadding_matrixmult, activation, subsampling, probability"<<endl;
		return 0;
	}
	
	return 0;
}
