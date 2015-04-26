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
#include <stdlib.h>
#include "Util.h"
long long stringToLongLong(string s) {
	long long tempNum;
	stringstream(s) >> tempNum;

//	cout << "Numero em String: " << s << endl;
//	cout << "Numero transformado: " << tempNum << endl << endl;

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

typedef struct {
	bool operator()(const Edge &e, const Edge &e1) {
		return e.getWeight() < e1.getWeight();
	}

} comprableEdge;
typedef struct {

	double minPath;
	vector<Edge> e;
	vector<Vertex*> v;
} MST;
Edge deleteMin(vector<Edge> &e) {

	Edge f = e[0];
	//cout << f.getOrig()->getId() << " D: " << f.getDest()->getId() << endl;

	e.erase(e.begin());
	return f;
}
void printVector(vector<Vertex*> edgeV) {
	for (size_t i = 0; i < edgeV.size(); i++) {
		cout << edgeV[i]->getId() << endl;
	}
}
void printVector(vector<Edge> edgeV) {
	for (size_t i = 0; i < edgeV.size(); i++) {
		cout << "SOURCE: " << edgeV[i].getOrig()->getId() << " DESTINY: " << edgeV[i].getDest()->getId() << "  Weight: " << edgeV[i].getWeight() << endl;
	}
}
MST kruskal(vector<Edge> edgeV, disjointSet &dis) {
	MST mst;
	mst.minPath = 0;
	int edgesAccepted = 0;
	vector<Vertex*> final;
	make_heap(edgeV.begin(), edgeV.end(), comprableEdge());
	sort_heap(edgeV.begin(), edgeV.end(), comprableEdge());
	//printVector(edgeV);
	string s;
	getline(cin, s);
	while (edgesAccepted < dis.getCount() - 1) {
		if (edgeV.size() <= 0) {
			cout << "END" << endl;
			break;

		}
		Edge e = deleteMin(edgeV); // e = (u,v)

		vector<Vertex*>& uset = dis.findSet(e.getDest());
		vector<Vertex*>& vset = dis.findSet(e.getOrig());
		if (uset != vset) { //ver != usar uset e vset modificar função que tinha e fazer overload do operador != para disjoined sets I think I know how to fix
			edgesAccepted++;
			mst.minPath += e.getWeight();

			dis.mergeSet(uset, vset);

			cout << " S: " << e.getOrig()->getId() << " D: " << e.getDest()->getId() << "  P " << e.getWeight() << endl;
			//cout << " S: " << e.getOrig()->getId() << " D: " << e.getDest()->getId() << "  P " << e.getWeight() << endl;

		}

	}

	dis.deleteZeros();
	cout << dis.getCount() << "  " << dis.getDisjoinedSet().size() << endl;
	mst.v = final;
	return mst;
}

void loadParse(string nodeFileName, string roadFile, string edgeFileName, Graph &grafo) {
	ifstream nodeRead, roadRead, edgeRead;

	long long idSource, idEdge, idDest, idNode;
	double lat, lon;

	string roadName, s;

	map<long long, Vertex*> vertexMap;
	map<long long, string> tempRoadMap;

	//READING NODE FILE
	nodeRead.open(nodeFileName.c_str());
	if (!nodeRead.fail()) {
		int count = 0;
		double x, y;
		double minLat, maxLat, minLon, maxLon;
		double minY, maxY, minX, maxX;
		double centerX, centerY;
		stringstream tempStream;

		minX = 181;
		maxX = -181;
		minY = 91;
		maxY = -91;

		//READING 4 FIRST NUMBERS, MIN/MAX LAT/LON
		getline(nodeRead, s, ';');
		minLat = stringToDouble(s);
		grafo.setMinLat(minLat);
		getline(nodeRead, s, ';');
		maxLat = stringToDouble(s);
		grafo.setMaxLat(maxLat);
		getline(nodeRead, s, ';');
		minLon = stringToDouble(s);
		grafo.setMinLon(minLon);
		getline(nodeRead, s, ';');
		maxLon = stringToDouble(s);
		grafo.setMaxLon(maxLon);
		getline(nodeRead, s, '\n');

		while (!nodeRead.eof()) {
			getline(nodeRead, s, ';');
			idNode = stringToLongLong(s);
			getline(nodeRead, s, ';');
			lat = stringToDouble(s);
			getline(nodeRead, s, ';');
			lon = stringToDouble(s);
			getline(nodeRead, s, ';');
			y = stringToDouble(s);
			getline(nodeRead, s);
			x = stringToDouble(s);
			//getline(nodeRead, s, '\n'); //Same as getline(nodeRead, s);

			if (nodeRead.eof()) //This line is needed because the parser has a empty line at its end
				break;
			//UPDATING MIN/MAX X/Y
			if (x > maxX) {
				maxX = x;

			} else if (x < minX) {
				minX = x;
			}
			if (y > maxY) {
				maxY = y;
			} else if (y < minY) {
				minY = y;
			}

			//centeredX is x-centerX -> by decreasing X by the maps center X, we can center all the points around the origin (0,0)
			Vertex* vertexNew = new Vertex(idNode, lat, lon, x, y, 0, 0);
			vertexMap.insert(pair<long long, Vertex*>(idNode, vertexNew));

		}

		//Now that we have min/max x/y, we can calculate centerX and centerY with it
		centerX = (maxX + minX) / 2;
		centerY = (maxY + minY) / 2;
		grafo.setCenterX((maxX + minX) / 2);
		grafo.setCenterY((maxY + minY) / 2);
		grafo.setWidth(maxX - minX);
		grafo.setHeight(maxY - minY);

		//And now that we have the centerX and centerY, we can set all the vertex centeredX and Y values
		map<long long, Vertex*>::iterator it = vertexMap.begin();
		map<long long, Vertex*>::iterator ite = vertexMap.end();

		for (it = vertexMap.begin(); it != ite; it++) {
			it->second->setCenteredX(it->second->getX() - centerX);
			it->second->setCenteredY(it->second->getY() - centerY);
		}

	} else {
		cout << "Node file unexistent.\n";
	}
	nodeRead.close();
	//READING ROAD FILE
	roadRead.open(roadFile.c_str());
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

		}
	} else {
		cout << "Road file unexistent.\n";
	}
	roadRead.close();

	//READING EDGE FILE
	edgeRead.open(edgeFileName.c_str());
	int count = 0;
	if (!edgeRead.fail()) {
		while (!edgeRead.eof()) {

			getline(edgeRead, s, ';');
			idEdge = stringToLongLong(s);
			getline(edgeRead, s, ';');
			idSource = stringToLongLong(s);
			getline(edgeRead, s, ';');
			idDest = stringToLongLong(s);

			if (edgeRead.eof()) //This line is needed because the parser has a empty line at its end
				break;

			string roadName = tempRoadMap[idEdge]; //uses roadnames associated with the id
			Vertex* org = vertexMap[idSource];
			Vertex* dest = vertexMap[idDest];

			double peso = distance(org->getLat(), org->getLon(), dest->getLat(), dest->getLon());

			Edge e(org, dest, roadName, peso, idEdge);
			Edge f(dest, org, roadName, peso, idEdge);
			org->addEdge(e);
			dest->addEdge(f);
			//We assume that there is no edge where org and dest are the same node
			grafo.addToEdgeSet(e);

		}
	} else {
		cout << "Edge file unexistent.\n";
	}

	edgeRead.close();
	cout << "Dis" << endl;
	getline(cin, s);
	grafo.createDisjoinedSet(vertexMap);
//	disjointSet d(vertexMap);
//	d.createDisjoinedSet();
 	cout << vertexMap.size() << endl;
 	cout << grafo.getVertexSet().size() << endl;
//	d.getCount();
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
