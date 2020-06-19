#include <iostream>
#include <vector>
#include<memory>
#include <utility>
#include <array>
#include <set>
#include <deque>
#include <algorithm>

void printTable(const char* table, int& row, int& column){

	for(int yter=0; yter != row; ++yter){
		for(int xter=0; xter != column; ++xter){
			std::cout << *(table + (yter*column) + xter);
		}
		std::cout << std::endl;
	}

}

char* handleTable(std::deque<std::pair<int, int>>& goodPersonLocation, int& row, int& column, bool& TrueOrFalse){

	std::array<std::pair<int, int>, 2> possiblePos = { 
		std::make_pair(0, -1),
		std::make_pair(-1, 0),
	};

	auto table = new char[row*column+1];
	for(int yter=0; yter != row; ++yter){
		for(int xter=0; xter != column; ++xter){
			std::cin >> *(table + (yter*column) + xter);
			if(TrueOrFalse){
				std::array<int, 2> remainPossiblePos;
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
								if(*(table + (posY*column) + posX) == '.'){ *(table + (posY*column) + posX) = '#'; }else if (*(table + (posY*column) + posX) == 'G'){ TrueOrFalse = false; }
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
						goodPersonLocation.push_back(std::make_pair(xter, yter));
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
	printTable(  table,  row,  column);

	return table;

}


void bruteForceTheArray(char* table, std::deque<std::pair<int, int>>& goodPersonLocation, int& row, int& column, bool& TrueOrFalse){

	if(goodPersonLocation.size() == 0){
		TrueOrFalse = true;
		return;
	}

	std::unique_ptr<bool[]> remainPossiblePos(new bool[column]{false});

	for(auto location = goodPersonLocation.cbegin(); (location != goodPersonLocation.cend()) && TrueOrFalse; ++location){
		int posX = location->first;
		int posY = location->second;

		if(*(table + (posY * column) + posX) == '.')
			continue;
		else{
			while(posY != row){

				for(int iter=1; *(table + (posY * column) + posX + iter) != '#' && ((posX + iter) != column); ++iter){
					if(remainPossiblePos[posX + iter - 1] != true) remainPossiblePos[posX + iter - 1] = true; else break;
				}

				for(int iter=-1; *(table + (posY * column) + posX + iter) != '#' && ((posX + iter) != -1); --iter){
					if(remainPossiblePos[posX + iter - 1] != true) remainPossiblePos[posX + iter - 1] = true; else break;
				}

				while(posY != (row -1)){
					for(auto iter = 0; iter != column; ++iter){
					auto position = remainPossiblePos[iter];
						switch (*(table + ((posY + 1) * column) + position)){
							case 'G':
								*(table + ((posY + 1) * column) + position) = '.';
								break;
							case '#':
								position = false;
								break;
						}
					}
				}
				++posY;
			}
			TrueOrFalse = (remainPossiblePos[column - 1] == (column - 1)) ? true : false;
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
		std::deque<std::pair<int, int>> goodPersonLocation;
		auto table = handleTable(goodPersonLocation, row, column, TrueOrFalse);
		bruteForceTheArray(table, goodPersonLocation, row, column, TrueOrFalse);
		std::cout << (TrueOrFalse ? "Yes" : "No" ) << std::endl;
		delete [] table;
	}
}
