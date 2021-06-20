#include "structs and functions.h"

void InteractiveMode()
{
	string types[3] = { "Undirected;", "Directed;", "Graph" };
	int type = Choose(types);
	int size = EnterNumber("size");

	GraphMatrix* Matrix = new GraphMatrix(type, size);
	GraphList* List = new GraphList(type, size);
	Graph* graph;

	types[0] = "List;";
	types[1] = "Matrix;";
	int type_graph = Choose(types);
	switch (type_graph)
	{
	case 0:
		graph = List;
		break;
	default:
		graph = Matrix;
		break;
	}

	string functions[17] =
	{
		"Autogenerator matrix;",
		"Add edge;",
		"Enter matrix;",
		"Change size;",
		"Convert graph;",
		"Print matrix;",
		"Check conected;",
		"Conected tops (in depth);",
		"Minimal distance between tops;",
		"Distance to all tops from selected;",
		"Table of minimal ways;",
		"Topological sorting;",
		"Tree;",
		"Weigth;",
		"Minimal tree;",
		"Weigth of Minimal tree;",
		"Back."
	};

	int position = 0;
	bool end = false;

	while (!end)
	{
		system("cls");
		cout << blue + "    Hello user.\n    There are the functions you can do." << endl;
		for (int i = 0; i < 17; i++)
		{
			if (i == position)
				cout << red + "->  " << light_blue + functions[i] << endl;
			else cout << "    " << light_blue + functions[i] << endl;
		}
		char key;
		key = _getch();
		if ((int)key != 13)
		{
			if ((int)key == -32)
			{
				key = _getch();
				if ((int)key == 72)
				{
					if (position > 0)
						position--;
					else position = 16;
				}

				if ((int)key == 80)
				{
					if (position < 16)
						position++;
					else position = 0;
				}
			}
		}
		else
		{
			system("cls");
			GraphMatrix Converted_Matrix = GraphMatrix(List->directed, size);
			GraphList Converted_List = GraphList(Matrix->directed, size);
			int index_s;
			int index_f;
			int weight;
			switch (position)
			{
			case 0:
				graph->Autogenerate(EnterNumber("number of edges of graph"));
				SystemPause();
				break;
			case 1:
				index_s = EnterNumber("start point");
				index_f = EnterNumber("finish point");
				weight = EnterNumber("weight");
				graph->EnterEdge(index_s, index_f, weight);
				SystemPause();
				break;
			case 2:
				graph->EnterMatrix();
				SystemPause();
				break;
			case 3:
				size = EnterNumber("new size");
				graph->ChangeSize(size);
				break;
			case 4:
				switch (type_graph)
				{
				case 0:
					Converted_Matrix = MakeMatrix(*List);
					*Matrix = Converted_Matrix;
					graph = Matrix;
					type_graph++;
					break;
				default:
					Converted_List = MakeList(*Matrix);
					*List = Converted_List;
					graph = List;
					type_graph--;
					break;
				}
				break;
			case 5:
				graph->Print();
				SystemPause();
				break;
			case 6:
				if (graph->CheckConnected())
					cout << green + "Graph is conected." << endl;
				else cout << green + "Graph isn't conected." << endl;
				SystemPause();
				break;
			case 7:
				index_s = EnterNumber("index of top");
				types[1] = "In order;";
				types[0] = "By weight;";
				types[2] = "output";
				if (index_s < size)
				{
					vector<int> way = graph->TopsInDepth(index_s, Choose(types));
					for (int i = 0; i < way.size(); i++)
						cout << green << way[i] << " ";
					cout << endl;
				}
				else cout << red + "Index of top is out the range." << endl;
				SystemPause();
				break;
			case 8:
				index_s = EnterNumber("start point");
				index_f = EnterNumber("finish point");
				if (index_f < size && index_s < size)
					cout << green + "Distance is " << (graph->MinimalWay(index_s, index_f)) << endl;
				else cout << red + "Index of top is out of range." << endl;
				SystemPause();
				break;
			case 9:
				index_s = EnterNumber("start point");
				if (index_s < size)
					for (int i = 0; i < size; i++)
						cout << green << (graph->MinimalWaysFromTop(index_s)[i]) << " ";
				else cout << red + "Index of top is out of range.";
				cout << endl;
				SystemPause();
				break;
			case 10:
				PrintTable(graph->MinimalWayTable());
				SystemPause();
				break;
			case 11:
				graph->TopologicalSort();
				cout << green + "Graph successfully sorted." << endl;
				SystemPause();
				break;
			case 12:
				index_s = EnterNumber("start point");
				types[1] = "In order;";
				types[0] = "By weight;";
				types[2] = "output";
				PrintTable(graph->Tree(index_s,Choose(types)));
				SystemPause();
				break;
			case 13:
				index_s = EnterNumber("start point");
				types[1] = "In order;";
				types[0] = "By weight;";
				types[2] = "output";
				cout << green << graph->WeigthOfTree(graph->Tree(index_s, Choose(types))) << endl;
				SystemPause();
				break;
			case 14:
				PrintTable(graph->MinimalSpanningTree());
				SystemPause();
				break;
			case 15:
				cout << green << graph->WeigthOfTree(graph->MinimalSpanningTree()) << endl;
				SystemPause();
				break;
			case 16:
				end = true;
				break;
			}
		}
	}
}