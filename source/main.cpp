#include <iostream>
#include <vector>

#include "VectorMaker.h"
#include "bst.h"

void inline PHL_g(bool bLineBefore = true, bool bLineAfter = true)
{
    if(bLineBefore)
        printf("\n");

    printf("=========================================================================");

    if(bLineAfter)
        printf("\n");
}

int main()
{
    std::vector<int> testVect;
    char sArrSize[10];
    printf("\nArray Size:");
    scanf("%s",sArrSize);

    int iArrSize = atoi(sArrSize);

    VectorMaker::CreateVector(testVect, iArrSize, 0, 100);

    VectorMaker::PrintVector(testVect, "Test");

    BST tree("Test");

    tree.Build(testVect);

    tree.PrintTreeDetails();

    tree.Print(BST::PrintType::Ascending);

    PHL_g();

    tree.Print(BST::PrintType::Descending);

    PHL_g();

    tree.Print(BST::PrintType::Tree);

    printf("\nDone!\n");
    

    return 0;
}