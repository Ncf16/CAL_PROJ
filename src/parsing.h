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
#include "menu.h"
#include <math.h>
#include "Util.h"
#define PI acos(-1)
long long atol(string s);
double deg2rad(double deg);
double rad2deg(double rad);
double distance(double lat1, double lon1, double lat2, double lon2);
void loadParse(string edgeFileName, string nodeFileName, string roadFile, Graph &grafo);
string LongLongToString(long long s);

#endif /* SRC_PARSING_H_ */
