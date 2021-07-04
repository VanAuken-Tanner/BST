#pragma once
#include <iostream>
#include <vector>
#include <string>

class VectorMaker
{
public:
    static void CreateVector(std::vector<int> &vOut, int iVecSize, int iMin, int iMax);
    static void PrintVector(std::vector<int> vPrint, std::string sName = "");
};