#include <stdio.h>
#include <queue>
#include <conio.h>
#include <iostream>

using namespace std;

class Graph
{
private:
	int n; 
	int **edge;
	int *parent;
public:
	Graph(int size = 2);
	~Graph();
	bool isConnected(int, int);
	void addEdge(int, int);
	void breadthFirstSearch(int, int);
	void printSolution(int);
};

Graph::Graph(int size)
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

Graph::~Graph()
{
	for (int i = 0; i < n; ++i)
		delete[] edge[i];
	delete[] edge;
}

bool Graph::isConnected(int i, int j)
{
	return (edge[i - 1][j - 1] == 1);
}
 
void Graph::addEdge(int i, int j)
{
	if (i >= 1 && i <= n && j >= 1 && j <= n)
		edge[i - 1][j - 1] = edge[j - 1][i - 1] = 1;
}

void Graph::printSolution(int goal)
{
	if (goal != 0)
	{
		printSolution(parent[goal]);
		cout << goal << " ";
	}
}

void Graph::breadthFirstSearch(int start, int goal)
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
	Graph g(9);
 
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	g.addEdge(2, 5);
	g.addEdge(2, 6);
	g.addEdge(3, 4);
	g.addEdge(3, 5);
	g.addEdge(3, 7);
	g.addEdge(3, 8); 
	g.addEdge(3, 9);
 	g.addEdge(5, 8);
 	
	g.breadthFirstSearch(1, 8);
	return 1;
}
