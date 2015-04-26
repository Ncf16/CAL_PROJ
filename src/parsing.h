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
#include <set>
#include "Util.h"
#define PI acos(-1)
long long atol(string s);
double deg2rad(double deg);
double rad2deg(double rad);
double distance(double lat1, double lon1, double lat2, double lon2);
void loadParse(string edgeFileName, string nodeFileName, string roadFile, Graph &grafo);

//template<class Comparable>
//void quickSort(vector<Comparable> &v) {
//	quickSort(v, 0, v.size() - 1);
//}
//
//template<class Comparable>
//void quickSort(vector<Comparable> &v, int left, int right) {
//	if (right - left <= 10)  // se vetor pequeno
//		insertionSort(v, left, right);
//	else {
//		Comparable x = median3(v, left, right);  // x é o pivot
//		int i = left;
//		int j = right - 1;  // passo de partição
//		for (;;) {
//			while (v[++i] < x)
//				;
//			while (x < v[--j])
//				;
//			if (i < j)
//				swap(v[i], v[j]);
//			else
//				break;
//		}
//		swap(v[i], v[right - 1]);  //repoe pivot
//		quickSort(v, left, i - 1);
//		quickSort(v, i + 1, right);
//	}
//}
//template<class Comparable>
//const Comparable &median3(vector<Comparable> &v, int left, int right) {
//	int center = (left + right) / 2;
//	if (v[center] < v[left])
//		swap(v[left], v[center]);
//	if (v[right] < v[left])
//		swap(v[left], v[right]);
//	if (v[right] < v[center])
//		swap(v[center], v[right]);
////coloca pivot na posicao right-1
//	swap(v[center], v[right - 1]);
//	return v[right - 1];
//}
#endif /* SRC_PARSING_H_ */
