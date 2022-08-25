#include <map>
#include <iostream>
#include <sstream>
#include <ostream>
#include <istream>
#include <vector>
#include<stdio.h>
#include <stdlib.h>
using namespace std;

struct Person {
	public:
		string name, id;
};

unsigned long long jsp_hash(const string &s);
void orderf(map<unsigned long long,map<unsigned long long,Person *> >&bigmap, vector<Person *>&persons, string orders, unsigned long long hashnum);
void orderFinal(map<unsigned long long,map<unsigned long long,Person *> >&bigmap, vector<Person *>&persons, string orders, unsigned long long hashnum);
string toHex(string id, unsigned long long hash);
int main() {
	
	map<unsigned long long,map<unsigned long long,Person *> > bigmap;
	map<unsigned long long,map<unsigned long long,Person *> >::iterator  ps;
	map<unsigned long long,Person *>::iterator qs;
	vector<Person *> persons,orderPersons;
	string pName, pId, define, line;
	stringstream ss;
	unsigned long long hashval;

	while(getline(cin, line)) {
		ss.clear();
		ss << line;
		ss >> define;
		if(define == "PERSON") {
			ss >> pName >> pId;
			Person * nperson = new Person;
			nperson->name = pName;
			nperson->id = pId;
			persons.push_back(nperson);
		}
		if(define == "ORDER") {
			ss >> pName >> hashval;
			bigmap.clear();
			orderf(bigmap,persons,pName,hashval);
			orderPersons.clear();
			orderFinal(bigmap,orderPersons,pName,hashval);

	cout << "Last: " << orderPersons[orderPersons.size()-1]->name << " " <<  orderPersons[orderPersons.size()-1]->id << endl << "First: " <<  orderPersons[0]->name << " " << orderPersons[0]->id << endl; 
		}
	}
/*	map<unsigned long long,map<unsigned long long,Person*> >::iterator it, itz;
	map<unsigned long long,Person*>::iterator its;
	for(it = bigmap.begin(); it != bigmap.end(); it++) {
		if(it->second.empty()) cout << endl << "EMPTY" << endl;
		for(its = it->second.begin(); its != it->second.end(); its++) {
			cout << its->second->name << " " << its->second->id << endl;
		}
	}*/
	for(size_t i = 0; i < orderPersons.size(); i++) {
		delete orderPersons[i];
	}
	return 0;
}

unsigned long long jsp_hash(const string &s) {
	size_t i;
	unsigned long long h, t;
	h = 0x6bd300f29f1505ULL;
	for(i = 0; i < s.size(); i++) {
		t = h & 0x3ffffffffffffffULL;
		h = (t << 5) ^ h ^ s[i];
	}
	return h;
}

void orderf(map<unsigned long long,map<unsigned long long,Person *> > &bigmap, vector<Person*> &persons, string orders, unsigned long long hashnum) {
	unsigned long long jsphash;
	string concat;
	for(size_t i = 0; i < persons.size(); i++) {
		concat = persons[i]->name + persons[i]->id + orders;
		jsphash = jsp_hash(concat);
		bigmap[jsphash % hashnum][jsphash] = persons[i];
	}
}

string toHex(string id, unsigned long long hash) {
	char buff[200];
	string hashhex;
	sprintf(buff, "%llX", hash);
	hashhex = buff;
	for(size_t i = 0; i < hashhex.size(); i++) {
		if((hashhex[i] >= 65) && (hashhex[i] < 97)) {
			hashhex[i] = hashhex[i] + 32;
		}
	}
	return id + hashhex;
}

void orderFinal(map<unsigned long long,map<unsigned long long,Person *> >&bigmap, vector<Person *>&persons, string orders, unsigned long long hashnum){
	map<unsigned long long,map<unsigned long long,Person*> >::iterator it, itz, itp;
	map<unsigned long long,Person*>::iterator its;
	unsigned long long hash;
	unsigned long long dif1, dif2;
	while(!bigmap.empty()) {
		hash = jsp_hash(orders);
		it = bigmap.lower_bound(hash%hashnum);
		if(it == bigmap.begin()) {
			its = it->second.lower_bound(hash);
			if (its == it->second.end()) {
				its--;
			}
			persons.push_back(its->second);
			orders = toHex(its->second->id,hash);
			it->second.erase(its);
			if(it->second.empty()) {
				bigmap.erase(it);
			}
		}
		else if(it == bigmap.end()) {
			it--;
			its = it->second.lower_bound(hash);
			if (its == it->second.end()) {
				its--;
			}
			persons.push_back(its->second);
			orders = toHex(its->second->id,hash);
			it->second.erase(its);
			if(it->second.empty()) {
				bigmap.erase(it);
			}
		}
		else{
			dif1 = it->first - (hash%hashnum);
			it--;
			dif2 = (hash%hashnum) - it->first;
			if(dif1 <= dif2) {
				it++;
				its = it->second.lower_bound(hash);
				if (its == it->second.end()) {
					its--;
				}
				persons.push_back(its->second);
				orders = toHex(its->second->id,hash);
				it->second.erase(its);
				if(it->second.empty()) {
					bigmap.erase(it);
				}
			}
			else {
				its = it->second.lower_bound(hash);
				if (its == it->second.end()) {
					its--;
				}
				persons.push_back(its->second);
				orders = toHex(its->second->id,hash);
				it->second.erase(its);
				if(it->second.empty()) {
					bigmap.erase(it);
				}
			}
		}
	}
}
