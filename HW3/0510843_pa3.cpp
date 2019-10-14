#include<cstdlib>
#include<fstream>
#include<iostream>
#include<list>
using namespace std;
class poly_node;
class poly		//polynomial
{
	friend ostream& operator<<(ostream& os, poly& a);
	public:
		poly();//constructor
		//poly(poly &a);
		~poly();
		poly& operator=(poly);
		poly operator+(const poly&);
		poly operator-(const poly&);
		poly operator*(const poly&);
		list<poly_node> node;
		void push_back(poly_node);
		int term;
};
class poly_node
{
	friend ostream& operator<<(ostream& os, poly_node& a);
	public:
		poly_node();
		~poly_node();
		//poly_node& operator=(poly_node&);
		int expo;
		int coeff;
};
ostream& operator<<(ostream& os, poly& a);
ostream& operator<<(ostream& os, poly_node& a);
int main(int argc, char* argv[])
{
	if(!argv[1])
	{
		cout<<"The file doesn't existed."<<endl;
		exit(0);
	}
	ifstream ifile(argv[1],ios::in);
	ofstream ofile(argv[2],ios::out);
	int number_node;
	int exponential;
	int coefficient;
	int i;
	char oper;
	poly_node poly_node_tmp;
	poly poly_sum;
	ifile>>number_node;
	for(i=0;i<number_node;i++)
	{
		ifile>>coefficient>>exponential;
		poly_node_tmp.expo=exponential;
		poly_node_tmp.coeff=coefficient;
		if(coefficient!=0)
			poly_sum.push_back(poly_node_tmp);
	}
	//cout<<"poly_temp1:"<<endl<<poly_sum<<endl;
	int fffff=0;
	while(ifile>>oper>>number_node)
	{
		poly poly_tmp1;
		for(i=0;i<number_node;i++)
		{
			ifile>>coefficient>>exponential;
			poly_node_tmp.expo=exponential;
			poly_node_tmp.coeff=coefficient;
			if(coefficient!=0)
				poly_tmp1.push_back(poly_node_tmp);
		}
		//cout<<"[poly_temp1:"<<endl<<poly_tmp1<<"]"<<endl;
		switch(oper)
		{
			case '+':
				//cout<<"[i= "<<i<<"]"<<endl;
				poly_sum=poly_sum+poly_tmp1;
				//cout<<"poly_sum:"<<endl<<poly_sum<<endl;
				//cout<<"[+++][poly_sum:"<<endl<<poly_sum<<"]"<<endl;
				//cout<<"poly_sum.term = "<<poly_sum.term<<endl;
				break;
			case '-':
				poly_sum=poly_sum-poly_tmp1;
				//cout<<"poly_sum:"<<endl<<poly_sum<<endl;
				//cout<<"[---][poly_sum:"<<endl<<poly_sum<<"]"<<endl;
				//cout<<"poly_sum.term = "<<poly_sum.term<<endl;
				break;
			case '*':
				poly_sum=poly_sum*poly_tmp1;
				//cout<<"poly_sum:"<<endl<<poly_sum<<endl;
				//cout<<"[***][poly_sum:"<<endl<<poly_sum<<"]"<<endl;
				//cout<<"poly_sum.term = "<<poly_sum.term<<endl;
				break;
		}
		//cout<<fffff<<endl<<"poly_sum.term"<<poly_sum.term<<endl;
		//fffff++;
	}
	ofile<<poly_sum.term<<endl<<poly_sum;
	//cout<<poly_sum.term<<endl<<poly_sum;
	ifile.close();
	ofile.close();
}
poly::poly()
{
	//cout<<"poly is constructed"<<endl;
	term=0;
}
/*
poly::poly(poly &a)
{
	list<poly_node>::const_iterator i;
	for(i=a.node.begin();i!=a.node.end();i++)
	{
		node.push_back(*i);
		//cout<<"HIHIHIHI coeff =  "<<i->coeff<<endl;
	}
}
*/
poly::~poly()
{
	//cout<<"poly is destructed"<<endl;
}
poly& poly::operator=(poly a)
{
	swap(this->node,a.node);
	swap(this->term,a.term);
	return *this;
}
poly poly::operator+(const poly& a)
{
	list<poly_node>::const_iterator i,j;
	poly poly_temp;
	poly_node poly_node_temp;
	i=node.begin();
	j=a.node.begin();
	while(i!=node.end() || j!=a.node.end())
	{
		if(i==node.end())
		{
			for(;j!=a.node.end();j++)
				poly_temp.push_back(*j);
				//cout<<"[END-LHS]"<<endl;
				//cout<<poly_temp<<endl;
		}
		else if(j==a.node.end())
		{
			for(;i!=node.end();i++)
				poly_temp.push_back(*i);
				//cout<<"[END-RHS]"<<endl;
				//cout<<poly_temp<<endl;
		}
		else if(i->expo > j->expo)
		{
			poly_temp.push_back(*i);
			i++;
			//cout<<"[LHS]"<<endl;
			//cout<<poly_temp<<endl;
		}
		else if(i->expo < j->expo)
		{
			poly_temp.push_back(*j);
			j++;
			//cout<<"[RHS]"<<endl;
			//cout<<poly_temp<<endl;
		}
		else if(i->expo == j->expo && (i->coeff + j->coeff)!=0)
		{
			poly_node_temp.expo=i->expo;
			poly_node_temp.coeff=(i->coeff + j->coeff);
			poly_temp.push_back(poly_node_temp);
			i++;
			j++;
			//cout<<"[ADD]"<<endl;
			//cout<<poly_temp<<endl;
		}
		else if(i->expo == j->expo && (i->coeff + j->coeff)==0)
		{
			i++;
			j++;
			//cout<<"[IGNORE]"<<endl;
		}
	}
	//cout<<"poly_temp.term = "<<poly_temp.term<<endl;
	//cout<<"poly_temp_operator++++:"<<endl<<poly_temp<<endl;
	//cout<<"+++++"<<endl;
	return poly_temp;
}
poly poly::operator-(const poly& a)
{
	list<poly_node>::const_iterator i,j;
	poly poly_temp;
	poly_node poly_node_temp;
	i=node.begin();
	j=a.node.begin();
	while(i!=node.end() || j!=a.node.end())
	{
		if(i==node.end())
		{
			for(;j!=a.node.end();j++)
				poly_temp.push_back(*j);
		}
		else if(j==a.node.end())
		{
			for(;i!=node.end();i++)
				poly_temp.push_back(*i);
		}
		else if(i->expo > j->expo)
		{
			poly_temp.push_back(*i);
			i++;
		}
		else if(i->expo < j->expo)
		{
			poly_temp.push_back(*j);
			j++;
		}
		else if(i->expo == j->expo && (i->coeff - j->coeff)!=0)
		{
			poly_node_temp.expo=i->expo;
			poly_node_temp.coeff=(i->coeff - j->coeff);
			poly_temp.push_back(poly_node_temp);
			i++;
			j++;
		}
		else if(i->expo == j->expo && (i->coeff - j->coeff)==0)
		{
			i++;
			j++;
		}
		//cout<<"poly_temp_operator++++:"<<endl<<poly_temp<<endl;
	}
	//cout<<"poly_temp_operator++++:"<<endl<<poly_temp<<endl;
	//cout<<"-----"<<endl;
	return poly_temp;
}
poly poly::operator*(const poly& a)
{
	list<poly_node>::const_iterator i,j;
	poly poly_sum;
	poly_node poly_node_temp;
	i=node.begin();
	for(j=a.node.begin();j!=a.node.end();j++)
	{
		if((i->coeff * j->coeff)!=0)
		{
			poly_node_temp.expo=i->expo+j->expo;
			poly_node_temp.coeff=(i->coeff * j->coeff);
			poly_sum.push_back(poly_node_temp);
		}
	}
	i++;
	for(;i!=node.end();i++)
	{
		poly poly_temp;
		for(j=a.node.begin();j!=a.node.end();j++)
		{
			if((i->coeff * j->coeff)!=0)
			{
				poly_node_temp.expo=i->expo+j->expo;
				poly_node_temp.coeff=(i->coeff * j->coeff);
				poly_temp.push_back(poly_node_temp);
			}
		}
		poly_sum=poly_sum+poly_temp;
	}
	//cout<<"*****"<<endl;
	//cout<<"poly_temp_operator++++:"<<endl<<poly_temp<<endl;
	return poly_sum;
}
void poly::push_back(poly_node a)
{	
	term++;
 	node.push_back(a);
}
poly_node::poly_node()
{
	//cout<<"poly node is constructed"<<endl;
}
poly_node::~poly_node()
{
	//cout<<"poly node is destructed"<<endl;
}
/*
poly_node& poly_node::operator=(poly_node& a)
{
	expo=a.expo;
	coeff=a.coeff;
	return *this;
}
*/
ostream& operator<<(ostream& os, poly& a)
{
	list<poly_node>::iterator i;
	for(i=a.node.begin();i!=a.node.end();i++)
	{
		//os<<i->coeff<<"x^"<<i->expo<<endl;
		os<<i->coeff<<" "<<i->expo<<endl;
	}
	return os;
}
/*
ostream& operator<<(ostream& os, poly_node& a)
{
	os<<"exponential = "<<a.expo<<"coefficient = "<<a.coeff<<endl;
	return os;
}
*/