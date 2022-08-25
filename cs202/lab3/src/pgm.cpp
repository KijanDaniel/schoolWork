//Kijan Daniel
//Dr. Plank
//Lab3 
//This program lets one mess with pgm files
//9/13/2021
#include "pgm.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

bool Pgm::Read(const std::string &file)
{
  ifstream fin;
  string s;
  size_t i, j, r, c, v;

  fin.open(file.c_str());
  if (fin.fail()) return false;
  
  if (!(fin >> s)) return false;
  if (s != "P2") return false;
  if (!(fin >> c) || c <= 0) return false;
  if (!(fin >> r) || r <= 0) return false;
  if (!(fin >> i) || i != 255) return false;

  Pixels.resize(r);
  for (i = 0; i < r; i++) {
    Pixels[i].clear();
    for (j = 0; j < c; j++) {
      if (!(fin >> v) || v > 255) return false;
      Pixels[i].push_back(v);
    }
  }
  if (fin >> s) return false;
  fin.close();
  return true;
}

bool Pgm::Write(const std::string &file) const  {//Im sorry about all the casting but I hate seeing the warnings
	int r,c;
	int specialNum = 255;
	int counter = 1;
	if(Pixels.empty()) {//Makes sure there are pixels
		return false;
	}
	r = Pixels.size();
	c = Pixels[0].size();
	if((r == 0) || (c == 0)) {//Makes sure that the pixel vector is filled properly
		return false;
	}
	ofstream outFile;
	outFile.open(file.c_str());
	if(outFile.fail()) {//Checks to see that the file open properly
		return false;
	}
	outFile << "P2" << endl;//Prints the pgm file into the file selected
	outFile << c << " " << r << endl;
	outFile << specialNum << endl;
	for(int i = 0; i < r; i++) {
		for(int z = 0; z < c; z++) {
			outFile << Pixels[i][z];
			if((r*c) == ((i+1)*(z+1))) {
				outFile << endl;
				break;
			}
			if((counter % 20) == 0) {
				outFile << endl;
			}
			else {
				outFile << " ";
			}
			counter++;
		}
	}
	

	return true;
}
bool Pgm::Create(size_t r, size_t c, size_t pv) {
	if(((int)r <= 0) || ((int)c <= 0) || ((int)pv < 0) || ((int)pv > 255)) {//Makes sure that all conditions are met to make a appropriate pgm file
		return false;
	}
	Pixels.resize(r, vector<int>(c));
	for(int i = 0; i < (int)r; i++) {
		for(int z = 0; z < (int)c; z++) {
			Pixels[i][z] = pv;//Fills the pixel vector with the assigned color value
		}
	}
	return true;
}
bool Pgm::Clockwise() {
	int r, c;
	if(Pixels.empty()) {
		return false;
	}
	r = Pixels[0].size();
	c = Pixels.size();
	if((r <= 0)||(c <= 0)) {
		return false;
	}
	vector< vector<int> > nPixels(r, vector<int>(c));
	for(int i = 0; i < (int)Pixels.size(); i++) {
		for(int z = 0; z < (int)Pixels[0].size(); z++) {
			nPixels[z][i] = Pixels[i][z];//Swaps the rows and cols
		}
	}
	int ph1 = 0, ph2 = 0;
	for(int i = 0; i < r; i++) {//Does a horizontal flip to achieve a 90 deg rotation
		for(int z = 0; z < c/2; z++) {
			ph1 = nPixels[i][z];
			ph2 = nPixels[i][c-z-1];
			nPixels[i][z] = ph2;
			nPixels[i][c-z-1] = ph1;
		}
	}
	Pixels.resize(r);
	for(int i = 0; i < r; i++) {
		Pixels[i].resize(c);
	}
	for(int i = 0; i < r; i++) {
		for(int z = 0; z < c; z++) {
			Pixels[i][z] = nPixels[i][z];//Fills out the new resized Pixel vector
		}
	}

	return true;
}
bool Pgm::Cclockwise() {
	int r, c;
	if(Pixels.empty()) {
		return false;
	}
	r = Pixels[0].size();
	c = Pixels.size();
	if((r <= 0)||(c <= 0)) {
		return false;
	}
	
	vector< vector<int> > nPixels(r, vector<int>(c));
	for(int i = 0; i < (int)Pixels.size(); i++) {
		for(int z = 0; z < (int)Pixels[0].size(); z++) {
			nPixels[z][i] = Pixels[i][z];//Flips the rows and cols
		}
	}
	Pixels.resize(r);
	for(int i = 0; i < r; i++) {
		Pixels[i].resize(c);
	}
	for(int i = 0; i < r; i++) {
		for(int z = 0; z < c; z++) {//Flips the vector vertically
			Pixels[i][z] = nPixels[r-1-i][z];
		}
	}
	return true;
}
bool Pgm::Pad(size_t w, size_t pv) {
	if(((int)w <= 0) || ((int)pv < 0) || ((int)pv > 255)) {
		return false;
	}
	int r, c;
	if(Pixels.empty()) {
		return false;
	}
	c = Pixels[0].size();
	r = Pixels.size();
	vector< vector<int> > nPixels(r+(w*2), vector<int>(c+(w*2)));
	for(int i = 0; i < (int)nPixels.size(); i++){
		for(int z = 0; z < (int)nPixels[0].size(); z++) {//Fills out the new vector with all pads
			nPixels[i][z] = pv;
		}
	}
	for(int i = 0; i < r; i++) {
		for(int z = 0; z < c; z++) {
			nPixels[i+w][z+w] = Pixels[i][z];//Fills out the new vector with the picture in the middle
		}
	}
	r = r + (w*2);
	c = c + (w*2);
	Pixels.resize(r);
	for(int i = 0; i < r; i++) {
		Pixels[i].resize(c);
	}
	for(int i = 0; i < r; i++) {
		for(int z = 0; z < c; z++) {
			Pixels[i][z] = nPixels[i][z];//Fills out the pixel vector
		}
	}


	return true;
}
bool Pgm::Panel(size_t r, size_t c) {
	if(((int)r <= 0) || ((int)c <= 0)) {
		return false;
	}
	int rn, cn;
	if(Pixels.empty()) {
		return false;
	}	
	cn = Pixels[0].size();
	rn = Pixels.size();
	vector< vector<int> > nPixels(rn * r, vector<int>(cn * c));
	for(int i = 0; i < (int)nPixels.size(); i++){
		for(int z = 0; z <(int)nPixels[0].size(); z++) {
			nPixels[i][z] = Pixels[i%rn][z%cn];//Fills out the large vector with repeated images by using the mod
		}
	}
	int last = rn * r;
	int first = c * cn;
	Pixels.resize(last);
	for(int i = 0; i < (last); i++) {
		Pixels[i].resize(first);
	}
	for(int i = 0; i < (last); i++) {
		for(int z = 0; z < (first); z++) {
			Pixels[i][z] = nPixels[i][z];//Fills the new resized pixel vector
		}
	}


	return true;
}
bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols) {
	if(((int)r < 0) ||  ((int)c < 0) || ((int)rows <= 0) || ((int)cols <= 0)) {
		return false;
	}
	if((cols+c) > Pixels[0].size()) {
		return false;
	}
	if((rows+r) > Pixels.size()) {//Error checking
		return false;
	}
	vector< vector<int> > nPixels(rows, vector<int>(cols));
	for(int i = 0; i < (int)rows; i++) {
		for(int z = 0; z < (int)cols; z++) {
			nPixels[i][z] = Pixels[r+i][c+z];//Fills out the temp vector with the crop 
		}
	}
		
	Pixels.resize(rows);
	for(int i = 0; i < (int)rows; i++) {
		Pixels[i].resize(cols);
	}
	for(int i = 0; i < (int)(rows); i++) {
		for(int z = 0; z < (int)(cols); z++) {
			Pixels[i][z] = nPixels[i][z];//fills out the new resized vector 
		}
	}
	return true;
}

