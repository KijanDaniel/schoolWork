//Kijan Daniel
//Dr. Plank
//9/6/2021
//Lab2 bigwhite.cpp
#include <cstdio>
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char** argv) {
	int r, c;
	int white = 255;
	if(argc != 3) {
		fprintf(stderr, "usage: bigwhite rows cols\n");
		return 0;
	}
	c = atoi(argv[2]);//Takes in the parameters set out by the user
	r = atoi(argv[1]);
	if((c <= 0) || (r <= 0)){
		fprintf(stderr, "usage: bigwhite rows cols\n");
		return 0;
	}
	cout << "P2" << endl << c << " " << r << endl;
	for(int i = 0; i < r; i++) {
		for(int z = 0; z < c; z++) {
			cout << white << endl;//outputs the appropriate amount fo white pixels
		}
	}
	cout << white << endl;
	return 0;
}
