/*
 * grafo.cpp
 *
 *  Created on: 22/04/2015
 *      Author: Filipe
 */
#include "grafo.h"

using namespace std;
/**
 * Removes all edges leading to that vertex we want to delete
 */
void Vertex::removeVertex(const long long & in) {
	for (size_t i = 0; i < adj.size(); i++) {
		if (*(adj[i].getDest()) == in) {
			adj.erase(adj.begin() + i);
			i -= 2;
		}
	}
}
/**
 * Equal operator for vertices
 */
bool operator==(Vertex lhs, Vertex rhs) {
	if (lhs.getId() == rhs.getId())
		return true;
	else
		return false;
}
/**
 * Vertex constructor with only the id
 */
Vertex::Vertex(long long in) :
		id(in), visited(false), lat(0), lon(0), x(0), y(0) {
}
/**
 * Vertex Constructor with all the information
 */
Vertex::Vertex(long long in, double lat, double lon, double x, double y) :
		id(in), visited(false), lat(lat), lon(lon), x(x), y(y) {
}
/**
 * Adds an edge to a vertex's edge vector
 */
void Vertex::addEdge(Edge e) {
	adj.push_back(e);
}
/**
 * Edge constructor with the destiny vertex and its weight
 */
Edge::Edge(Vertex*d, double w) : //TODO check if id should be 0
		dest(d), weight(w), id(0) {
}
/**
 * Edge constructor with all the information
 */
Edge::Edge(Vertex *orig, Vertex*d, string name, double w, long long id) {
	this->name = name;
	this->dest = d;
	this->orig = orig;
	this->weight = w;
	this->id = id;
}
/**
 * returns a vector with Vertices when a width search is performed from a Vertex
 */
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
/**
 * returns a vector with Vertices when a depth search is performed
 */
vector<long> Graph::dfs(vector<Vertex*> vec) const {

	vector<long> answer;
	for (size_t i = 0; i < vec.size(); i++) {
		if (!vec[i]->visited) {
			dfs(answer, vec[i]);
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
/**
 * returns the max Latitude of the graph
 */
double Graph::getMaxLat() const {
	return maxLat;
}
/**
 * sets the max Latitude of the graph
 */
void Graph::setMaxLat(double maxLat) {
	this->maxLat = maxLat;
}
/**
 * returns the max Longitude of the graph
 */
double Graph::getMaxLon() const {
	return maxLon;
}
/**
 * sets the max Longitude of the graph
 */
void Graph::setMaxLon(double maxLon) {
	this->maxLon = maxLon;
}
/**
 * returns the min Latitude of the graph
 */
double Graph::getMinLat() const {
	return minLat;
}
/**
 * sets the min Latitude of the graph
 */
void Graph::setMinLat(double minLat) {
	this->minLat = minLat;
}
/**
 * returns the min Longitude of the graph
 */
double Graph::getMinLon() const {
	return minLon;
}
/**
 * sets the min Longitude of the graph
 */
void Graph::setMinLon(double minLon) {
	this->minLon = minLon;
}
/**
 * retuns the origin of the edge (Vertex)
 */
Vertex* Edge::getOrig() const {
	return orig;
}
/**
 * sets the origin of the edge (Vertex)
 */
void Edge::setOrig(Vertex* orig) {
	this->orig = orig;
}
/**
 * return the center of the graph (X coord)
 */
double Graph::getCenterX() const {
	return centerX;
}
/**
 * sets the center of the graph (X coord)
 */
void Graph::setCenterX(double centerX) {
	this->centerX = centerX;
}
/**
 * return the center of the graph (Y coord)
 */
double Graph::getCenterY() const {
	return centerY;
}
/**
 * sets the center of the graph (Y coord)
 */
void Graph::setCenterY(double centerY) {
	this->centerY = centerY;
}
/**
 * returns the height of the graph
 */
double Graph::getHeight() const {
	return height;
}
/**
 * sets the height of the graph
 */
void Graph::setHeight(double height) {
	this->height = height;
}
/**
 * return the width of the graph
 */
double Graph::getWidth() const {
	return width;
}
/**
 * sets the width of the graph
 */
void Graph::setWidth(double width) {
	this->width = width;
}
/**
 * Vertex constructor
 */
Vertex::Vertex(long long in, double lat, double lon, double x, double y, double centeredX, double centeredY) :
		id(in), visited(false), lat(lat), lon(lon), x(x), y(y), centeredX(centeredX), centeredY(centeredY) {
}
/**
 * creates a disjoined set given a map
 */
void Graph::createDisjoinedSet(map<long long, Vertex*> toBeProcessed) {

	map<long long, Vertex*>::iterator it = toBeProcessed.begin();
	map<long long, Vertex*>::iterator ite = toBeProcessed.end();
	cout << "DisjoinedSet" << endl;
	for (; it != ite; it++) {
		it->second->setVisited(false);
	}
	it = toBeProcessed.begin();
	int i = 0;
	for (; it != ite; it++) {
		vector<Vertex *> res;
		if (!it->second->isVisited()) {
			createDisjoinedSet(it->second, res);
			vertexSet.push_back(res);

		}
		i++;
	}

}
/**
 * creates a disjoined set given a vertex and a vertex vector
 */
void Graph::createDisjoinedSet(Vertex *v, vector<Vertex *> &vec) {

	v->setVisited(true);

	vec.push_back(v);
	vector<Edge>::iterator it = v->getAdj().begin();
	vector<Edge>::iterator ite = v->getAdj().end();
	for (; it != ite; it++) {
		if (!it->getDest()->isVisited()) {
			createDisjoinedSet(it->getDest(), vec);
		}
		if (!it->getOrig()->isVisited()) {
			createDisjoinedSet(it->getOrig(), vec);
		}

	}

}
/**
 * adds centrals to the graph
 */
void Graph::addCentrals() {
	for (size_t i = 0; i < vertexSet.size(); i++) {
		addCentralsAux(vertexSet[i], i);
	}
}
/**
 * Adds an auxiliar central
 */
void Graph::addCentralsAux(vector<Vertex*> &vec, const int &count) {

	double incLon = maxLon - minLon * 1.0;

	if (incLon < 0.05)
		incLon /= 10.0;
	else
		while (incLon >= 0.05) {
			incLon /= 10.0;
		}
	//For is just to be safe, in case anything fails. It´s expected to work for the first node of every vector
	for (size_t j = 0; j < vec.size(); j++) {
		double newLon = vec[j]->getLon() + incLon;
		if (newLon < maxLon) {
			double newY = vec[j]->getY();
			double newX = deg2rad(newLon);
			double newLat = vec[j]->getLat();
			Vertex * central(count, newLat, newLon, newX, newY, newX - centerX, newY - centerY);

			double peso = distance(vec[j]->getLat(), vec[j]->getLon(), newLat, newLon);
			Edge e(central, vec[j], "Road to Central", peso, count);
			Edge f(vec[j], central, "Road to Central", peso, count);

			central->addEdge(e);
			vec[j]->addEdge(f);

			vec.push_back(central);
			edgeSet.push_back(e);
			return;
		}

		else {
			newLon = vec[j]->getLon() - incLon;
			double newY = vec[j]->getY();
			double newX = deg2rad(newLon);
			double newLat = vec[j]->getLat();
			Vertex * central(count, newLat, newLon, newX, newY, newX - centerX, newY - centerY);

			double peso = distance(vec[j]->getLat(), vec[j]->getLon(), newLat, newLon);
			Edge e(central, vec[j], "Road to Central", peso, count);
			Edge f(vec[j], central, "Road to Central", peso, count);

			central->addEdge(e);
			vec[j]->addEdge(f);

			vec.push_back(central);
			edgeSet.push_back(e);

			return;
		}
	}

}
