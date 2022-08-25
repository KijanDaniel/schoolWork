//Kijan Daniel
//Dr. Plank
//9/6/2021
//Lab2 neg.cpp
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <string.h>
#include <stdio.h>
using namespace std;

int main() {
	int p;
	string p2;
	if(cin >> p2) {
		if(p2 == "P2") {//The if statements are error checks
			cout << p2 << endl;
		}
		else {
			fprintf(stderr, "Error");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Error");
		return 0;
	}
	for(int i = 0; i < 2; i++) {
		if(cin >> p) {
			cout << p << " ";
		}
		else {
			fprintf(stderr, "Error");
			return 0;
		}
	}
	cout << endl;
	if(cin >> p) {
		if(p != 255) {
			fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
			return 0;
		}
		cout << p << endl;
	}
	else {
		fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
		return 0;
	}
	while(cin >> p) {
		cout << 255 - p << endl;//This is what flips the colors
	}
	return 0;
}
