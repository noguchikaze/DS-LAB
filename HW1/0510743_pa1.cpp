#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

bool is_prime(int n)
{
	if(n==2)
		return true;
	else
	{
	int sqr = sqrt(n);
	//cout<<"Sqrt of "<<n<<" is "<<sqr<<endl;
	for(int i = 2; i <= sqr; i++)
	{

		if(n%i != 0)
		{
	//		cout<<"n%i is "<<n%i<<" while i is "<<i<<endl;
			continue;
		}
		else
			return false;
	}
	return true;
	}
}
int main(int argc, char*argv[])
{
	ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	fout.open(argv[2]);
	int r;

	while(fin>>r||!fin.eof())
	{	
	//	fout<<"test number: "<<r<<' ';
		if(is_prime(r))	//if it is prime
			fout<<1<<'\n';
		else if(!is_prime(r))
			fout<<0<<'\n';
		else
			cout<<"error"<<endl;
	}
	fin.close();
	fout.close();
	return 0;
}
