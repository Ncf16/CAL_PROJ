/*
 * disjoint-set.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Filipe
 */

#ifndef SRC_DISJOINT_SET_CPP_
#define SRC_DISJOINT_SET_CPP_

#include<vector>
#include<iostream>
#include <queue>
#include<map>
#include "grafo.h"
using namespace std;
typedef struct {
	bool operator()(const vector<Vertex *> &vec1, const vector<Vertex *> &vec2) {
		return vec1.size() > vec2.size();
	}

} compareSize;
class disjointSet {
private:

	priority_queue<vector<Vertex *>, vector<vector<Vertex *> >, compareSize> disjoinedSet;
	map<int, Vertex*> toBeProcessed;
public:
	disjointSet();
	void createSet(Vertex *v);
	void mergeSet(vector<Vertex *> &vec, vector<Vertex*> &vec2);
	Vertex* findSet(long long id);
};

#endif /* SRC_DISJOINT_SET_CPP_ */
