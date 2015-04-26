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
#include <map>
#include<string>
#include<iostream>
#include<climits>

#include "graphviewer.h"

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

	long long getId() const {
		return id;
	}

	void setId(long long id) {
		this->id = id;
	}

	string getName() const {
		return name;
	}

	void setName(const string& name) {
		this->name = name;
	}

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
	double centeredX;
	double y;
	double centeredY;
	bool drawed;

public:
	Vertex(long long in, double lat, double lon, double x, double y, double centeredX, double centeredY);
	Vertex(long long in);
	Vertex(long long in, double lat, double lon, double x, double y);
	friend class Graph;
	friend bool operator==(Vertex lhs, Vertex rhs);
	void removeVertex(const long long &in);
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
	double getCenteredX() const {
		return centeredX;
	}

	void setCenteredX(double centeredX) {
		this->centeredX = centeredX;
	}

	double getCenteredY() const {
		return centeredY;
	}

	void setCenteredY(double centeredY) {
		this->centeredY = centeredY;
	}

	bool isDrawed() const {
		return drawed;
	}

	void setDrawed(bool drawed) {
		this->drawed = drawed;
	}
};

class Graph {
	vector<vector<Vertex *> > vertexSet;
	vector<Edge> edgeSet;
	double minLat, maxLat, minLon, maxLon;
	double centerX, centerY;
	double width, height;
public:

	vector<vector<Vertex *> > getVertexSet() {
		return vertexSet;
	}
	int getNumVertex() const {
		return vertexSet.size();
	}
	bool addVertex(const long & in);
	bool addVertex(Vertex * v);
	void addEdge(Edge e);
	bool addEdge(const long long & sourc, const long long & dest, double w);
	bool addEdge(const long long & sourc, const long long & dest, double w, const long long idEdge);
	Vertex * findVertex(const long long &info, vector<Vertex*> vec);
	bool removeVertex(const long &in);
	bool removeEdge(const long &sourc, const long &dest);
	int getEdgeSize(const long &inf);
	vector<long> dfs(vector<Vertex*> vec) const;
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
	double getCenterX() const;
	void setCenterX(double centerX);
	double getCenterY() const;
	void setCenterY(double centerY);
	double getHeight() const;
	void setHeight(double height);
	double getWidth() const;
	void setWidth(double width);
	void addToEdgeSet(Edge e) {
		edgeSet.push_back(e);
	}
	void createDisjoinedSet(map<long long, Vertex*> toBeProcessed);
	void createDisjoinedSet(Vertex *v, vector<Vertex *> &vec);
	const vector<Edge>& getEdgeSet() const {
		return edgeSet;
	}
	void setEdgeSet(const vector<Edge>& edgeSet) {
		this->edgeSet = edgeSet;
	}
	void setVertexSet(const vector<vector<Vertex*> >& vertexSet) {
		this->vertexSet = vertexSet;
	}
	void addCentrals();
	void addCentralsAux(vector<Vertex*>& vec, const int &count);
	void graphDisplay();
};

#endif /* SRC_GRAFO_H_ */
