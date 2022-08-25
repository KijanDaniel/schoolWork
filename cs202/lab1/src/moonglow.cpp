#include <iostream>

using namespace std;

int main() {
	double scores = 0.0, avgScores = 0.0, finalScore = 0.0;
	double iterator = 0.0;
	string names, finalName;
	while(true) {//Infinite loop that only cancels when a creak happens
		if(cin >> scores) {
			finalScore = scores + finalScore;//Checks if its a number first
		}
		else{
			if(cin.eof()) {//End of file check
				break;
			}
			cin.clear();
		
		if(cin >> names) { //This checks to see if the string is what is required to create a new name
			if(names =="AVERAGE") {//This checks if there is the average keyword
				iterator = 0.0;
				while(cin >> scores) {
					avgScores = scores + avgScores;//Calculates average without divide
					iterator++;
				}
				if(iterator > 0) {//Error check so you dont divide by zero
					avgScores = avgScores / iterator;
					finalScore = finalScore + avgScores;
					avgScores = 0;
				}
				if(cin.eof()){
					break;
				}
				cin.clear();
			}
			if(names == "NAME") {//Checks for the name keyword
				if(cin >> names) {
					finalName = names;
				}
				else {
					if(cin.eof()){
						break;
					}
					cin.clear();
				}
			}
		}
		else {
			if(cin.eof()) {
				break;
			}
			cin.clear();
		}
		}
	}
	cin.clear();
	cout << finalName << " " << finalScore << endl;//Final print out
	return 0;
}
