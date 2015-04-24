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
#include "disjointSet.h"
#include <list>
#include <map>

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

void loadParse(char * nodeFileName, char * roadFile, char * edgeFileName, Graph &grafo) {
	ifstream nodeRead, roadRead, edgeRead;

	long long idSource;
	long long idEdge;
	long long idDest;
	long long lat;
	long long lon;
	long long idNode;
	string roadName;
	string s;
	map<long long, Vertex*> vertexMap;
	map<long long, string> tempRoadMap;
	//READING NODE FILE
	nodeRead.open(nodeFileName);
	if (!nodeRead.fail()) {
		getline(nodeRead, s, ';');
		grafo.setMinLat(atol(s));
		getline(nodeRead, s, ';');
		grafo.setMaxLat(atol(s));
		getline(nodeRead, s, ';');
		grafo.setMinLon(atol(s));
		getline(nodeRead, s, ';');
		grafo.setMaxLon(atol(s));
		getline(nodeRead, s, '\n');

		while (!nodeRead.eof()) {
			getline(nodeRead, s, ';');
			idNode = atol(s);
			getline(nodeRead, s, ';');
			lat = atol(s);
			getline(nodeRead, s, ';');
			lon = atol(s);
			getline(nodeRead, s, '\n');
			//acrescentar directamente ou ap�s input
			vertexMap.insert(pair<int, Vertex*>(idNode, new Vertex(idNode, lat, lon)));
		}
	} else {
		cout << "Node file unexistent.\n";
	}
	nodeRead.close();
	//READING ROAD FILE
	roadRead.open(roadFile);
	if (!roadRead.fail()) {
		while (!roadRead.eof()) {
			getline(roadRead, s, ';');
			idEdge = atol(s);
			getline(roadRead, s, ';');
			roadName = s;
			getline(roadRead, s, ';');
			//Does nothing. We do not need the true/false line
			getline(roadRead, s, '\n');
			tempRoadMap.insert(pair<long long, string>(idEdge, roadName));
		}
	} else {
		cout << "Road file unexistent.\n";
	}
	roadRead.close();
	cout << vertexMap.size() << endl;
	//READING EDGE FILE
	edgeRead.open(edgeFileName);
	if (!edgeRead.fail()) {
		while (!edgeRead.eof()) {
			//add edges
			getline(edgeRead, s, ';');
			idEdge = atol(s);
			cout << idEdge << endl;
			getline(edgeRead, s, ';');
			idSource = atol(s);
			cout << idSource << endl;
			getline(edgeRead, s, ';');
			idDest = atol(s);
			cout << idDest << endl;
			getline(edgeRead, s, '\n');
			cout << "S" << endl;
			cout << "Here\n";
			string roadName = tempRoadMap[idEdge];
			Vertex* org = vertexMap[idSource];
			Vertex* dest = vertexMap[idDest];

			int peso = distance(org->getLat(), org->getLon(), dest->getLat(), dest->getLon());

			Edge e(org, dest, roadName, peso, idEdge);
			org->addEdge(e);
			dest->addEdge(e);   //We assume that there is no edge where org and dest are the same node

		}
	} else {
		cout << "Edge file unexistent.\n";
	}
	cout << "Disjoint" << endl;
	getline(cin, s);
	edgeRead.close();
	getline(cin, s);
	disjointSet d(vertexMap, idNode);
	d.createDisjoinedSet();
	cout << d.getDisjoinedSet().size() << endl;
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
	Graph grafo;
	loadParse("files/tondelinha/tond1.txt", "files/tondelinha/tond2.txt", "files/tondelinha/tond3.txt", grafo);
	return 0;
}
