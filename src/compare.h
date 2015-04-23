/*
 * compare.h
 *
 *  Created on: 23/04/2015
 *      Author: Filipe
 */

typedef struct {
	bool operator()(const Vertex * s,const Vertex *v) {
		if (s->getId() > v->getId())
			return true;
		else
			return false;
	}
} comparableVertex;

typedef struct {
	bool operator()(const Edge &s, const Edge &v) {
		if (s.getWeight() > v.getWeight())
			return true;
		else
			return false;
	}
} comparableEdge;
