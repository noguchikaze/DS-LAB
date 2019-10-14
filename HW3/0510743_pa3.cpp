#include<bits/stdc++.h>
using namespace std;
class Poly;
class Poly_node
{
	public:
		int order;
		int coeff;
		Poly_node():coeff(0), order(0){}
		Poly_node(int a, int b)
		{
			order = a;
			coeff = b;
		}
		~ Poly_node(){}
};//end of class Poly_node

class Poly
{
	public:
		Poly()
		{ term = 0; }
		Poly(const Poly& a)//copy ctor
		{
			list<Poly_node>::const_iterator	pit;
			term = a.term;
			for(pit = a.node.begin(); pit != a.node.end(); pit++)
			{
				push_back(Poly_node(pit->order, pit->coeff));
			}
		}
		~ Poly()
		{
			list<Poly_node>::iterator first;
			for( first = node.begin(); first != node.end();)	//if first == NULL break
			{
				//last = first;	//let last point to the same node as first node
				first = node.erase(first);	//delete the current node
				first ++;	//let the first pointer points to next pointer
			}
		}
		void push_back(Poly_node);
		list<Poly_node> node;
		int term;
		Poly Add_poly(const Poly&);
		Poly Sub_poly(const Poly&);
		Poly Mul_poly(const Poly&);
		void print_poly();

};//end of class Poly

int main(int argc, char* argv[])
{
	if(!argv[1])
	{
		cout<<"The file doesn't existed."<<endl;
		exit(0);
	}
	int count = 0;
	ifstream  fin(argv[1],ios::in);
	ofstream  fout(argv[2],ios::out);
	char  op; //operator
	int terms;  // to store the terms read from the file
	int order_in, coeff_in;
	Poly  poly_sum;
	Poly_node  poly_node_temp;
	list<Poly_node>:: const_iterator pit2;  //iterator accessing poly_sum

	fin >> terms; //read in the terms of the following polynomial
	for(int i = 0; i < terms; i++)
	{
		fin >> coeff_in >> order_in;
		if(coeff_in != 0)
			poly_sum.push_back(Poly_node(order_in, coeff_in));
	}

	poly_sum.term = poly_sum.node.size(); //to get rid of zero coeff

	//for(int a = 0; a < 10; a++)
	while(fin >> op >> terms)
	{
		Poly  poly_node_temp1;  //put the list ctor here to avoid the situation that i have to delet it everytime
		for(int i = 0; i < terms; i++)
		{
			fin >> coeff_in >> order_in;  //read in the exp and coeff
			poly_node_temp1.push_back(Poly_node(order_in, coeff_in)); //add to the templist
		}//end of for

		poly_node_temp1.term = poly_node_temp1.node.size();

		if(op == '+')
		{
			poly_sum = poly_sum.Add_poly(poly_node_temp1); //add two lists together
			continue;
		}
		else if(op == '-')
		{
			poly_sum = poly_sum.Sub_poly(poly_node_temp1); //poly_sum - poly_node_temp
		}
		else if(op == '*')
		{
			poly_sum = poly_sum.Mul_poly(poly_node_temp1);
		}

	}//end of while
	//after all the operations it's time to print them out

	//poly_sum.print_poly();	//it's cout function
	poly_sum.term = poly_sum.node.size();
	for( pit2 = poly_sum.node.begin(); pit2 != poly_sum.node.end(); pit2++)
	{
		if(pit2->coeff == 0)
		{
			poly_sum.term --;
		}
	}
	fout << poly_sum.term << '\n';
	pit2 = poly_sum.node.begin();
	for(int i = 0; i < poly_sum.node.size(); i++, pit2 ++)
	{
		//fout << pit2->coeff << ' ' << pit2->order << '\n';
		if(pit2->coeff != 0)  // as long as the coeff is not zero that it exists
		{
			fout << pit2->coeff << ' ' << pit2->order << '\n';
		}
	}//end of for
	fin.close();
	fout.close();
}//end of main


Poly Poly::Mul_poly(const Poly& muller)
{
	list<Poly_node>::const_iterator i,j;
	Poly poly_sum;
	// start the multiplication from the first term of muller
	for(j = muller.node.begin(); j != muller.node.end(); j++)
	{//muller = MUL(bn Xn), this = MUL(am, Xm)
		Poly poly_temp;
		int exp = j->order;	//exp = j
		int coe = j->coeff;	//coe = bj
		//cout<<"Muller coeff, order = (" << coe << ',' << exp << ')'<<endl;
		for(i = node.begin(); i != node.end(); i++)
		{//start from a0 ends at am
			//cout<<"Mul coeff, order = (" << i->coeff << ',' << i->order << ')'<<endl;
			Poly_node poly_node_temp;
			poly_node_temp.coeff = (i->coeff)*coe;	//coeff = ai*bj
			poly_node_temp.order = (i->order)+exp;	//order = i*j
			poly_temp.push_back(poly_node_temp);	//push into temp of mul
		}//end of for, that is we have A*bj in poly_temp
		poly_sum = poly_sum.Add_poly(poly_temp);
		//CAUTION!!!!!!!!!sum = NULL for the first time
	}//end of for
	poly_sum.print_poly();
	return	poly_sum;
}

Poly  Poly::Add_poly(const Poly& adder)
{
	list<Poly_node>::const_iterator i,j;  //iterator
	Poly  poly_temp;
	Poly_node poly_node_temp;
	i = node.begin();
	j = adder.node.begin();
	//check if empty
	/*  if(adder.term == 0)
	    {
	    for(; i != node.end() ; i++)
	    {
	    poly_temp.push_back(*i);
	    }
	    return poly_temp;  //if empty then return sum += sum
	    }*/
	//not empty so let's start to add two poly together
	while( i != node.end() || j != adder.node.end())
	{//as long as either i or j is not empty that it can enter the loop
		if( i == node.end())
		{
			for(; j != adder.node.end(); j++)
			{
				poly_temp.push_back(*j);  //j points to each node of list in adder
			}
		}
		else if( j == adder.node.end())
		{
			for(; i != node.end(); i++)
			{
				poly_temp.push_back(*i);
			}
		}
		else if( i->order < j->order)
		{
			if(j->order != 0)
			{
				poly_temp.push_back(*j);
			}
			j++;
		}
		else if( i->order > j->order)
		{
			poly_temp.push_back(*i);
			i++;
		}
		else if( i->order == j->order)
		{
			poly_node_temp.order = i-> order;
			poly_node_temp.coeff = (i->coeff) + (j->coeff);
			if(poly_node_temp.coeff != 0)
			{
				poly_temp.push_back(poly_node_temp);
			}
			i++;  j++;
		}
	}//end of while

	return  poly_temp;
}


Poly  Poly::Sub_poly(const Poly& subber)
{
	list<Poly_node>::const_iterator i,j;  //iterator
	Poly  poly_temp;
	Poly_node poly_node_temp;
	i = node.begin();
	j = subber.node.begin();
	//not empty so let's start to add two poly together
	while( i != node.end() || j != subber.node.end())
	{//as long as either i or j is not empty that it can enter the loop
		if( i == node.end())//the original sum list is empty
		{
			for(; j != subber.node.end(); j++)
			{
				poly_node_temp.order = j->order;
				poly_node_temp.coeff = (j->coeff)*(-1);
				poly_temp.push_back(poly_node_temp);
			}
		}
		else if( j == subber.node.end())
		{
			for(; i != node.end(); i++)
			{
				poly_temp.push_back(*i);
			}
		}
		else if( i->order < j->order)
		{
			if(j->order != 0)
			{
				poly_node_temp.order = j->order;
				poly_node_temp.coeff = (j->coeff)*(-1);
				poly_temp.push_back(poly_node_temp);
			}
			j++;
		}
		else if( i->order > j->order)
		{
			poly_temp.push_back(*i);
			i++;
		}
		else if( i->order == j->order)
		{
			poly_node_temp.order = i-> order;
			poly_node_temp.coeff = (i->coeff) - (j->coeff);
			if(poly_node_temp.coeff != 0)
			{
				poly_temp.push_back(poly_node_temp);
			}
			i++;  j++;
		}
	}//end of while
	return  poly_temp;
}


void Poly::push_back(Poly_node a)
{
	term++;
	node.push_back(a);
}

void Poly::print_poly()
{
	list<Poly_node>::const_iterator pit;
	for(pit = node.begin(); pit != node.end(); pit++)
	{
		if(pit->coeff != 0)
		{
		}
	}
}
