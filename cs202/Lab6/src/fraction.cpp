//10/18/21
//Dr. Plank
//Lab 6
//Does basic math with fractions
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "fraction.hpp"
using namespace std;


void Fraction::Clear() {
	denominator.clear();
	numerator.clear();
}
bool Fraction::Multiply_Number(int n) {
	if(n <= 0) {
		return false;
	}
	if(n == 1) {
		return true;
	}
	if(denominator.find(n) != denominator.end()) {//Sees if it can delete the number from opp side
		denominator.erase(denominator.find(n));
		return true;
	}
	else {
		numerator.insert(n);
	}
	return true;
}
bool Fraction::Divide_Number(int n) {
	if(n <= 0) {
		return false;
	}
	if(n == 1) {
		return true;
	}
	if(numerator.find(n) != numerator.end()) {//Sees if it can delete the number from opp side
		numerator.erase(numerator.find(n));
		return true;
	}
	else {
		denominator.insert(n);
	}
	return true;
}
bool Fraction::Multiply_Factorial(int n) {
	if(n <= 0) {
		return false;
	}
	for(int i = 2; i <= n; i++) {
		if(denominator.find(i) != denominator.end()) {//Sees if it can delete the number from opp side
			denominator.erase(denominator.find(i));
		}
		else {
			numerator.insert(i);
		}
	}
	return true;
}
bool Fraction::Divide_Factorial(int n) {
	if(n <= 0) {
		return false;
	}
	for(int i = 2; i <= n; i++) {
		if(numerator.find(i) != numerator.end()) {//Sees if it can delete the number from opp side
			numerator.erase(numerator.find(i));
		}
		else {
			denominator.insert(i);
		}
	}
	return true;
}
bool Fraction::Multiply_Binom(int n, int k) {
	if(n <= 0) {
		return false;
	}
	if(k < 0) {
		return false;
	}
	for(int i = 2; i <= n; i++) {
		if(denominator.find(i) != denominator.end()) {//Sees if it can delete the number from opp side
			denominator.erase(denominator.find(i));
		}
		else {
			numerator.insert(i);//Inserts the number
		}
	}
	for(int i = 2; i <= k; i++) {
		if(numerator.find(i) != numerator.end()) {
			numerator.erase(numerator.find(i));
		}//Sees if it can delete the number from opp side
		else {
			denominator.insert(i);
		}
	}
	for(int i = 2; i <= (n-k); i++) {
		if(numerator.find(i) != numerator.end()) {
			numerator.erase(numerator.find(i));
		}
		else {
			denominator.insert(i);
		}
	}
	return true;
}
bool Fraction::Divide_Binom(int n, int k) {
	if(n <= 0) {
		return false;
	}
	if(k < 0) {
		return false;
	}
	for(int i = 2; i <= n; i++) {
		if(numerator.find(i) != numerator.end()) {
			numerator.erase(numerator.find(i));
		}
		else {
			denominator.insert(i);
		}
	}
	for(int i = 2; i <= k; i++) {
		if(denominator.find(i) != denominator.end()) {
			denominator.erase(denominator.find(i));
		}
		else {
			numerator.insert(i);
		}
	}
	for(int i = 2; i <= (n-k); i++) {
		if(denominator.find(i) != denominator.end()) {//Sees if it can delete the number from opp side
			denominator.erase(denominator.find(i));
		}
		else {
			numerator.insert(i);
		}
	}
	return true;
}
void Fraction::Invert() {
	numerator.swap(denominator); //just a sipmple swap
}
void Fraction::Print() const {
	multiset <int>::const_iterator nit;
	int counter = 1;
	for(nit = numerator.begin(); nit != numerator.end(); nit++) {
		if((counter == (int)numerator.size()) && (denominator.size() < 1)) {
			cout << *nit << endl;
		}
		else {
			if(counter == (int)numerator.size()) {//All the if statements check if you need a space or not based on pos.
				cout << *nit;
			}
			else {
				cout << *nit << " * ";
			}
		}
		counter++;
	}
	if(numerator.empty() && denominator.empty()) {
		cout << 1 << endl;
	}
	else {
		if(numerator.empty()) {
			cout << 1;
		}
	}
	counter = 1;
	for(nit = denominator.begin(); nit != denominator.end(); nit++) {
		if(counter == (int)denominator.size()) {
			if((counter == 1) && (denominator.size() > 0)) {
				cout << " / " << *nit << endl;
			}
			else {
				if(counter != 1) {
					cout << " / " << *nit << endl;
				}
				else {
					cout << *nit << endl;
				}
			}
		}
		else {
			cout << " / " << *nit;
		}
		counter++;
	}
}
double Fraction::Calculate_Product() const {
	double holder = 1; 
	double holder1 = 1;
	multiset <int>::const_iterator nit;
	for(nit = numerator.begin(); nit != numerator.end(); nit++) {
		if(*nit <= 0){
		}
		else {
			holder = holder * *nit;
		}
	}
	for(nit = denominator.begin(); nit != denominator.end(); nit++) {
		if(*nit <= 0) {
		}
		else {
			holder1 = holder1 * *nit;
		}
	}
	return (holder / holder1);
}

