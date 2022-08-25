#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
using namespace std;

class Node {
  public: 
    string name;                    // The node's name
    vector <class Edge *> adj;      // The node's adjacency list in the residual graph.
    int visited;                    // A visited field for depth-first search.
	Edge *backedge;
};

class Edge {
  public:
    void Print() const;             // This prints the edge's name and residual flow.
    string name;                    // The edge's name (to store in the edge map).
    Node *n1;                       // The "from" node
    Node *n2;                       // The "to" node
    Edge *reverse;                  // The reverse edge, for processing the residual graph
    int original;                   // The original edge capacity.
    int residual;                   // The edge capacity in the residual graph.
};

class Graph {
  public:
     Graph();
     ~Graph();
     void Print() const;                 /* Print the graph to stdout. */
     string Verbose;                     /* G = print graph at each step. 
                                            P = print augmenting paths at each step.
                                            B = Basic: print graph at beginning and end. */
     Node *Get_Node(const string &s);    /* Create a node, or return it if already created. */
     Edge *Get_Edge(Node *n1, Node *n2); /* Create an edge or return it if already created. */
     int MaxFlow();                      /* Do the max flow calculation for the graph. */
     int Find_Augmenting_Path();         /* Find and process an augmenting path. */
  
     bool BFS();                  /* DFS to find an augmenting path - returns success. */
     vector <Edge *> Path;               /* The augmenting path. */

     int NPaths;                         /* Number of paths for the calculation. */
     int MaxCap;                         /* Maximum edge capacity */

     Node *Source;                       /* Source and sink node. */
     Node *Sink;

     vector <Node *> Nodes;              /* All of the nodes. */
     vector <Edge *> Edges;              /* All of the edges. */

     map <string, Node *> N_Map;         /* The nodes, keyed by name. */
     map <string, Edge *> E_Map;         /* The edges, keyed by name. */
};

Edge *Graph::Get_Edge(Node *n1, Node *n2)
{
  string en;
  Edge *e;

  en = n1->name + "->";
  en += n2->name;

  if (E_Map.find(en) != E_Map.end()) return E_Map[en];
  e = new Edge;
  e->name = en;
  E_Map[en] = e;
  Edges.push_back(e);
  e->original = 0;
  e->residual = 0;
  e->n1 = n1;
  e->n2 = n2;
  e->reverse = NULL;
  return e;
}

Node *Graph::Get_Node(const string &s)
{
  Node *n;

  if (N_Map.find(s) != N_Map.end()) return N_Map[s];

  n = new Node;
  n->name = s;
  n->visited = 0;
  N_Map[s] = n;
  Nodes.push_back(n);
  return n;
}


void Edge::Print() const
{
  printf("[%s:%d]", name.c_str(), residual);
}

void Graph::Print() const
{
  size_t i, j;
  Node *n;

  printf("Graph:\n");
  for (i = 0; i < Nodes.size(); i++) {
    n = Nodes[i];
    printf("  ");
    printf("Node: %s - ", n->name.c_str());
    for (j = 0; j < n->adj.size(); j++) n->adj[j]->Print();
    printf("\n");
  }
}

Graph::Graph()
{

  MaxCap = 0;
  Source = NULL;
  Sink = NULL;
}

Graph::~Graph()
{
  size_t i;

  for (i = 0; i < Nodes.size(); i++) delete Nodes[i];
  for (i = 0; i < Edges.size(); i++) delete Edges[i];
}

bool Graph::BFS() {

	queue<Node*> daque;
	Node *holder;
	while(!daque.empty()) {
		daque.pop();
	}
	daque.push(Source);
	Source->visited = 1;
	while(!daque.empty()) {
		holder = daque.front();
		daque.pop();
		holder->visited = 1;
		for(int i = 0; i < (int)holder->adj.size(); i++) {
			if((holder->adj[i]->n2->visited == 0)&&(holder->adj[i]->original == 1)) {
				holder->adj[i]->n2->visited = 1;
				holder->adj[i]->n2->backedge = holder->adj[i]->reverse;
				daque.push(holder->adj[i]->n2);
				if(holder->adj[i]->n2->name == "SINK") {
					return true;
				}
			}
		}
	}
	return false;
}

int main(int argc, char **argv)
{
	Graph *G;
	int counter;
	vector<Graph *> biggraph;
	string line,holder;
	Edge *E,*E1;
	vector<string>words;
	vector<string>dice;
	Node *n,*n1;
	if(argc > 4) {
		return 0;
	}
	ifstream ifs(argv[1]);
	if(ifs.is_open()) {
		while(getline(ifs,line)) {
/*			for(int i = 0; i < (int)line.size(); i++) {
				for(int z = i+1; z< (int)line.size(); z++) {
					if(line[z] == line[i]) {
						line.erase(line.begin() + z);
					}
				}
			}*/
			dice.push_back(line);
		}
		ifs.close();
	}
	else {
		cout << "Unable to open dice file" << endl;
		return 1;
	}
	ifs.open(argv[2]);
	if(ifs.is_open()) {
		while(getline(ifs,line)) {
			words.push_back(line);
		}
		ifs.close();
	}
	else {
		cout << "Unable to open words file" << endl;
		return 1;
	}
for(int i = 0; i < (int)words.size(); i++) {
	G = new Graph;
	n = new Node;
	counter = 0;
	n->name = "SOURCE";
	n->visited = 0;
	n->backedge = NULL;
	G->Nodes.push_back(n);
	G->Source = n;
	G->Verbose = 'B';
	for(int i = 0; i < (int)dice.size(); i++) {
	//	cout << dice[i] << endl;
		n = new Node;
		n->visited = 0;
		n->name = dice[i];
		n->backedge = NULL;
		G->Nodes.push_back(n);

		E = new Edge;
		E->n1 = G->Nodes[0];
		E->n2 = n;
		E->name = dice[i];
		E->original = 1;
		E->residual = 0;
		E1 = new Edge;
		E1->n1 = n;
		E1->n2 = G->Nodes[0];
		E1->name = "RSOURCE";
		E1->residual = 1;
		E1->original = 0;
		E->reverse = E1;
		E1->reverse = E;
		G->Edges.push_back(E);
		G->Edges.push_back(E);
		G->Nodes[0]->adj.push_back(E);
		n->adj.push_back(E1);
		counter++;
	}
	n1 = new Node;
	n1->name = "SINK";
	n1->visited = 0;
	n->backedge = NULL;
	for(int j = 0; j < (int)words[i].size(); j++) {
	//	cout << words[i][j] << endl;
		n = new Node;
		n->visited = 0;
		n->name = words[i][j];
		n->backedge = NULL;
		G->Nodes.push_back(n);
		
		E = new Edge;
		E->n1 = n;
		E->n2 = n1;
		E->original = 1;
		E->residual = 0;
		E->name = "SINK";
		E1 = new Edge;
		E1->n1 = n1;
		E1->n2 = n;
		E1->residual = 1;
		E1->original = 0;
		E1->name = words[i][j];
		E->reverse = E1;
		E1->reverse = E;
		G->Edges.push_back(E1);
		G->Edges.push_back(E);
		n->adj.push_back(E);
		n1->adj.push_back(E1);
	}
	G->Sink = n1;
	G->Nodes.push_back(n1);
	biggraph.push_back(G);
//	cout << endl;
	for(int p = 1; p < (int)dice.size()+1; p++) {
//		cout << "Outer: " << G->Nodes[p]->name << endl;
		for(int j = dice.size()+1; j < (int)G->Nodes.size()-1; j++) {
//			cout << "Inner: " << G->Nodes[j]->name << endl;
			
			for(int f = 0; f < (int)G->Nodes[p]->name.size(); f++) {
//				cout << "Compare: " << G->Nodes[p]->name[f] << ' ' << G->Nodes[j]->name[0] << endl; 
				if(G->Nodes[p]->name[f] == G->Nodes[j]->name[0]) {
//					cout << "hey" << endl;	
					E = new Edge;
					E->n1 = G->Nodes[p];
					E->n2 = G->Nodes[j];
					E->name = G->Nodes[p]->name + ' ' + G->Nodes[j]->name[0];
					E->original = 1;
					E->residual = 0;
//					cout <<  G->Nodes[p]->name + ' ' + G->Nodes[j]->name[0] << endl;
					E1 = new Edge;
					E1->n1 = G->Nodes[j];
					E1->n2 = G->Nodes[p];
					E1->name = 'R' +  G->Nodes[p]->name +' ' + G->Nodes[j]->name[0];
					E1->residual = 1;
					E1->original = 0;
					E->reverse = E1;
					E1->reverse = E;
					G->Edges.push_back(E);
					G->Edges.push_back(E1);
					G->Nodes[p]->adj.push_back(E);
					G->Nodes[j]->adj.push_back(E1);
				}
			}
		}
	}
	while(	G->BFS()) {
		n1 = G->Sink;

		while(n1 != G->Source) {
		//	cout << n1->name;
//			cout << "While" << endl;
			n1->backedge->original = 1;
			n1->backedge->residual = 0;
			n1->backedge->reverse->original = 0;
			n1->backedge->reverse->residual = 1;
//			cout << n1->backedge->n1->name << ' ' << n1->backedge->n2->name << ' ' << n1->backedge->original << ' ' << n1->backedge << endl;
			n1 = n1->backedge->n2;
		}
//		cout << "whileend" << endl;
		for(int i = 0; i < (int)G->Nodes.size(); i++) {
			G->Nodes[i]->visited = 0;
		}
	}
	bool checker = false;
	string wordh = words[i];
	string wordh1;
	for(int i = 0; i < (int)G->Sink->adj.size(); i++) {
		if(checker == true) {
			break;
		}
		if(G->Sink->adj[i]->residual == 1) {
			checker = true;
		}
	}
	if(checker == true) {
		cout << "Cannot spell " << words[i] << endl;
	}
	else {
		for(int i = dice.size()+1; i < (int)G->Nodes.size()-1; i++) {
			for(int z = 0; z < (int)G->Nodes[i]->adj.size(); z++) {
				if(G->Nodes[i]->adj[z]->residual == 0) {
					wordh1.clear();
					for(int p = 1; p < (int)G->Nodes[i]->adj[z]->name.size()-2; p++) {
						wordh1 = wordh1 + G->Nodes[i]->adj[z]->name[p];
					}
					for(int w = 0; w < (int)dice.size(); w++) {
						if(wordh1 == dice[w]) {
							cout << w;
							break;
						}
					}
				}
			}
			if(i != (int)G->Nodes.size()-2) {
				cout << ',';
			}
			else {
				cout << ':';
			}
		}
		cout << ' ' << wordh << endl;
	}

//	G->Print();
/*	for(int i = 0; i < G->Edges.size(); i++) {
		cout << G->Edges[i]->n1->name << ' ' << G->Edges[i]->n2->name << ' ' << G->Edges[i]->reverse->n1->name << ' ' << G->Edges[i]->reverse->n2->name << endl;
	}*/

}
}
