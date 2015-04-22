/*
 * parsing.cpp
 *
 *  Created on: 22/04/2015
 *      Author: Filipe
 */
#include "parsing.h"
#include "grafo.h"
void load(char * fileName) {

	ifstream read;
	read.open(fileName);
	long idSource;
	long idEdge;
	long idDest;
	string name;

	if (!read.fail())
		while (!read.eof()) {

			string s;
			stringstream in;
			getline(read, s);
			in << s;
			in >> idEdge >> idSource >> idDest;
			cout << idSource << "  " << idDest << "  " << idEdge << endl;

		}

}

int main() {
	cout << "Treta\n";
	load("tond3.txt");
	return 0;
}
/*

 string s;
 stringstream in;
 getline(read, s, ';');
 in << s;
 in >> idEdge;
 getline(read, s, ';');
 in >> idSource;
 getline(read, s, ';');
 in >> idDest;
 getline(read, s, '\n');
 cout << idSource << "  " << idDest << "  " << idEdge << endl;
 getline(read, s);

 * */
