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

void loadParse(string nodeFileName, string roadFile, string edgeFileName,
		Graph &grafo) {
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

//			cout << "O idNode e " << idNode << endl;
//			cout << "A latitude e " << lat << endl;
//			cout << "A longitude e " << lon << endl;
//			cout << "O idNode do inserido e " << vertexMap[idNode]->getId()
//					<< endl;
//			cout << "A latitude do inserido e " << vertexMap[idNode]->getLat()
//					<< endl;
//			cout << "A longitude do inserido e " << vertexMap[idNode]->getLon()
//					<< endl;
//			cout << "O x do inserido e " << vertexMap[idNode]->getX() << endl;
//			cout << "O y do inserido e " << vertexMap[idNode]->getY() << endl
//					<< endl;

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

//		cout << setprecision(10);
//		cout << count++ << endl;
//		cout << "A latitude min e " << grafo.getMinLat() << endl;
//		cout << "A latitude max e " << grafo.getMaxLat() << endl;
//		cout << "A longitude min e " << grafo.getMinLon() << endl;
//		cout << "A longitude e max" << grafo.getMaxLon() << endl << endl;
//
//		cout << "O min X e " << minX << endl;
//		cout << "O max X e " << maxX << endl;
//		cout << "O min Y e " << minY << endl;
//		cout << "O max Y e " << maxY << endl << endl;
//
//		cout << "A width e " << maxX - minX << endl;
//		cout << "A height e " << maxY - minY << endl << endl;
//
//		cout << "O x central e " << (maxX + minX) / 2 << endl;
//		cout << "O y central e " << (maxY + minY) / 2 << endl << endl;

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

//			cout << count++ << endl;
//			cout << "O idEdge e " << idEdge << endl;
//			cout << "A estrada lida e " << roadName << endl;
//			cout << "A estrada no map e " << roadName1 << endl << endl;

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

//			cout << "Edge nr. " << count++ << endl;
//			cout << "Reading idEdge, idSource, idDest" << endl;
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

			double peso = distance(org->getLat(), org->getLon(), dest->getLat(),
					dest->getLon());
//			cout << setprecision(10);
//			cout << "org->getLat() : " << org->getLat() << endl;
//			cout << "org->getLon() : " << org->getLon() << endl;
//			cout << "dest->getLat() : " << dest->getLat() << endl;
//			cout << "dest->getLon() : " << dest->getLon() << endl;
//			cout << "org->getId() : " << org->getId() << endl;
//			cout << "O peso disto e: " << peso << endl << endl;

			Edge e(org, dest, roadName, peso, idEdge);
			Edge f(dest, org, roadName, peso, idEdge);
			org->addEdge(e);
			dest->addEdge(f);
			//We assume that there is no edge where org and dest are the same node

			//cout << "O peso e: " << peso << endl;
//			cout << "Edge id: " << idEdge << " where idOrig is " << org->getId() << " and idDest is " << dest->getId() << endl << endl;
//			cout << "Edge id: " << idEdge << " where edge weight pulled from origin " << org->getAdj()[0].getWeight() << " and idDest is " << dest->getId() << endl << endl;
		}
	} else {
		cout << "Edge file unexistent.\n";
	}
	//cout << "Creating Disjoint Set" << endl;

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
	dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2))
			+ cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
	dist = acos(dist);
	dist = rad2deg(dist);
	dist = dist * 60 * 1.1515;
	return dist * 1.609344;
}

int main() {
	Graph grafo;
	loadParse("files/tondelinha/tond1.txt", "files/tondelinha/tond2.txt",
			"files/tondelinha/tond3.txt", grafo);
	menu();
//	return 0;
}
