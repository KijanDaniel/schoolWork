//Kijan Daniel
//Dr. Plank
//3/27/2022
//Sorting
#include <iostream>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <ios>
using namespace std;

void recursive_sort(vector <double> &v, int start, int size, int print);
//Lol I made a whole main 
/*int main(int argc, char *argv[]) {
	vector<double> vec;
	int size; 
	int seed;
	(void)argc;
	size = atoi(argv[1]);
	seed = atoi(argv[3]);
	srand48(seed);
	for(int i = 0; i < size; i++) {
		vec.push_back(drand48()*10);
	}
	recursive_sort(vec,0,vec.size(),1);
	cout << "                    "; 
	for(int i = 0; i < (int)vec.size(); i++) {
		cout << ' ' << vec[i];
	}
	cout << endl;
	return 1;
}
*/
void sort_doubles(vector<double> &v, bool print) {
	(void)print;
	recursive_sort(v,0,v.size(),1);	
	for(int i = 0; i < (int)v.size(); i++) {
		cout << ' ' << v[i];
	}
}
void recursive_sort(vector <double> &v, int start, int size, int print) {
	if(size <= 1) {
/*		for(int i = 0; i < v.size(); i++) {
			cout << ' ' << v[i];
		}
		cout << endl; */
		return;
	}
	cout << "S:" << setw(6) << start << setw(6) << size << setw(6) << ' ';
	for(int i = 0; i < (int)v.size(); i++) {
		cout << ' ' << fixed << setprecision(2) << v[i]; 
	}
	cout << endl;
	int left,right;
	double tmp, middle;
	if(size == 2) {
		if(v[start] > v[start+1]) {
			tmp = v[start];
			v[start] = v[start+1];
			v[start+1] = tmp;
		}
/*		for(int i = 0; i < v.size(); i++) {
			cout << ' ' << v[i];
		}
		cout << endl; */
		return;
	}
	if(v[start] >= v[start+size-1]) {
		if(v[start] == v[start+size-1]) {
			middle = start+size-1;
		}
		else if(v[start] == v[start+size/2]) {
			middle = start+size/2;
		}
		else if(v[start+size/2] == v[start+size-1]) {
			middle = start+size-1;
		}
		else if(v[start+size-1] > v[start+size/2]) {
			middle = start+size-1;
		}
		else if(v[start] > v[start+size/2]) {
			middle = start+size/2;
		}
		else {
			middle = start;
		}
	}
	else {
		if(v[start] == v[start+size-1]) {
			middle = start+size-1;
		}
		else if(v[start] == v[start+size/2]) {
			middle = start+size/2;
		}
		else if(v[start+size/2] == v[start+size-1]) {
			middle = start+size-1;
		}
		else if(v[start] > v[start+size/2]) {
			middle = start;
		}
		else if(v[start+size-1] > v[start+size/2]) {
			middle = start+size/2;
		}
		else {
			middle = start+size-1;
		}
	}
//	cout << endl << v[middle] << " middlei: " << middle << ' '  << v[start] << " starti: " << start <<endl;
	left = start+1;
	right = start+size-1;
	tmp = v[middle];
	v[middle] = v[start];
	v[start] = tmp;
	cout << "M:" << setw(6) << start << setw(6) << size << setw(6) << fixed << setprecision(2) << v[start];
	for(int i = 0; i < (int)v.size(); i++) {
		cout << ' ' << fixed << setprecision(2) << v[i]; 
	}
	cout << endl;
	while(left <= right){
		while(v[left] < v[start]) {
			if(left == (start + size)){
				break;
			}
			left++;
		}
		while(v[right] > v[start]) {
			if(right == start) {
				break;
			}
			right--;
		}
		if(right >= left) {
			if((v[left] >= v[start]) && (v[right] <= v[start])) {
				tmp = v[left];
				v[left] = v[right];
				v[right] = tmp;
				if(right != left) {
					right--;
				}
				left++;
			}
		}
/*		if((v[right] < v[start]) && (v[left] > v[start])) {
			tmp = v[right];
			v[right] = v[left];
			v[left] = tmp;
		}
		if(v[left] <= v[start]) {
			if(left == (start+size-1)) {
				break;
			}
			left++;
		}
		if(v[right] >= v[start]) {
				right--;
		}*/
	}
	tmp = v[start];
	v[start] = v[right];
	v[right] = tmp;
	cout << "P:" << setw(6) << start << setw(6) << size << setw(6) << right;
	for(int i = 0; i < (int)v.size(); i++) {
		cout << ' ' << fixed << setprecision(2) << v[i]; 
	}
	cout << endl;
	recursive_sort(v,start,right-start,print);
	recursive_sort(v,left,(start+size)-left,print);
/*	for(int i = 0; i < v.size(); i++) {
		cout << ' ' << v[i];
	}
	cout << endl; */
	return;
}


