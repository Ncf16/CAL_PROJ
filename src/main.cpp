/*
 * main.cpp
 *
 *  Created on: 26/04/2015
 *      Author: Filipe
*/

#include "parsing.h"
#include "grafo.h"
#include "disjointSet.h"
int main() {
		Graph grafo;
		cout<<"Here"<<endl;
		loadParse("files/teste/test1.txt", "files/teste/test2.txt", "files/teste/test3.txt", grafo);

	//Graph myGraph;

	/*myGraph.addVertex(1, 'H');
	myGraph.addVertex(2, 'I');
	myGraph.addVertex(3, 'F');
	myGraph.addVertex(4, 'E');
	myGraph.addVertex(5, 'G');
	myGraph.addVertex(6, 'D');
	myGraph.addVertex(7, 'B');
	myGraph.addVertex(8, 'A');
	myGraph.addVertex(9, 'C');
	*/

/*	for (int i = 1; i < 10; i++) {
		myGraph.addVertex(i);

	}*/
	/*
	myGraph.addEdge(1, 2, 3);
	myGraph.addEdge(1, 3, 4);
	myGraph.addEdge(1, 4, 4);

	myGraph.addEdge(2, 5, 2);

	myGraph.addEdge(3, 5, 5);
	myGraph.addEdge(3, 4, 3);
	myGraph.addEdge(3, 6, 3);

	myGraph.addEdge(4, 6, 5);

	myGraph.addEdge(5, 8, 4);
	myGraph.addEdge(5, 7, 6);

	myGraph.addEdge(6,9, 3);
	myGraph.addEdge(6, 7, 2);
	myGraph.addEdge(7, 8, 2);
	myGraph.addEdge(7,9, 4);
	*/


	/*	myGraph.addEdge(8, 7, 2);

	myGraph.addEdge(7, 9, 4);
	myGraph.addEdge(7, 6, 2);

	myGraph.addEdge(6, 9, 3);*/
/*	myGraph.addEdge(1, 2, 2);
	myGraph.addEdge(1, 7, 4);
	myGraph.addEdge(2, 3, 4);
	myGraph.addEdge(2, 4, 2);
	myGraph.addEdge(2, 7, 6);
	myGraph.addEdge(3, 4, 3);
	myGraph.addEdge(4, 5, 5);
	myGraph.addEdge(4, 6, 3);
	myGraph.addEdge(5, 6, 3);
	myGraph.addEdge(5, 8, 4);
	myGraph.addEdge(6, 7, 5);
	myGraph.addEdge(6, 8, 4);
	myGraph.addEdge(7, 9, 2);
	myGraph.addEdge(8, 9, 3);

	vector<Edge> e;

	for (size_t i = 0; i < myGraph.getVertexSet().size(); i++) {
		vector<Edge> a = myGraph.getVertexSet()[i]->getAdj();
		for (size_t j = 0; j < a.size(); j++) {
			e.push_back(a[j]);
		}

	}
	disjointSet d;
	d.createSet(myGraph.getVertexSet());

	string s;
	//int t = GetMilliCount();
	//MST m = kruskal(e, d);
	//cout << m.minPath << endl;*/

	/*int j = GetMilliSpan(t);
	cout << j << endl;
	for (size_t i = 0; i < myGraph.getVertexSet().size(); i++) {
	if (!myGraph.getVertexSet()[i]->isVisited()) {

	cout << myGraph.getVertexSet()[i]->getId() << "  ERRO\n";
	break;
	}*/
	//	}
	//	menu();*/


	return 0;
}
