/*
 * parsing.cpp
 *
 *  Created on: 22/04/2015
 *      Author: Filipe
 */
#include "parsing.h"
#include "grafo.h"

long long atol(string s) {
	long long n = 0;
	for(unsigned int i = 0; i < s.length(); i++) {
		n*=10;
		n += s[i] - '0';
	}

	return n;
}

void load(char * fileName) {

	ifstream read;
	read.open(fileName);
	long long idSource;
	long long idEdge;
	long long idDest;
	string name;

	if (!read.fail()) {
		while (!read.eof()) {

			string s;
			getline(read, s, ';');
			cout << s << "  " << s.size() << endl;
			idEdge = atol(s);
			getline(read, s, ';');
			cout << s << "  " << s.size() << endl;
			idSource = atol(s);
			getline(read, s, ';');
			cout << s << "  " << s.size() << endl;
			idDest = atol(s);
			getline(read, s, '\n');
			cout << idEdge << "  " << idSource << "  " << idDest << endl;
		}
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
