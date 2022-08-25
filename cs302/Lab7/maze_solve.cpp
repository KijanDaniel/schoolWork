//Kijan Daniel
//4/3/2022
//Dr. Plank
//Maze Solver
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;
class square {
	public:
		bool top = false;
		bool right = false;
		bool bottom = false;
		bool left = false;
};
class Node {
	public:
		int id;
		vector<int> edges;
		int visited;
};

class Graph {
	public:
		vector <Node *> nodes;
		vector <int> finalpath;
		bool dfs(Node* n);
};

bool Graph::dfs(Node* n) {
	if(n->visited == 1) {
		return false;
	}
	if(n->id == nodes.size()-1) {
		finalpath.push_back(n->id);
		return true;
	}
	n->visited = 1;
	for(int i = 0; i < n->edges.size(); i++) {
		if(dfs(nodes[n->edges[i]])) {
			finalpath.push_back(n->id);
			return true;
		}
	}
	return false;
}

int main() {

	string define,name;
	int tmp,tmp1,tmp2,row,col;
	stringstream ss;
	vector<square> maze;
	Graph g;
	Node *n;
	while(cin  >> name) {
		if(name == "ROWS") {
			cin >> row;
			cout << name << ' ' << row << ' ';
			cin >> name;

			if(name == "COLS") {
				cin >> col;

			    cout << name << ' ' << col << endl;
			}
			maze.resize(col*row);
		}
		if(name == "WALL") {
			cin >> tmp;
			cin >> tmp1;
			if(tmp1 > tmp) {
				tmp2 = tmp1;
				tmp1 = tmp;
				tmp = tmp2;
			}

			cout << name << ' ' << tmp << ' ' << tmp1 << endl;
		    if((tmp-tmp1) == 1) {
				maze[tmp1].right = true;
				maze[tmp].left = true;
			}
			else if(((tmp-tmp1) / col) == 1) {
				maze[tmp1].bottom = true;
				maze[tmp].top = true;
			}
		}
	}

	for(int i = 1; i < col; i++) {
		maze[i].top = true;
	}
	for(int i = 0; i < row; i++) {
		maze[i*col].left = true;
	}
	for(int i = 0; i < col-1; i++) {
		maze[(row-1) *col + i].bottom = true;
	}
	for(int i = 0; i < row; i++) {
		maze[i*col + col-1].right = true;
	}

	for(size_t i = 0; i < maze.size(); i++) {
		n = new Node;
		n->id = i;
		n->visited = 0;
		g.nodes.push_back(n);
	}
	for(size_t i = 0; i < maze.size(); i++) {
		if(maze[i].top == false) {
			if(i != 0) {
				g.nodes[i]->edges.push_back(i-col);
			}
		}
		if(maze[i].right == false) {
			g.nodes[i]->edges.push_back(i+1);
		}
		if(maze[i].left == false) {
			g.nodes[i]->edges.push_back(i-1);

		}
		if(maze[i].bottom == false) {
			if(i != (maze.size()-1)) {
				g.nodes[i]->edges.push_back(i+col);
			}
		}
	}

	g.dfs(g.nodes[0]);
	for(int i = g.finalpath.size()-1; i >= 0; i--) {
		cout << "PATH " << g.finalpath[i] << endl;
	}
	for(int i = 0; i < g.nodes.size(); i++) {
		delete g.nodes[i];
	}
	return 1;
}


