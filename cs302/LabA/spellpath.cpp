//Kijan Daniel
//Dr. Plank 
//5/10/22
//This plays the spell game
#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>
#include <ostream>
using namespace std;

/*class Node {
	public:
		int id;
		char name;
		vector <Node*> adj;
		int visited;
};*/

class Graph{
	public:
	/*	vector <Node *> nodes;
		vector<Node *> finalpath;
		void dfs(Node * danode);*/
		vector<string>graph;
		int MaxPathLen(int r, int c, vector<string>bgraph);
};
/*void Graph::dfs(Node * danode) {
	finalpath.push_back(danode);
	if(danode->visited == 1) {
		return;
	}
	danode->visited = 1;
	for(int i = 0; i < danode->adj.size(); i++) {
		if(danode->adj[i]->visited != 1) {
			dfs(danode->adj[i]);
		}
	}
	return;
}*/
int Graph::MaxPathLen(int r, int c, vector<string>bgraph) {
	if(bgraph[r][c] == '-') {
		return 0;
	}
	char value;
	int a,b,c1,d,e,f,big;
	vector<int>biggest;
	a = 0;
	b = 0;
	c1 = 0;
	d = 0;
	e = 0;
	f = 0;
	big = 0;
	value = bgraph[r][c];
	bgraph[r][c] = '-';
	if((r-1) >= 0) {
		if(((bgraph[r-1][c] + 1) == value) || ((bgraph[r-1][c] - 1) == value)) {
			a = MaxPathLen(r-1,c,bgraph);
		}
	}
	if((r+1) != (int)bgraph.size()) {	
		if(((bgraph[r+1][c] + 1) == value) || ((bgraph[r+1][c] - 1) == value)) {
			b = MaxPathLen(r+1,c,bgraph);
		}
	}
	if((c-1) >= 0) {
		if(((bgraph[r][c-1] + 1) == value) || ((bgraph[r][c-1] - 1) == value)) {
			c1 = MaxPathLen(r,c-1,bgraph);
		}
	}
	if((c+1) != (int)bgraph[0].size()) {
		if(((bgraph[r][c+1] + 1) == value) || ((bgraph[r][c+1] - 1) == value)) {
			d = MaxPathLen(r,c+1,bgraph);
		}
	}
	if((c%2) == 0) {
		if((r+1) != (int)bgraph.size()) {
			if((c+1) != (int)bgraph[0].size()) {
				if(((bgraph[r+1][c+1] + 1) == value) || ((bgraph[r+1][c+1] - 1) == value)) {
					e = MaxPathLen(r+1,c+1,bgraph);
				}
			}
			if((c-1) >= 0) {
				if(((bgraph[r+1][c-1] + 1) == value) || ((bgraph[r+1][c-1] - 1) == value)) {
					f = MaxPathLen(r+1,c-1,bgraph);
				}
			}
		}
	}
	if((c%2) == 1) {
		if((r-1) >= 0) {
			if((c-1) >= 0) {
				if(((bgraph[r-1][c-1] + 1) == value) || ((bgraph[r-1][c-1] - 1) == value)) {
					e = MaxPathLen(r-1,c-1,bgraph);
				}
			}
			if((c+1) != (int)bgraph[0].size()) {
				if(((bgraph[r-1][c+1] + 1) == value) || ((bgraph[r-1][c+1] - 1) == value)) {
					f = MaxPathLen(r-1,c+1,bgraph);
				}
			}
		}
	}
	bgraph[r][c] = value;
	biggest.resize(6);
	biggest[0] = a;
	biggest[1] = b;
	biggest[2] = c1;
	biggest[3] = d;
	biggest[4] = e;
	biggest[5] = f;
	for(int i = 0; i < (int)biggest.size(); i++) {
		if(biggest[i] > big) {
			big = biggest[i];
		}
	}
	return big+1;
}
int main() {
	int rows;
	vector<int>holder1;
//	stringstream ss;
//	Node *node;
	Graph *graph;
	string line;
	graph = new Graph;
	while(getline(cin,line)) {
		graph->graph.push_back(line);
/*		ss.clear();
		ss << line;
		while(ss >> var) {
			node = new Node;
			node->id = count;
			node->name = var;
			node->visited = 0;
			count++;
			graph->nodes.push_back(node);
		}*/
	}
	for(int i = 0; i < (int)graph->graph.size(); i++) {
		for(int z = 0; z < (int)graph->graph[i].size(); z++) {
			holder1.push_back(graph->MaxPathLen(i,z,graph->graph));
		}
	}
	rows = 0;
	for(int i = 0; i < (int)holder1.size(); i++) {
		if(rows < holder1[i]) {
			rows = holder1[i];
		}
	}
	cout << rows << endl;
/*	rows = (int)graph->nodes.size() / cols;
	for(int i = 0; i < graph->nodes.size(); i++) {
		if(i < ((int)graph->nodes.size()-cols)) {
			graph->nodes[i]->adj.push_back(graph->nodes[i+cols]);
			graph->nodes[i+cols]->adj.push_back(graph->nodes[i]);
		}
		if(0 != ((i+1)%cols)) {
			graph->nodes[i]->adj.push_back(graph->nodes[i+1]);
			graph->nodes[i+1]->adj.push_back(graph->nodes[i]);
		}
	}
	for(int i = 0; i < graph->nodes.size(); i++) {
		cout << graph->nodes[i]->id << graph->nodes[i]->visited << ": ";
		for(int z = 0; z < graph->nodes[i]->adj.size(); z++) {
			cout << graph->nodes[i]->adj[z]->id << ' ';
		}
		cout << endl;
	}
	graph->nodes[5]->adj.pop_back();

	graph->nodes[6]->adj.pop_back();
	graph->nodes[7]->adj.pop_back();
	graph->nodes[1]->adj.pop_back();
	graph->dfs(graph->nodes[0]);
	for(int i = 0; i < graph->finalpath.size(); i++) {
		cout << graph->finalpath[i]->id << ' ';
	}
	cout << endl;
	
	cout << cols << ' ' << rows << endl;*/
	return 1;
}
