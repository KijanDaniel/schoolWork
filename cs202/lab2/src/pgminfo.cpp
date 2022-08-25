//Kijan Daniel	
//Dr. Plank
//9/6/2021
//Lab2 pgminfo.cpp
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
	
	int r, c, p;
	string checker;
	double pixel, average, counter;
	cin >> checker;
	if(checker != "P2") {//All of the if statements are error checks for the input
		fprintf(stderr, "Bad PGM file -- first word is not P2\n");
		return 0;
	}
	if(cin >> c){
		if(c < 0) {
			fprintf(stderr, "Bad PGM file -- No column specification\n");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Bad PGM file -- No column specification\n");
		return 0;
	}
	if(cin >> r){
		if(r < 0) {
			fprintf(stderr, "Bad PGM file -- No row specification\n");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Bad PGM file -- No row specification\n");
		return 0;
	}
	if(cin >> p) {
		if(p != 255) {
			fprintf(stderr, "Bad PGM file -- No 255 after rows and collums\n");
			return 0;
		}
	}
	else {
		fprintf(stderr, "Bad PGM file -- No 255");
		return 0;
	}
	counter = 0;
	while(cin >> pixel) {
		if(counter >= r * c) {
			fprintf(stderr, "Bad PGM file -- Extra stuff after the pixels\n");
			return 0;
		}
		if((pixel < 0) || (pixel > 255)) {
			fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n",(int)counter);
			return 0;
		}
		average = average + pixel;
		counter++;
	}
	average = average/counter;//Outputs the disected information
	printf("# Rows:%12d\n", r);
	printf("# Columns:%9d\n", c);
	printf("# Pixels:%10d\n", r*c);
	printf("Avg Pixel:%9.3f\n", average);
	return 0;
}
