/*
 * grafo.cpp
 *
 *  Created on: 22/04/2015
 *      Author: Filipe
 */
#include "grafo.h"
#include<iostream>

void Vertex::removeVertex(const long & in) {
	for (size_t i = 0; i < adj.size(); i++) {
		if (*(adj[i].getDest()) == in) {
			adj.erase(adj.begin() + i);
			i -= 2;
		}
	}
}
bool operator==(Vertex lhs, Vertex rhs) {
	if (lhs.getId() == rhs.getId())
		return true;
	else
		return false;
}

Vertex::Vertex(long long in) :
		id(in), visited(false), lat(0), lon(0) {
}

Vertex::Vertex(long long in, double lat, double lon) :
		id(in), visited(false), lat(lat), lon(lon) {
}

bool Vertex::addEdge(Edge e) {
	adj.push_back(e);
}

Edge::Edge(Vertex*d, double w) : //TODO check if id should be 0
		dest(d), weight(w),id(0) {
}

//ter id ou não
Edge::Edge(Vertex *orig, Vertex*d, string name, double w, long long id) {
	this->name = name;
	this->dest = d;
	this->orig = orig;
	this->weight = w;
	this->id = id;
}

vector<long> Graph::bfs(Vertex * v) const {
	vector<long> answer;
	Vertex *check;
	queue<Vertex *> fila;
	fila.push(v);
	do {
		check = fila.front();
		fila.pop();
		answer.push_back(check->id);
		check->visited = true;
		for (size_t j = 0; j < check->adj.size(); j++) {
			if (!check->adj[j].getDest()->visited) {
				fila.push(check->adj[j].getDest());
			}
		}
	} while (!fila.empty());

	return answer;
}

vector<long> Graph::dfs() const {

	vector<long> answer;
	for (size_t i = 0; i < vertexSet.size(); i++) {
		if (!vertexSet[i]->visited) {
			dfs(answer, vertexSet[i]);
		}
	}
	return answer;
}
void Graph::dfs(vector<long> &vec, Vertex* v) const {
	v->visited = true;
	vec.push_back(v->id);

	for (size_t i = 0; i < v->adj.size(); i++) {
		if (!v->adj[i].dest->visited) {
			dfs(vec, v->adj[i].dest);
		}
	}
}
int Graph::getEdgeSize(const long &inf) {
	Vertex *source = findVertex(inf);
	return source->adj.size();
}

bool Graph::removeVertex(const long &in) {

	Vertex *v = findVertex(in);
	if (v == NULL)
		return false;

	for (size_t i = 0; i < vertexSet.size(); i++) {

		if ((*vertexSet[i]) == (*v)) {
			vertexSet.erase(vertexSet.begin() + i);
			i -= 2;
		} else
			vertexSet[i]->removeVertex(in);
	}
	return true;
}

bool Graph::addEdge(const long & sourc, const long & dest, double w) {

	Vertex *source = findVertex(sourc);
	Vertex *destiny = findVertex(dest);

	if (source == NULL || destiny == NULL)
		return false;
	Edge e(destiny, w);
	source->adj.push_back(e);
	return true;
}

bool Graph::addEdge(const long & sourc, const long & dest, double w, long id) {

	Vertex *source = findVertex(sourc);
	Vertex *destiny = findVertex(dest);

	if (source == NULL || destiny == NULL)
		return false;
	Edge e(destiny, w);
	e.id = id;
	source->adj.push_back(e);

	return true;
}

Vertex * Graph::findVertex(const long &info) {
	for (size_t i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->getId() == info) {
			return vertexSet[i];
		}
	}
	return NULL;
}
bool Graph::removeEdge(const long &sourc, const long &dest) {
	bool found = false;
	Vertex *source = findVertex(sourc);
	Vertex *destiny = findVertex(dest);
	if (source == NULL || destiny == NULL)
		return false;

	vector<Edge> e = source->adj;
	for (size_t i = 0; i < e.size(); i++) {
		if (*e[i].getDest() == *destiny) {
			source->adj.erase(source->adj.begin() + i);
			e = source->adj;
			i -= 2;
			found = true;
		}
	}
	return found;
}
bool Graph::addVertex(const long &in) {
	if (getNumVertex() == 0) {
		vertexSet.push_back(new Vertex(in));
		vertexSet[vertexSet.size() - 1]->visited = false;
		return true;
	} else {
		for (size_t i = 0; i < vertexSet.size(); i++) {
			if (vertexSet[i]->id == in) {
				return false;
			}
		}
	}
	vertexSet.push_back(new Vertex(in));
	vertexSet[vertexSet.size() - 1]->visited = false;
	return true;
}

int Graph::getNumVertex() const {
	return vertexSet.size();
}

vector<Vertex *> Graph::getVertexSet() const {
	return vertexSet;
}

bool Graph::addVertex(Vertex *v) {
	if (getNumVertex() == 0) {
		vertexSet.push_back(v);
		return true;
	} else {
		for (size_t i = 0; i < vertexSet.size(); i++) {
			if (vertexSet[i] == v) {
				return false;
			}
		}
	}

	return true;

}
bool Graph::addEdge(Edge e) {

	e.orig->adj.push_back(e);

	//tentar adicionar ou tentar encontrar, ver como fazer + eficiente
}

double Graph::getMaxLat() const {
	return maxLat;
}

void Graph::setMaxLat(double maxLat) {
	this->maxLat = maxLat;
}

double Graph::getMaxLon() const {
	return maxLon;
}

void Graph::setMaxLon(double maxLon) {
	this->maxLon = maxLon;
}

double Graph::getMinLat() const {
	return minLat;
}

void Graph::setMinLat(double minLat) {
	this->minLat = minLat;
}

double Graph::getMinLon() const {
	return minLon;
}

void Graph::setMinLon(double minLon) {
	this->minLon = minLon;
}
