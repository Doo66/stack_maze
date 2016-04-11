#include <iostream>
#include <stack>
#include <cstdio>
#include <cassert>
#define N 10

using namespace std;

struct Pos
{

	int _row;	//行
	int _col;	//列

	//Pos(int row, int col)
	//	:_row(row),_col(col)
	//{}
};

void GetMaze(int* a, int n)
{
	FILE* fout = fopen("MazeMap.txt", "r");
	assert(fout);
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n;)
		{
			char ch = fgetc(fout);
			if(ch == '1' || ch == '0')
			{
				a[i*n+j] = ch - '0';
				j++;
			}
			else
			{
				continue;
			}
		}
	}
	fclose(fout);
}


void PrintMaze(int* maze, int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; i<=n; j++)
		{
			cout<<maze[i*n+j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

bool IsValid(int* a, int n, Pos pos)
{
	if(a[n*pos._row + pos._col] == 0 && pos._row < n && pos._row >= 0 && pos._col < n && pos._col >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GetPath(int* a, int n,	Pos& entry, stack<Pos>& path)
{
	Pos cur = entry;
	path.push(cur);
	while(!path.empty())
	{
		a[cur._row*n+cur._col] = 2;
		if(cur._row == n-1)
		{
			return true;
		}
		//向上检索
		Pos next = cur;
		next._row--;
		if(IsValid(a, n, next))
		{
			cur = next;
			path.push(cur);
			continue;
		}
		//向下检索
		next = cur;
		next._row++;
		if(IsValid(a, n, next))
		{
			cur = next;
			path.push(cur);
			continue;
		}
		//向左检索
		next = cur;
		next._col--;
		if(IsValid(a, n, next))
		{
			cur = next;
			path.push(cur);
			continue;
		}
		//向右检索
		next = cur;
		next._col++;
		if(IsValid(a, n, next))
		{
			cur = next;
			path.push(cur);
			continue;
		}
		//return false;
		cur = path.top();
		path.pop();
	}
	return false;
}

void TestMaze()
{
	int arr[N][N] ={};
	GetMaze((int*)arr, N);
	PrintMaze((int*)arr, N);
	stack<Pos> path;
	Pos entry = {2, 0};
	cout<<GetPath((int*)arr, N,entry,path)<<endl;
	PrintMaze((int*)arr, N);
}

int main()
{
	TestMaze();
	return 0;
}
