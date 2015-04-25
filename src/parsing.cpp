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
#include <iomanip>

long long stringToLongLong(string s) {
	long long tempNum;
	stringstream(s) >> tempNum;

	cout << "Numero em String: " << s << endl;
	cout << "Numero transformado: " << tempNum << endl << endl;

	return tempNum;
}

double stringToDouble(string s) {
	double tempNum;
	stringstream(s) >> tempNum;

//	cout << setprecision(10);
//	cout << "Numero em String: " << s << endl;
//	cout << "Numero transformado: " << tempNum << endl;

	return tempNum;
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
	long long idNode;
	double lat;
	double lon;
	string roadName;
	string s;
	map<long long, Vertex*> vertexMap;
	map<long long, string> tempRoadMap;

	//READING NODE FILE
	nodeRead.open(nodeFileName);
	if (!nodeRead.fail()) {
		int count = 0;
		int tempNum;
		stringstream tempStream;

		getline(nodeRead, s, ';');

		grafo.setMinLat(stringToDouble(s));
		getline(nodeRead, s, ';');
		grafo.setMaxLat(stringToDouble(s));
		getline(nodeRead, s, ';');
		grafo.setMinLon(stringToDouble(s));
		getline(nodeRead, s, ';');
		grafo.setMaxLon(stringToDouble(s));
		getline(nodeRead, s, '\n');
//		cout << "A latitude min e " << grafo.getMinLat() << endl;
//		cout << "A latitude max e " << grafo.getMaxLat() << endl;
//		cout << "A longitude min e " << grafo.getMinLon() << endl;
//		cout << "A longitude e max" << grafo.getMaxLon() << endl;

		while (!nodeRead.eof()) {
			getline(nodeRead, s, ';');
			idNode = stringToLongLong(s);
			cout << "1 read" << endl;
			getline(nodeRead, s, ';');
			lat = stringToDouble(s);
			cout << "2 read" << endl;
			getline(nodeRead, s, ';');
			lon = stringToDouble(s);
			cout << "3 read" << endl;
			getline(nodeRead, s, '\n');
			cout << "4 read" << endl << endl;
			//acrescentar directamente ou após input

			if (nodeRead.eof()) //This line is needed because the parser has a empty line at its end
				break;

			Vertex* vertexNew = new Vertex(idNode, lat, lon);
			vertexMap.insert(pair<long long, Vertex*>(idNode, vertexNew));

//			cout << setprecision(10);
//			cout << count++ << endl;
//			cout << "O idNode e " << idNode << endl;
//			cout << "A latitude e " << lat << endl;
//			cout << "A longitude e " << lon << endl;
//			cout << "O idNode do inserido e " << vertexMap[idNode]->getId()
//					<< endl;
//			cout << "A latitude do inserido e " << vertexMap[idNode]->getLat()
//					<< endl;
//			cout << "A longitude do inserido e " << vertexMap[idNode]->getLon()
//					<< endl << endl;

		}
		cout << "Existem " << vertexMap.size() << " vertices." << endl << endl;
	} else {
		cout << "Node file unexistent.\n";
	}
	nodeRead.close();
	//READING ROAD FILE
	roadRead.open(roadFile);
	if (!roadRead.fail()) {
		int count = 0;
		while (!roadRead.eof()) {
			getline(roadRead, s, ';');
			idEdge = stringToLongLong(s);

			getline(roadRead, s, ';');
			roadName = s;

			getline(roadRead, s, '\n');
			//Does nothing. We do not need the true/false line

			if (roadRead.eof()) //This line is needed because the parser has a empty line at its end
				break;

			tempRoadMap[idEdge] = roadName;
			string roadName1 = tempRoadMap[idEdge];

			cout << count++ << endl;
			cout << "O idEdge e " << idEdge << endl;
			cout << "A estrada lida e " << roadName << endl;
			cout << "A estrada no map e " << roadName1 << endl << endl;

		}
	} else {
		cout << "Road file unexistent.\n";
	}
	roadRead.close();

	//READING EDGE FILE
	edgeRead.open(edgeFileName);
	int count = 0;
	if (!edgeRead.fail()) {
		while (!edgeRead.eof()) {

			cout << "Edge nr. " << count++ << endl;
			cout << "Reading idEdge, idSource, idDest" << endl;
			//add edges
			getline(edgeRead, s, ';');
			idEdge = stringToLongLong(s);
			getline(edgeRead, s, ';');
			idSource = stringToLongLong(s);
			getline(edgeRead, s, ';');
			idDest = stringToLongLong(s);
			//getline(edgeRead, s, '\n');

			if (edgeRead.eof()) //This line is needed because the parser has a empty line at its end
				break;

			string roadName = tempRoadMap[idEdge]; //uses roadnames associated with the id
			Vertex* org = vertexMap[idSource];
			Vertex* dest = vertexMap[idDest];

			int peso = distance(org->getLat(), org->getLon(), dest->getLat(), dest->getLon());
			cout << setprecision(10);
			cout << "org->getLat() : " << org->getLat() << endl;
			cout << "org->getLon() : " << org->getLon() << endl;
			cout << "dest->getLat() : " << dest->getLat() << endl;
			cout << "dest->getLon() : " << dest->getLon() << endl;
			cout << "org->getId() : " << org->getId() << endl;
			cout << "O peso disto e: " << peso << endl << endl;

			Edge e(org, dest, roadName, peso, idEdge);
			org->addEdge(e);
			dest->addEdge(e); //We assume that there is no edge where org and dest are the same node
			//cout << "O peso e: " << peso << endl;
			//cout << "Edge id: " << idEdge << " where idOrig is " << org->getId() << " and idDest is " << dest->getId() << endl << endl;
			//cout << "Edge id: " << idEdge << " where edge weight pulled from origin " << org->getAdj()[0].getWeight() << " and idDest is " << dest->getId() << endl << endl;
		}
	} else {
		cout << "Edge file unexistent.\n";
	}
	cout << "Creating Disjoint Set" << endl;

	edgeRead.close();
	getline(cin, s);
	disjointSet d(vertexMap);
	cout << vertexMap.size() << endl;
	d.createDisjoinedSet();
	cout << d.getDisjoinedSet().size() << endl;
	d.getCount();
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
//	Graph grafo;
//	loadParse("files/tondelinha/tond1.txt", "files/tondelinha/tond2.txt", "files/tondelinha/tond3.txt", grafo);
	menu();
	return 0;
}
