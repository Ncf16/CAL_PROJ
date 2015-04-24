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

class disjointSet {
private:
	//priority_queue<vector<Vertex *>, vector<vector<Vertex *> >, compareSize>
	vector<vector<Vertex *> > disjoinedSet;
	map<long long, Vertex*> toBeProcessed;
	long long firstId;
public:
	disjointSet();
	disjointSet(map<long long, Vertex*> toBeProcessed, long long id);
	void createSet(Vertex *v);
	void mergeSet(vector<Vertex *> &vec, vector<Vertex*> &vec2);
	Vertex* findSet(long long id);
	void createDisjoinedSet();
	void createDisjoinedSet(Vertex *v, vector<Vertex *> &vec);
	vector<vector<Vertex *> > getDisjoinedSet() const;
	void setDisjoinedSet(const vector<vector<Vertex *> > disjoinedSet);
	long long getFirstId() const;
	void setFirstId(long long firstId);
	map<long long, Vertex*> getToBeProcessed() const;
	void setToBeProcessed(const map<long long, Vertex*> toBeProcessed);

};
#endif
