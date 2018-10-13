//這是老鼠走迷宮的概念
#include<bits/stdc++.h>
using namespace std;

void show_maze(char**);
void method1(char*, char*); //the method using stack
void method2(); //the method using queue
enum {E = 0, S, W, N};  //enumerates the direction
struct Mouse
{
	int x,y,dir;  //coordinate current direction of the mouse

	Mouse()
	{ x = 0; y = 0; dir = N;}
	Mouse(int a, int b, int c) //constructor
	{
		x = a;  y = b; dir = c;
	}

	//~Mouse(); //destructor
};
struct offset
{
	int hor;  int ver;  //horizontal and vertical
};
int main(int argc, char* argv[])
{

	
	if(argc == 3)
	{
		cout << "execute the first method"<<endl;
		method1(argv[1],argv[2]);
	}
	else if(argc == 4)
	{
		cout<<"execute both method"<<endl;
		method1(argv[1],argv[3]);
		//    method2();
	}
	else
		cout<<"wrong input"<<endl;

	return 0;
}//end of main

void method1( char* input, char* output)
{
	//announce the operands in the code//
	char block;  //the item that stores the value from matrix
	int l,w;  //represents length and width of the maze
	int sx,sy;  //start x and start y
	int direction;  //store the direction counter
	stack<Mouse> step; //create a stack storing the steps
	Mouse last_move;//the movings dir = moving direction
	ifstream  fin;
	ofstream  fout;
	//-----------offset tabel----------------
	offset move[4];
	move[E].hor = 1;  move[E].ver = 0;
	move[S].hor = 0;  move[S].ver = 1;
	move[W].hor = -1; move[W].ver = 0;
	move[N].hor = 0;  move[N].ver = -1;
	//------------done setting---------------
	fin.open(input);  //open the input file
	fout.open(output);
	fin>>l>>w;  //read in w:vertical l:horizontal
	//create a matrix of type 'Maze'
	char**  mark = new char*[w];
	for(int i = 0; i < w; i++)
	{
		mark[i] = new char[l];
	}

	cout<<"this is the maze"<<endl;
	//read the maze from file and assign value to the mark
	for(int i = 0; i < w; i++) //at least read the amount of the matrix
	{
		cout<<endl;
		for(int j = 0; j < l; j++)
		{
			fin>>block;
			mark[i][j] = block;
			//cout<<mark[i][j]<<' ';
			if(block == 'S') //START
			{
				step.push(Mouse(i-1,j,N)); //step is a type of Mouse
				direction = -1;
				sx = i; //start x
				sy = j; //start y
			}//end of if
		}//end of for
	}//end of for


	//start to walk in the maze
	while(!step.empty())
	{
		
		last_move = step.top();  //last step including the direction
		step.pop(); //pop out last move including direction
		mark[last_move.x][last_move.y] = '0';
		int row = last_move.y - move[last_move.dir].hor;  //back to last coordinate
		int col = last_move.x - move[last_move.dir].ver;  //same
		if( direction != -1)  //if not starting step
		{  direction = last_move.dir; }
		while(direction < 3) //there are more moves
		{ //shift a direction
			direction ++; //change to next direction
			row += move[direction].hor; //next y
			col += move[direction].ver; //next x
			//step out and trial
			if(mark[col][row] == 'E')
			{
				cout<<"success XD"<<endl;
				for(int i = 0; i < w; i++)
				{
					for(int j = 0; j < l; j++)
					{
						fout<<mark[i][j]<<' ';
						cout<<mark[i][j]<<' ';
					}
					fout<<'\n';
					cout<<'\n';
				}
				cout<<"s = ("<<sx<<", "<<sy<<')'<<endl;
				return;
			}
			else if(mark[col][row] == '2' )
			{
				cout<<"encounter a wall"<<endl;
				row -= move[direction].hor; //back to last position
				col -= move[direction].ver; //same
				continue;
			}
			else if(mark[col][row] == '1')
			{
				cout<<"already stepped"<<endl;
				row -= move[direction].hor;
				col -= move[direction].ver;
			}
			else if(mark[col][row] == '0')
			{
				//cout<<"step over with direction "<< direction << "and now at ( "
				//<<col<<','<<row<<" )"<<endl;
				mark[col][row] = '1'; //mark as already came
				step.push(Mouse( col , row , direction));
				cout << '(' << col  << ',' << row <<')' << endl;
				//push last position
				direction = -1; //back to try East again
			}
		}
	}//end of while
	fout.close();
	fin.close();
	
}//end of method 1

