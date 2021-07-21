#include <fstream>
#include <iostream>

using namespace std;

struct Node
{
	int stt;// so thu tu
	int g;// khoang cach tu dinh ban dau den dinh hien ta
	int f; // f=h+g;
	int h;// duong di ngan nhat
	int color;// danh dau dinh di qua
	int dad;// dinh cha
};
int a[100][100];
Node p[100];
Node Open[100];
Node Close[100];
 
void ReadfileInput1(int *b, int &n)
{
	fstream myfile("input1.txt");
	if (!myfile.is_open())
	{
		cout << "Khong the mo duoc file" << endl;
	}
	else
	{
		myfile >> n;
		for (int i = 0; i < n; i++)
		{
			myfile >> b[i];
 		}
	}
}
 
void ReadfileInput2(int a[100][100], int &n, int &start, int &finsh)
{
 
	fstream shichiki("input2.txt");
	if (!shichiki.is_open())
	{
		cout << "Khong the mo duoc file !";
	}
	else
	{
		shichiki >> n >> start >> finsh;
 
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				shichiki >> a[i][j];
		}
	}
	shichiki.close();
 
}
void printfmaxtric(int a[100][100], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << "\t";
		}
		cout << "\n";
	}
 
}
 
int Count(int n, Node *Open)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (Open[i].color == 1)
			count = count + 1;
	}
	return count;
}
int Find(int n, Node *Open)
{
 
	for (int i = 0; i < n; i++)
		if (Open[i].color == 1)
			return i;
}
int Findmin(int n, Node *Open)
{
	int min1 = Find(n, Open);
	int min = Open[min1].f;
	for (int i = 0; i < n; i++)
	{
		if (Open[i].f < min && Open[i].color == 1)
		{
			min1 = i;
			min = Open[i].f;
		}
	}
	return min1;
}
void Init(int n, int *b)
{
	for (int i = 0; i < n; i++)
	{
		p[i].stt = i;
		p[i].color = 0;
		p[i].g = b[i];
		p[i].dad = 0;
		p[i].f = p[i].g;
		p[i].h = 0;
	}
}
int  Findpoint(int n, Node *q, int o)
{
	for (int i = 0; i < n; i++)
		if (q[i].stt == o)
			return  i;
}
void astar(int a[100][100], int n, int start, int finsh, int b[])
{
	int l = 0;
	Open[l] = p[start];
	Open[l].color = 1;
	Open[l].f = Open[l].h + Open[l].g;
	l++;
	int w = 0;
	while (Count(l, Open) != 0) // kiem tra xem tap Open co con phan tu nao khong
	{
		int k = Findmin(n, Open); // tim vi tri nho nhat trong Open
		Open[k].color = 2; // cho diem tim duoc vao Close
		Close[w] = Open[k];
		Close[w].color = 2;
		w++;
		p[Findpoint(n, p, Open[k].stt)].color = 2;
		if (Findpoint(n, p, Open[k].stt) == finsh)
		{
			cout << "Duong di qua  la" << endl;
			cout << finsh << "\t";
			int y = Findpoint(w, Close, finsh);
			int u = Close[y].dad;
			while (u != start)
			{
				y = Findpoint(w, Close, u);
				u = Close[y].dad;
				cout << u << "\t";
			}
			break;
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				if (a[Findpoint(n, p, Open[k].stt)][i] != 0 && p[i].color == 0)// neu chua co trong Open va Close
				{
					Open[l] = p[i];
					Open[l].color = 1;
					Open[l].h = a[Findpoint(n, p, Open[k].stt)][i] + Open[k].h;// tinh h khoang cach ngan nhat tu dinh bat dau den dinh hien tai 
					Open[l].f = Open[l].g + Open[l].h;
					Open[l].dad = Findpoint(n, p, Open[k].stt);
					p[i].color = 1;
					l++;
				}
				if (a[Findpoint(n, p, Open[k].stt)][i] != 0 && p[i].color == 1)// neu dinh da co trong open
				{
					int h = Findpoint(l, Open, p[i].stt);
					Node tam = p[i];
					tam.color = 1;
					tam.h = a[Findpoint(n, p, Open[k].stt)][i] + Open[k].h;
					tam.dad = k;
					tam.f = tam.h + tam.g;
					if (tam.f < Open[h].f)//neu f trang thai hien tai be hon trang thai cap nhat truoc do			
						Open[h] = tam;
				}
				if (a[Findpoint(n, p, Open[k].stt)][i] != 0 && p[i].color == 2)// neu dinh da co trong Close
				{
					int h = Findpoint(l, Close, p[i].stt);
					Node tam = p[i];
					tam.color = 1;
					tam.h = a[Findpoint(n, p, Open[k].stt)][i] + Open[k].h;
					tam.dad = k;
					tam.f = tam.h + tam.g;
					if (tam.f < Close[h].f)//neu f trang thai hien tai be hon trang thai truoc do	
					{
						Open[l] = tam;// them vao Open
						Close[h].color = 1;//danh dau dinh do thuoc Open						
						l++;
					}
				}
			}
		}
	}
}
 
int main()
{
	int n;	
	int start;
	int finsh;
	int b[100];
 
	ReadfileInput2(a, n, start, finsh);
	ReadfileInput1(b, n);
 
	Init(n, b);
	cout << "Dinh bat dau" << endl;
	cout << start << endl;
	cout << "Dinh ket thuc" << endl;
	cout << finsh << endl;
	
	printfmaxtric(a, n);
 
	astar(a, n, start, finsh, b);
	
	return 0;
}
