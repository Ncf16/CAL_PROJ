/*
 * disjointSet.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Filipe
 */

#include "disjointSet.h"

disjointSet::disjointSet() {
}

void disjointSet::createSet(Vertex *v) {
	vector<Vertex*> vec;
	vec.push_back(v);
	disjoinedSet.push(vec);
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
