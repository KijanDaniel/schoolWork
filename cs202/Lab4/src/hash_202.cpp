//Kijan Daniel
//9/21/2021
//This lab uses a hash table
//Lab4
//I made this lab way harder than it had to be by having rly messy code :(
//Dr. Planks cs202 class
#include "hash_202.hpp"
#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;

string Hash_202::Set_Up(size_t table_size, const std::string &fxn, const std::string &collision)
{
	if(table_size <= 0) {
		return "Bad table size";
	}
	if((fxn != "Last7") && (fxn != "XOR")) {
		return "Bad hash function";
	}
	if((collision != "Linear") && (collision != "Double")) {
		return "Bad collision resolution strategy";
	}
	if(Keys.size() > 0) {
		return "Hash table already setup";
	}
	if(Vals.size() > 0) {
		return "Hash table already setup";
	}
	Keys.resize(table_size);
	Vals.resize(table_size);
	if(fxn == "Last7") {
		Fxn = 'L';
	}
	else {
		Fxn = 'X';
	}
	if(collision == "Linear") {
		Coll = 'L';
	}
	else {
		Coll = 'D';
	}
	return "";
}

string Hash_202::Add(const string &key, const string &val)
{
	if((Keys.size() <= 0) || (Vals.size() <= 0)) {
		return "Hash table not set up";
	}
	if(key.empty()) {
		return "Empty key";
	}
	for(int i = 0; i < (int)key.size(); i++) { //Checks to see if the key is a valid hex character
		if(key[i] < 0) {
			return "Bad key (not all hex digits)";
		}
		if(key[i] > 102) {
			return "Bad key (not all hex digits)";
		}
		if((key[i] > 70) && (key[i] < 97)) {
			return "Bad key (not all hex digits)";
		}//I wanted to error check for ascii characters between 10 and 65 but it just wouldnt let me and I have no clue why
	}
	if(val.empty()) {
		return "Empty val";
	}
	int checker = 0;
	for(int i = 0; i < (int)Keys.size(); i++) {
		if((int)Keys[i].size() > 0) {
			checker++; //Makes sure hash table is empty
		}
	}
	if(checker == (int)Keys.size()) {
		return "Hash table full";
	}
	string hexVal;
	istringstream ss;
	int indexVal = 0;
	int indexVal2 = 0;
		if(key.size() < 7) {
			hexVal = key;
		}
		else {
			hexVal = key.substr(key.size() - 7, key.size());//takes the last seven characters
		}
		ss.clear();
		ss.str(hexVal);
		ss >> hex >> indexVal;	
		indexVal = indexVal % Keys.size();	//Modulo by table
		int sevens = 0;
		int placeHolder = 0;
		int leftSevens = 0; //This looks if there are any left over characters that didnt go even into seven
		vector <string> xorseven;
		sevens = key.size() / 7;//Sees how many seven char strings there are
		leftSevens = key.size() % 7;//Chcks for left overs
		if(leftSevens != 0) {
			xorseven.resize(sevens + 1);
			if(key.size() > 7) {
				xorseven[sevens] = key.substr(key.size() - leftSevens, key.size());//Gets left over
			}
			else {
				xorseven[0] = key;//Only gets leftover if the string is to short
			}
		}
		else {
			xorseven.resize(sevens);
		}
		for(int i = 0; i < sevens; i++) {
			xorseven[i] = key.substr(i * 7, 7);
		}
		indexVal2 = 0;
		for(int i = 0; i < (int)xorseven.size(); i++) {
			ss.clear();
			ss.str(xorseven[i]);
			ss >> hex >> placeHolder;
			indexVal2 = indexVal2 ^ placeHolder;//Xors all the seven char strings
					
		}
		indexVal2 = indexVal2 % Keys.size();


		int indexValL = indexVal;
		int indexValX = indexVal2;
	if(Fxn == 'X') {
		indexVal = indexVal2;
	}
	if((Keys[indexVal].empty()) && (Keys[indexVal].empty())) {//Enters in vals if there is a free spot
		Keys[indexVal] = key;
		Vals[indexVal] = val;
	}
	else {
		int isItIn = 0;
		if(Coll == 'L') {
			for(int i = 0; i < (int)Keys.size(); i++) {
				if((indexVal+ i) >= (int)Keys.size()) {//Checks for a free spot using linear
					if((Keys[(indexVal+i)%Keys.size()].empty()) && (Keys[(indexVal+i)%Keys.size()].empty())) {
						Keys[(indexVal+i)%Keys.size()] = key;
						Vals[(indexVal+i)%Keys.size()] = val;
						isItIn++;
						break;
					}
				}
				else {
					if((Keys[indexVal+i].empty()) && (Keys[indexVal+i].empty())) {
						Keys[indexVal+i] = key;
						Vals[indexVal+i] = val;
						isItIn++;
						break;
					}
				}
			}
		}
		if(Coll == 'D') {
			if(indexValX == 0) {
				indexValX = 1;
			}
			if(indexValL == 0) {
				indexValL = 1;
			}
			if(Fxn == 'X') {
				for(int i = 0; i < (int)Keys.size(); i++) {//Checks for a free spot using double
					if((indexVal + i * indexValL) < (int)Keys.size()) {
						if(Keys[(indexVal + i * indexValL)] == "") {
							Keys[(indexVal + i * indexValL)] = key;
							Vals[(indexVal + i * indexValL)] = val;
							isItIn++;
							break;
						}
					}
					else {
						if(Keys[(indexVal + i * indexValL)%Keys.size()] == "") {
							Keys[(indexVal + i * indexValL)%Keys.size()] = key;
							Vals[(indexVal + i * indexValL)%Keys.size()] = val;
							isItIn++;
							break;
						}	
					}
				}
			}
			if(Fxn == 'L') {
				for(int i = 0; i < (int)Keys.size(); i++) {
					if((indexVal + i * indexValX) < (int)Keys.size()) {
						if(Keys[(indexVal + i * indexValX)] == "") {
							Keys[(indexVal + i * indexValX)] = key;
							Vals[(indexVal + i * indexValX)] = val;
							isItIn++;
							break;
						}
					}
					else {
						if(Keys[(indexVal + i * indexValX)%Keys.size()] == "") {
							Keys[(indexVal + i * indexValX)%Keys.size()] = key;
							Vals[(indexVal + i * indexValX)%Keys.size()] = val;
							isItIn++;
							break;
						}	
					}
				}
			}
		}
		if(isItIn == 0) {
			return "Cannot insert key";
		}

	

	}
	return "";
	
}


string Hash_202::Find(const string &key)//All the same as add I just copy and pasted my code from add and made minor tweaks
{	
	if(key == "") {
		return "";
	}
	istringstream ss;
	int indexVal = 0;
	if(Fxn == 'L') {
		string hexVal;
		if(key.size() < 7) {
			hexVal = key;
		}
		else {
			hexVal = key.substr(key.size() - 7, key.size());
		}
		ss.clear();
		ss.str(hexVal);
		ss >> hex >> indexVal;	
		indexVal = indexVal % Keys.size();
	}
	if(Fxn == 'X') {
		int sevens = 0;
		int placeHolder = 0;
		int leftSevens = 0; //This looks if there are any left over characters that didnt go even into seven
		vector <string> xorseven;
		sevens = key.size() / 7;
		leftSevens = key.size() % 7;
		if(leftSevens != 0) {
			xorseven.resize(sevens + 1);
			if(key.size() > 7) {
				xorseven[sevens] = key.substr(key.size() - leftSevens, key.size());
			}
			else {
				xorseven[0] = key;
			}
		}
		else {
			xorseven.resize(sevens);
		}
		for(int i = 0; i < sevens; i++) {
			xorseven[i] = key.substr(i * 7, 7);
		}
		for(int i = 0; i < (int)xorseven.size(); i++) {
			ss.clear();
			ss.str(xorseven[i]);
			ss >> hex >> placeHolder;
			indexVal = indexVal ^ placeHolder;
					
		}
		indexVal = indexVal % Keys.size();
	}
	if(Keys[indexVal] == key) {
		return Vals[indexVal];
	}
	int found = 0;
	if(Coll == 'L') {
		for(int i = 0; i < (int)Keys.size(); i++) {
			if((indexVal + i) >= (int)Keys.size()) {
				if(Keys[(indexVal+i)%Keys.size()] == key) {
					return Vals[(indexVal+i)%Keys.size()]; 
				}
			}
			else {
				if(Keys[indexVal+i] == key) {
					return Vals[indexVal+i]; 
				}
			}
			Nprobes++;
		}
	}
	if(Coll == 'D') {
			
			if(Fxn == 'X') {
				int indexVal2 = 0;
				string hexVal;
				if(key.size() < 7) {
					hexVal = key;
				}
				else {
					hexVal = key.substr(key.size() - 7, key.size());
				}
				ss.clear();
				ss.str(hexVal);
				ss >> hex >> indexVal2;	
				indexVal2 = indexVal2 % Keys.size();
				if(indexVal2 == 0) {
					indexVal2 = 1;
				}
				for(int i = 0; i < (int)Keys.size(); i++) {
					if((indexVal + i * indexVal2) < (int)Keys.size()) {
						if(Keys[(indexVal + i * indexVal2)] == key) {
							return Vals[(indexVal + i * indexVal2)];
							found++;
						}
					}
					else {
						if(Keys[(indexVal + i * indexVal2)%Keys.size()] == key) {
							return Vals[(indexVal + i * indexVal2)%Keys.size()];
							found++;
						}	
					}
					Nprobes++;
				}
			}
			if(Fxn == 'L') {
				int indexVal2 = 0;
				int sevens = 0;
				int placeHolder = 0;
				int leftSevens = 0; //This looks if there are any left over characters that didnt go even into seven
				vector <string> xorseven;
				sevens = key.size() / 7;
				leftSevens = key.size() % 7;
				if(leftSevens != 0) {
						xorseven.resize(sevens + 1);
					if(key.size() > 7) {
						xorseven[sevens] = key.substr(key.size() - leftSevens, key.size());
					}
					else {
						xorseven[0] = key;
					}
				}
				else {
					xorseven.resize(sevens);
				}
				for(int i = 0; i < sevens; i++) {
					xorseven[i] = key.substr(i * 7, 7);
				}
				for(int i = 0; i < (int)xorseven.size(); i++) {
					ss.clear();
					ss.str(xorseven[i]);
					ss >> hex >> placeHolder;
					indexVal2 = indexVal2 ^ placeHolder;
					
				}
				indexVal2 = indexVal2 % Keys.size();
				if(indexVal2 == 0) {
					indexVal2 = 1;
				}
				for(int i = 0; i < (int)Keys.size(); i++) {
					if((indexVal + i * indexVal2) < (int)Keys.size()) {
						if(Keys[(indexVal + i * indexVal2)] == key) {
							return Vals[(indexVal + i * indexVal2)]; 
						}
					}
					else {
						if(Keys[(indexVal + i * indexVal2)%Keys.size()] == key) {
							return Vals[(indexVal + i * indexVal2)%Keys.size()];
						}	
					}
					Nprobes++;
				}
			}

	}	
	Nprobes = 0;
	return "";
	
}

void Hash_202::Print() const
{
	for(int i = 0; i < (int)Keys.size(); i++) {
		if(Keys[i] != "") {
			printf("%5i %s %s\n", i, Keys[i].c_str(), Vals[i].c_str());
		}
	}
}

size_t Hash_202::Total_Probes()//Uses teh find script with a increment on nprobes each time there is a collision
{
	Nprobes = 0;
	size_t nprobes = 0;
  for(int i = 0; i < (int)Keys.size(); i++) {
	Find(Keys[i]);
	nprobes = Nprobes + nprobes;
	Nprobes = 0;
	}
  return nprobes;

}
