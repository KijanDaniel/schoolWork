//Kijan Daniel
//Dr. Plank
//3/3/2022
//This program uses enumeration
#include <vector>
#include <iostream>
#include <ostream>
#include <map>
using namespace std;

class Matrix {
	public:
		int W,E,P;
		vector <int> Perm;
		vector <int> Non_X;
		vector <int> E_ID;
		void Print();
		void Permute(int index);
		void Choose(int index,int k);
		void Calc();
};

int main(int argc, char **argv) {

	int totalw,totale,size;
	Matrix *newMatrix = new Matrix;	
	vector<int> wHolder;
	if(argc != 4) {
		cout << "Not enough command line info" << endl;
		return 0;
	}
	string ws = argv[1];
	string es = argv[2];
	totalw = 0;
	for(size_t i = 0; i < ws.size(); i++) {//These two for loops converts the string number into a real int
		size = 1;
		for(size_t z = ws.size()-1; z > i; z--) {
			size = size*10;
		}
		totalw = totalw + ((ws[i]-48)*size);
	}
	totale = 0;
	for(size_t i = 0; i < es.size(); i++) {
		size = 1;
		for(size_t z = es.size()-1; z > i; z--) {
			size = size*10;
		}
		totale = totale + ((es[i]-48)*size);
	}
	newMatrix->W = totalw;//assigns all values needed
	newMatrix->E = totale;
	newMatrix->P = *argv[3];
	wHolder.resize(totalw);
	for(int i = 0; i < totalw; i++) {
		wHolder[i] = i;
	}
	newMatrix->Perm = wHolder;
	newMatrix->Permute(0);
	delete newMatrix;
	return 0;
}

void Matrix::Print() {
	map<int,char> sortMap;
	map<int,char>::iterator it;
	int holder = 0;
	for(size_t i = 0; i < Perm.size(); i++) {//fills the map with values sorted by their position in vector
		holder = Perm[i] + W*i;
		sortMap.insert(make_pair(holder,'X'));
	}
	for(size_t i = 0; i < E_ID.size(); i++) {
		sortMap.insert(make_pair(E_ID[i],'E'));
	}
	if(P == 'x') {
		for(int i = 0; i< W; i++) {
			for(int z = 0; z < W; z++) {
				if(sortMap.find(i*W+z) != sortMap.end()) {//prints with format of x
					it = sortMap.find(i*W+z);
					cout << it->second;
				}
				else {
					cout << '.';
				}
			}
			cout << endl;
		}
		cout << endl;
	}
	if(P == 'h') {
		holder = 0;
		for(int i = 0; i< W; i++) {
			for(int z = 0; z < W; z++) {
				if(sortMap.find(i*W+z) != sortMap.end()) {//Prints  with format of h
					holder = holder | 1 << z;//calculates the needed hex value
				}
			}
			cout << hex << (int)holder << endl;
			holder = 0;
		}
		cout << endl;
	}
}

void Matrix::Permute(int index){
	size_t i;
	int tmp;
	/*Base Case*/

	if((size_t)index == Perm.size()) {
		Calc();
		Choose(0,E);
		return;
	}
	/*Swap*/

	for(i = index; i < Perm.size(); i++) {
		tmp = Perm[i];
		Perm[i] = Perm[index];
		Perm[index] = tmp;
		Permute(index+1);
		tmp = Perm[i];
		Perm[i] = Perm[index];
		Perm[index] = tmp;
	}
		
}

void Matrix::Choose(int index,int k){

	/*base case**/
	
	if(k == 0) {
		Print();
		return;
	}

	if((size_t)k > (Non_X.size() - index)) {
		return;
	}

	E_ID.push_back(Non_X[index]);
	Choose(index+1,k-1);
	E_ID.pop_back();

	Choose(index+1,k);

}

void Matrix::Calc(){//calcs the non x values
	Non_X.clear();
	for(int i = 0; i < W; i++) {
		for(int z = 0; z < W; z++) {
			if((Perm[i] + W*i) == (i*W+z)) {//Checks to see if the value is supposed to be an x

			}
			else {
				Non_X.push_back((i*W+z));
			}
		}
	}

}
