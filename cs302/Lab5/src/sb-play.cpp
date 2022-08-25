//Kijan Daniel
//Dijoint sets superball
//3/20/2022
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include "disjoint_set.hpp"
using namespace std;
using plank::Disjoint_Set;

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

class Moves {
	public:
		int first;
		int second;
};
class Superball {
  public:
    Superball(int argc, char **argv);
	void analyze_superball();
	void nchoosek(int index,int n);
	void genmoves();
	void moveranker();
	int score1();
    int r;
    int c;
    int mss;
    int empty;
	Disjoint_Set *d;
	map<int,vector<Moves *> > movemap;
	vector <int> pmoves;
	vector <int> moves;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
	map<int,int>score;
};


void usage(const char *s) 
{
  fprintf(stderr, "usage: sb-read rows cols min-score-size colors\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

Superball::Superball(int argc, char **argv)
{
  int i, j;
  string s;

  if (argc != 5) usage(NULL);

  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
  if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

  colors.resize(256, 0);

  for (i = 0; i < (int)strlen(argv[4]); i++) {
    if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
    if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
    if (colors[argv[4][i]] != 0) usage("Duplicate color");
    colors[argv[4][i]] = 2+i;
    colors[toupper(argv[4][i])] = 2+i;
  }

  board.resize(r*c);
  goals.resize(r*c, 0);

  empty = 0;

  for (i = 0; i < r; i++) {
    if (!(cin >> s)) {
      fprintf(stderr, "Bad board: not enough rows on standard input\n");
      exit(1);
    }
    if ((int)s.size() != c) {
      fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", i);
      exit(1);
    }
    for (j = 0; j < c; j++) {
      if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
        fprintf(stderr, "Bad board row %d - bad character %c.\n", i, s[j]);
        exit(1);
      }
      board[i*c+j] = s[j];
      if (board[i*c+j] == '.') empty++;
      if (board[i*c+j] == '*') empty++;
      if (isupper(board[i*c+j]) || board[i*c+j] == '*') {
        goals[i*c+j] = 1;
        board[i*c+j] = tolower(board[i*c+j]);
      }
    }
  }
}

int main(int argc, char **argv)
{
  Superball *s;
  int i, checker;
  int ngoal, tgoal;
  map<int,vector<Moves *> >::iterator it;
  vector<Moves*> vec;
  s = new Superball(argc, argv);

  tgoal = 0;
  ngoal = 0;
  for (i = 0; i < s->r*s->c; i++) {
    if (s->goals[i] && s->board[i] != '*') {
      tgoal += s->colors[s->board[i]];
      ngoal++;
    }
  }
	s->genmoves();
	s->nchoosek(0,2);
	s->analyze_superball();
	checker = s->score1();
	if(checker == -1) {
		it = s->movemap.end();
		it--;
		vec = it->second;
		cout << "SWAP " << vec[0]->first/s->c <<" " << vec[0]->first%s->c << " " << vec[0]->second/s->c << " " << vec[0]->second%s->c << endl;
	}
	else {
		cout << "SCORE " << checker/s->c << " " << checker%s->c << endl;
	}


  exit(0);
}
int Superball::score1() {
	const vector<int>*vi;
	map<int,int>scoreboard;
	map<int,int>::iterator it;
	vi = d->Get_Sizes();
	for(it = score.begin(); it != score.end(); it++) {
		if((vi->at(it->first) >= mss) && (board[it->second] != '*')) {
			scoreboard.insert(make_pair(vi->at(it->first),it->second));
		}
	}
	if(scoreboard.empty()) {
		return -1;
	}
	else {
		it = scoreboard.end();
		it--;
		return it->second;
	}

}
void Superball::analyze_superball(){
	map<int,int>::iterator it;
	d = new Disjoint_Set;
	int holder, holder1;
	d->Initialize(r*c);
	score.clear();
	for(int i = 0; i < r; i++) {
		for(int z = 0; z < c; z++) {
			holder = z - 1;
			holder1 = i - 1;
			if(holder >= 0) {
				if((board[i*c+z] == board[i*c+holder])&& (board[i*c+z] != '*')&& (board[i*c+z] != '.')) {
					if(d->Find(i*c+z) != d->Find(i*c+holder)) {
						d->Union(d->Find(i*c+z),d->Find(i*c+holder));
					}
				}
			}
			if(holder1 >= 0) {
		//		cout << board[i*c+z] << " " << board[holder1*c+z] << endl;
				if((board[i*c+z] == board[holder1*c+z])&& (board[i*c+z] != '*')&& (board[i*c+z] != '.')) {
				//	cout << " row: " << i << " col: " << z << endl;
					if(d->Find(i*c+z) != d->Find(holder1*c+z)) {
						d->Union(d->Find(i*c+z),d->Find(holder1*c+z));
					}
				}
			}
		}
	}
	for(int i = 0; i < (int)goals.size(); i++) {
		if(goals[i] == 1) {
			holder = d->Find(i);
			if(score.find(holder) == score.end()) {
				score.insert(make_pair(holder,i));
			}
			else {
				it = score.find(holder);
				it->second = i;
			}
		}
	}

/*	vi = d->Get_Sizes();
	cout << "Scoring sets:" << endl;
	for(it = score.begin(); it != score.end(); it++) {
		if((vi->at(it->first) >= mss) && (board[it->second] != '*')) {
			cout << "  Size: " << setw(2) << vi->at(it->first) << "  Char: " << (char)board[it->second] << "  Scoring Cell: " << it->second/c << "," << it->second%c << endl;
		}
	}
	*/

	return;
}

void Superball::genmoves() {
	for(int i = 0; i < (int)board.size(); i++) {
		if((board[i] != '*') && (board[i] != '.')) {
			moves.push_back(i);
		}
	}
	return;
}

void Superball::nchoosek(int index, int n) {

	if(n == 0) {
		moveranker();
		return;
	}

	if(n > (int)moves.size() - index) return;

	pmoves.push_back(moves[index]);
	nchoosek(index+1, n-1);
	pmoves.pop_back();
	nchoosek(index+1, n);
}

void Superball::moveranker() {
	int tmp,tmp1;
	const vector<int>*vi;
	map<int, vector<Moves *> >::iterator it;
	Moves *m;
	tmp = board[pmoves[0]];
	board[pmoves[0]] = board[pmoves[1]];
	board[pmoves[1]] = tmp;
	analyze_superball();
	vi = d->Get_Sizes();
	tmp1 = 0;
	for(int i = 0; i < (int)vi->size(); i++) {
		tmp1 = tmp1 + vi->at(i);
	}
	m = new Moves;
	m->first = pmoves[0];
	m->second = pmoves[1];
	if(movemap.find(tmp1) != movemap.end()) {
		it = movemap.find(tmp1);
		it->second.push_back(m);
	}
	else {
		vector<Moves *> *tmpv;
		tmpv = new vector<Moves *>;
		tmpv->push_back(m);
		movemap.insert(make_pair(tmp1,*tmpv));
	}
	tmp = board[pmoves[0]];
	board[pmoves[0]] = board[pmoves[1]];
	board[pmoves[1]] = tmp;
	return;
}
