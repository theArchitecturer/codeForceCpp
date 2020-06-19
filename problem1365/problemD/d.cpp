#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <array>
#include <set>
#include <deque>
#include <algorithm>

char *handleTable(int *goodPersonLocation, int &row, int &column, bool &TrueOrFalse, int &size)
{

    std::array<int, 2> possiblePos = {-column, -1};

    auto table = new char[row * column + 1];
    for (int yter = 0; yter != row; ++yter)
    {
        for (int xter = 0; xter != column; ++xter)
        {
            auto normalPosition = yter * column + xter;
            std::cin >> *(table + normalPosition);
            if (TrueOrFalse)
            {
                std::array<int, 2> remainPossiblePos{0, 1};
                if (xter == 0)
                {
                    remainPossiblePos[0] = 2;
                }

                if (yter == 0)
                {
                    remainPossiblePos[1] = 2;
                }

                switch (*(table + (yter * column) + xter))
                {
                    case 'B':
                        for (int pos : remainPossiblePos)
                        {
                            if (pos != 2)
                            {
                                auto aroundPosition = normalPosition + possiblePos[pos];
                                switch (*(table + aroundPosition))
                                {
                                    case '.':
                                        *(table + aroundPosition) = '#';
                                        break;
                                    case 'G':
                                        TrueOrFalse = false;
                                        break;
                                }
                            }
                        }
                        break;
                    case 'G':
                        for (const auto &pos : remainPossiblePos)
                        {
                            if (pos != 2)
                            {
                                auto aroundPosition = normalPosition + possiblePos[pos];
                                if (*(table + aroundPosition) == 'B')
                                {
                                    TrueOrFalse = false;
                                }
                            }
                        }
                        goodPersonLocation[size++] = {normalPosition};
                        break;
                    case '.':
                        for (const auto &pos : remainPossiblePos)
                        {
                            if (pos != 2)
                            {
                                auto aroundPosition = normalPosition + possiblePos[pos];
                                if (*(table + aroundPosition) == 'B')
                                {
                                    *(table + (yter * column) + xter) = '#';
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

void bruteForceTheArray(char *table, int *goodPersonLocation, int &row, int &column, bool &TrueOrFalse, int &size)
{

    if (size == 0)
    {
        TrueOrFalse = true;
        return;
    }

    auto remainPossiblePos = new bool[column + 1]{false};

    for (auto yter = 0; yter != size && TrueOrFalse; ++yter)
    {
        auto location = goodPersonLocation[yter];

        if (*(table + location) == '.')
            continue;
        else
        {
            while (location < (row*column))
            {
                auto posX = location % column;
                auto beginRowPosition = location - posX;

                bool TrueInPos=false;
                for(int iter=0, sharp_before=0; iter<column; ++iter){
                    if(remainPossiblePos[iter] == true) TrueInPos = true;
                    if(*(table + beginRowPosition + iter) =='#' || iter == (column - 1)){
                        if (TrueInPos) {
                            for(;sharp_before < iter; ++sharp_before){
                                remainPossiblePos[sharp_before] = true;
                            }
                            sharp_before = ++iter;
                        }else{
                            sharp_before = ++iter;
                        }
                    }
                }

                while (location < (row - 1)*column)
                {
                    for (auto iter = 0; iter != column; ++iter)
                    {
                        if (remainPossiblePos[iter])
                        {
                            switch (*(table + location + column + iter))
                            {
                                case 'G':
                                    *(table + location + column + iter) = '.';
                                    break;
                                case '#':
                                    remainPossiblePos[iter] = false;
                                    break;
                            }
                        }
                    }
                }
                location += column;
            }
            TrueOrFalse = (remainPossiblePos[column - 1] == true) ? true : false;
        }
    }
}

int main(int argc, const char *argv[])
{
    int test; // number of text case
    std::cin >> test;

    for (int iter = 0; iter != test; ++iter)
    {
        int row;
        int column;
        std::cin >> row >> column;

        bool TrueOrFalse = true;
        auto size = 0;
        auto goodPersonLocation = new int[row * column];
        auto table = handleTable(goodPersonLocation, row, column, TrueOrFalse, size);
        bruteForceTheArray(table, goodPersonLocation, row, column, TrueOrFalse, size);
        std::cout << (TrueOrFalse ? "Yes" : "No") << std::endl;
        delete[] table;
        delete[] goodPersonLocation;
    }
}
