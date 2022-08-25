//10/18/21
//Dr. Plank
//Lab6
//does a basic probability for  a gambling game called keno
#include "fraction.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdio>
using namespace std;

int main() {

	double bet, returnholder, finalp, finalz;
	int size, catchholder;
	vector <double> returns;
	vector <int> catchs;
	vector <Fraction> fractions;
	Fraction f;
	
	cin >> bet;
	cin >> size;

	while(cin >> catchholder >> returnholder) {
		catchs.push_back(catchholder);
		returns.push_back(returnholder);
		fractions.push_back(f);
	}
	for(int i = 0; i < (int)catchs.size(); i++) {
		fractions[i].Multiply_Binom((80-size),(20 - catchs[i]));//formula provided in write up
		fractions[i].Multiply_Binom(size,catchs[i]);
		fractions[i].Divide_Binom(80,20);
	}

	printf("Bet: %.2f\n", bet);
	cout << "Balls Picked: " << size << endl;
	for(int i = 0; i < (int)catchs.size(); i++) {
		finalp = fractions[i].Calculate_Product();
		cout << "  Probability of catching " << catchs[i] << " of " << size << ": " << finalp << " -- Expected return: " << finalp * returns[i] << endl;
	}
	finalz = bet * -1;
	for(int i = 0; i < (int)fractions.size(); i++) {
		finalp = fractions[i].Calculate_Product();
		finalz = finalp * returns[i] + finalz;
	}
	printf("Your return per bet: %.2f\n",finalz);//print f for formatting
	printf("Normalized: %.2f\n",finalz/bet);
	return 0;
}
