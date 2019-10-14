#include<bits/stdc++.h>
using namespace std;
enum {E=0, S, W, N};    //east = +x; north = +y;
struct Graph
{
    int x, y, dir;   //寬長
    Graph(){    x = 0; y = 0; dir=0;   }
    Graph(int a, int b, int c)
    {   y=a; x=b; dir=c;    }
};

struct vertex
{
    int node;   //紀錄map的樣貌 1不能走 0可以走
    bool edge[4];   //紀錄ESWN的edge是否存在
    bool dir[4];    //紀錄ESWN的方向是否走過
    vertex()
    {
        node = 0;
        for(int i = 0; i < 4; i++)
        {
            edge[i] = 0;    dir[i] = 0;
        }
    }
};

struct offset
{
    short int hor, ver;
};

int main(int argc, char* argv[])
{
    ifstream fin;
    ofstream fout;
    bool flag = 0;
    int x, y;	//存長寬用的
    stack<Graph> step;  //紀錄回頭路
    queue<Graph> route; //最後要印出來的路線都存在裡面
    char vrtx;    //read in each vertex
    int edge_total; //紀錄edge是不是都被走過一次了
    fin.open(argv[1]);
    fout.open(argv[2]);
    
    fin >> x >> y;

    vertex** map = new vertex*[y];  //先建立垂直的pointer
    for( int i = 0; i < y; i++) //動態配置
    {
        map[y] = new vertex[x];
    }

    //讀進整個graph的樣子到map裡面
    for(int i = 0; i < y; i++)
    {
        for( int j = 0; j < x; j++)
        {
            fin >> vrtx;
            switch(vrtx)
            {
                case('1'):   //不存在的節點or牆壁
                    map[i][j].node = 1;
                    break;
                case('0'):   //存在的節點
                    map[i][j].node = 0;
                    break;
            }//end of switch
        }//end of for
    }//end of for
    //.............檢查所有的vertex的edges............
    int x_cor = 0;  int y_cor = 0;  //用來記錄最後一個存在的vertex
    for(int i = 1; i < y-1; i++)//1到y-2才是graph的範圍
    {
        for(int j = 1; j < x-1; j++)//同上
        {//檢查4個方向 看看有沒有edge存在 預設都不存在
            if(map[i][j].node == 0)//如果現在的vertex存在
            {
                x_cor = j;  y_cor = i;
                if(map[i][j+1].node == 0)   //右邊 x+1 可以走的話
                {   map[i][j].edge[E]=1;    edge_total++;   }    //edge存在
                if(map[i][j-1].node == 0)    //左邊 x-1 可以走的話
                {   map[i][j].edge[W]=1;    edge_total++;    }    //edge存在
                if(map[i+1][j].node == 0)    //上面 y+1 可以走的話
                {   map[i][j].edge[N]=1;    edge_total++;    }   //edge 存在
                if(map[i-1][j].node == 0)    //下面 y-1 可以走的話
                {   map[i][j].edge[S]=1;    edge_total++;    }   //edge存在
            }//end of if
        }//end of for
    }//end of for
	//設定起點為(x_cor, y_cor)
    step.push(Graph(y_cor-1, x_cor, N));    //假設起點的前一步往北走
	route.push(Graph(y_cor,x_cor,N));
    edge_total = edge_total/2;  //因為每個edge在上面的迴圈會加到兩次
    //-----------offset tabel----------------
	offset move[4];
	move[E].hor = 1;  move[E].ver = 0;
	move[N].hor = 0;  move[N].ver = -1;
	move[W].hor = -1; move[W].ver = 0;
	move[S].hor = 0;  move[S].ver = 1;
	//------------done setting---------------

    //...........開始traverse這個graph.................
    //先找起點
    Graph last_move;  //紀錄last move
    //last_move.x = x_cor;    last_move.y = y_cor-1;  //起始值在起點
    int direction = -1; //方向起始值
    last_move.dir = -1;
    while( !step.empty() && edge_total!=0 )  //當stack pop 出所有路徑且edge都走過才跳出迴圈
    {//已經沒路可走 換個方向 而起始條件已經先弄好
        //要pop出stack 裡面的路 塞到queue裡面
        last_move = step.top();
        step.pop();
        //回到上一步的位置
        int col = last_move.y - move[last_move.dir].ver;
        int row = last_move.x - move[last_move.dir].hor;
        if(direction != -1) //非起始值
        {   //先把回頭的路線丟進queue裡面 dir紀錄從上個點走來的方向
			if(!step.empty())
            {	route.push(Graph(col, row, step.top().dir));	}
			else//step empty 代表路都走完了
			{	break;	}	//跳出迴圈	
            direction = last_move.dir;  //回到上一步的方向
        }
        //到下面的迴圈判斷是否有路
       while(direction < 3)//還有方向或路需要確認是否可以走
       {
            direction ++;//換個方向
            //檢查下一步可能發生的事情
            if(map[col+move[direction].ver][row+move[direction].hor].node == 1)
            //如果他想嘗試的下一步沒有vertex存在
            {   
				continue;   //換個方向試試看
            }
            else if(map[col][row].dir[direction] == 1)  //如果他想嘗試的方向已經走過
            {
                continue;   //再換個方向試試看
            }
            else if(map[col][row].edge[direction] == 1) //如果想走的edge存在
            {   
                map[col][row].dir[direction] = 1;   //把要走的edge標示為已走過
                //朝direction走一步
                row += move[direction].hor; col += move[direction].ver;
                int opposite_way = (direction+2)%4; //direction的反方向
                map[col][row].dir[opposite_way] = 1; //把剛剛走的edge標示為已走過
                step.push(Graph(col,row, direction));  //push進stack
                route.push(Graph(col,row, direction));  //push進queue
				if(edge_total>0)
	            {    edge_total--;   }	//把還沒走的edge數量-1
				direction = -1;	//再從E開始trail
            }
       }//end of while 
    }//end of while
    
    //跳出迴圈->代表所有的路徑都存在queue裡面了!!
    while(!route.empty())   //印出queue的路徑
    {//注意 因為y軸標示跟題目相反 要改一下
        Graph tmp = route.front();
		route.pop();
        fout << tmp.x << ' ' << (y-tmp.y) << endl;
    }

    cout << "End of code" << endl;

    fout.close(); fin.close();
}//end of main
