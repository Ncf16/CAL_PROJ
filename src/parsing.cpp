/*
 * parsing.cpp
 *
 *  Created on: 22/04/2015
 *      Author: Filipe
 */
#include "parsing.h"
#include "grafo.h"
#include "compare.h"
#include <math.h>
#include <list>

long long atol(string s) {
	long long n = 0;
	for (unsigned int i = 0; i < s.length(); i++) {
		n *= 10;
		n += s[i] - '0';
	}
	return n;
}
double deg2rad(double deg) {
	return (deg * PI / 180);
}
double rad2deg(double rad) {
	return (rad * 180 / PI);
}


void loadParse(char * edgeFileName, char * nodeFileName, char * roadFile, Graph &grafo) {
	ifstream edgeRead, nodeRead, roadRead;
	nodeRead.open(nodeFileName);
	edgeRead.open(edgeFileName);
	roadRead.open(roadFile);
	long long idSource;
	long long idEdge;
	long long idDest;
	long long lat;
	long long lon;
	long long idNode;
	string s;
	set<Vertex*, comparableVertex> setVertex;
	set<Edge, comparableEdge> setEdge;
	set<edgeTemp, comparableEdgeTemp> setEdgeTemp;

	set<Vertex*, comparableVertex>::iterator it;
	set<Vertex*, comparableVertex>::iterator ite;

	if ((!nodeRead.fail()) && (!edgeRead.fail()) && (!roadRead.fail())) {
		while (!nodeRead.eof()) {
			getline(nodeRead, s, ';');
			idNode = atol(s);
			getline(nodeRead, s, ';');
			lat = atol(s);
			getline(nodeRead, s, ';');
			lon = atol(s);
			getline(nodeRead, s, '\n');
			//acrescentar directamente ou após input
			setVertex.insert(new Vertex(idNode, lat, lon));
		}
		it = setVertex.begin();
		ite = setVertex.end();

		while (!edgeRead.eof()) {
			//add edges
			getline(edgeRead, s, ';');
			idEdge = atol(s);
			getline(edgeRead, s, ';');
			idSource = atol(s);
			getline(edgeRead, s, ';');
			idDest = atol(s);
			getline(edgeRead, s, '\n');
			Vertex *org = *it;
			it++;
			Vertex *dest = *it;
			it++;
			if (it == ite)
				break;
			//find aos vertex
			int peso = distance(org->getLat(), org->getLon(), dest->getLat(), dest->getLon());
			Edge e(org, dest, peso, idEdge);

			setEdge.insert(e);
			//grafo.addVertex(idSource);
			//grafo.addVertex(idDest);
			//grafo.addEdge(idSource, idDest, distance(1, 1, 1, 1), idEdge);
		}
	} else {
		cout << "The files you tried to open don´t exist\n";
	}
	cout << setEdge.size() << endl << setVertex.size() << endl;
	edgeRead.close();
	nodeRead.close();
}
//ver link
double distance(double lat1, double lon1, double lat2, double lon2) {
	double theta, dist;
	theta = lon1 - lon2;
	dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
	dist = acos(dist);
	dist = rad2deg(dist);
	dist = dist * 60 * 1.1515;
	return dist * 1.609344;
}
int main() {
	Graph p;
	loadParse("files/tond3.txt", "files/tond1.txt", "files/tond2.txt", p);
	return 0;
}

