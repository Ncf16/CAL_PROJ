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

public:
	disjointSet();
	void createSet();
	void createSet(vector<Vertex*> vec);
	void createSet(Vertex *v);
	vector<Vertex *>  mergeSet(vector<Vertex *> &vec, vector<Vertex*> &vec2);
	vector<Vertex*>& findSet(Vertex *v);
	void createDisjoinedSet();
	void createDisjoinedSet(Vertex *v, vector<Vertex *> &vec);
	vector<vector<Vertex *> > getDisjoinedSet() const;
	void setDisjoinedSet(const vector<vector<Vertex *> > disjoinedSet);
	long long getFirstId() const;
	void setFirstId(long long firstId);
	void setToBeProcessed(const map<long long, Vertex*> toBeProcessed);
	int getCount() {
		int count = 0;
		for (size_t i = 0; i < disjoinedSet.size(); i++) {
			count += disjoinedSet[i].size();
		}
		return count;
	}
	void deleteZeros() {
		for (size_t i = 0; i < disjoinedSet.size(); i++) {
			if (disjoinedSet[i].size() == 0) {
				disjoinedSet.erase(disjoinedSet.begin() + i);
				i -= 1;
			}
		}
	}
};
#endif
