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

	std::vector<std::pair<int, int>> possiblePos = { 
		std::make_pair(1, 0),
		std::make_pair(0, -1),
		std::make_pair(-1, 0),
	};
	std::array<int, 3> remainPossiblePos{ 0, 1, 2 };

	auto table = new char[row*column+1];
	for(int yter=0; yter != row; ++yter){
		for(int xter=0; xter != column; ++xter){
			std::cin >> *(table + (yter*column) + xter);
			if(xter == 0){
				remainPossiblePos[2] = 3;
			} 
			if (xter == (row - 1)){
				remainPossiblePos[0] = 3;
			}
			if(yter == 0){
				remainPossiblePos[1] = 3;
			}
			for(const auto& pos : remainPossiblePos){
				std::cout << pos;
			}
			std::cout << std::endl;

			switch(*(table + (yter*column) + xter)){
				case 'B':
					for(int pos : remainPossiblePos){
						if(pos != 3){
							int posX = xter + possiblePos[pos].first; 
							int posY = yter + possiblePos[pos].second;
							/* std::cout << "deref in B0" << posX << posY << std::endl; */
							if(*(table + (posY*column) + posX) == '.'){
								*(table + (posY*column) + posX) = '#';
							/* std::cout << "deref in B1" << std::endl; */
							}else if (*(table + (posY*column) + posX) == 'G'){
								TrueOrFalse = false;
							/* std::cout << "deref in B2" << std::endl; */
								return table;
							}
						} 					
					}
					break;
				case 'G':
					for(const auto& pos: remainPossiblePos){
						if(pos != 3){
							if(*(table + ((yter + possiblePos[pos].second)*column) + (xter + possiblePos[pos].first)) == 'B'){
								TrueOrFalse = false;
								return table;
							}
							/* std::cout << "deref in G" << std::endl; */
						}
					}
					goodPersonLocation.push_back(std::make_pair(xter, yter));
					break;
				case '.':
					if(yter != 0){
						if(*(table + ((yter - 1)*column) + xter) == 'B')
							*(table + (yter*column) + xter) = '#';
					}
					break;
			}
		}
	}

	if(*(table + row*column) == 'B'){
		TrueOrFalse = false;
		return table;
	}
	printTable(table, row, column);

	return table;

}


void bruteForceTheArray(char* table, std::deque<std::pair<int, int>>& goodPersonLocation, int& row, int& column, bool& TrueOrFalse){

	if((goodPersonLocation.size() == 0) && ((table + row*column) != nullptr) && (*(table + row*column) != 'B')){
		TrueOrFalse = true;
		return;
	}

	std::set<int> remainPossiblePos;
	while((!goodPersonLocation.empty()) && TrueOrFalse){
		auto location = goodPersonLocation.begin();
		int posX = location->first;
		int posY = location->second;

		if(*(table + (posY * column) + posX) == '.')
			goodPersonLocation.pop_front();
		else{
			while(posY != row){

				for(int iter=0; *(table + (posY * column) + posX + iter) != '#' && ((posX + iter) != column); ++iter){
					remainPossiblePos.insert(posX + iter);
				}

				for(int iter=0; *(table + (posY * column) + posX + iter) != '#' && ((posX + iter) != -1); --iter){
					remainPossiblePos.insert(posX + iter);
				}

				while(posY != (row -1)){
					for(auto& position: remainPossiblePos){
						switch (*(table + ((posY + 1) * column) + position)){
							case 'G':
								*(table + ((posY + 1) * column) + position) = '.';
								break;
							case '#':
								remainPossiblePos.erase(position);
						}
					}
				}
				++posY;
			}
			TrueOrFalse = (std::find(remainPossiblePos.cbegin(), remainPossiblePos.cend(), (column - 1)) != remainPossiblePos.cend()) ? true : false;
			if(TrueOrFalse)
				break;
			goodPersonLocation.pop_front();
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
