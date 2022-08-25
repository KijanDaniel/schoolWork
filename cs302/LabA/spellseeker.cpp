//Kijan Daniel
//Dr. Plank 
//5/10/22
//This plays the spell game
#include <cstdlib> 
#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class Answer {
	public:
		int length;
		int r;
		int c;
		string key;
		Answer *nexta;
};

class SpellSeeker {
	public:
		vector<string> bgraph;
		string visited;
		map <string,Answer *> cache;
		int total_r;
		string keyh;
		int total_c;
		void dfs(int r, int c, string &key);
		Answer *Solve(int r, int c);
};

void SpellSeeker::dfs(int r, int c, string &key) {
	if(bgraph[r][c] == '-') {
		return;
	}
	if(r < 0) {
		return;
	}
	if(c < 0) {
		return;
	}
	if(r >= total_r) {
		return;
	}
	if(c >= total_c) {
		return;
	}
	if(visited[r*total_c+c] == '1') {
		return;
	}
	visited[r*total_c+c] = '1';
	char value = bgraph[r][c];
	key[r*total_c+c] = 'O';
	if((r-1) >= 0) {
		if(((bgraph[r-1][c] + 1) == value) || ((bgraph[r-1][c] - 1) == value)) {
			dfs(r-1,c,key);
		}
	}
	if((r+1) != (int)bgraph.size()) {	
		if(((bgraph[r+1][c] + 1) == value) || ((bgraph[r+1][c] - 1) == value)) {
			dfs(r+1,c,key);
		}
	}
	if((c-1) >= 0) {
		if(((bgraph[r][c-1] + 1) == value) || ((bgraph[r][c-1] - 1) == value)) {
			dfs(r,c-1,key);
		}
	}
	if((c+1) != (int)bgraph[0].size()) {
		if(((bgraph[r][c+1] + 1) == value) || ((bgraph[r][c+1] - 1) == value)) {
			dfs(r,c+1,key);
		}
	}
	if((c%2) == 0) {
		if((r+1) != (int)bgraph.size()) {
			if((c+1) != (int)bgraph[0].size()) {
				if(((bgraph[r+1][c+1] + 1) == value) || ((bgraph[r+1][c+1] - 1) == value)) {
					dfs(r+1,c+1,key);
				}
			}
			if((c-1) >= 0) {
				if(((bgraph[r+1][c-1] + 1) == value) || ((bgraph[r+1][c-1] - 1) == value)) {
					dfs(r+1,c-1,key);
				}
			}
		}
	}
	if((c%2) == 1) {
		if((r-1) >= 0) {
			if((c-1) >= 0) {
				if(((bgraph[r-1][c-1] + 1) == value) || ((bgraph[r-1][c-1] - 1) == value)) {
					dfs(r-1,c-1,key);
				}
			}
			if((c+1) != (int)bgraph[0].size()) {
				if(((bgraph[r-1][c+1] + 1) == value) || ((bgraph[r-1][c+1] - 1) == value)) {
					dfs(r-1,c+1,key);
				}
			}
		}
	}
	return;
}


Answer* SpellSeeker::Solve(int r, int c) {
	map <string,Answer *>::iterator it;
	Answer *nAnswer,*a,*b,*c1,*d,*e,*f;
	vector<int>lengths;
	vector<Answer*>which;
	int big,place;
/*	if((r < 0) || (c < 0)) {
		nAnswer = new Answer;
		nAnswer->r = r;
		nAnswer->c = c;
		nAnswer->length = 1;
		nAnswer->nexta = NULL;
		return nAnswer;
	}
	if((r >= total_r) || (c >= total_c)) {
		nAnswer = new Answer;
		nAnswer->r = r;
		nAnswer->c = c;
		nAnswer->length = 1;
		nAnswer->nexta = NULL;
		return nAnswer;
	}
	if(bgraph[r][c] == '-') {
		nAnswer = new Answer;
		nAnswer->r = r;
		nAnswer->c = c;
		nAnswer->length = 1;
		nAnswer->nexta = NULL;
		return nAnswer;
	}*/
	big = 0;
	place = 0;
	which.clear();
	visited.clear();
	lengths.clear();
	keyh.clear();
	for(int i = 0; i < total_c*total_r; i++) {
		keyh = keyh + '-';
		visited = visited + '0';
	}
	dfs(r,c,keyh);
	keyh[r*total_c+c] = 'X';
	if(cache.find(keyh) != cache.end()) {
		it = cache.find(keyh);
		return it->second;
	}
	char value = bgraph[r][c];
	bgraph[r][c] = '-';

	nAnswer = new Answer;
	nAnswer->r = r;
	nAnswer->c = c;
	nAnswer->key = keyh;
	if((r-1) >= 0) {
		if(((bgraph[r-1][c] + 1) == value) || ((bgraph[r-1][c] - 1) == value)) {
			a = Solve(r-1,c);
			which.push_back(a);
			lengths.push_back(a->length);
		}
	}
	if((r+1) != (int)bgraph.size()) {	
		if(((bgraph[r+1][c] + 1) == value) || ((bgraph[r+1][c] - 1) == value)) {
			b = Solve(r+1,c);
			which.push_back(b);
			lengths.push_back(b->length);
		}
	}
	if((c-1) >= 0) {
		if(((bgraph[r][c-1] + 1) == value) || ((bgraph[r][c-1] - 1) == value)) {
			c1 = Solve(r,c-1);
			which.push_back(c1);
			lengths.push_back(c1->length);
		}
	}
	if((c+1) != (int)bgraph[0].size()) {
		if(((bgraph[r][c+1] + 1) == value) || ((bgraph[r][c+1] - 1) == value)) {
			d = Solve(r,c+1);
			which.push_back(d);
			lengths.push_back(d->length);
		}
	}
	if((c%2) == 0) {
		if((r+1) != (int)bgraph.size()) {
			if((c+1) != (int)bgraph[0].size()) {
				if(((bgraph[r+1][c+1] + 1) == value) || ((bgraph[r+1][c+1] - 1) == value)) {
					e = Solve(r+1,c+1);
					which.push_back(e);
					lengths.push_back(e->length);
				}
			}
			if((c-1) >= 0) {
				if(((bgraph[r+1][c-1] + 1) == value) || ((bgraph[r+1][c-1] - 1) == value)) {
					f = Solve(r+1,c-1);
					which.push_back(f);
					lengths.push_back(f->length);
				}
			}
		}
	}
	if((c%2) == 1) {
		if((r-1) >= 0) {
			if((c-1) >= 0) {
				if(((bgraph[r-1][c-1] + 1) == value) || ((bgraph[r-1][c-1] - 1) == value)) {
					e = Solve(r-1,c-1);
					which.push_back(e);
					lengths.push_back(e->length);
				}
			}
			if((c+1) != (int)bgraph[0].size()) {
				if(((bgraph[r-1][c+1] + 1) == value) || ((bgraph[r-1][c+1] - 1) == value)) {
					f = Solve(r-1,c+1);
					which.push_back(f);
					lengths.push_back(f->length);
				}
			}
		}
	}
	if(!which.empty() && !lengths.empty()) {
		for(int i = 0; i < (int)lengths.size(); i++) {
			if(big < lengths[i]) {
				big = lengths[i];
				place = i;
			}
		}
		nAnswer->nexta = which[place];
		nAnswer->length = which[place]->length+1;
	}
	else {
		nAnswer->nexta = NULL;
		nAnswer->length = 1;
	}
		cache.insert(make_pair(nAnswer->key,nAnswer));
	bgraph[r][c] = value;
	return nAnswer;

}

int main() {
	int cols, rows,place,length;
	vector<int>holder1;
	vector<Answer *>finala;
	Answer *fun;
	SpellSeeker *graph;
	string line;
	graph = new SpellSeeker;
	while(getline(cin,line)) {
		cols = (int)line.size();
		graph->bgraph.push_back(line);
		graph->total_c = cols;
	}
	rows = graph->bgraph.size();
	graph->total_r = rows;
	for(int i = 0; i < rows; i++) {
		for(int z = 0; z < cols; z++) {
			finala.push_back(graph->Solve(i,z));
		}
	}
	length = 0;
	for(int i = 0; i < (int)finala.size(); i++) {
		if(length < finala[i]->length) {
			length = finala[i]->length;
			place = i;
		}
	}
	fun = finala[place];
	for(int i = 0; i < (int)graph->bgraph.size(); i++) {
		cout << graph->bgraph[i] << endl;
	}
	cout << "PATH" << endl;
	while(fun->nexta != NULL) {
		cout << fun->r << ' ' << fun->c << endl;
		fun = fun->nexta;
	}
	cout << fun->r << ' ' << fun->c << endl;
	delete graph;
}

