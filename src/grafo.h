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
	Vertex *orig;
	Vertex * dest;
	double weight;
	long long id;

public:
	Edge(Vertex *d, double w);
	Edge(Vertex *orig, Vertex*d, double w, long long id);
	Vertex* getDest() const {
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
	long long id;
	vector<Edge> adj;
	bool visited;
	long long lat;
	long long lon;
public:
	Vertex(long in);
	Vertex(long in, long long lat, long long lon);
	friend class Graph;
	friend bool operator==(Vertex lhs, Vertex rhs);
	void removeVertex(const long & in);
	long long getId() const {
		return id;
	}
	void setId(long id) {
		this->id = id;
	}
	long long getLat() {
		return lat;
	}
	long long getLon() {
		return lon;
	}
	void setLat(long long lat) {
		this->lat = lat;
	}
	void setLon(long long lon) {
		this->lon = lon;
	}
	vector<Edge>& getAdj() {
		return adj;
	}
	void setAdj(const vector<Edge>& adj) {
		this->adj = adj;
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
	long long minLat;
	long long maxLat;
	long long minLon;
	long long maxLon;
public:
	vector<Vertex *> getVertexSet() const;
	int getNumVertex() const;
	bool addVertex(const long & in);
	bool addVertex(Vertex * v);
	bool addEdge(Edge e);
	bool addEdge(const long & sourc, const long & dest, double w);
	bool addEdge(const long & sourc, const long & dest, double w,
			const long idEdge);
	Vertex * findVertex(const long &info);
	bool removeVertex(const long &in);
	bool removeEdge(const long &sourc, const long &dest);
	int getEdgeSize(const long &inf);
	vector<long> dfs() const;
	void dfs(vector<long> &vec, Vertex * v) const;
	vector<long> bfs(Vertex * v) const;
	void bfs(vector<long> &vec, Vertex * v) const;

	long long getMaxLat() const;

	void setMaxLat(long long maxLat);

	long long getMaxLon() const;

	void setMaxLon(long long maxLon);

	long long getMinLat() const;

	void setMinLat(long long minLat);

	long long getMinLon() const;

	void setMinLon(long long minLon);
};
#endif /* SRC_GRAFO_H_ */
