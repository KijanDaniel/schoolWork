#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include "bitmatrix.hpp"
using namespace std;

unsigned int djb_hash(const string &s);
Bitmatrix::Bitmatrix(int rows, int cols)
{
	 //Checks the rows
	if(rows <= 0) {
		throw((string) "Bad rows");
	}
		 //Checks the cols
	if(cols <= 0) {
		throw((string) "Bad cols");
	}
	M.resize(rows);
	string zeros;
	for(int i = 0; i < cols; i++) {
		zeros = zeros + '0';
	}
	for(size_t z = 0; z < M.size(); z++) {
		M[z] = zeros;
	}
}
           
Bitmatrix::Bitmatrix(const string &fn)
{
	ifstream fin;
	string placeHolder;
	string placeHolder2;
	fin.open(fn.c_str());
	if(fin.fail()) {//Checks to see if the file opened
		throw((string) "Can't open file");
	}
		while(getline(fin,placeHolder)) {
			for(int z = 0; z < (int)placeHolder.size(); z++) {
					if((placeHolder[z] == '0') || (placeHolder[z] == '1')) {
						placeHolder2.push_back(placeHolder[z]);
					}
					else {
						if(placeHolder[z] == ' ') {
						}
						else {
						 throw((string)"Bad file format");
						}
					}
				
			}
			if((int)placeHolder.size() != 0) {
				M.push_back(placeHolder2);
			}
			placeHolder2.clear();
		}
}
        
Bitmatrix *Bitmatrix::Copy() const
{
	Bitmatrix *matrix = new Bitmatrix(M.size(),M[0].size());//Dynamically allocate new pointer
	matrix->M.resize(M.size());
	for(int i = 0; i < (int)M.size(); i++) {
		matrix->M[i] = M[i];//Copies the matrix
	}
	return matrix;
}
                 
bool Bitmatrix::Write(const string &fn) const
{
	ofstream fo;
	fo.open(fn.c_str());
	if(fo.fail()) {
		return false;
	}
	for(int i = 0; i < (int)M.size(); i++) {
		fo << M[i] << endl;
	}
	fo.close();
	return true;
}
 
void Bitmatrix::Print(size_t w) const
{
	if(w <= 0) {
		w = 0;
	}
	for(size_t i = 0; i < M.size(); i++) {
		if((w > 0) && (i > 0)) {
			if((i % w) == 0) {
				cout << endl;
			}
		}
		for(size_t z = 0; z < M[i].size(); z++) {
			if((w > 0) && (z > 0)) {
				if((z % w) == 0) {
					cout << " ";
				}
			}
			if((M[i][z] == '0') || (M[i][z] == '1')){
				cout << M[i][z];
			}
		}
			cout << endl;
	}
}
                 
bool Bitmatrix::PGM(const string &fn, int p, int border) const
{
	ofstream fo;
	fo.open(fn.c_str());
	if(fo.fail()) {
		return false;
	}
	int width = (border * (M[0].size() + 1)) + (p * M[0].size());
	int height = (border * (M.size() + 1)) + (p * M.size());
	fo << "P2" << endl;
	fo << width << " " << height << endl;
	fo << 255 << endl;
	for(int z = 0; z < border; z++) {
		for(int i = 0; i < width; i++) {
			fo << 0 << " ";
		}
		fo << endl;
	}

	for(int i = 0; i < M.size(); i++) {
		for(int q = 0; q < p; q++) {
			for(int z = 0; z < M[0].size(); z++) {
				for(int y = 0; y < border; y++) {
					fo << 0 << " ";
				}
				for(int u = 0; u < p; u++) {
					if(M[i][z] == '1') {
						fo << 100 << " ";
					}
					if(M[i][z] == '0') {
						fo << 255 << " ";
					}
				}
			}
			for(int y = 0; y < border; y++) {
				if(y != (border - 1)) {
					fo << 0 << " ";
				}
				else {
					fo << 0;
				}
			}
			fo << endl;
		}
		if((i + 1) != M.size()) {
			for(int z = 0; z < border; z++) {
				for(int i = 0; i < width; i++) {
					fo << 0 << " ";
				}
				fo << endl;
			}
		}
	}
	for(int z = 0; z < border; z++) {
		for(int i = 0; i < width; i++) {
			fo << 0 << " ";
		}
		fo << endl;
	}


	fo.close();
	return true;

}

int Bitmatrix::Rows() const
{
	int increment = 0;
	for(int i = 0; i < (int)M.size(); i++) {
		increment++;
	}
	return increment;
}
                            
int Bitmatrix::Cols() const
{
	int increment = 0;
	for(int i = 0; i < (int)M[0].size(); i++) {
		increment++;
	}
	return increment;
}
                            
char Bitmatrix::Val(int row, int col) const
{
	if(((row) > (int)M.size()) || ((col) > (int) M[0].size())) {
		return 'x';
	}
	if((M[row][col] != '0') && (M[row][col] != '1')) {
		return 'x';
	}
	return M[row][col];
}
            
bool Bitmatrix::Set(int row, int col, char val)
{
	if(((row) > (int)M.size()) || ((col) > (int) M[0].size())) {
		return false;
	}
	if((row < 0) || (col < 0)) {
		return false;
	}
	if((val != '0') && (val != '1')) {
		return false;
	}
	M[row][col] = val;
	return true;
}
        
bool Bitmatrix::Swap_Rows(int r1, int r2)
{
	if((r1 > (int)M.size()) || (r2 > (int) M.size())) {
		return false;
	}
	string r1r = M[r1];//These are the place holders
	string r2r = M[r2];
	M[r1] = r2r;
	M[r2] = r1r;
	return true;
}
              
bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
	if((r1 >= (int)M.size()) || (r2 >= (int)M.size())) {
		return false;
	}
	char placeHolder;
	for(size_t i = 0; i < M[r1].size(); i++) {
		placeHolder = (M[r1][i] + M[r2][i]) % 2;
		placeHolder = placeHolder + '0';
		M[r1][i] = placeHolder;
	}
	return true;
}
      

Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2)
{
	Bitmatrix *copym = new Bitmatrix(a1->Rows(), a1->Cols());
	int a1rows = a1->Rows();
	int a2rows = a2->Rows();
	int a1cols = a1->Cols();
	int a2cols = a2->Cols();
	if(a1rows == a2rows) {
		if(a2cols == a2cols) {
		}
		else {
			return NULL;
		}
	}
	else {
		return NULL;
	}
	char characterHolder = '0';
	for(size_t i = 0; i < a1rows; i++) {
		for(size_t z = 0; z < a1cols; z++) {
			characterHolder = (a1->Val(i,z) + a2->Val(i,z)) % 2;
			characterHolder = characterHolder + '0';
			copym->Set(i,z,characterHolder);
		}
	}
	return copym;

}

Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{
 	int a1rows = a1->Rows();
	int a2rows = a2->Rows();
	int a1cols = a1->Cols();
	int a2cols = a2->Cols(); 
	Bitmatrix *copym = new Bitmatrix(a1rows,a2cols);
	if(a1cols != a2rows) {
		return NULL;
	}
	char characterHolder = '0';
	int number = 0;
	for(int i = 0; i < a1rows; i++) {
		for(int z = 0; z < a2cols; z++) {
			for(int y = 0; y < a1cols; y++) {
				number = number + a1->Val(i,y) * a2->Val(y,z);
			}
			number = number % 2;
			if(number == 0) {
				copym->Set(i,z,'0');
			}
			else {
				copym->Set(i,z,'1');
			}
			number = 0;
		}
	}
	return copym;

}

Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
	Bitmatrix *copym = new Bitmatrix(rows.size(), a1->Cols());
	for(int i = 0; i < rows.size(); i++) {
		if(rows[i] > a1->Rows()) {
			return NULL;
		}
	}
	for(int i = 0; i < rows.size(); i++) {
		for(int z = 0; z < a1->Cols(); z++) {
			copym->Set(i,z,a1->Val(rows[i],z));
		}
	}
	return copym;

}

Bitmatrix *Inverse(const Bitmatrix *m)
{
	int mrows = m->Rows();
	int mcols = m->Cols();
	if(mcols != mrows) {
		return NULL;
	}
	Bitmatrix *copym = new Bitmatrix(mrows,mcols);
	Bitmatrix *copyi = new Bitmatrix(mrows,mcols);
	for(int i = 0; i < mrows; i++) {
		for(int z = 0; z < mcols; z++) {
			copym->Set(i,z,m->Val(i,z));
			if(z == i) {
				copyi->Set(i,z,'1');
			}
		}
	}
	for(int i = 0; i < mrows - 1; i++) {//Loops through the whole matrix
		if(copym->Val(i,i) == '1') {//checks to see if val is 1
			for(int z = i + 1; z < mrows; z++) {//if it is 1 then it loops through all following rows checking for 1s
				if(copym->Val(z,i) == '1') {
					if(copym->R1_Plus_Equals_R2(z,i)){
						copyi->R1_Plus_Equals_R2(z,i);
					}
					else {
						return NULL;
					}								//if it is equal to one it adds rows and replaces
				}
			}
		}
		else {
			for(int z = i + 1; z < mrows; z++) {//Loops through all following rows 
				if(copym->Val(i,i) == '0') {
					if(copym->Val(z,i) == '1') {//if the val is zero it swaps rows
						if(copym->Swap_Rows(z,i)) {
							copyi->Swap_Rows(z,i);
						}
						else {
							return NULL;
						}
					}
				}
				if(copym->Val(z,i) == '1') {//once the val is one it does as the top loop did
					if(copym->R1_Plus_Equals_R2(z,i)) {
						copyi->R1_Plus_Equals_R2(z,i);
					}
					else {
						return NULL;
					}
				}
				
			}
			if(copym->Val(i,i) == '0') {
				return NULL;
			}
		}
	}
//	for(int i = 0; i < copym->Rows(); i++) {
//		for(int z = 0; z < copym->Cols(); z++) {
//			cout << copym->Val(i,z);
//		}
//		cout << endl;
//	}
	for(int i = mrows - 1; i >= 0; i--) {
		for(int z = i + 1; z < mrows; z++) {
			if(copym->Val(i,z) == '1') {
				if(copym->R1_Plus_Equals_R2(i,z)) {
					copyi->R1_Plus_Equals_R2(i,z);
				}
				else {
					return NULL;
				}
			}
		}
	}
	return copyi;

}



BM_Hash::BM_Hash(int size)
{
	if(size <= 0) {
		throw((string) "Bad size");
	}
	Table.resize(size);
	
}

bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
	unsigned int place = djb_hash(key);
	place = place % Table.size();
	Table[place].push_back(HTE());
	Table[place][Table[place].size()-1].key = key;
	Table[place][Table[place].size()-1].bm = bm;
	return true;
}
    
Bitmatrix *BM_Hash::Recall(const string &key) const
{
	unsigned int place = djb_hash(key);
	place = place % Table.size();
	for(size_t i = 0; i < Table[place].size(); i++) {
		if(Table[place][i].key == key) {
			return Table[place][i].bm;
		}
	}
	
	return NULL;
}

unsigned int djb_hash(const string &s) {
	size_t i;
	unsigned int h;
	h = 5381;

	for(i = 0; i < s.size(); i++) {
		h = (h << 5) + h + s[i];
	}
	return h;
}
      
vector <HTE> BM_Hash::All() const
{
	vector <HTE> rv;
	int counter = 0;
	for(size_t i = 0; i < Table.size(); i++) {
		for(size_t z = 0; z < Table[i].size(); z++) {
			counter++;
		}
	}
	rv.resize(counter);
	counter = 0;
	for(size_t i = 0; i < Table.size(); i++) {
		for(size_t z = 0; z < Table[i].size(); z++) {
			rv[counter].bm = Table[i][z].bm;
			rv[counter].key = Table[i][z].key;
			counter++;
		}
	}
	return rv;
}
