#include <stdio.h>
#include <stack>
#include <queue>
#include <vector>
#include <conio.h>
#include <iostream>
using namespace std;

class Vertex
{
	private:
		int node;
		int priority;
	public:
		Vertex();
		Vertex(int, int );
		int getNode() const;
		int getPriority() const;
};

Vertex::Vertex()
{
	node = 0;
	priority = 0;	
}

Vertex::Vertex(int v, int p)
{
	node = v;
	priority = p;
}

int Vertex::getNode() const
{
	return node;
}
	
int Vertex::getPriority() const
{
	return priority;
}

struct priComparer
{
    bool operator()(const Vertex& v1, const Vertex& v2) const
    {
    	return (v1.getPriority() > v2.getPriority());
	}
};

class Graph
{
	private:
		int n; 
		int **edge;
		int *heuristic;
		int *parent;
	public:
		Graph(int size = 2);
		~Graph();
		bool isConnected(int, int);
		void addEdge(int, int);
		void addHeuristic(int, int);
		void hillClimbingSearch(int, int);
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
	heuristic = new int[n];
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

void Graph::addHeuristic(int i, int value)
{
	heuristic[i] = value;
}

void Graph::printSolution(int goal)
{
	if (goal != 0)
	{
		printSolution(parent[goal]);
		cout << goal << " ";
	}
}

void Graph::hillClimbingSearch(int start, int goal)
{
	if (start > n || start < 1 || goal > n || goal < 1)
	{
		cout << "Khong tim duoc duong di\n";
		return;
	}
	stack <int> open;
	priority_queue <Vertex, vector<Vertex>, priComparer> list;
	bool *close = new bool[n];
	parent = new int[n];
	Vertex vertex;
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
			v = open.top();
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
				list.push(Vertex(i, heuristic[i]));
				parent[i] = v;
			}
		}
		while (!list.empty())
		{
			vertex = list.top();
			list.pop();
			i = vertex.getNode();
			open.push(i);
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
 	
 	g.addHeuristic(1, 4);
 	g.addHeuristic(2, 10);
 	g.addHeuristic(3, 20);
 	g.addHeuristic(4, 3);
 	g.addHeuristic(5, 5);
 	g.addHeuristic(6, 6);
 	g.addHeuristic(7, 2);
 	g.addHeuristic(8, 9);
	g.addHeuristic(9, 4);
 	
	g.hillClimbingSearch(1, 8);
	return 1;
}
