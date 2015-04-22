/*
 * parsing.cpp
 *
 *  Created on: 22/04/2015
 *      Author: Filipe
 */
#include "parsing.h"
#include "grafo.h"
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
void load(char * edgeFileName, char * nodeFileName, Graph &grafo) {
	ifstream edgeRead, nodeRead;
	nodeRead.open(nodeFileName);
	edgeRead.open(edgeFileName);
	long long idSource;
	long long idEdge;
	long long idDest;
	long long lat;
	long long lon;
	long long idNode;
	string s;
	list<Vertex*> listaVertex;
	list<Edge> listaEdge;
	cout << "Indices" << endl;

	if ((!nodeRead.fail()) && (!edgeRead.fail())) {
		while (!nodeRead.eof()) {
			getline(nodeRead, s, ';');
			idNode = atol(s);
			getline(nodeRead, s, ';');
			lat = atol(s);
			getline(nodeRead, s, ';');
			lon = atol(s);
			getline(nodeRead, s, '\n');
			//acrescentar directamente ou após input
			listaVertex.push_back(new Vertex(idNode, lat, lon));
		}
		while (!edgeRead.eof()) {
			//add edges
			getline(edgeRead, s, ';');
			idEdge = atol(s);
			getline(edgeRead, s, ';');
			idSource = atol(s);
			getline(edgeRead, s, ';');
			idDest = atol(s);
			getline(edgeRead, s, '\n');
			Vertex *org;
			Vertex *dest;
			//find aos vertex
			listaEdge.push_back(Edge(org, dest, distance(org->getLat(), org->getLon(), dest->getLat(), dest->getLon()), idEdge));
			//grafo.addVertex(idSource);
			//grafo.addVertex(idDest);
			//grafo.addEdge(idSource, idDest, distance(1, 1, 1, 1), idEdge);
		}
	}
	edgeRead.close();
	nodeRead.close();
}
int main() {
	cout << "Treta\n";
	Graph p;
	load("tond3.txt", "tond1.txt", p);
	return 0;
}

double distance(double lat1, double lon1, double lat2, double lon2) {
	double theta, dist;
	theta = lon1 - lon2;
	dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
	dist = acos(dist);
	dist = rad2deg(dist);
	dist = dist * 60 * 1.1515;
	return dist * 1.609344;
}
