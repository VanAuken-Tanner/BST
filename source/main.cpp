#include <iostream>
#include <vector>

#include "VectorMaker.h"
#include "bst.h"

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

    // tree.Print(BST::PrintType::Ascending);

    // printf("\n=======================================================\n");

    // tree.Print(BST::PrintType::Descending);

    // printf("\n=======================================================\n");

    tree.Print(BST::PrintType::Tree);

    printf("\nDone!\n");
    

    return 0;
}