#include<bits/stdc++.h>
using namespace std;
class Poly;
class Poly_node
{
public:
  int order;
  int coeff;
  Poly_node(int a, int b)
  {
    order = a;
    coeff = b;
  }
  ~ Poly(){}
};//end of class Poly_node

class Poly
{
public:
  Poly()
  { term = 0;  }
  ~ Poly();
  void push_back(Poly_node);
  list<Poly_node> node;
  int term;
  Poly Add_poly(const Poly&);
  Poly Sub_poly(const Poly&);
  Poly Mul_poly(const Poly&);

};//end of class Poly

int main(int argc, char* argv[])
{
  if(!argv[1])
	{
		cout<<"The file doesn't existed."<<endl;
		exit(0);
	}
  ifstream  fin;
  ofstream  fout;
  char  op; //operator
  int terms;  // to store the terms read from the file
  int order_in, coeff_in;
  Poly  poly_sum;
  Poly_node  poly_node_temp;
//  list<Poly>::const iterator pit1;  //iterator accessing poly_node_temp
//  list<Poly>::const iterator pit2;  //iterator accessing poly_sum
  fin.open(argv[1]);
  fout.open(argv[2]);

  fin >> terms; //read in the terms of the following polynomial
  for(int i = 0; i < terms; i++)
  {
      fin >> order_in >> coeff_in;
      if(coeff_in != 0)
      poly_sum.push_back(Poly_node(order_in, coeff_in));
  }
  poly_sum.term = poly_sum.node.size(); //to get rid of zero coeff

  while(fin >> op >> terms)
  {
    Poly  poly_node_temp1;  //put the list ctor here to avoid the situation that i have to delet it everytime
    fin >> order_in >> coeff_in; //read in the terms of the coefficient
    for(int i = 0; i < terms; i++)
    {
      fin >> order_in >> coeff_in;  //read in the exp and coeff
      poly_node_temp1.push_back(Poly_node(order_in, coeff_in)); //add to the templist
    }//end of for

    poly_node_temp1.term = poly_node_temp1.node.size();

      if(op == '+')
      {
          poly_sum = poly_sum.Add_poly(poly_node_temp1); //add two lists together
      }
      else if(op == '-')
      {
          poly_sum = poly_sum.Sub_poly(poly_node_temp1); //poly_sum - poly_node_temp
      }
      else if(op == '*')
      {
          poly_sum = poly_sum.Mul_poly(poly_node_temp1)
      }

  }//end of while
  //after all the operations it's time to print them out
  fout << poly_sum.size() << '\n';
  pit2 = poly_sum.begin();
  for(int i = 0; i < poly_sum.size(); i++, pit2 ++)
  {
    if(*pit2.coeff != 0)  // as long as the coeff is not zero that it exists
    {
      fout << poly_sum.coeff << ' ' << poly_sum.order << '\n'
    }
  }//end of for
  fin.close();
  fout.close();
}//end of main

Poly  Poly::Add_poly(const Poly& adder)
{
  list<Poly>::const iterator i,j;  //iterator
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
      poly_temp.push_back(*j);
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
  list<Poly>::const iterator i,j;  //iterator
  Poly  poly_temp;
  Poly_node poly_node_temp;
  i = node.begin();
  j = subber.node.begin();
  //not empty so let's start to add two poly together
  while( i != node.end() || j != subber.node.end())
  {//as long as either i or j is not empty that it can enter the loop
    if( i == node.end())
    {
      for(; j != subber.node.end(); j++)
      {
        poly_temp.push_back(*j);  //j points to each node of list in subber
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
      poly_temp.push_back(*j);
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
