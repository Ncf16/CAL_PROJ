/*
 * grafo.cpp
 *
 *  Created on: 22/04/2015
 *      Author: Filipe
 */
#include "grafo.h"
#include "parsing.h"
using namespace std;

void Vertex::removeVertex(const long long & in) {
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
		id(in), visited(false), lat(0), lon(0), x(0), y(0) {
}

Vertex::Vertex(long long in, double lat, double lon, double x, double y) :
		id(in), visited(false), lat(lat), lon(lon), x(x), y(y) {
}

void Vertex::addEdge(Edge e) {
	adj.push_back(e);
}

Edge::Edge(Vertex*d, double w) : //TODO check if id should be 0
		dest(d), weight(w), id(0) {
}

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

Vertex* Edge::getOrig() const {
	return orig;
}

void Edge::setOrig(Vertex* orig) {
	this->orig = orig;
}

double Graph::getCenterX() const {
	return centerX;
}

void Graph::setCenterX(double centerX) {
	this->centerX = centerX;
}

double Graph::getCenterY() const {
	return centerY;
}

void Graph::setCenterY(double centerY) {
	this->centerY = centerY;
}

double Graph::getHeight() const {
	return height;
}

void Graph::setHeight(double height) {
	this->height = height;
}

double Graph::getWidth() const {
	return width;
}

void Graph::setWidth(double width) {
	this->width = width;
}

Vertex::Vertex(long long in, double lat, double lon, double x, double y, double centeredX, double centeredY) :
		id(in), visited(false), lat(lat), lon(lon), x(x), y(y), centeredX(centeredX), centeredY(centeredY) {
}

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

void Graph::addCentrals() {
	for (size_t i = 0; i < vertexSet.size(); i++) {
		addCentralsAux(vertexSet[i], i);
	}
}
void Graph::addCentralsAux(vector<Vertex*> &vec, const int &count) {

	double incLon = maxLon - minLon * 1.0;

	if (incLon < 0.05)
		incLon /= 10.0;
	else
		while (incLon >= 0.05) {
			incLon /= 10.0;
		}
	//For is just to be safe, in case anything fails. It�s expected to work for the first node of every vector
	for (size_t j = 0; j < vec.size(); j++) {
		double newLon = vec[j]->getLon() + incLon;
		if (newLon < maxLon) {
			double newY = vec[j]->getY();
			double newX = deg2rad(newLon);
			double newLat = vec[j]->getLat();
			Vertex * central = new Vertex(count, newLat, newLon, newX, newY, newX - centerX, newY - centerY);

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
			Vertex * central = new Vertex(count, newLat, newLon, newX, newY, newX - centerX, newY - centerY);

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

void Graph::graphDisplay() {
	GraphViewer *gv = new GraphViewer(600, 600, false);
	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	vector<Edge> tempEdges = edgeSet;
	long long edgeId;
	for (size_t i = 0; i < tempEdges.size(); i++) {
		edgeId = tempEdges[i].getId();
		Vertex* org = tempEdges[i].getOrig();
		Vertex* dest = tempEdges[i].getDest();

		if (org->isDrawed() == false) {
			gv->addNode(org->getId(), org->getX(), org->getY());
			org->setDrawed(true);
		}
		if (dest->isDrawed() == false) {
			gv->addNode(dest->getId(), dest->getX(), dest->getY());
			dest->setDrawed(true);
		}

		gv->addEdge(edgeId, org->getId(), dest->getId(), EdgeType::UNDIRECTED);
		if (tempEdges[i].getName() != "")
			gv->setEdgeLabel(edgeId, tempEdges[i].getName());
		else
			gv->setEdgeLabel(edgeId, LongLongToString(edgeId));

		gv->rearrange();
	}
}

