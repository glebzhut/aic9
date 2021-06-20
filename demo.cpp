#include "structs and functions.h"

void Demonstaration()
{
	cout << blue + "Hello user. Now i show all functions i can use." << endl;

	cout <<  "Now I create Undirected Graph based on Matrix and List with 6 tops and add edge(First top, Second top, Weigth) (0,1,5)." << endl;
	GraphMatrix Matrix(false, 6);
	GraphList List(false, 6);
	GraphMatrix Matrix_converted(false, 6);
	GraphList List_converted(false, 6);
	Matrix.EnterEdge(0, 1, 5);
	List.EnterEdge(0, 1, 5);

	
	SystemPause();
	cout << blue + "This is information in Matrix" << endl;
	Matrix.Print();
	cout << endl << blue + "This is information in List" << endl;
	List.Print();
	SystemPause();

	cout << blue + "Now i generate 20 different edges in each Graph." << endl;
	Matrix.Autogenerate(20);
	List.Autogenerate(20);

	SystemPause();
	cout << blue + "This is information in Matrix" << endl;
	Matrix.Print();
	cout << endl << blue + "This is information in List" << endl;
	List.Print();
	SystemPause();

	cout << blue + "Now i converte Matrix to List and List to Matrix." << endl;
	List_converted = MakeList(Matrix);
	Matrix_converted = MakeMatrix(List);

	SystemPause();
	cout << blue + "This is information in Matrix." << endl;
	Matrix.Print();
	cout << endl << blue + "This is information in matrix converted to list." << endl;
	List_converted.Print();

	SystemPause();
	cout << blue + "This is information in List" << endl;
	List.Print();
	cout << endl << blue + "This is information in List converted to Matrix." << endl;
	Matrix_converted.Print();
	SystemPause();

	cout << blue + "Now i chech that graph is connected." << endl;

	SystemPause();
	cout << blue + "This is information about Matrix." << endl;
	cout << green << Matrix.CheckConnected() << endl;
	cout << endl << blue + "This is information about List." << endl;
	cout << green << List.CheckConnected() << endl;
	SystemPause();
	
	cout << blue + "Now i change graph(size, number of edges) to (4, 2) (two edges are not connected) and chech that graph is connected." << endl;
	Matrix = GraphMatrix(0, 4);
	Matrix.EnterEdge(0, 1, 5);
	Matrix.EnterEdge(2, 3, 10);
	List = MakeList(Matrix);

	SystemPause();
	cout << blue + "This is information about Matrix." << endl;

	cout << green << Matrix.CheckConnected() << endl;
	Matrix.Print();
	cout << endl << blue + "This is information about List." << endl;
	cout << green << List.CheckConnected() << endl;
	List.Print();
	SystemPause();

	cout << blue + "Now i generate 12 different edges in Graph and do traverse in depth in order from 0 top." << endl;
	Matrix.Autogenerate(12);
	List = MakeList(Matrix);

	SystemPause();
	cout << blue + "This is information in Matrix" << endl;
	Matrix.Print();
	cout << endl;
	PrintList(Matrix.TopsInDepth(0, 1));
	cout << endl << blue + "This is information in List" << endl;
	List.Print();
	cout << endl;
	PrintList(List.TopsInDepth(0, 1));
	SystemPause();

	cout << blue + "Now i do traverse in depth by weigth." << endl;

	SystemPause();
	cout << blue + "This is information in Matrix" << endl;
	Matrix.Print();
	cout << endl;
	PrintList(Matrix.TopsInDepth(0, 0));
	cout << endl << blue + "This is information in List" << endl;
	List.Print();
	cout << endl;
	PrintList(List.TopsInDepth(0, 0));
	SystemPause();

	cout << blue + "Now i show you table of minimal ways to different tops." << endl;

	SystemPause();
	cout << blue + "This is information about Matrix(same for List)" << endl;
	Matrix.Print();
	cout << endl;
	PrintTable(Matrix.MinimalWayTable());
	SystemPause();

	cout << blue + "Now i build spanning tree of graph for 0 top.." << endl;

	SystemPause();
	cout << blue + "This is information about Matrix(same for List)" << endl;
	Matrix.Print();
	cout << endl;
	cout << blue + "This is spanning tree(in depth in order)" << endl;
	PrintTable(Matrix.Tree(0, 1));
	cout << blue + "His weigth "<< green << Matrix.WeigthOfTree(Matrix.Tree(0, 1)) << endl;
	cout << endl;
	cout << blue + "This is spanning tree(in depth by weigth)" << endl;
	PrintTable(Matrix.Tree(0, 0));
	cout << blue + "His weigth " << green << Matrix.WeigthOfTree(Matrix.Tree(0, 0)) << endl;

	cout << blue + "Now i build minimal spanning tree of graph." << endl;

	SystemPause();
	cout << blue + "This is information about Matrix(same for List)" << endl;
	Matrix.Print();
	cout << endl;
	cout << blue + "This is minimal spanning tree." << endl;
	PrintTable(Matrix.Tree(0, 1));
	cout << blue + "His weigth " << green << Matrix.WeigthOfTree(Matrix.MinimalSpanningTree()) << endl;
	SystemPause();

	cout << blue + "Now I create Directed Graph based on Matrix and List with 6 tops and add edge(First top, Second top, Weigth) (0,1,5)." << endl;
	Matrix = GraphMatrix(true, 6);
	List = GraphList(true, 6);
	Matrix_converted = Matrix;
	List_converted = List;
	Matrix.EnterEdge(0, 1, 5);
	List.EnterEdge(0, 1, 5);


	SystemPause();
	cout << blue + "This is information in Matrix" << endl;
	Matrix.Print();
	cout << endl << blue + "This is information in List" << endl;
	List.Print();
	SystemPause();

	cout << blue + "Now i generate 20 different edges in each Graph." << endl;
	Matrix.Autogenerate(20);
	List.Autogenerate(20);

	SystemPause();
	cout << blue + "This is information in Matrix" << endl;
	Matrix.Print();
	cout << endl << blue + "This is information in List" << endl;
	List.Print();
	SystemPause();

	cout << blue + "Now i converte Matrix to List and List to Matrix." << endl;
	List_converted = MakeList(Matrix);
	Matrix_converted = MakeMatrix(List);

	SystemPause();
	cout << blue + "This is information in Matrix." << endl;
	Matrix.Print();
	cout << endl << blue + "This is information in matrix converted to list." << endl;
	List_converted.Print();

	SystemPause();
	cout << blue + "This is information in List" << endl;
	List.Print();
	cout << endl << blue + "This is information in List converted to Matrix." << endl;
	Matrix_converted.Print();
	SystemPause();

	cout << blue + "Now i chech that graph is connected." << endl;

	SystemPause();
	cout << blue + "This is information about Matrix." << endl;
	cout << green << Matrix.CheckConnected() << endl;
	cout << endl << blue + "This is information about List." << endl;
	cout << green << List.CheckConnected() << endl;
	SystemPause();

	cout << blue + "Now i change graph(size, number of edges) to (4, 2) (two edges are not connected) and chech that graph is connected." << endl;
	Matrix = GraphMatrix(0, 4);
	Matrix.EnterEdge(0, 1, 5);
	Matrix.EnterEdge(2, 3, 10);
	List = MakeList(Matrix);

	SystemPause();
	cout << blue + "This is information about Matrix." << endl;

	cout << green << Matrix.CheckConnected() << endl;
	Matrix.Print();
	cout << endl << blue + "This is information about List." << endl;
	cout << green << List.CheckConnected() << endl;
	List.Print();
	SystemPause();

	cout << blue + "Now i create graph with edges(Start point, Finish point, Weigth) (0,3,7), (3,1,8), (3,2,4), (2,1,2)." << endl;
	Matrix = GraphMatrix(1, 4);
	Matrix.EnterEdge(0, 3, 7);
	Matrix.EnterEdge(3, 1, 8);
	Matrix.EnterEdge(2, 1, 2);
	Matrix.EnterEdge(3, 2, 4);
	List = MakeList(Matrix);

	SystemPause();
	cout << blue + "This is information about Matrix." << endl;
	Matrix.Print();
	Matrix.TopologicalSort();
	cout << endl << blue + "This is information in sorted Matrix." << endl;
	Matrix.Print();
	SystemPause();



	cout << blue + "Thank you for using. Goodbye." << endl;
	SystemPause();
}