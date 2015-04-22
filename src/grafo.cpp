/*
 * grafo.cpp
 *
 *  Created on: 22/04/2015
 *      Author: Filipe
 */


#include "grafo.h"

int main() {
	cout << "Treta\n";
	return 0;
}

Edge::Edge(Vertex*d, double w) :
		dest(d), weight(w) {
}

void Vertex::removeVertex(const long & in) {

	for (size_t i = 0; i < adj.size(); i++) {

		if (*(adj[i].dest) == in) {

			adj.erase(adj.begin() + i);
			i -= 2;
		}
	}
}

bool operator==(Vertex lhs, Vertex rhs) {
	if (lhs.id == rhs.id)
		return true;
	else
		return false;
}

Vertex::Vertex(long in) :
		id(in), visited(false) {
}

vector<long> Graph::bfs(Vertex * v) const {
	vector<long> answer;
	Vertex *check;
	queue<Vertex*> fila;
//quem queremos visitar por ordem de aparencia e não ir a um e visitar todos os descendentes desse
	fila.push(v);
	do {
		check = fila.front();
		fila.pop();
		answer.push_back(check->id);
		check->visited = true;
		for (size_t j = 0; j < check->adj.size(); j++) {
			if (!check->adj[j].dest->visited) {
				fila.push(check->adj[j].dest);
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

Vertex * Graph::findVertex(const long &info) {
	for (size_t i = 0; i < vertexSet.size(); i++) {
		if (vertexSet[i]->id == info) {
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
		if (*e[i].dest == *destiny) {

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
