//Kijan Daniel
//5/10/22
//Dr. Plank
//This plays the dond game
#include <string>
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <vector>
using namespace std;

class dondc {
	public:
		double recursive(double t, double last, double s); 
		vector<vector<double> > cache;
};

double dondc::recursive(double t, double last, double s) {
	double p = 0;
	if(cache.size() == 0) {
		cache.resize(s);
		for(int i = 0; i < (int)cache.size(); i++) {
			cache[i].resize(t+1,-1);
		}
	}
/*	for(int i = 0; i < cache.size(); i++) {
		for(int z = 0; z < cache[i].size(); z++) {
			cout << cache[i][z] << ' ';
		}
		cout << endl;
	}*/

	if((t == 1) && (last == -1)) {
		return 1;
	}
	if(cache[last][t] != -1) {
		return cache[last][t];
	}
	if((t == 1) && (last != -1)) {
		if((last == (s-1)) || (last == 0)) {
			cache[last][t] = (s-2)/s;
			return (s-2)/s;
		}
		else {

			cache[last][t] = (s-3)/s;
			return (s-3)/s;
		}
	}
	if((t == 1) && (last == -1)) {
		return 1;
	}
//	cout << "P: " << p << endl;
//	cout << "LAST: " << last << endl;
	for(int i = 0; i < s; i++) {
		if((i < (last-1)) || (i > (last+1)) || (last == -1)){ 
			p = p + (recursive(t-1,i,s)/s);
//			cout << "SIDE: " << i << " PERCENT: " << p << endl;
		}
	}
	cache[last][t] = p;
	return p;

}

int main(int argc, char **argv) {
	if(argc != 4) {
		cout << "Invalid command line" << endl;
		return 0;
	}
	double t,s,last,hey;
	s = atoi(argv[1]);
	t = atoi(argv[2]);
	last = atoi(argv[3]);
/*	double total, p;
	p = 1;
	total = 0;
	for(int i = t; i > 0; i--) {
		for(int z = 0; z < s; z++) {
			cout << "Z: " << z << endl;
			for(int h = 0; h < s; h++) {
				if((h > z+1) || (h < z-1)){
					cout << "h: " << h << ' ';
					total = total + (1.0/(double)s);
					cout << total << ' ';
				}
			}
		}
		p = p * (total/s);
	}
	cout << endl;
	cout << p << endl;
	cout << s << ' ' << t << ' ' << last << endl;*/
	dondc *don = new dondc;
	hey = don->recursive(t,last,s);
	cout << hey << endl;
	return 0;
}


