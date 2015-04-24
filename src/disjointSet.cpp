/*
 * disjointSet.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Filipe
 */

#include "disjointSet.h"
#include<fstream>
disjointSet::disjointSet() {
}
void disjointSet::createSet(Vertex *v) {
	vector<Vertex*> vec;
	vec.push_back(v);
	disjoinedSet.push_back(vec);
}

disjointSet::disjointSet(map<int, Vertex*> toBeProcessed, long long id) {
	this->toBeProcessed = toBeProcessed;
	this->firstId = id;

}

void disjointSet::mergeSet(vector<Vertex *> &vec, vector<Vertex*> &vec2) {

	if (vec.size() > vec2.size()) {
		for (size_t i = 0; i < vec2.size(); i++) {

			vec.push_back(vec2[i]);
			vec2.erase(vec2.begin() + i);
			i -= 2;

		}
	} else {
		for (size_t i = 0; i < vec.size(); i++) {

			vec2.push_back(vec[i]);
			vec.erase(vec.begin() + i);
			i -= 2;

		}
	}
}
Vertex* disjointSet::findSet(long long id) {
	return toBeProcessed[id];
}
vector<vector<Vertex *> > disjointSet::getDisjoinedSet() const {
	return disjoinedSet;
}

void disjointSet::setDisjoinedSet(const vector<vector<Vertex *> > disjoinedSet) {
	this->disjoinedSet = disjoinedSet;
}

long long disjointSet::getFirstId() const {
	return firstId;
}

void disjointSet::setFirstId(long long id) {
	this->firstId = id;
}

map<int, Vertex*> disjointSet::getToBeProcessed() const {
	return toBeProcessed;
}

void disjointSet::setToBeProcessed(const map<int, Vertex*> toBeProcessed) {
	this->toBeProcessed = toBeProcessed;
}

long long atol2(string s) {
	long long n = 0;
	for (unsigned int i = 0; i < s.length(); i++) {
		n *= 10;
		n += s[i] - '0';
	}
	return n;
}
void disjointSet::createDisjoinedSet() {
}
int main() {

	cout << "IN" << endl;
	ifstream nodeRead;
	char * nodeFileName = "files/tondelinha/tond1.txt";

	long long lat;
	long long lon;
	long long idNode;
	string roadName;
	string s;
	map<int, Vertex*> vertexMap;
	map<int, string> tempRoadMap;

	//READING NODE FILE
	nodeRead.open(nodeFileName);
	if (!nodeRead.fail()) {
		getline(nodeRead, s, ';');
		getline(nodeRead, s, ';');
		getline(nodeRead, s, ';');
		getline(nodeRead, s, ';');
		getline(nodeRead, s, '\n');

		while (!nodeRead.eof()) {
			getline(nodeRead, s, ';');
			idNode = atol2(s);
			getline(nodeRead, s, ';');
			lat = atol2(s);
			getline(nodeRead, s, ';');
			lon = atol2(s);
			getline(nodeRead, s, '\n');
			//acrescentar directamente ou após input
			vertexMap.insert(pair<int, Vertex*>(idNode, new Vertex(idNode, lat, lon)));
		}
	} else {
		cout << "Node file unexistent.\n";
	}
	nodeRead.close();

	disjointSet d(vertexMap, idNode);
	cout << d.getToBeProcessed().size() << endl;
	return 0;
}
