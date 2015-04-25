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
#include<string>
using namespace std;

class Graph;
class Vertex;

class Edge {
	Vertex *orig;
	Vertex * dest;
	string name;
	double weight;
	long long id;

public:
	Edge(Vertex *d, double w);
	Edge(Vertex *orig, Vertex*d, string name, double w, long long id);
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
	Vertex* getOrig() const;
	void setOrig(Vertex* orig);

	friend class Graph;
	friend class Vertex;
};

class Vertex {
	long long id;
	vector<Edge> adj;
	bool visited;
	double lat;
	double lon;
	double x;
	double y;
public:
	Vertex(long long in);
	Vertex(long long in, double lat, double lon, double x, double y);
	friend class Graph;
	friend bool operator==(Vertex lhs, Vertex rhs);
	void removeVertex(const long & in);
	void addEdge(Edge e);
	long long getId() const {
		return id;
	}
	void setId(long id) {
		this->id = id;
	}
	double getLat() {
		return lat;
	}
	double getLon() {
		return lon;
	}
	void setLat(double lat) {
		this->lat = lat;
	}
	void setLon(double lon) {
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

	double getX() const {
		return x;
	}

	void setX(double x) {
		this->x = x;
	}

	double getY() const {
		return y;
	}

	void setY(double y) {
		this->y = y;
	}
};

class Graph {
	vector<Vertex *> vertexSet;
	double minLat;
	double maxLat;
	double minLon;
	double maxLon;
public:
	vector<Vertex *> getVertexSet() const;
	int getNumVertex() const;
	bool addVertex(const long & in);
	bool addVertex(Vertex * v);
	void addEdge(Edge e);
	bool addEdge(const long & sourc, const long & dest, double w);
	bool addEdge(const long & sourc, const long & dest, double w, const long idEdge);
	Vertex * findVertex(const long &info);
	bool removeVertex(const long &in);
	bool removeEdge(const long &sourc, const long &dest);
	int getEdgeSize(const long &inf);
	vector<long> dfs() const;
	void dfs(vector<long> &vec, Vertex * v) const;
	vector<long> bfs(Vertex * v) const;
	void bfs(vector<long> &vec, Vertex * v) const;
	vector<Vertex *> prim();
	double getMaxLat() const;
	void setMaxLat(double maxLat);
	double getMaxLon() const;
	void setMaxLon(double maxLon);
	double getMinLat() const;
	void setMinLat(double minLat);
	double getMinLon() const;
	void setMinLon(double minLon);
};
#endif /* SRC_GRAFO_H_ */
