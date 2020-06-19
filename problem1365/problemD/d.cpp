#include <iostream>
#include <vector>
#include<memory>
#include <utility>
#include <array>
#include <set>
#include <deque>
#include <algorithm>

struct Pos{
	int first;
	int second;
};


char* handleTable(Pos* goodPersonLocation, int& row, int& column, bool& TrueOrFalse, int& size){

	std::array<std::pair<int, int>, 2> possiblePos = { 
		std::make_pair(0, -1),
		std::make_pair(-1, 0),
	};

	auto table = new char[row*column+1];
	for(int yter=0; yter != row; ++yter){
		for(int xter=0; xter != column; ++xter){
			std::cin >> *(table + (yter*column) + xter);
			if(TrueOrFalse){
				std::array<int, 2> remainPossiblePos{0, 1};
				if(xter == 0){
					remainPossiblePos[1] = 2;
				} 

				if(yter == 0){
					remainPossiblePos[0] = 2;
				}

				switch(*(table + (yter*column) + xter)){
					case 'B':
						for(int pos : remainPossiblePos){
							if(pos != 2){
								int posX = xter + possiblePos[pos].first; 
								int posY = yter + possiblePos[pos].second;
								switch (*(table + (posY*column) + posX)){
									case '.':
										*(table + (posY*column) + posX) = '#'; 
										break;
									case 'G':
										TrueOrFalse = false;
										break;
								}
							} 					
						}
						break;
					case 'G':
						for(const auto& pos: remainPossiblePos){
							if(pos != 2){
								if(*(table + ((yter + possiblePos[pos].second)*column) + (xter + possiblePos[pos].first)) == 'B'){
									TrueOrFalse = false;
								}
							}
						}
						goodPersonLocation[size++] = { .first = xter, .second = yter };
						break;
					case '.':
						for(const auto& pos: remainPossiblePos){
							if(pos != 2){
								if(*(table + ((yter + possiblePos[pos].second)*column) + (xter + possiblePos[pos].first)) == 'B'){
									*(table + (yter*column) + xter) = '#';
								}
								break;
							}
						}

				}
			}
		}
	}

	return table;

}


void bruteForceTheArray(char* table, Pos* goodPersonLocation, int& row, int& column, bool& TrueOrFalse, int& size){

	if(size == 0){
		TrueOrFalse = true;
		return;
	}

	auto remainPossiblePos = new bool[column+1] {false};

	for(auto location = goodPersonLocation; (location != goodPersonLocation + size) && TrueOrFalse; ++location){
		int posX = location->first;
		int posY = location->second;

		if(*(table + (posY * column) + posX) == '.')
			continue;
		else{
			while(posY != row){

				for(int iter=0; table[(posY*column) + (posX+iter)] != '#' && (posX + iter) != column; ++iter){
					if ( remainPossiblePos[posX + iter ] == false ) remainPossiblePos[posX + iter] = true; 
					else break;
				}

				for(int iter=0; table[(posY*column) + (posX+iter)] != '#' && (posX + iter) != -1; --iter){
					if ( remainPossiblePos[posX + iter ] == false ) remainPossiblePos[posX + iter] = true; 
					else break;
				}

				while(posY != (row -1)){
					for(auto iter = 0; iter != column; ++iter){
						if(remainPossiblePos[iter]){
							switch (*(table + ((posY + 1) * column) + iter)){
								case 'G':
									*(table + ((posY + 1) * column) + iter) = '.';
									break;
								case '#':
									remainPossiblePos[iter] = false;
									break;
							}
						}
					}
				}
				++posY;
			}
			TrueOrFalse = (remainPossiblePos[column - 1] == true) ? true : false;
		}

	}
}

int main(int argc, const char* argv[]){
	int test; // number of text case
	std::cin >> test;

	for(int iter=0; iter != test; ++iter) {
		int row;
		int column;
		std::cin >> row >> column;

		bool TrueOrFalse = true;
		auto size = 0;
		// std::vector<std::pair<int, int>> goodPersonLocation;
		auto goodPersonLocation = new Pos[row*column];
		auto table = handleTable(goodPersonLocation, row, column, TrueOrFalse, size);
		bruteForceTheArray(table, goodPersonLocation, row, column, TrueOrFalse, size);
		std::cout << (TrueOrFalse ? "Yes" : "No" ) << std::endl;
		delete [] table;
		delete [] goodPersonLocation;
	}
}
