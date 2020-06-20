#include <iostream>

template<typename T>
void printArray(T* arrayToPrint, int& row, int& column)
{
    // for(int iter=0; iter < row*column; ++iter)
    // {
    //     std::cout << *(arrayToPrint + iter);
    // }
    for (auto iter = 0; iter < row; ++iter) {
        for (auto yter = 0; yter < column; ++yter) {
            std::cout << *(arrayToPrint + iter*yter);
        }
        std::cout << std::endl; 
    }
    std::cout << std::endl;
};


