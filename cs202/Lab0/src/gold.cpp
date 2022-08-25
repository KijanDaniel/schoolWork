#include <iostream>

using namespace std;

int main() {

	char c;
	int total = 0;
	
	while(cin >> c) {
		if((c != '.') && (c != '-'))
		{
			total = total + (c - 'A' + 1);
		}
	}
	cout << total << endl;
	return 0;
}
