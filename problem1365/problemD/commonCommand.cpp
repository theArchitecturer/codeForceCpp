#include <iostream>

template<typename T>
void printArray(T* arrayToPrint, int& row, int& column)
{
    for(int iter=0; iter < row*column; ++iter)
    {
        std::cout << *(arrayToPrint + iter);
    }
    std::cout << std::endl;
}
