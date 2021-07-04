#include "bst.h"
#include <iostream>

bool debug_g = false;
bool debugB_g = false;

//debug copy pasta
// if(debug_g)
//         printf("\n");

BST::BST()
{
    m_sName = "No Name";
    m_root = nullptr;
    m_iNumNodes = 0;
}

BST::BST(std::string sName)
{
    m_sName = sName;
    m_root = nullptr;
    m_iNumNodes = 0;
}

BST::~BST()
{

}

void BST::Build(std::vector<int> input)
{
    for(int i = 0; i < input.size(); i++)
    {
        Insert(input.at(i));
    }
}

void BST::Print(PrintType type)
{
    if(debug_g)
        printf("\nPrinting Tree... num nodes(%d)", m_iNumNodes);

    printf("\n");

    if(type == Tree)
        PrintTreeLikeTree();
    else
        PrintNodeRecur(m_root, type);
}

void BST::PrintNodeRecur(node* toPrint, PrintType type)
{
    if (toPrint == nullptr)
        return;

    node* first;
    node* second;

    if(type == Ascending)
    {
        first = toPrint->left;
        second = toPrint->right;
    }
    else
    {
        first = toPrint->right;
        second = toPrint->left;
    }

    if(first != nullptr)
        PrintNodeRecur(first, type);

    for(int i = 1; i < toPrint->iCount; i++)
    {
        printf("|%d|", toPrint->iVal);
    }

    if(second != nullptr)
        PrintNodeRecur(second, type);
}

BST::node* BST::CreateNode(int iVal, node* pParent)
{
    if(debug_g && pParent == nullptr)
        printf("\nCreating root node... val(%d)",iVal);
    else if(debug_g)
        printf("\nCreating node... val(%d) parent val(%d)",iVal, pParent->iVal);

    node* newNode = new node;
    newNode->iVal = iVal;
    newNode->parent = pParent;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->iSize = 1;
    newNode->iHeight = 0;
    newNode->iCount = 1;

    m_iNumNodes++;

    if(debug_g)
        printf("\nNumber of Nodes: %d",m_iNumNodes);

    return newNode;
}

void BST::Insert(int iVal)
{
    if(debug_g)
        printf("\nInserting...(%d)",iVal);

    if(m_root == nullptr)
    {
        m_root = CreateNode(iVal,nullptr);
        return;
    }

    node* iter = m_root;
    while(iter != nullptr)
    {
        //look at current node
        //if less than look at left node
        //if more than look at right node
        //if target node is null, insert. 
        //else move to target node & loop
        if(iVal < iter->iVal)
        {
            if(debug_g)
                printf("\nValue less than current node. %d < %d", iVal, iter->iVal);

            if(iter->left)
            {
                iter = iter->left;
            }
            else
            {
                iter->left = CreateNode(iVal, iter);
                UpdateSize(iter);
                UpdateHeight(iter);
            }
        }
        else if (iVal > iter->iVal)
        {
            if(debug_g)
                printf("\nValue greater than current node. %d > %d", iVal, iter->iVal);

            if(iter->right)
            {
                iter = iter->right;
            }
            else
            {
                iter->right = CreateNode(iVal, iter);
                UpdateSize(iter);
                UpdateHeight(iter);
            }
        }
        else if (iter->iVal == iVal)
        {
            if(debug_g)
                printf("\nValue equal to current node. %d = %d", iVal, iter->iVal);

            iter->iCount++;
            iter = nullptr;
        }
        
    }//end while
  
}


BST::node* BST::GetMinNode()
{
    if(m_root == nullptr)
        return nullptr;
    
    node* iter = m_root;

    while(iter->left)
    {
        iter = iter->left;
    }

    return iter;
}

BST::node* BST::GetMaxNode()
{
    if(m_root == nullptr)
        return nullptr;
    
    node* iter = m_root;

    while(iter->right)
    {
        iter = iter->right;
    }

    return iter;
}

int BST::GetTreeHeight()
{
    if(m_root == nullptr)
        return 0;

    return m_root->iHeight + 1;
}

int BST::GetTreeSize()
{
    if(m_root == nullptr)
        return 0;

    return m_root->iSize;
}

void BST::PrintTreeDetails()
{
    printf("\n==============================");
    printf("\nTree: %s", m_sName.c_str());
    printf("\n==============================");
    printf("\nSize   of Tree: %d", GetTreeSize());
    printf("\nHeight of Tree: %d", GetTreeHeight());
    printf("\nMin    of Tree: %d", GetMinNode()->iVal);
    printf("\nMax    of Tree: %d", GetMaxNode()->iVal);
    printf("\n==============================");
}

void BST::UpdateSize(node* target)
{
    if(target == nullptr)
        return;

    target->iSize++;
    UpdateSize(target->parent);
}

void BST::UpdateHeight(node* target)
{
    if(target == nullptr)
        return;

    int iLH = -1;
    int iRH = -1;

    if(target->left)
        iLH = target->left->iHeight;

    if(target->right)
        iRH = target->right->iHeight;

    if(iLH > iRH)
        target->iHeight = iLH + 1;
    else
        target->iHeight = iRH + 1;

    UpdateHeight(target->parent);
}

void BST::PrintTreeLikeTree()
{
    //build a 2d vect of vals
    //print our vals

    std::vector<std::vector<int>> output;

    if(debugB_g)
        printf("\nCalled Print Tree like Tree...");

    AddNodeToVector(output, m_root);

    //if we got here then we should have recursively
    //gotten all of our nodes into this array
    printf("\n===============================================\n");
    for(int i = 0; i < output.size(); i++)
    {
        printf("%d:", i);
        for(int j = 0; j < output[i].size(); j++)
        {
            printf("|%d|", output[i][j]);
        }
        printf("\n");
    }
    printf("===============================================\n");
}

void BST::AddNodeToVector(std::vector<std::vector<int>> &output, node* node)
{
    if(node == nullptr)
    {
        if(debugB_g)
            printf("\nBOUNCE");
        return;
    }
    

    if(debugB_g)
        printf("\nAdding node val(%d) with height(%d) to vector...", node->iVal, node->iHeight);

    int nodeIndex = GetTreeHeight() - (node->iHeight + 1);

    if(debugB_g)
        printf("\nNode Index: %d", nodeIndex);

    if(output.size() <= nodeIndex)
    {
        if(debugB_g)
            printf("\nCreating new row...");

        std::vector<int> newRow;
        newRow.push_back(node->iVal);
        output.push_back(newRow);
    }
    else
    {
        if(debugB_g)
            printf("\nAdding node to row... height(%d)", node->iHeight);

        output[nodeIndex].push_back(node->iVal);
    }

    
    AddNodeToVector(output, node->left);
    AddNodeToVector(output, node->right);

}






