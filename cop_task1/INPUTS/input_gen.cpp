#include <iostream>
#include <fstream> 
#include <ctime> 
using namespace std;
int main(int argc, char** argv)
{
	srand (time(j));
	ofstream fout;
	fout.open(argv[1]);

		for(int j=0;j<stoi(argv[2]);j++)
		{
			for(int k=0;k<stoi(argv[2]);k++)
			{

				fout<<rand()%100<<" ";
			}
			fout<<endl;
		}
		//fout.close();
}