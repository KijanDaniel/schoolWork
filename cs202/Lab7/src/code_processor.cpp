//10/25/2021
//Dr. Plank
//Kijan Daniel
//Lab 7 
//A code server
#include "code_processor.hpp"
#include <set>
#include <map>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

bool Code_Processor::New_Prize(const string &id, const string &description, int points, int quantity) {
	if(Prizes.find(id) != Prizes.end()) {//Makes sure the prize isnt already in
		return false;
	}
	if(points <= 0) {
		return false;
	}
	if(quantity <= 0) {
		return false;
	}
	Prize *p = new Prize;//Makes the new prize
	p->id = id;
	p->description = description;
	p->points = points;
	p->quantity = quantity;
	Prizes.insert(pair<string,Prize *>(id,p));
	return true;
}

bool Code_Processor::New_User(const string &username, const string &realname, int starting_points) {
	if(Names.find(username) != Names.end()) {//Makes sure the user isnt already in
		return false;
	}
	if(starting_points < 0) {
		return false;
	}
	User *u = new User;//Makes the new user
	u->username = username;
	u->realname = realname;
	u->points = starting_points;
	Names.insert(pair<string,User *>(username,u));
	return true;
}

bool Code_Processor::Delete_User(const string &username) {
	if(Names.find(username) == Names.end()) {
		return false;
	}
	set<string>::iterator itr;
	map<string,User *>::iterator itr1 = Names.find(username);
	User *u = itr1->second;
	for(itr = u->phone_numbers.begin(); itr != u->phone_numbers.end(); itr++) {//Erases all the phone numbers for user
		if(Phones.find(*itr) == Phones.end()) {
		}
		else {
			Phones.erase(*itr);
		}
	}
	Names.erase(username);//Deletes username
	delete u;//Deletes user pointer
	return true;
}

bool Code_Processor::Add_Phone(const string &username, const string &phone) {
	if(Names.find(username) == Names.end()) {//Makes sure there isnt the phone already in 
		return false;
	}
	if(Phones.find(phone) != Phones.end()) {
		return false;
	}
	map<string,User *>::iterator itr = Names.find(username);
	Phones.insert(pair<string,User*>(phone,itr->second));
	User * u = itr->second;
	u->phone_numbers.insert(phone);
	return true;
}

bool Code_Processor::Remove_Phone(const string &username, const string &phone) {
	if(Names.find(username) == Names.end()) {
		return false;
	}
	if(Phones.find(phone) == Phones.end()) {
		return false;
	}
	User * u;
	set<string>::iterator itr2;
	map<string,User *>::iterator itr = Names.find(username);
	map<string,User *>::iterator itr1 = Phones.find(phone);
	if(itr->second != itr1->second) {
		return false;
	}
	Phones.erase(itr1);//Erases from phone
	u = itr->second;
	itr2 = u->phone_numbers.find(phone);//Erases from phone set
	u->phone_numbers.erase(itr2);
	return true;
}

string Code_Processor::Show_Phones(const string &username) const {
	if(Names.find(username) == Names.end()) {//Checks for name
		return "BAD USER";
	}
	set<string>::iterator itr;
	string returnVal;
	map<string,User *>::const_iterator itr1 = Names.find(username);
	User * u = itr1->second;
	for(itr = u->phone_numbers.begin(); itr != u->phone_numbers.end(); itr++) {
		returnVal = returnVal + *itr + "\n";
	}
	return returnVal;
}

int Code_Processor::Enter_Code(const string &username, const string &code) {
	set<string>::iterator itr;
	for(itr = Codes.begin(); itr != Codes.end(); itr++) {//Checks for code 
		if(code == *itr) {
			return -1;
		}
	}
	if(Names.find(username) == Names.end()) {
		return -1;
	}
	map<string, User *>::iterator itr1 = Names.find(username);
	User * u = itr1->second;
	size_t i;//DJB hash
	unsigned int h;
	h = 5381;
	for(i = 0; i < code.size(); i++) {
		h = (h << 5) + h + code[i];
	}
	if((h % 17) == 0) {
		Codes.insert(code);
		u->points = u->points + 10;
		return 10;
	}
	if((h % 13) == 0) {
		Codes.insert(code);
		u->points = u->points + 3;
		return 3;
	}
	return 0;
}

int Code_Processor::Text_Code(const string &phone, const string &code) {
	set<string>::iterator itr;
	for(itr = Codes.begin(); itr != Codes.end(); itr++) {//Checks for code
		if(code == *itr) {
			return -1;
		}
	}
	if(Phones.find(phone) == Phones.end()) {
		return -1;
	}
	map<string, User *>::iterator itr1 = Phones.find(phone);
	User * u = itr1->second;
	size_t i;
	unsigned int h;//DJb hash
	h = 5381;
	for(i = 0; i < code.size(); i++) {
		h = (h << 5) + h + code[i];
	}
	if((h % 17) == 0) {
		Codes.insert(code);
		u->points = u->points + 10;
		return 10;
	}
	if((h % 13) == 0) {
		Codes.insert(code);
		u->points = u->points + 3;
		return 3;
	}
	return 0;
}

bool Code_Processor::Mark_Code_Used(const string &code) {
	set<string>::iterator itr;
	for(itr = Codes.begin(); itr != Codes.end(); itr++) { //checks for code
		if(code == *itr) {
			return false;
		}
	}
	size_t i;
	unsigned int h;//Djb hash
	h = 5381;
	for(i = 0; i < code.size(); i++) {
		h = (h << 5) + h + code[i];
	}
	if((h % 17) == 0) {
		Codes.insert(code);
		return true;
	}
	if((h % 13) == 0) {
		Codes.insert(code);
		return true;
	}
	return false;
}

int Code_Processor::Balance(const string &username) const {
	if(Names.find(username) == Names.end()) {
		return -1;
	}
	map<string, User *>::const_iterator itr = Names.find(username);
	User * u = itr->second;
	return u->points;
}
bool Code_Processor::Redeem_Prize(const string &username, const string &prize) {
	if(Names.find(username) == Names.end()) {
		return false;
	}
	if(Prizes.find(prize) == Prizes.end()) {
		return false;
	}
	User *u;
	Prize * p; 
	map<string, User *>::iterator itr;
	map<string, Prize *>::iterator itr1;
	itr = Names.find(username);
	itr1 = Prizes.find(prize);
	u = itr->second;
	p = itr1->second;
	if(p->points > u->points) {
		return false;
	}
	u->points = u->points - p->points;
	p->quantity = p->quantity - 1;
	if(p->quantity <= 0) {//Deletes prize if no more quantity
		delete p;
		Prizes.erase(prize);
	}
	return true;
}

Code_Processor::~Code_Processor(){
	map<string,User *>::iterator itr;
	map<string, Prize *>::iterator itr1;
	for(itr = Names.begin(); itr != Names.end(); itr++) {
		delete itr->second;
	}
	for(itr1 = Prizes.begin(); itr1 != Prizes.end(); itr1++) {
		delete itr1->second;
	}
}

bool Code_Processor::Write(const string &filename) const {
	ofstream ofs;
	ofs.open(filename.c_str());
	if(ofs.fail()) {
		return false;
	}
	map<string,User *>::const_iterator itr;//I formatted even though we didnt have to bc I didnt read properly
	map<string,Prize *>::const_iterator itr2;
	set<string>::iterator itr1;
	User *u;
	Prize *p;
	for(itr2 = Prizes.begin(); itr2 != Prizes.end(); itr2++) {
		p = itr2->second;
		ofs << left << setw(10) << "PRIZE" << setw(10) << p->id << setw(6) << p->points << setw(6) << p->quantity << " " << p->description << "\n";
	}
	for(itr = Names.begin(); itr != Names.end(); itr++) {
		u = itr->second;
		ofs << left << setw(10) << "ADD_USER" << setw(10) << u->username << setw(6) << u->points << " " << u->realname << "\n";
	}
	for(itr = Phones.begin(); itr != Phones.end(); itr++) {
		u = itr->second;
		ofs << left << setw(10) << "ADD_PHONE" << setw(10) << u->username << " " << itr->first << "\n";
	}
	for(itr1 = Codes.begin(); itr1 != Codes.end(); itr1++) {
		ofs << left << setw(10) << "MARK_USED" << *itr1 << "\n";
	}
	ofs.close();
	return true;
}



