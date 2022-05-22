#include "VectorMaker.h"
#include <random>
#include <ctime>

void VectorMaker::CreateVector(std::vector<int> &out, int iVecSize, int iMin, int iMax)
{
    std::mt19937 generator;
    generator.seed(std::time(0));
    std::uniform_int_distribution<int> distribution(iMin,iMax);
    if(iVecSize < 1)
        iVecSize = distribution(generator);

    printf("Creating Vector of size %d", iVecSize);

    for(int i = 0; i < iVecSize; i++)
    {
        out.push_back(distribution(generator));
    }
}

void VectorMaker::PrintVector(std::vector<int> vPrint, std::string sName)
{
    printf("\n========================================\n");
    if(sName.size() > 0)
        printf("%s:(size:%li)\n", sName.c_str(), vPrint.size());

    for(int i = 0; i < vPrint.size(); i++)
    {
        printf("|%d|",vPrint.at(i));
    }
    printf("\n========================================\n");
}