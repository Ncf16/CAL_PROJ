/*
 * grafo.h
 *
 *  Created on: 22/04/2015
 *      Author: Filipe
 */

#ifndef SRC_GRAFO_H_
#define SRC_GRAFO_H_
#include <vector>
#include <queue>
using namespace std;
class Graph;
class Vertex;

class Edge {
	Vertex * dest;
	double weight;
public:
	Edge(Vertex *d, double w);

	const Vertex* getDest() const {
		return dest;
	}

	void setDest(Vertex* dest) {
		this->dest = dest;
	}

	double getWeight() const {
		return weight;
	}

	void setWeight(double weight) {
		this->weight = weight;
	}

	friend class Graph;
	friend class Vertex;

};
class Vertex {
	long id;
	vector<Edge> adj;
	bool visited;
public:
	Vertex(long in);
	friend class Graph;
	friend bool operator==(Vertex lhs, Vertex rhs);
	void removeVertex(const long & in);
	long getId() {
		return id;
	}

	const vector<Edge>& getAdj() const {
		return adj;
	}

	void setAdj(const vector<Edge>& adj) {
		this->adj = adj;
	}

	void setId(long id) {
		this->id = id;
	}

	bool isVisited() const {
		return visited;
	}

	void setVisited(bool visited) {
		this->visited = visited;
	}
};

class Graph {
	vector<Vertex *> vertexSet;
public:
	vector<Vertex *> getVertexSet() const;
	int getNumVertex() const;
	bool addVertex(const long & in);
	bool addEdge(const long & sourc, const long & dest, double w);
	Vertex * findVertex(const long &info);
	bool removeVertex(const long &in);
	bool removeEdge(const long &sourc, const long &dest);
	int getEdgeSize(const long &inf);
	vector<long> dfs() const;
	void dfs(vector<long> &vec, Vertex * v) const;
	vector<long> bfs(Vertex * v) const;
	void bfs(vector<long> &vec, Vertex * v) const;
};

#endif /* SRC_GRAFO_H_ */
