#include <stdio.h>
#include <queue>
#include <conio.h>
#include <iostream>

using namespace std;

int n; 
int **edge;
int *parent;
void initGraph(int);
bool isConnected(int, int);
void addEdge(int, int);
void breadthFirstSearch(int, int);
void printSolution(int);

void initGraph(int size)
{
	int i, j;
 
	if (size < 2)
		n = 2;
	else 
		n = size;
 
	edge = new int*[n];
	for (i = 0; i < n; i++)
		edge[i] = new int[n];
	
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			edge[i][j] = 0;
}

freeGraph()
{
	for (int i = 0; i < n; ++i)
		delete[] edge[i];
	delete[] edge;
}

bool isConnected(int i, int j)
{
	return (edge[i - 1][j - 1] == 1);
}
 
void addEdge(int i, int j)
{
	if (i >= 1 && i <= n && j >= 1 && j <= n)
		edge[i - 1][j - 1] = edge[j - 1][i - 1] = 1;
}

void printSolution(int goal)
{
	if (goal != 0)
	{
		printSolution(parent[goal]);
		cout << goal << " ";
	}
	
}

void breadthFirstSearch(int start, int goal)
{
	if (start > n || start < 1 || goal > n || goal < 1)
	{
		cout << "Khong tim duoc duong di\n";
		return;
	}
	queue <int> open;
	bool *close = new bool[n];
	parent = new int[n];
	int i, v;
 
	for (i = 0; i < n; i++)
	{
		close[i] = false;
		parent[i]=0;
	}
 
	open.push(start);
 
	while (!open.empty())
	{
		do
		{
			if (open.empty())
			{
				cout << "That bai!\n";
				delete[] close;
				return;
			} 
			v = open.front();
			open.pop();
		} while (close[v - 1] == true);
 
		close[v - 1] = true;
 
		if (v == goal)
		{
			cout << "Thanh cong!\n";
			cout << "Loi giai tim duoc la: ";
 
			printSolution(goal);
			delete[] close;
			return;
		}
		
		for (i = 1; i <= n; i++)
		{
			if (isConnected(v, i) && !close[i - 1])
			{
				open.push(i);
				parent[i] = v;
			}
		}
	}

	cout << "That bai!\n";
	delete[] close;
}

int main()
{
	initGraph(9);
 
	addEdge(1, 2);
	addEdge(1, 3);
	addEdge(1, 4);
	addEdge(2, 5);
	addEdge(2, 6);
	addEdge(3, 4);
	addEdge(3, 5);
	addEdge(3, 7);
	addEdge(3, 8); 
	addEdge(3, 9);
 	addEdge(5, 8);
 	
	breadthFirstSearch(1, 8);
	return 1;
}
