//Dr. Plank
//Lab9
//11/8/2021
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void do_enumeration(string &s, int index, int n_ones);

int main(int argc, char* argv[]) {
	
	if(argc != 3) {
		return -1;
	}
	int size = atoi(argv[1]);
	int ones = atoi(argv[2]);
	string hello = "";
	for(int i = 0; i < size; i++) {
		hello = hello + '-';
	}
	do_enumeration(hello, 0, ones);

	//build starting string
	//string length
	//make intial recurtion call
}

void do_enumeration(string &s, int index, int n_ones) {
/*	if((index == s.size())) {
		cout << s << endl;
		finder = s.rfind("01");
		if(finder == string::npos) {
			return;
		}
		s[finder] = '1';
		for(int i = finder+1; i < s.size(); i++) {
			if(s[i] == '1') {
				n_ones = n_ones + 1;
			}
			s[i] = '-';
		}
		n_ones = n_ones - 1;
		return do_enumeration(s,finder+1,n_ones);
	} */
	if((((int)s.length()-n_ones) == index) && (n_ones <= 0)) {
		cout << s << endl;
	}
	if(((int)s.size() - index) > n_ones) {
		s[index] = '0';
		do_enumeration(s,index + 1,n_ones);
	}
	if(n_ones > 0) {
		s[index] = '1';
		do_enumeration(s,index+1,n_ones-1);
	}

/*	if((s[index] != 1) && (s[index] != 0)) {
			if((s.size() - index) > n_ones) {
				s[index] = '0';
				return do_enumeration(s,index + 1,n_ones);
			}
			else {
				s[index] = '1';
				return do_enumeration(s,index+1,n_ones-1);
			}
		} */
}
