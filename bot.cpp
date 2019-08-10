#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS;  // global variables
int COLS;
int NUM;
int chops = 0;
int walks = 0;
int walks2 = 0;
bool NotEnoughLumber = true;
int builds = 0;
int colums = 0;
vector<int> dwarfcount = {0};
int lastDwarf = 0;
vector<vector<bool>> spots;
int is = 0, js = 0;

int fill(vector<vector<bool>>& values){
	for(int i =0; i< ROWS; i++){
		vector<bool> spot;
		for(int j = 0; j < COLS; j++){
			spot.push_back(false);
		}
		values.push_back(spot);
	}
	return 0;
}

int reset(vector<vector<bool>>& values){
	for(int i =0; i< ROWS; i++){
		for(int j = 0; j < COLS; j++){
			values[i][j] = false;
		}
	}
	return 0;
}

/* onStart: 
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do 
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message

  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;
  fill(spots);
}

bool isNextToATree(Dwarf & dwarf, int r, int c){
	if(dwarf.look(r, c) == EMPTY){
		if ( (	((dwarf.look(r + 1, c) == PINE_TREE) || (dwarf.look(r + 1, c) == APPLE_TREE)) && (dwarf.look(r + 2, c) != DWARF)  && (dwarf.look(r + 1, c + 1) != DWARF)  && (dwarf.look(r + 1, c - 1) != DWARF)	) ||
		(	((dwarf.look(r -1,  c) == PINE_TREE) || (dwarf.look(r - 1, c) == APPLE_TREE)) && (dwarf.look(r - 2, c) != DWARF)  && (dwarf.look(r - 1, c - 1) != DWARF)  && (dwarf.look(r - 1, c + 1) != DWARF)) ||
		(	((dwarf.look(r, c + 1) == PINE_TREE) || (dwarf.look(r, c + 1) == APPLE_TREE)) && (dwarf.look(r, c + 2) != DWARF)  && (dwarf.look(r + 1, c  +1) != DWARF)  && (dwarf.look(r - 1, c + 1) != DWARF)) ||
		(	((dwarf.look(r, c - 1) == PINE_TREE) || (dwarf.look(r, c - 1) == APPLE_TREE)) && (dwarf.look(r - 1, c - 1) != DWARF)  && (dwarf.look(r, c - 2) != DWARF)  && (dwarf.look(r + 1, c - 1) != DWARF)) ){
			return true;
		}
	}
	return false;
}

bool isNextToAPick(Dwarf & dwarf, int r, int c){
	if(dwarf.look(r, c) == EMPTY){
		if ( (	((dwarf.look(r + 1, c) == PUMPKIN) || (dwarf.look(r + 1, c) == APPLE_TREE)) && (dwarf.look(r + 2, c) != DWARF)  && (dwarf.look(r + 1, c + 1) != DWARF)  && (dwarf.look(r + 1, c - 1) != DWARF)	) ||
		(	((dwarf.look(r -1,  c) == PUMPKIN) || (dwarf.look(r - 1, c) == APPLE_TREE)) && (dwarf.look(r - 2, c) != DWARF)  && (dwarf.look(r - 1, c - 1) != DWARF)  && (dwarf.look(r - 1, c + 1) != DWARF)) ||
		(	((dwarf.look(r, c + 1) == PUMPKIN) || (dwarf.look(r, c + 1) == APPLE_TREE)) && (dwarf.look(r, c + 2) != DWARF)  && (dwarf.look(r + 1, c  +1) != DWARF)  && (dwarf.look(r - 1, c + 1) != DWARF)) ||
		(	((dwarf.look(r, c - 1) == PUMPKIN) || (dwarf.look(r, c - 1) == APPLE_TREE)) && (dwarf.look(r - 1, c - 1) != DWARF)  && (dwarf.look(r, c - 2) != DWARF)  && (dwarf.look(r + 1, c - 1) != DWARF)) ){
			return true;
		}
	}
		return false;
	
}

bool NotLinedUp(Dwarf & dwarf, int r){
	int dwarves = 0;
	for(int i = 0; i < 6; i++){
		if (dwarf.look(r, i) == DWARF){
			dwarves++;
		}
	}
	if(dwarves == 6){
		return false;
	}
	else{ 
		return true;
	}
}

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
	// Get current position of the dwarf
	int r = dwarf.row();
	int c = dwarf.col();
	int rr = 0, cc = 0, proximity, newproximity = 1000;
	if(dwarf.name() > dwarfcount[dwarfcount.size() - 1]){
		dwarfcount.push_back(dwarf.name() );
		lastDwarf = dwarf.name();
		log<< lastDwarf<<endl;
	}
	if( (6 < hours) && (hours < 15) && (day ==1) ){
		if(walks <= lastDwarf){
			walks++;
			for (int i = 0; i < ROWS; i++){
				for (int j = 0; j < i; j++){
					if(dwarf.look(i, j) == EMPTY){
						dwarf.start_walk(i, j);
					}
				}
			}
		}
		if ((dwarf.look(r, c+1) == PINE_TREE) || (dwarf.look(r, c+1) == APPLE_TREE)|| (dwarf.look(r, c+1) == FENCE)) {
			log << "Found a tree -- chop" <<" "<<r<<" "<<c+1<<dwarf.name()<< endl;
			dwarf.start_chop(EAST);
			chops++;
			return;
		}
		if((dwarf.look(r, c-1) == PINE_TREE) || (dwarf.look(r, c-1) == APPLE_TREE)|| (dwarf.look(r, c-1) == FENCE)){
			 log << "Found a tree -- chop" << " "<<r<<" "<<c-1<<dwarf.name()<< endl;
			dwarf.start_chop(WEST);
			chops++;
			return;
		}
		if((dwarf.look(r-1, c) == PINE_TREE) || (dwarf.look(r-1, c) == APPLE_TREE)|| (dwarf.look(r - 1, c) == FENCE)){
			 log << "Found a tree -- chop" <<" "<< r-1<<" "<<c<<dwarf.name()<< endl;
			dwarf.start_chop(NORTH);
			chops++;
			return;
		}
		if((dwarf.look(r+1, c) == PINE_TREE) || (dwarf.look(r+1, c) == APPLE_TREE)|| (dwarf.look(r + 1, c) == FENCE)){
			 log << "Found a tree -- chop" <<" "<< r+1<<" "<<c<< dwarf.name()<<endl;
			dwarf.start_chop(SOUTH);
			chops++;
			return;
		}
		else {
			for (int i = 0; i < ROWS; i++){
				for (int j = 0; j <= i; j++){
					if( ((dwarf.look(i, j) == PINE_TREE) || (dwarf.look(i, j) == APPLE_TREE)) && (spots[i][j] == false) ){
						proximity = pow((i + j), 2) - pow((r+c), 2);
						proximity = abs(proximity);
						if(proximity < newproximity){
							newproximity = proximity;
							rr = i;
							cc = j;
						}
					}
				}
			}
			spots[rr][cc] = true;
			if(isNextToATree(dwarf, rr + 1, cc) == true){
				rr = rr+1;
				log << "Walk to " << rr << " " << cc << " "<<dwarf.name()<<" "<<endl;
				dwarf.start_walk(rr, cc);
				return;
			}
			if(isNextToATree(dwarf, rr - 1, cc) == true){
				rr = rr-1;
				log << "Walk to " << rr << " " << cc << " "<<dwarf.name()<<" "<<endl;
				dwarf.start_walk(rr, cc);
				return;
			}
			if(isNextToATree(dwarf, rr, cc+1) == true){
				cc = cc+1;
				log << "Walk to " << rr << " " << cc <<" "<<dwarf.name()<<" "<< endl;
				dwarf.start_walk(rr, cc);
				return;
			}
			if(isNextToATree(dwarf, rr, cc -1) == true){
				cc = cc-1;
				log << "Walk to " << rr << " " << cc << " "<<dwarf.name()<<" "<<endl;
				dwarf.start_walk(rr, cc);
				return;
			}
		}
	}
	/*if(day == 7){
		for(int i = 0; i < ROWS; i++){
			if( (dwarf.row() == (i + 1)) && (	dwarf.look(i, dwarf.col()) == EMPTY) ){
				dwarf.start_build(NORTH);
				return;
			}
			if(dwarf.look(dwarf.row() - 1, dwarf.col()) == FENCE){
				dwarf.start_walk(dwarf.row() + 1, dwarf.col());
				log << "Walk to " << dwarf.row() + 1 << " " << dwarf.col() << endl;
				return;
			}
			if( (dwarf.look(i, dwarf.name()) == EMPTY) && NotLinedUp(dwarf, i + 1) ){
				dwarf.start_walk(i + 1, dwarf.name());
				log << "Walk to " << i+1 << " " << dwarf.name() << endl;
				colums++;
				return;
			}
		}
	}*/
	if( (day != 1) && (6 <= hours) && (hours < 15) ){
		if (dwarf.look(r, c+1) == FENCE){
			log << "Found a fence -- chop" <<" "<<r<<" "<<c+1<<dwarf.name()<< endl;
			dwarf.start_chop(EAST);
			chops++;
			return;
		}
		if(dwarf.look(r, c-1) == FENCE){
			 log << "Found a fence -- chop" << " "<<r<<" "<<c-1<<dwarf.name()<< endl;
			dwarf.start_chop(WEST);
			chops++;
			return;
		}
		if(dwarf.look(r - 1, c) == FENCE){
			 log << "Found a fence -- chop" <<" "<< r-1<<" "<<c<<dwarf.name()<< endl;
			dwarf.start_chop(NORTH);
			chops++;
			return;
		}
		if(dwarf.look(r + 1, c) == FENCE){
			 log << "Found a fence -- chop" <<" "<< r+1<<" "<<c<< dwarf.name()<<endl;
			dwarf.start_chop(SOUTH);
			chops++;
			return;
		}
		if ((dwarf.look(r, c+1) == PUMPKIN) || (dwarf.look(r, c+1) == APPLE_TREE)) {
			log << "Found a pick -- chop" <<" "<<r<<" "<<c+1<<dwarf.name()<< endl;
			dwarf.start_pick(EAST);
			chops++;
			return;
		}
		if((dwarf.look(r, c-1) == PUMPKIN) || (dwarf.look(r, c-1) == APPLE_TREE)){
			 log << "Found a pick -- chop" << " "<<r<<" "<<c-1<<dwarf.name()<< endl;
			dwarf.start_pick(WEST);
			chops++;
			return;
		}
		if((dwarf.look(r-1, c) == PUMPKIN) || (dwarf.look(r-1, c) == APPLE_TREE)){
			 log << "Found a pick -- chop" <<" "<< r-1<<" "<<c<<dwarf.name()<< endl;
			dwarf.start_pick(NORTH);
			chops++;
			return;
		}
		if((dwarf.look(r+1, c) == PUMPKIN) || (dwarf.look(r+1, c) == APPLE_TREE)){
			 log << "Found a pick -- chop" <<" "<< r+1<<" "<<c<< dwarf.name()<<endl;
			dwarf.start_pick(SOUTH);
			chops++;
			return;
		}
		else {
			for (int i = 0; i < ROWS; i++){
				for (int j = 0; j <= i; j++){
					if( ((dwarf.look(i, j) == PUMPKIN) || (dwarf.look(i, j) == APPLE_TREE))  ){
						proximity = pow((i + j), 2) - pow((r+c), 2);
						proximity = abs(proximity);
						if(proximity < newproximity){
							newproximity = proximity;
							rr = i;
							cc = j;
						}
					}
				}
			}
			spots[rr][cc] = true;
			if(isNextToAPick(dwarf, rr + 1, cc) == true){
				rr = rr+1;
				log << "Walk to " << rr << " " << cc << " "<<dwarf.name()<<" "<<endl;
				dwarf.start_walk(rr, cc);
				return;
			}
			if(isNextToAPick(dwarf, rr - 1, cc) == true){
				rr = rr-1;
				log << "Walk to " << rr << " " << cc << " "<<dwarf.name()<<" "<<endl;
				dwarf.start_walk(rr, cc);
				return;
			}
			if(isNextToAPick(dwarf, rr, cc+1) == true){
				cc = cc+1;
				log << "Walk to " << rr << " " << cc <<" "<<dwarf.name()<<" "<< endl;
				dwarf.start_walk(rr, cc);
				return;
			}
			if(isNextToAPick(dwarf, rr, cc -1) == true){
				cc = cc-1;
				log << "Walk to " << rr << " " << cc << " "<<dwarf.name()<<" "<<endl;
				dwarf.start_walk(rr, cc);
				return;
			}
		}
	}
	if( (15 <= hours) && (hours <= 21)  ){
		if(    dwarf.look(dwarf.row() + 1, dwarf.col())==EMPTY  ){
			dwarf.start_build(SOUTH);
			log<< "Building South "<< builds++<<" "<<dwarf.name()<<" "<<lastDwarf<< endl;
		}
		if( dwarf.look(dwarf.row(), dwarf.col() + 1) == EMPTY ){
			dwarf.start_build(EAST);
			log<< "Building East "<<builds++<<" "<<dwarf.name()<<" "<<lastDwarf<< endl;
		}
		if(    dwarf.look(dwarf.row() - 1, dwarf.col())==EMPTY  ){
			dwarf.start_build(NORTH);
			log<< "Building North "<< builds++<<" "<<dwarf.name()<<" "<<lastDwarf<< endl;
		}
		if( dwarf.look(dwarf.row(), dwarf.col() - 1) == EMPTY ){
			dwarf.start_build(WEST);
			log<< "Building West "<<builds++<<" "<<dwarf.name()<<" "<<lastDwarf<< endl;
		}
		reset(spots);
	}
}