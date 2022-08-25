//Kijan Daniel
//Music library sorter
//Dr. Plank
//2/6/2022
#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <ostream>
using namespace std;

class Song {
	public:
		string title;
		int time;
		int track;
};

class Album {
	public:
		map <int, Song *> songs;
		string name;
		int time;
};

class Artist {
	public:
		map <string, Album *> albums;
		string name;
		int time;
		int nsongs;
};
void deletef(vector<Artist *> &artists);
int timeCal(string time);
void sorting(vector<Artist*>&artists);
string timeCalB(int time);
int main(int argc, char *argv[]) {
	if(argc != 2) {
		return 0;
	}
	ifstream filein (argv[1]);
	int checker, pos, track;
	string title, time, artist, album, genre;
	string line;
	vector<Artist *> artists;
	vector<Artist *>::iterator it;
	map<int, Song *>::iterator itsz;
	map<string, Album*>::iterator its;
	pair<string, Album*> albumpair;
	pair<int, Song *> songpair;
	stringstream ss;
	while(getline(filein,line)) {//while loop that reads in a file stream line by line 
		ss << line;
		ss >> title >> time >> artist >> album >> genre >> track;//divides the info from the file into needed specifications
		for(long unsigned int i = 0; i < title.size(); i++) {//replaceses all the underscores with spaces
			if(title[i] == '_') {
				title[i] = ' ';
			}
		}
		for(long unsigned int i = 0; i < artist.size(); i++) {
			if(artist[i] == '_') {
				artist[i] = ' ';
			}
		}
		for(long unsigned int i = 0; i < album.size(); i++) {
			if(album[i] == '_') {
				album[i] = ' ';
			}
		}
		for(long unsigned int i = 0; i < genre.size(); i++) {
			if(genre[i] == '_') {
				genre[i] = ' ';
			}
		}
		ss.clear();
		checker = 0;
		for(long unsigned int i = 0; i < artists.size(); i++) {//checks if the artists name has already been called before
			if(artist == artists[i]->name) {
				checker = 1;
				pos = i;
			}
		}
		if(checker == 1) {//case 1 name and album exist
			its = artists[pos]->albums.find(album);
			if(its != artists[pos]->albums.end()) {
				Song *song = new Song;
				song->title = title;
				song->time = timeCal(time);
				song->track = track;
				artists[pos]->time = timeCal(time) + artists[pos]->time;
				artists[pos]->nsongs = artists[pos]->nsongs + 1;
				its->second->time = its->second->time + timeCal(time);
		//		artists[pos]->albums->time = artists[pos]->albums->time + timeCal(time);
				songpair = make_pair(track, song);
				its->second->songs.insert(songpair);
			}
			else {//case 2 name exists
				Album * albump = new Album;
				Song *song = new Song;
				albump->name = album;
				albump->time = timeCal(time);
				song->title = title;
				song->track = track;
				song->time = timeCal(time);
				artists[pos]->time = timeCal(time) + artists[pos]->time;
				artists[pos]->nsongs = artists[pos]->nsongs + 1;
				songpair = make_pair(track, song);
				albump->songs.insert(songpair);
				albumpair = make_pair(album, albump);
				artists[pos]->albums.insert(albumpair);
			}
		}
		else {//case 3 nothing exists yet
			Artist *newartist = new Artist;
			newartist->name = artist;
			newartist->nsongs = 1;
			newartist->time = timeCal(time);
	
			Album *albump = new Album;
			albump->name = album;
			albump->time = timeCal(time);

			Song *song = new Song;
			song->title = title;
			song->track = track;
			song->time = timeCal(time);

			artists.push_back(newartist);
			albump->songs.insert(make_pair(track,song));
			newartist->albums.insert(make_pair(album,albump));
		}
	}
	filein.close();
	sorting(artists);
	for(long unsigned int i = 0; i < artists.size(); i++) {//print out in formatted way
		cout << artists[i]->name << ": " << artists[i]->nsongs << ", " << timeCalB(artists[i]->time) << endl;
		for(its = artists[i]->albums.begin(); its != artists[i]->albums.end(); its++) {
			cout << "        " << its->first << ": " << its->second->songs.size() << ", " << timeCalB(its->second->time) << endl;
			for(itsz = its->second->songs.begin(); itsz != its->second->songs.end(); itsz++) {
				cout << "                " << itsz->second->track << ". " << itsz->second->title << ": " << timeCalB(itsz->second->time) << endl;
			}
		}
	}
	deletef(artists);//makes sure all pointers are gone so no memory leak
	return 0;
}

int timeCal(string time) {//turns min:sec to sec
	int time1, time2;
	sscanf(time.c_str(), "%d:%d", &time1, &time2);
	time1 = time1 * 60;
	return time1 + time2;
}

void sorting(vector<Artist*>&artists) {//sorts the artists by their name
	Artist *artisth;

	for(long unsigned int i = 0; i < artists.size(); i++) {
		for(long unsigned int j = i+1; j < artists.size(); j++) {
			if(artists[i]->name > artists[j]->name) {
				artisth = artists[i];
				artists[i] = artists[j];
				artists[j] = artisth;
			}
		}
	}
}
string timeCalB(int time) {//turns sec to min:sec
	string time1;
	stringstream ss;
	ss.clear();
	int mins, seconds;
	string min, second;
	mins = time/60;
	seconds = time %60;
	ss << mins;
	ss >> min;
	ss.clear();
	ss << seconds;
	ss >> second;
	if(seconds < 10) {
		time1 = min + ":0" + second;
	}
	else {
		time1 = min + ':' + second;
	}
	return time1;
}

void deletef(vector<Artist *> &artists) {//deletes all pointers so no memory leak
	map<int, Song *>::iterator itsz;
	map<string, Album*>::iterator its;
	for(long unsigned int i = 0; i < artists.size(); i++) {
		for(its = artists[i]->albums.begin(); its != artists[i]->albums.end(); its++) {
			for(itsz = its->second->songs.begin(); itsz != its->second->songs.end(); itsz++) {
				delete itsz->second;
			}
			delete its->second;
		}
		delete artists[i];
	}
}
