//Kijan Daniel
//Dr. Plank 
//9/6/2021
//Lab2 hflip.cpp
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <string.h>

using namespace std;

int main(){
	int r, c, checker, ph1, ph2, size;
	string p2;
	if(cin >> p2) {
		if(p2 != "P2") {
			fprintf(stderr, "Bad PGM file -- first word is not P2\n");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Error");
		return 0;
	}
	
	if(cin >> c) {
		if(c <= 0) {
			fprintf(stderr, "Bad PGM file -- No column specification\n");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Bad PGM file -- No column specification\n");
		return 0;
	}
	
	if(cin >> r) {
		if(r <= 0){
			fprintf(stderr, "Error");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Error");
		return 0;
	}

	if(cin >> checker) {
		if(checker != 255) {
			fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns");
		return 0;
	}
	size = r * c;
	vector<int> array(size, 0);
	for(int i = 0; i <(int) array.size(); i++) {
		if(cin >> checker) {
			if((checker < 0) || (checker > 255)) {
				fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", i);
				return 0;
			}
		}
		else{
			fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", i);
			return 0;
		}
		array[i] = checker;
	}
	if(cin >> checker) {
		fprintf(stderr, "Bad PGM file -- Extra stuff after the pixels\n");
		return 0;
	}
/*	vector<int> copy(size,0)
	for(int i = 0; i < r; i++) {
		for(int z = 0; z < c; z++) {
			copy[z + (i * c)] = array[ */
	for(int i = 0; i < r; i++) {
		for(int z = 0; z < c/2; z++) {
			ph1 = array[z + (c*i)];
			ph2 = array[(c-z-1) + (c*i)];
			array[z + (c*i)] = ph2;
			array[(c-z-1) + (c*i)] = ph1;
		}
	}
	cout << p2 << endl;
	cout << c << " " << r << endl;
	cout << 255 << endl;
	for(int i = 0; i < (int)array.size(); i++) {
		cout << array[i] << endl;
	} 
	return 0;
}
