//Kijan Daniel 
//superball
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

class Superball {
  public:
    Superball(int argc, char **argv);
	void analyze_superball();
    int r;
    int c;
    int mss;
    int empty;
	Disjoint_Set *d;
    vector <int> board;
    vector <int> goals;
    vector <int> colors;
};


void usage(const char *s) 
{
  fprintf(stderr, "usage: sb-read rows cols min-score-size colors\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

Superball::Superball(int argc, char **argv)
{
  long unsigned int i, j;
  string s;

  if (argc != 5) usage(NULL);

  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad rows");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad cols");
  if (sscanf(argv[3], "%d", &mss) == 0 || mss <= 0) usage("Bad min-score-size");

  colors.resize(256, 0);

  for (i = 0; i < strlen(argv[4]); i++) {
    if (!isalpha(argv[4][i])) usage("Colors must be distinct letters");
    if (!islower(argv[4][i])) usage("Colors must be lowercase letters");
    if (colors[argv[4][i]] != 0) usage("Duplicate color");
    colors[argv[4][i]] = 2+i;
    colors[toupper(argv[4][i])] = 2+i;
  }

  board.resize(r*c);
  goals.resize(r*c, 0);

  empty = 0;

  for (i = 0; i < (long unsigned int)r; i++) {
    if (!(cin >> s)) {
      fprintf(stderr, "Bad board: not enough rows on standard input\n");
      exit(1);
    }
    if ((int)s.size() != c) {
      fprintf(stderr, "Bad board on row %d - wrong number of characters.\n", (int)i);
      exit(1);
    }
    for (j = 0; (int)j < c; j++) {
      if (s[j] != '*' && s[j] != '.' && colors[s[j]] == 0) {
        fprintf(stderr, "Bad board row %d - bad character %c.\n", (int)i, s[j]);
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
  int i;
  int ngoal, tgoal;
 
  s = new Superball(argc, argv);

  tgoal = 0;
  ngoal = 0;
  for (i = 0; i < s->r*s->c; i++) {
    if (s->goals[i] && s->board[i] != '*') {
      tgoal += s->colors[s->board[i]];
      ngoal++;
    }
  }
	s->analyze_superball();

  exit(0);
}

void Superball::analyze_superball(){//All i do is loop through the board looking for like colors touching and then I just union those tiles
	map<int,int>score;
	map<int,int>::iterator it;
	d = new Disjoint_Set;
	const vector<int>*vi;
	int holder, holder1;
	d->Initialize(r*c);
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

	vi = d->Get_Sizes();
	cout << "Scoring sets:" << endl;
	for(it = score.begin(); it != score.end(); it++) {
		if((vi->at(it->first) >= mss) && (board[it->second] != '*')) {
			cout << "  Size: " << setw(2) << vi->at(it->first) << "  Char: " << (char)board[it->second] << "  Scoring Cell: " << it->second/c << "," << it->second%c << endl;
		}
	}
	

	return;
}
