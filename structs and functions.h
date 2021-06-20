#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <time.h>
#include <random>

using namespace std;

//Colors in console
const string light_blue = "\u001B[36m";
const string blue = "\u001B[34m";
const string green = "\u001B[32m";
const string yellow = "\u001B[33m";
const string red = "\u001B[31m";

//Adition functions
int EnterNumber(string mark);
int Choose(string types[3]);
int Min(int a, int b, int c);
int FindMin(vector<int>& a);
void PrintList(vector<int> list);
void PrintTable(vector<vector<int>> table);
void SystemPause();

//Virtual graph
struct Graph 
{
	virtual void Autogenerate(int number_of_edges) = 0;

	virtual void EnterEdge(int x_pos, int y_pos, int weight) = 0;

	virtual void EnterMatrix() = 0;

	virtual void ChangeSize(int size) = 0;

	virtual bool CheckConnected() = 0;

	virtual vector<int> TopsInDepth(int number, int type) = 0;

	virtual vector<vector<int>> MinimalWayTable() = 0;

	virtual int MinimalWay(int first_top, int second_top) = 0;

	virtual vector<int> MinimalWaysFromTop(int top) = 0;

	virtual void TopologicalSort() = 0;

	virtual vector<vector<int>> Tree(int number, int type) = 0;

	int WeigthOfTree(vector<vector<int>> tree)
	{
		int weigth = 0;
		for (int i = 0; i < tree.size(); i++)
			weigth += tree[i][2];
		return weigth;
	}

	virtual vector<vector<int>> MinimalSpanningTree() = 0;

	virtual void Print() = 0;
};

struct GraphList;

//Graph based on matrix
struct GraphMatrix : Graph
{
	bool directed;
	vector<vector<int>> Matrix;

	GraphMatrix(bool type, int size) {
		directed = type;
		vector<vector<int>> a(size, vector<int>(size, 0));
		Matrix = a;
	}

	void Autogenerate(int number_of_edges)override
	{
		if (((!directed && !(number_of_edges % 2) ) || directed) && number_of_edges <= (Matrix.size() * (Matrix.size() - 1)))
		{
			vector<vector<int>> a(Matrix.size(), vector<int>(Matrix.size(), 0));
			Matrix = a;
			while (number_of_edges > 0)
			{
				int x_pos = rand() % Matrix.size();
				int y_pos = rand() % Matrix.size();
				if (!Matrix[x_pos][y_pos] && x_pos != y_pos)
				{
					Matrix[x_pos][y_pos] = rand() % 20;
					number_of_edges--;
					if (!directed)
					{
						Matrix[y_pos][x_pos] = Matrix[x_pos][y_pos];
						number_of_edges--;
					}
				}
			}
			cout << green + "Successfully generated." << endl;
		}
		else
			cout << red + "Number of edges of graph is out of range." << endl;
	}

	void EnterEdge(int x_pos, int y_pos, int weight)override
	{
		if (x_pos < Matrix.size() && x_pos >= 0 && y_pos < Matrix.size() && y_pos >= 0 && x_pos != y_pos)
		{
			Matrix[x_pos][y_pos] = weight;
			if (!directed)
				Matrix[y_pos][x_pos] = Matrix[x_pos][y_pos];
			cout << green + "Successfully added." << endl;
		}
		else
			cout << red + "Point is out of range." << endl;
	}

	void EnterMatrix()override
	{
		directed = true;
		cout << light_blue;
		for (int i = 0; i < Matrix.size(); i++)
			for (int j = 0; j < Matrix.size(); j++)
			{
				cin >> Matrix[i][j];
				if (i == j)
					Matrix[i][i] = 0;
			}
		cout << green + "Successfully entered." << endl;
	}

	void ChangeSize(int size)override
	{
		vector<vector<int>> New_Matrix(size, vector<int>(size, 0));
		if (size > Matrix.size())
		{
			for (int i = 0; i < Matrix.size(); i++)
				for (int j = 0; j < Matrix.size(); j++)
					New_Matrix[i][j] = Matrix[i][j];
		}
		else
		{
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					New_Matrix[i][j] = Matrix[i][j];
		}
		Matrix = New_Matrix;
	}

	vector<int> TopsThatUsed()
	{
		vector<int> tops (Matrix.size(), 0);
		for (int i = 0; i < Matrix.size(); i++)
			for (int j = 0; j < Matrix.size(); j++)
				if (Matrix[i][j])
				{
					tops[i] = 1;
					tops[j] = 1;
				}
		return tops;
	}

	void ConnectedTops(int type, vector<int> &tops, vector<int> &way, int index_of_top)
	{
		tops[index_of_top] = 2;
		way.push_back(index_of_top);
		if (type)
		{
			for (int i = 0; i < tops.size(); i++)
			{

				if (Matrix[index_of_top][i])
					if (tops[i] == 1)
						ConnectedTops(type, tops, way, i);
			}
		}
		else
		{
			vector<int> a = Matrix[index_of_top];
			int min = FindMin(a);
			while (min >= 0)
			{
				if (tops[min] == 1)
					ConnectedTops(type, tops, way, min);
				min = FindMin(a);
			}
		}
	}

	bool CheckConnected()override
	{
		bool Connected_graph = true;
		vector<int> tops = TopsThatUsed();
		vector<vector<int>> table = Matrix;
		if (directed)
		{
			for (int i = 0; i < Matrix.size(); i++)
				for (int j = 0; j < Matrix.size(); j++)
					if (table[i][j])
						table[j][i]= table[i][j];
		}
		int n = 0;
		while (!tops[n])
			n++;
		vector<int> way;
		ConnectedTops(1, tops, way, n);
		for (int i = 0; i < tops.size(); i++)
			if (tops[i] == 1)
				Connected_graph = false;
		return Connected_graph;
	}

	vector<int> TopsInDepth(int number, int type)override
	{
		vector<int> way;
		vector<int> tops = TopsThatUsed();
		if (tops[number])
			ConnectedTops(type, tops, way, number);
		return way;
	}

	vector<vector<int>> MinimalWayTable()override
	{
		vector<vector<int>> table_distance = Matrix;
		for (int i = 0; i < table_distance.size(); i++)
			for (int j = 0; j < table_distance.size(); j++)
				if (table_distance[i][j] == 0 && i != j)
					table_distance[i][j]--;
		for (int k = 0; k < table_distance.size(); k++)
			for (int i = 0; i < table_distance.size(); i++)
				for (int j = 0; j < table_distance.size(); j++)
					table_distance[i][j] = Min(table_distance[i][j], table_distance[i][k], table_distance[k][j]);
		return table_distance;
	}

	int MinimalWay(int start_top, int finish_top)override
	{
		return MinimalWayTable()[start_top][finish_top];
	}

	vector<int> MinimalWaysFromTop(int top)override
	{
		return MinimalWayTable()[top];
	}

	void TopologicalSort()override
	{
		if (CheckConnected())
		{
			vector<int> way;
			way = TopsInDepth(0, 1);
			vector<vector<int>> new_matrix(way.size(),vector<int>(way.size(),0));
			for (int i = 0; i < way.size(); i++)
				for (int j = 0; j < way.size(); j++)
					new_matrix[i][j] = Matrix[way[i]][way[j]];
			Matrix = new_matrix;
		}
	}

	void AddEdge(int type, vector<int>& tops, vector<vector<int>>& tree, int index_of_top)
	{
		tops[index_of_top] = 2;
		if (type)
		{
			for (int i = 0; i < tops.size(); i++)
			{

				if (Matrix[index_of_top][i])
					if (tops[i] == 1)
					{
						vector<int> edge;
						edge.push_back(index_of_top);
						edge.push_back(i);
						edge.push_back(Matrix[index_of_top][i]);
						tree.push_back(edge);
						AddEdge(type, tops, tree, i);
					}
			}
		}
		else
		{
			vector<int> a = Matrix[index_of_top];
			int min = FindMin(a);
			while (min >= 0)
			{
				if (tops[min] == 1)
				{
					vector<int> edge;
					edge.push_back(index_of_top);
					edge.push_back(min);
					edge.push_back(Matrix[index_of_top][min]);
					tree.push_back(edge);
					AddEdge(type, tops, tree, min);
				}
				min = FindMin(a);
			}
		}
	}

	vector<vector<int>> Tree(int number, int type)override
	{
		vector<vector<int>> tree;
		if (!directed && CheckConnected())
		{
			vector<int> tops = TopsThatUsed();
			AddEdge(type, tops, tree, number);
		}
		return tree;
	}

	vector<vector<int>> MinimalSpanningTree()override
	{
		vector<vector<int>> min_tree = Tree(0, 0);
		for (int i = 1; i < Matrix.size(); i++)
		{
			vector<vector<int>> current_tree = Tree(i, 0);
			if (WeigthOfTree(current_tree) < WeigthOfTree(min_tree))
				min_tree = current_tree;
		}
		return min_tree;
	}

	void Print()override
	{
		for (int i = 0; i < Matrix.size(); i++)
		{
			for (int j = 0; j < Matrix.size(); j++)
			{
				cout << green << Matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
};

//Convertation
GraphList MakeList(GraphMatrix Matrix);
GraphMatrix MakeMatrix(GraphList List);

//Graph based on list
struct GraphList : Graph
{
	bool directed;
	int number_of_tops;
	vector<vector<int>> List;

	GraphList(bool type, int size) {
		directed = type;
		number_of_tops = size;
		vector<vector<int>> a;
		List = a;
	}

	void Autogenerate(int number_of_edges)override
	{
		if (((!directed && !(number_of_edges % 2)) || directed) && number_of_edges <= (number_of_tops * (number_of_tops - 1)))
		{
			GraphMatrix Matrix = GraphMatrix(directed, number_of_tops);
			vector<vector<int>> a;
			List = a;
			while (number_of_edges > 0)
			{
				int x_pos = rand() % number_of_tops;
				int y_pos = rand() % number_of_tops;
				if (!Matrix.Matrix[x_pos][y_pos] && x_pos != y_pos)
				{
					Matrix.Matrix[x_pos][y_pos] = rand() % 20;
					vector<int> edge(3, 0);
					edge[0] = x_pos;
					edge[1] = y_pos;
					edge[2] = Matrix.Matrix[x_pos][y_pos];
					List.push_back(edge);
					number_of_edges--;
					if (!directed)
					{
						Matrix.Matrix[y_pos][x_pos] = Matrix.Matrix[x_pos][y_pos];
						edge[1] = x_pos;
						edge[0] = y_pos;
						List.push_back(edge);
						number_of_edges--;
					}
				}
			}
			
			cout << green + "Successfully generated." << endl;
		}
		else
			cout << red + "Number of edges of graph is out of range." << endl;
	}

	void EnterEdge(int x_pos, int y_pos, int weight)override
	{
		if (x_pos < number_of_tops && x_pos >= 0 && y_pos < number_of_tops && y_pos >= 0 && x_pos != y_pos)
		{
			GraphList New_List = GraphList(directed, number_of_tops);
			New_List.List = List;
			GraphMatrix Matrix = MakeMatrix(New_List);
			Matrix.Matrix[x_pos][y_pos] = weight;
			if (!directed)
				Matrix.Matrix[y_pos][x_pos] = Matrix.Matrix[x_pos][y_pos];
			New_List = MakeList(Matrix);
			List = New_List.List;
			cout << green + "Successfully added." << endl;
		}
		else
			cout << red + "Point is out of range." << endl;
	}

	void EnterMatrix()override
	{
		directed = true;
		GraphMatrix Matrix = GraphMatrix(directed, number_of_tops);
		cout << light_blue;
		for (int i = 0; i < Matrix.Matrix.size(); i++)
			for (int j = 0; j < Matrix.Matrix.size(); j++)
			{
				cin >> Matrix.Matrix[i][j];
				if (i == j)
					Matrix.Matrix[i][i] = 0;
			}
		GraphList New_List = MakeList(Matrix);
		List = New_List.List;
		cout << green + "Successfully entered." << endl;
	}

	void ChangeSize(int size)override
	{
		GraphList New_List = GraphList(directed, number_of_tops);
		New_List.List = List;
		GraphMatrix Matrix = MakeMatrix(New_List);
		vector<vector<int>> New_Matrix(size, vector<int>(size, 0));
		if (size > number_of_tops)
		{
			for (int i = 0; i < number_of_tops; i++)
				for (int j = 0; j < number_of_tops; j++)
					New_Matrix[i][j] = Matrix.Matrix[i][j];
		}
		else
		{
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					New_Matrix[i][j] = Matrix.Matrix[i][j];
		}
		Matrix.Matrix = New_Matrix;
		New_List = MakeList(Matrix);
		List = New_List.List;
		number_of_tops = size;
	}

	bool CheckConnected()override
	{
		GraphList New_List = GraphList(directed, number_of_tops);
		New_List.List = List;
		GraphMatrix Matrix = MakeMatrix(New_List);
		return Matrix.CheckConnected();
	}

	vector<int> TopsInDepth(int number, int type)override
	{
		GraphList New_List = GraphList(directed, number_of_tops);
		New_List.List = List;
		GraphMatrix Matrix = MakeMatrix(New_List);
		return Matrix.TopsInDepth(number, type);
	}

	vector<vector<int>> MinimalWayTable()override
	{
		GraphList New_List = GraphList(directed, number_of_tops);
		New_List.List = List;
		GraphMatrix Matrix = MakeMatrix(New_List);
		return Matrix.MinimalWayTable();
	}

	int MinimalWay(int start_top, int finish_top)override
	{
		return MinimalWayTable()[start_top][finish_top];
	}

	vector<int> MinimalWaysFromTop(int top)override
	{
		return MinimalWayTable()[top];
	}

	void TopologicalSort()override
	{
		GraphList New_List = GraphList(directed, number_of_tops);
		New_List.List = List;
		GraphMatrix Matrix = MakeMatrix(New_List);
		Matrix.TopologicalSort();
		New_List = MakeList(Matrix);
		List = New_List.List;
	}

	vector<vector<int>> Tree(int number, int type)override
	{
		GraphList New_List = GraphList(directed, number_of_tops);
		New_List.List = List;
		GraphMatrix Matrix = MakeMatrix(New_List);
		return Matrix.Tree(number,type);
	}

	vector<vector<int>> MinimalSpanningTree()override
	{
		GraphList New_List = GraphList(directed, number_of_tops);
		New_List.List = List;
		GraphMatrix Matrix = MakeMatrix(New_List);
		return Matrix.MinimalSpanningTree();
	}

	void Print()override
	{
		for (int i = 0; i < List.size(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cout << green << List[i][j] << " ";
			}
			cout << endl;
		}
	}
};

void InteractiveMode();
void Demonstaration();
void Benchmark();

void Menu();