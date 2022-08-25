//cs302
//kijan daniel
//Dr. Plank 
//2/20/2022
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <list>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "cs302-midi.h"
using namespace std;

void CS302_Midi::el_to_nd()
{
	vector<ND*> bigvec;
	ND *holder;
	double time1 = 0;
	nd = new NDMap;
	bigvec.resize(129, NULL);
	list<Event*>::iterator it;
	for(it = el->begin(); it != el->end(); it++) {
		time1 = time1 + double((*it)->time);
		if((*it)->key == 'O') {//This checks the 4 possible conditions
			holder = new ND;
			holder->pitch = (*it)->v1;
			holder->volume = (*it)->v2;
			holder->key = 'N';
			holder->start = time1/480;
			bigvec[(*it)->v1] = holder;
		}
		else if(((*it)->key == 'D') && ((*it)->v1 == 1)) {
			holder = new ND;
			holder->start = time1/480;
			holder->key = 'D';
			bigvec[128] = holder;
		}
		else if((*it)->key == 'F') {
			bigvec[(*it)->v1]->stop = time1/480;
			nd->insert(make_pair(bigvec[(*it)->v1]->start,bigvec[(*it)->v1]));
			bigvec[(*it)->v1] = NULL;
		}
		else if(((*it)->key == 'D') && ((*it)->v1 == 0)) {
			bigvec[128]->stop = time1/480;
			nd->insert(make_pair(bigvec[128]->start,bigvec[128]));
			bigvec[128] = NULL;
		}
	}
}

void CS302_Midi::nd_to_el()
{
	el = new EventList;
	map<int,multimap<int,Event*> > bigmap;
	map<int,multimap<int,Event*> >::iterator its,itl;
	multimap<int,Event*>::iterator itz;
	multimap<double, ND *>::iterator it;
	list<Event*>::iterator itp;
	int pitch1,vol,time1,time2,time0,timeO, iterator1,time3;
	vector<Event*> ordered;
	Event *event1, *event2;
	for(it = nd->begin(); it != nd->end(); it++) {//This loads the bigmap with all of the events keyed on time
		if(it->second->key == 'N') {
			pitch1 = it->second->pitch;
			vol = it->second->volume;
			time1= rint(it->second->start * 480);
			time2= rint(it->second->stop * 480);
			if((time1-time2) == 0) { //ignore if the time diffrence is equal to zero	
				continue;
			}
			event1 = new Event;
			event1->time = time1;
			event1->key = 'O';
			event1->v1 = pitch1;
			event1->v2 = vol;
			event2 = new Event;
			event2->time = time2;
			event2->key = 'F';
			event2->v1 =  pitch1;
			bigmap[time1].insert(make_pair(time1,event1));
			bigmap[time2].insert(make_pair(time2,event2));
		}
		else if(it->second->key == 'D') {
			time1 = rint(it->second->start * 480);
			time2 = rint(it->second->stop * 480);
			if((time1-time2) == 0) {
				continue;
			}
			event1 = new Event;
			event1->time = time1;
			event1->key = 'D';
			event1->v1 = 1;
			event2 = new Event;
			event2->time = time2;
			event2->key = 'D';
			event2->v1 = 0;
			bigmap[time1].insert(make_pair(time1,event1));
			bigmap[time2].insert(make_pair(time2,event2));
		}
		else {
			cout << "Failed to provide a good key";
		}
	}
	for(its = bigmap.begin(); its != bigmap.end(); its++) {
		if(its != bigmap.begin()) {
			itl = --its;
			its++;
			time0 = its->first - itl->first;
		}
		else {
			time0 = its->first;
		}
		iterator1 = 1;
		for(itz = its->second.begin(); itz != its->second.end(); itz++) {
			if(itz->second->key == 'F') {//This is so that all off events at given time happend before on events
				if(iterator1 == 1) {
					itz->second->time = time0;
				}
				else {
					itz->second->time = 0;
				}
				el->push_back(itz->second);
				iterator1++;
			}
			if(itz->second->key == 'D') {
				if(itz->second->v1 == 1) {
					if(iterator1 == 1) {
						itz->second->time = time0;
					}
					else {
						itz->second->time = 0;
					}
					el->push_back(itz->second);
					iterator1++;
				}
			}
		}
		for(itz = its->second.begin(); itz != its->second.end(); itz++) {
			if(itz->second->key == 'O') {//This is so that all on events at given time happend after off events
					if(iterator1 == 1) {
						itz->second->time = time0;
					}
					else {
						itz->second->time = 0;
					}
				el->push_back(itz->second);
				iterator1++;
			}
			if(itz->second->key == 'D') {
				if(itz->second->v1 == 0) {
					if(iterator1 == 1) {
						itz->second->time = time0;
					}
					else {
						itz->second->time = 0;
					}
					el->push_back(itz->second);
					iterator1++;
				}
			}
		}
	}
}

