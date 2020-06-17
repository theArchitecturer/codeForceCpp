#include <iostream>
#include <algorithm>


int findTheMostOccurence(int distanse_array[], int& sizeOfArray){
	int max=0;
	int count=1;
	for(int* iter = distanse_array; iter != (distanse_array + sizeOfArray); ++iter){
		if(iter == (distanse_array+sizeOfArray)){
			if(*iter == *(iter-1)){
				++count;
			}	
		}else{
			if(*iter == *(iter+1)){
				++count;
			}else{
				*iter = *(iter+1);
				max = (count>max) ? count : max;
				count = 1;
			}
		}

	}
	return max;
}

int main(int argc, const char* argv[]){

	int sizeOfArray;
	std::cin >> sizeOfArray;

	auto a_array = new int[sizeOfArray+1];
	for(int yter=0; yter < sizeOfArray; ++yter){
		int inputInt;
		std::cin >> inputInt;
		*(a_array + inputInt - 1)  = yter;
	}

	for(int yter=0; yter < sizeOfArray; ++yter){
		int inputInt;
		std::cin >> inputInt;
		*(a_array + inputInt - 1) = ((*(a_array + inputInt - 1) -= yter) < 0) ? *(a_array + inputInt - 1) + sizeOfArray : *(a_array + inputInt - 1);
	}

	std::sort(a_array, a_array+sizeOfArray);
	int max = findTheMostOccurence(a_array, sizeOfArray);
	delete [] a_array;
	std::cout << max << std::endl;

}
