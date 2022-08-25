//Dr. Plank 
//Lab9 
//Recursion lab 
//11/8/2021
#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>
using namespace std;

class Shifter {
	public:

		bool Read_Grid_And_Shapes(int argc, char ** argv);

		bool Apply_Shapes(int index,int r, int c);

		bool Find_Solution(int index);

		void Print_Solution() const;

	protected:

		vector <string> Grid;

		vector< vector <string> > Shapes;

		vector <int> Solution_Rows;
		vector <int> Solution_Cols;
};

int main(int argc, char ** argv) {

	Shifter daGame;
	daGame.Read_Grid_And_Shapes(argc,argv);
	daGame.Find_Solution(0);
	daGame.Print_Solution();
	return 1;
}


bool Shifter::Read_Grid_And_Shapes(int argc, char ** argv) {
	
	string first = argv[1]; //Reads in all the arg vals
	string second = "";
	int size = first.size();
	int increment = 0;
	vector <string> filler;
	stringstream ss;
	for(int i = 1; i < argc; i++) {
		first = argv[i];
		if(first.size() != (size_t)size) {
			return false;
		}
		for(size_t z = 0; z < first.size(); z++) {
			if((first[z] != '1') && (first[z] != '0')) {
				return false;
			}
		}
		Grid.push_back(argv[i]);
	}
	while(getline(cin, first)) { //Gets each line and splits shapes into there respective rows
		Shapes.push_back(filler);
		ss.clear();
		ss << first;
		while(ss >> second) {
			Shapes[increment].push_back(second);
		}
		increment++;
	}
	return true;
}

bool Shifter::Apply_Shapes(int index,int r, int c) {
	vector <string> Gridc = Grid;
	if(index >= (int)Shapes.size()) {
		return false;
	}
	if((Grid.size() - r) < Shapes[index].size()) {
		return false;
	}
	for(int i = 0; i < (int)Shapes[index].size(); i++) {
		if((Grid[0].size() - c) < Shapes[index][i].size()) {
			Grid = Gridc;//Reverts to og if it fails test
			return false;
		} 
		for(int z = 0; z < (int)Shapes[index][i].size(); z++) {
			Grid[r+i][c+z] = ((Grid[r+i][c+z] - 48) xor (Shapes[index][i][z] - 48)) + 48; //Gross line to make 1 or 0
		}
	}
	return true;
}

bool Shifter::Find_Solution(int index){
	if(Grid.size() == 0) {
		return false;
	}
	bool checker = true;
	for(int i = 0; i < (int)Grid.size(); i++) {
		for(int z = 0; z < (int)Grid[i].size(); z++) {
			if(Grid[i][z] == '1') {
				checker = true;
			}
			else {
				checker = false;
				break;
			}
		}
		if(checker == false) {
			break;
		}
	}
	if((index == (int)Shapes.size()) && checker) {
		return true;
	}
	for(int i = 0; i < (int)Grid.size(); i++) {
		for(int z = 0; z < (int)Grid[i].size(); z++) {
			if(Apply_Shapes(index,i,z)) {//Recursion statement
				if(Find_Solution(index+1)) {
					Solution_Rows.push_back(i);//Puts in reverse order what the solutions are
					Solution_Cols.push_back(z);
					return true;
				}
				Apply_Shapes(index,i,z);
			}
		}
	}
	return false;
}

void Shifter::Print_Solution() const {
	for(int i = 0; i < (int)Shapes.size(); i++) {
		for(int z = 0; z < (int)Shapes[i].size(); z++) {
			cout << Shapes[i][z] << " ";
		}
		cout << Solution_Rows[Solution_Rows.size()-1-i] << " " << Solution_Cols[Solution_Cols.size()-1-i] << endl;//Reverse order
	}
}


