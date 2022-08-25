//Kijan Daniel
//Dr. Plank
//Sorting
//3/27/2022
#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
//#include <random>
using namespace std;

void recursive_sort(vector<double> &v, vector<double> &temp, int start, int size, int print);
void srand48(long);
double drand48(void);
//Lol I made a whole main 
/*int main(int argc, char *argv[]) {
	vector<double> vec,vec1;
	int size;
	int seed;
	double tmp;
	(void)argc;
	size = atoi(argv[1]);
	seed = atoi(argv[3]);
	srand48(seed);
	for(int i = 0; i < size; i++) {
		tmp = drand48()*10;
		vec.push_back(tmp);
		vec1.push_back(tmp);
	}
	recursive_sort(vec, vec1, 0, size, 1);
	cout << "                    ";
	for(int i = 0; i < (int)vec.size(); i++) {
		cout << ' ' << vec[i];
	}
	cout << endl;
	return 0;
}
*/
void sort_doubles(vector<double> &v, bool print) {
	vector <double> v1;
	(void)print;
	v1.resize(v.size());
	for(int i = 0; i < (int)v1.size(); i++) {
		v1[i] = v[i];
	}
	recursive_sort(v,v1,0,v.size(),1);
	cout << "                    ";
	for(int i = 0; i < (int)v.size(); i++) {
		cout << ' ' << v[i];
	}
}
void recursive_sort(vector<double> &v, vector<double> &temp, int start, int size, int print) {
	double tmp, k, j;

	if(size == 1) {

		return;
	}

	cout << "B:" << setw(6) << start << setw(6) << size << setw(6) << ' ';
	for(int i = 0; i < (int)v.size(); i++) {
		cout << ' ' << fixed << setprecision(2) << v[i];
	}
	cout << endl;
	if(size == 2) {
		if(v[start] > v[start+1]) {
			tmp = v[start];
			v[start] = v[start+1];
			v[start+1] = tmp;
		}
		cout << "E:" << setw(6) << start << setw(6) << size << setw(6) << ' ';
		for(int i = 0; i < (int)v.size(); i++) {
			cout << ' ' << fixed << setprecision(2) << v[i];
		}
		cout << endl;
		return;
	}
	recursive_sort(v,temp,start,size/2,print);
	recursive_sort(v,temp,start+size/2,size-size/2,print);
	k = 0;//left vector it
	j = 0;//right vector it
	tmp = start+(size/2);//middle
/*	cout << "Before" << endl << endl;
	for(int i = start; i < size; i++) {
		cout << v[i] << ' ';
	}
	cout << endl; */
	for(int i = 0; i < size; i++) {
		if((i-k+start)>=(tmp)) {
			temp[i] = v[tmp + i - j];
		}
		else if((tmp + i - j) >= (size+start)) {
			temp[i] = v[i-k+start];
		}
		else if(v[i-k+start] > v[tmp + i - j]) {
			temp[i] = v[tmp + i -j];
		//	cout << v[i-k] << ' '  << v[start+size/2+i-j] << endl;
			k++;
		}
		else /*(v[i-k] < v[start + size/2 + i - j])*/ {
		//	cout << "hey" << endl;
			temp[i] = v[i-k+start];
			j++;

		}
	}
//	cout << "temp:" << endl << endl;
	for(int i = 0; i < size; i++) {
		v[i+start] = temp[i];
//		cout << temp[i] << ' ';
	}
//	cout << endl; 
	cout << "E:" << setw(6) << start << setw(6) << size << setw(6) << ' ';
	for(int i = 0; i < (int)v.size(); i++) {
		cout << ' ' << fixed << setprecision(2) << v[i];
	}
	cout << endl;
	return;
}


