//Implementation of the dlist class in c++
//Kijan Daniel
//Dr. Plank
//11/1/2021
#include <iostream>
#include "dlist.hpp"
#include <string>
using namespace std;

Dnode * Dnode::Next() {
	return flink;
}

Dnode * Dnode::Prev() {
	return blink;
}

Dlist::Dlist() {
	sentinel = new Dnode;
	sentinel->flink = sentinel;
	sentinel->blink = sentinel->flink;
	sentinel->s = "";
	size = 0;
}

Dlist::Dlist(const Dlist &d) {//All you have to do is setup the sentinel
	
	sentinel = new Dnode;
	sentinel->flink = sentinel;
	sentinel->blink = sentinel->flink;
	sentinel->s = "";
	size = 0;
	*this = d;
}

Dlist& Dlist::operator= (const Dlist &d) {//Lecture notes
	
	Dlist di;
	Dnode *dn;
	Clear();
	for(dn = d.Begin(); dn != d.End(); dn = dn->Next()) {
		di.Push_Back(dn->s);
	}
	while(!di.Empty()){
		Push_Back(di.Pop_Front());
	}
	return *this;

}

Dlist::~Dlist() {//Clear + get rid of sentinel
	Clear();
	delete sentinel;
}

void Dlist::Clear() {//Pop until clear
	while(!Empty()) {
		Pop_Front();
	}
}

bool Dlist::Empty() const{
	if(size == 0) {
		return true;
	}
	else {
		return false;
	}
}

size_t Dlist::Size() const{
	return size;
}

void Dlist::Push_Front(const string &s) {
	Dnode * holder = new Dnode;//The new node
	Dnode * holder1 = sentinel->flink;//Previous node
	holder->s = s;
	sentinel->flink = holder;
	holder->blink = sentinel;
	holder1->blink = holder;
	holder->flink = holder1;
	size++;//increment size
}


void Dlist::Push_Back(const string &s) {
	Dnode * holder = new Dnode;//new node
	Dnode * holder1 = sentinel->blink;//last node
	holder->s = s;
	sentinel->blink = holder;
	holder->flink = sentinel;
	holder1->flink = holder;
	holder->blink = holder1;
	size++;//increment size
}

string Dlist::Pop_Front() {
	string s;
	if(size == 0) {//Checks for size 
		return "false";
	}
	else {
		Dnode *deletor = sentinel->flink;//delete node
		Dnode *holder = deletor->flink;//node to patch the hole
		s = deletor->s;
		holder->blink = sentinel;
		sentinel->flink = holder;
		delete deletor;
		size--;//increment size
	}
	return s;
}

string Dlist::Pop_Back() {
	string s;
	if(size == 0) {//Check size
		return "false";
	}
	else {
		Dnode *deletor = sentinel->blink;//delete node
		Dnode *holder = deletor->blink;//
		s = deletor->s;
		holder->flink = sentinel;
		sentinel->blink = holder;
		delete deletor;
		size--;
	}
	return s;

}

Dnode * Dlist::Begin() const {
	return sentinel->flink;
}


Dnode * Dlist::End() const {
	return sentinel;
}

Dnode * Dlist::Rbegin() const {
	return sentinel->blink;
}
Dnode * Dlist::Rend() const {
	return sentinel;
}

void Dlist::Insert_Before(const string &s, Dnode *n) {//same as push but only one extra place holder
	Dnode * holder = new Dnode;
	Dnode * holder1 = n->blink;
	holder->flink = n;
	holder->blink = holder1;
	holder->s = s;
	holder1->flink = holder;
	n->blink = holder;
	size++;
}

void Dlist::Insert_After(const string &s, Dnode *n) {
	Dnode * holder = new Dnode;
	Dnode * holder1 = n->flink;
	holder->flink = holder1;
	holder->blink = n;
	holder->s = s;
	holder1->blink = holder;
	n->flink = holder;
	size++;
}

void Dlist::Erase(Dnode *n) {
	Dnode * deletorprev = n->Prev();
	Dnode * deletornext = n->Next();
	deletorprev->flink = deletornext;
	deletornext->blink = deletorprev;
	size--;
	delete n;
}
