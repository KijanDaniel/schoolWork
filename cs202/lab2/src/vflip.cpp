//Kijan Daniel
//Dr. Plank
//9/6/2021
//lab2 vflip.cpp
#include <vector>

#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <string.h>

using namespace std;

int main(){
	int r, c, checker;
	string p2;
	if(cin >> p2) {//All of the if statements are error checks
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
			fprintf(stderr, "Bad PGM file -- No row specification\n");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Bad PGM file -- No row specification\n");
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
	int size = r * c;
	vector<int> array(size, 0);//Reads in the pgm image and error checks to make sure the numbers are in range
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
		
	int d[r][c];
	int b[r][c];
	for(int i = 0; i < r; i++) { //copies the array into a 2d array
		for(int z = 0; z < c; z++) {
			d[i][z] = array[i*c + z];
		}
	}
	
	for(int i = 0; i < r; i++) {//flips the array vertically
		for(int z = 0; z < c; z++) {
			b[i][z] = d[r-1-i][z];
		}
	}
	cout << p2 << endl;
	cout << c << " " << r << endl;
	cout << 255 << endl;
	for(int i = 0; i < r; i++) {
		for(int z = 0; z < c; z++) {//prints out the array
			cout << b[i][z] << " ";
		}
		cout << endl;
	}
	return 0;
}
