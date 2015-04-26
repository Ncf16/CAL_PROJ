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

void disjointSet::createSet(vector<Vertex*> vec) {

	vector<Vertex*>::iterator it = vec.begin();
	vector<Vertex*>::iterator ite = vec.end();
	for (; it != ite; it++) {
		createSet(*it);
	}
}
void disjointSet::createSet(Vertex *v) {
	vector<Vertex*> vec;
	vec.push_back(v);
	disjoinedSet.push_back(vec);
}


vector<Vertex *> disjointSet::mergeSet(vector<Vertex *> &vec, vector<Vertex*> &vec2) {

	if (vec.size() > vec2.size()) {
		while (vec2.size() > 0) {

			vec.push_back(vec2[0]);
			vec2.erase(vec2.begin());

		}
		return vec;
	} else {
		while (vec.size() > 0) {

			vec2.push_back(vec[0]);
			vec.erase(vec.begin());

		}

		return vec2;
	}
	vector<Vertex *> v;
	return v;
}
vector<Vertex*>& disjointSet::findSet(Vertex *v) { //TODO try to alterar algoritmo,
	for (size_t i = 0; i < disjoinedSet.size(); i++) {

		for (size_t j = 0; j < disjoinedSet[i].size(); j++) {
			if (disjoinedSet[i][j] == v)
				return disjoinedSet[i];
		}
	}
	vector<Vertex *> vec;
	return vec;
}
vector<vector<Vertex *> > disjointSet::getDisjoinedSet() const {
	return disjoinedSet;
}

void disjointSet::setDisjoinedSet(const vector<vector<Vertex *> > disjoinedSet) {
	this->disjoinedSet = disjoinedSet;
}

 
