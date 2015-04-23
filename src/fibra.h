/*
 * fibra.h
 *
 *  Created on: 23/04/2015
 *      Author: Filipe
 */

#ifndef SRC_FIBRA_H_
#define SRC_FIBRA_H_

#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>
class fibra {
private:
	Graph rede;
	list<Vertex> centrais;
	long long latMin;
	long long latMax;
	long long lonMin;
	long long lonMax;
public:
	bool menu();
	void load();

};
void clearBuffer() {
	fflush(stdin);
}
void cleanScreen() {
	system("cls");
}
#endif /* SRC_FIBRA_H_ */
