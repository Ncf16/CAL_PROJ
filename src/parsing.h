/*
 * parsing.h
 *
 *  Created on: 22/04/2015
 *      Author: Filipe
 */

#ifndef SRC_PARSING_H_
#define SRC_PARSING_H_
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "grafo.h"
#include <math.h>
#include <set>

#define PI acos(-1)
long long atol(string s);
double deg2rad(double deg);
double rad2deg(double rad);
double distance(double lat1, double lon1, double lat2, double lon2);
void loadParse(char * edgeFileName, char * nodeFileName, Graph &grafo);
#endif /* SRC_PARSING_H_ */
