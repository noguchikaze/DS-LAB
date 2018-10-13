#include<bits/stdc++.h>
using namespace std;

void method1(char*, char*); //the method using stack
void method2(char*, char*); //the method using queue
enum {E = 0, S, W, N};  //enumerates the direction
#define PAUSE{ cout<<"press any key to contunue"<<endl; fgetc(stdin);}
struct Mouse
{
	int x,y,dir;  //coordinate current direction of the mouse
	Mouse()
	{ x = 0; y = 0; dir = N;}
	Mouse(int a, int b, int c) //constructor
	{
		x = a;  y = b; dir = c;
	}
};
struct Mice	//for the queue in method2
{
	int x,y,steps;
	int trace_num;
	Mice(){ x=0; y=0; steps=0; }
	Mice(int a, int b, int c)
	{ x = a; y = b; steps = c; trace_num = 0;}
	Mice(int a, int b, int c, int d)
	{ x = a; y = b; steps = c; trace_num = d;}
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
		method1(argv[1],argv[2]);
		method2(argv[1],argv[3]);
	}
	else
		cout<<"wrong input"<<endl;

	return 0;
}//end of main
void method2(char* input, char* output)
{
	//initialize
	queue<Mice> que;	//stores x,y,steps
	char block;	//to read in the element from maze
	int direction = 0;	//to store the dir
	int l,w;	//length and width of the maze
	int sx,sy;	//start x and y
	int trace_cnt = -1;;	//counter of trace_num
	int zeros = 0;	//calculate zeros to new trace[]
	Mouse** trace;	//info of "last x,y" & "Last dir"
	Mice last_pos;	//last position
	ifstream fin;
	ofstream fout;
	//-----------offset tabel----------------
	offset move[4];
	move[E].hor = 1;  move[E].ver = 0;
	move[S].hor = 0;  move[S].ver = 1;
	move[W].hor = -1; move[W].ver = 0;
	move[N].hor = 0;  move[N].ver = -1;
	//------------done setting---------------

	fin.open(input);
	fout.open(output);
	fin>>l>>w;  //read in w:vertical l:horizontal
	//create a matrix of type 'char'
	char**  mark = new char*[w];
	for(int i = 0; i < w; i++)
	{
		mark[i] = new char[l];
	}
	int** maze = new int*[w];
	for(int i = 0; i < w; i++)
	{
		maze[i] = new int[l];
	}
	//read the maze from file and assign value to the mark
	for(int i = 0; i < w; i++) //at least read the amount of the matrix
	{
		cout<<endl;
		for(int j = 0; j < l; j++)
		{
			fin>>block;
			if(block == '2')
			{
				maze[i][j] = -1;
			}
			else if(block == 'S')
			{
				maze[i][j] = -2;
				sx = i;	sy = j;	//store the starting coordinate
				que.push(Mice(i,j,0));	//current position and steps
			}
			else if(block == '0')
			{	maze[i][j] = 0; 	}
			else if(block == 'E')
			{	maze[i][j] = -3;	}
		}//end of for
	}//end of for

	trace = new Mouse*[w];	//to record the last coordinate and direction
	for(int i = 0; i < w; i++)
	{	trace[i] = new Mouse[l]; }	//build a big matrix of trace
	//the main function for loop
	for(;;)
	{
		last_pos = que.front();	//take out the first element
		que.pop();	//pop out an element
		//direction = 0;	//make direction back to East
		for( direction = 0; direction < 4; direction ++)	//while there are still other dir
		{
			//start from east, step out in current direction
			int i = last_pos.x + move[direction].ver;	//next x
			int j = last_pos.y + move[direction].hor;	//next y
			//check if next x and y have their way
			if( maze[i][j] == -3 )	//get to the end
			{
				trace[i][j] = Mouse(last_pos.x, last_pos.y, direction);
				cout<<"shortest road success! It takes "<< last_pos.steps + 1 << "steps to get to goal"<<endl;
				//trace back with the coordinate now in (i,j)
				for(direction = 0; direction < 4; direction ++)
				{
					
				}
				for(int k = 0; k < last_pos.steps + 1; k++)
				{
					if(maze[i][j] == -3 || maze[i][j] == -2)
					{
						
					}
					else
					{
						maze[i][j] = -4;
					}
					//one step backward
					cout << '(' << i << ',' << j << ')'
					<<" changes to (" << trace[i][j].x<<',' << trace[i][j].y <<')'<<endl;
					i = trace[i][j].x;
					j = trace[i][j].y;

				}
				cout<<"trace[1][4](x,y) = (" << trace[1][4].x << ',' << trace[1][4].y <<endl; 
				cout<<"maze[1][4]= " << maze[1][4] <<endl; 
				//print out the trace!!
				for(int i = 0; i < w; i++)
				{
					for(int j = 0; j < l; j++)
					{
						cout << '(' << trace[i][j].x << ',' << trace[i][j].y << ") ";
					}//end of inner for
					cout<<'\n';
				}//end of output maze
				//print out the maze!!!
				for(int i = 0; i < w; i++)
				{
					for(int j = 0; j < l; j++)
					{
						if(maze[i][j] == -1)
						{
							fout <<'2'<< ' ';
							cout <<'@'<< ' ';
						}
						else if(maze[i][j] == -2)
						{	
							cout << 'S' << ' ';
							fout << 'S' << ' ';
						}
						else if(maze[i][j] == -3)
						{	
							cout << 'E' << ' ';
							fout << 'E' << ' ';
						}
						else if(maze[i][j] == -4)
						{
							fout << 1 << ' ';
							cout << 1 << ' ';
						}
						else
						{
							fout << 0 << ' ';
							cout << 0 << ' ';
						}
					}//end of inner fo
					cout<<'\n';
					fout<<'\n';
				}//end of output maze
				return;
			}//end of if END
			else if (maze[i][j] == 0)	//there is a way
			{
				
				que.push(Mice(i, j, last_pos.steps + 1));	//push into queue
				//element put into trace is last coordinate and direction
				trace[i][j] = Mouse(last_pos.x, last_pos.y, direction);
				maze[i][j] = last_pos.steps + 1;
//				cout << '(' << i << ',' << j << ") comes from " 
//				<< '(' << last_pos.x << ',' << last_pos.y << ')' << endl;
			}//end of else if there is a way
			else	//if encountered a wall or already marked
			{ ;}	// do nothing
		}//end of inner for(;;)
	}//end of outer for(;;)
}//end of method2

void method1( char* input, char* output)
{//in this method, x = col = ver; y = row = hor
	//announce the operands in the code//
	bool flag = 0;
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

	//read the maze from file and assign value to the mark
	for(int i = 0; i < w; i++) //at least read the amount of the matrix
	{
		cout<<endl;
		for(int j = 0; j < l; j++)
		{
			fin>>block;
			mark[i][j] = block;
			cout<<mark[i][j]<<' ';
			if(block == 'S') //START
			{
				step.push(Mouse(i-1,j,N)); //step is a type of Mouse
				direction = -1;
			}//end of if
		}//end of for
	}//end of for


	//start to walk in the maze
	while(!step.empty())
	{

		last_move = step.top();  //last step including the direction
		step.pop(); //pop out last move including direction
		if(flag != 0)
		{
			mark[last_move.x][last_move.y] = '0';
		}
		flag++;
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
