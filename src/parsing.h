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
#include <list>

using namespace std;

#define PI 3.14159265358979323846
long long atol(string s);
double deg2rad(double deg);
double rad2deg(double rad);
double distance(double lat1, double lon1, double lat2, double lon2);
string load(string fileName);
#endif /* SRC_PARSING_H_ */
