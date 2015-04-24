/*
 * disjointSet.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Filipe
 */

#include "disjointSet.h"
#include<fstream>
disjointSet::disjointSet() {
	firstId = 0;
}
void disjointSet::createSet(Vertex *v) {
	vector<Vertex*> vec;
	vec.push_back(v);
	disjoinedSet.push_back(vec);
}

disjointSet::disjointSet(map<long long, Vertex*> toBeProcessed, long long id) {
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

map<long long, Vertex*> disjointSet::getToBeProcessed() const {
	return toBeProcessed;
}

void disjointSet::setToBeProcessed(const map<long long, Vertex*> toBeProcessed) {
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

	map<long long, Vertex*>::iterator it = toBeProcessed.begin();
	map<long long, Vertex*>::iterator ite = toBeProcessed.end();
	cout << "DisjoinedSet" << endl;
	for (; it != ite; it++) {
		it->second->setVisited(false);
	}
	it = toBeProcessed.begin();
	for (; it != ite; it++) {
		vector<Vertex *> res;
		if (!it->second->isVisited()) {
			createDisjoinedSet(it->second, res);
			disjoinedSet.push_back(res);
		}
	}

}

void disjointSet::createDisjoinedSet(Vertex *v, vector<Vertex *> &vec) {
	v->setVisited(true);
	vec.push_back(v);
	vector<Edge>::iterator it = v->getAdj().begin();
	vector<Edge>::iterator ite = v->getAdj().end();
	for (; it != ite; it++) {
		if (!it->getDest()->isVisited()) {
			createDisjoinedSet(it->getDest(), vec);
		}

	}

}

