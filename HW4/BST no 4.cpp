#include<bits/stdc++.h>
using namespace std;
#define COUNT 10
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
	//node(const node& node2){  data = node2.data; }  //copy ctor
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
	void insert(int); //have to print out to file
	void remove(int); //have to print out to file
	int search(int);
	//void search_rank();
	bool is_empty()
	{
		if(root == NULL)
		{ return true; }
		return false;
	}
	void replace(node*, node*);
	node* find(int target)
	{
		node *c = root;
		node *p = 0;
		while(c != NULL)
		{
			if( target == c->data)
				return c;
			else if(target < c->data)
			{
				p = c;
				c = c->left_ch;
			}
			else if(target > c->data)
			{
				p = c;
				c = c->right_ch;
			}
		}
		return NULL;
	}
};//end of struct BST

void print(node* root, int space);
void print2D(node* root);

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
	node node_temp;	//I think I don't even need it!
	//while loop to read the file
	while(fin >> op >> rin) //operator and data
	{
		//choose the operation
		if( op == '1')  //insertion
		{
			//cout << "INSERT :: " << rin << endl;
			tree.insert(rin);
			node* r = tree.root;
			//print2D(r);
		}
		else if( op == '2') //remove
		{
			tree.remove(rin);
			//node* r = tree.root;
			//print2D(r);
		}
		else if( op == '3') //search
		{
			temp = tree.search(rin);
			fout << temp << endl;

		}
		else if(op == '4')  //search by rank
		{
			//cout <<"ranking"<<endl;
		}
		else
		{ cout << op << " is an invalid input" << endl;}

	}//end of while
	//print2D(tree.root);

}//end of main

void BST::remove(int target)
{
	node* c = 0;
	node* left_max = 0; //the key node to take over the node deleted

	if(search(target) == -1)//if the target doesn't exist
	{
		//cout << "REMOVE :: 找不到 "<<target<< endl;
		return;
	}
	//find the target
	c = find(target);
	//cout << "target found, target = " << c->data << endl;
	if (c->left_ch == NULL)
	{
		//cout << target <<" 沒有左子樹 且";

		if (c->right_ch == NULL)	// if the target node has 0 child
		{
			//cout<<target<<" 沒有分支"<<endl;
			replace( c, 0 );
		}
		else	// the target node has only right child
		{
			//cout<<target<<" 只有右子樹"<<endl;
			replace( c , c->right_ch);
		}
	}
	else if( c->right_ch == NULL)	// the target node has only left child
	{
		//cout<<target<<" 只有左子樹"<<endl;
		replace(c, c->left_ch);
	}
	else// the target node has 2 children
	{// choose the left subtree's MAX
		//cout<<target<<" 有兩個小孩"<<endl;
		left_max = find_left_max(c);//c's left subtree's MAX node
		replace(left_max, left_max->left_ch);
		//接下來直接採取c->data = left_max的做法 不行再說
		c->data = left_max->data;
		delete left_max;
		return;
	}
	delete c;
	return;
}//end of remove

void BST::replace(node* original, node* new_node)
{
	node* parent = original->parent;
	if(parent != NULL)
	{
		if(original == parent->left_ch)
		{	parent->left_ch = new_node;	}
		else if(original == parent->right_ch)
		{	parent->right_ch = new_node;	}
		else
		{cout<<"REPLACE :: something about parent != NULL must be wrong"<<endl;}

		original->parent = NULL;
	}
	else if(parent == NULL)//original is the root
	{	root = new_node;	}
	else
	{	cout<<"REPLACE :: something about parent checking must be wrong"<<endl;}
	//only if new_node is not NULL that it needs a parent link
	if(new_node != NULL)
	{	new_node->parent = parent;	}
	original->left_ch = NULL;	original->right_ch = NULL;
}//end of replace

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
	//cout<<"SEARCH :: "<<target<<" is not found"<<endl;
	return -1;
}//end of search

void BST::insert(int x)
{
	node *p = root, *q = 0;
	if(root == NULL)
	{
		p = new node;	p->data = x;
		root = p;
		return;
	}
	while( p != NULL){//while root is not NULL
		q = p;  //q will be p's parent at last
		if( x == p->data)//an existing data
		{
			//cout<<"data already exist"<<endl;
			return;
		}
		if( x < p->data)
		{
			p = p->left_ch;
		}
		else if( x > p->data)
		{
			p = p->right_ch;
		}
		else
		{ cout<< "INSERT :: something must be wrong" << endl;}
	}//end of while

	p = new node;
	p->left_ch = 0; p->right_ch = 0; p->data = x; //copy the data
	//check if p is q's left child or right child
	p->parent = q;
	if( p->data < q->data)
	{
		q->left_ch = p;
	}
	else
	{
		q->right_ch = p;
	}
	return;
}//end of insert

void print2D(node* root)
{
	print(root, 0);
}

void print(node* root, int space)
{
	if(root == NULL)
		return;
	space+=COUNT;
	print(root->right_ch, space);
	cout<<endl;
	for(int i = COUNT; i < space; i++)
		cout<<' ';
	cout << root->data << endl;
	print(root->left_ch, space);

}//end of print
