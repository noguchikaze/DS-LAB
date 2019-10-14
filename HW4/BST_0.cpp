#include<bits/stdc++.h>
using namespace std;

struct node
{
  node* parent;
  node* left_ch;
  node* right_ch;
  int data;

  node():data(0)
  { left_ch = NULL; right_ch = NULL; parent = NULL; };
  ~node(){};
  node(int d)
  { data = d; }
  node(const node& node2){  data = node2.data; }  //copy ctor
};//end of struct node

struct BST  //binary search tree
{
  BST(){  root = NULL; }  //constructor
  ~BST(){}
  /*BST(const node& a)
  {
    node* node_temp = new node(a->data);
    root =
  }*/
  node* root;
  void insert(int, node*); //have to print out to file
  void delete(const node&); //have to print out to file
  int search(int);
  //void search_rank();
  bool is_empty()
  {
    if(root = NULL)
    { return true; }
    return false;
  }
};//end of struct BST

node* find_right_min(node* c)
{
  node* current = c->right_ch, *parent = 0;
  while( current != NULL )
  {
    parent = current;
    current = current->left_ch;
  }//end of while
  return parent;
}//end of find_right_min

node* find_left_max(node* c)
{//find MAX key in c->left_ch
  node *current = c->left_ch, *parent = 0;
  while(current != NULL)
  {//if current exists ===>>> points to next bigger key
    parent = current;
    current = current->right_ch;  //keep traversing to the right child
  }//end of while
  //when current->NULL and parent -> left_max that it breaks
  //so parent is what we are finding for
  return parent;  //even if c->left_ch is NULL that it will return NULL
}//end of find_left_max

int main(int argc, char** argv)
{
  ifstream fin; ofstream fout;
  fin.open(argv[1]);  fout.open(argv[2]);
  char op;  //1 to 4 operators
  int rin;  //data read in
  int temp = 0;
  BST tree;
  node node_temp;

  //while loop to read the file
  while(fin >> op >> rin) //operator and data
  {
    if(rin == 0)  //0 is invalid for BST
    {
      continue;
    }
    node_temp.data = rin;
    //choose the operation
    if( op == '1')  //insertion
    {
      tree.insert(rin, node_temp);
    }
    else if( op == '2') //deletion
    {
      tree.delete(node_temp);
    }
    else if( op == '3') //search
    {
      temp = tree.search(rin);
      if(temp != -1)
        fout << temp << ' ' << rin << endl;
    }
    else if(op == '4')  //search by rank
    {

    }
    else
    { cout << op << " is an invalid input" << endl;}
  }//end of while

}//end of main

void BST::delete(int target)
{
}//end of delete

int BST::search(int target)
{
  node *c = root, *p = 0;
  int level = 0;
  while(c != NULL)  //current node is not NULL
  {
    p = c;
    if(target == c->data)
      return level;
    else if(target < c->data)
    {
      c = c->left_ch;
    }
    else if(target > c->data)
    {
      c = c->right_ch;
    }
    level++;
  }//end of while
  cout<<"SEARCH :: nothing is found"<<endl;
  return -1;
}//end of search

void BST::insert(int x, node* node_in)
{
  node *p = root, *q = 0;

  while(p){//while root is not NULL
    q = p;  //q will be p's parent at last
    if(node_in.data == p->data)//an existing data
    {
      cout<<"data already exist"<<endl;
      return void;
    }
    if(node_in.data < root->data)
    {
      p = p->left_ch;
    }
    else if(node_in.data > root -> data)
    {
      p = p->right_ch;
    }
    else
    { cout<< "someting must be wrong" << endl;}
  }//end of while

  p = new node;
  p->left_ch = 0; p->right_ch = 0; p->data = x; //copy the data
  //check if p is q's left child or right child
  if(is_empty())
  {
    root = p; //p will be the root if the tree is empty
  }
  else if( p->data < q->data)
  {
    p->parent = q;  q->left_ch = p;
  }
  else
  {
    q->right_ch = p;
  }
}//end of insert
