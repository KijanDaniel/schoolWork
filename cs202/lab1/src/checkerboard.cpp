//Kijan Daniel
//8/30/2021
//Dr. Plank 
//Lab 1 
//Purpose: To create a checkerboard

#include <iostream>
#include <vector>
using namespace std;

int main() {
	
	int r,c,cs,w;
	char sc;
	if(!(cin >> r >> c >> sc >> cs >> w)) {//Error checking to make sure that there are enough inouts
		cerr << "usage: checkerboard  - stdin should contain R, C, SC, CS and W" << endl;
		return 0;
	}
	if((r <= 0) || (c <= 0) || (cs <= 0) || (w <= 0) || ((sc + cs) > 127)) {//Error checking so nothing is zero
		return 0;
	}
	for(int i = 0; i < r; i++) {//Rows
		for(int a = 0; a < w; a++) {//Row width
			for(int z = 0; z < c; z++) {//collums
				for(int y = 0; y < w; y++) {//collum width
					cout << (char)(sc + (i + z)%cs);
				}
			}
			cout << endl;
		}
	}
	return 0;
}
