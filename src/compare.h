/*

 * compare.h
 *
 *  Created on: 23/04/2015
 *      Author: Filipe
 */
typedef struct {
	long long id;
	string nome;
} edgeTemp;

typedef struct {
	bool operator()(const Vertex * s, const Vertex *v) {
		return (s->getId() > v->getId());
	}
} comparableVertex;

typedef struct {
	bool operator()(const Edge &s, const Edge &v) {
		return (s.getWeight() > v.getWeight());
	}
} comparableEdge;

typedef struct {

	bool operator()(const edgeTemp &e1, const edgeTemp &e2) {
		return e1.id > e2.id;
	}
} comparableEdgeTemp;
