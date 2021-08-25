#include "bst.h"

#include <iostream>

bool debugNodeCreate_g = false;

bool debug_g = false;

void inline PHL_g(bool bLineBefore = true, bool bLineAfter = true)
{
    if(bLineBefore)
        printf("\n");

    printf("=========================================================================");

    if(bLineAfter)
        printf("\n");
}

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

void BST::PrintNodeRecur(Node* toPrint, PrintType type)
{
    if (toPrint == nullptr)
        return;

    Node* first;
    Node* second;

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

BST::Node* BST::CreateNode(int iVal, Node* pParent)
{
    if(debug_g && pParent == nullptr)
        printf("\nCreating root node... val(%d)",iVal);
    else if(debug_g)
        printf("\nCreating node... val(%d) parent val(%d)",iVal, pParent->iVal);

    Node* newNode = new Node;
    newNode->iVal = iVal;
    newNode->parent = pParent;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->iSize = 1;
    newNode->iHeight = 0;
    newNode->iDepth = 0;
    newNode->iCount = 1;

    m_iNumNodes++;

    if(debugNodeCreate_g)
        PrintNode(newNode);

    if(debug_g)
         printf("\nNumber of Nodes: %d",m_iNumNodes);

    return newNode;
}

void BST::PrintNode(Node* toPrint)
{
    PHL_g();
    printf("\nNode    Val: %d", toPrint->iVal);
    printf("\nNode Height: %d", toPrint->iHeight);
    printf("\nNode Size  : %d", toPrint->iSize);
    printf("\nNode depth : %d", toPrint->iDepth);
    
    int iPVal = -1, iLCVal = -1, iRCVal = -1;
    if(toPrint->parent != nullptr)
        iPVal = toPrint->parent->iVal;
    if(toPrint->left != nullptr)
        iLCVal = toPrint->left->iVal;
    if(toPrint->right != nullptr)
        iRCVal = toPrint->right->iVal;

    printf("\nParent Val:%d\nLeft:%d  -  Right:%d", iPVal, iLCVal, iRCVal);
    PHL_g();
    
}

void BST::UpdateSize(Node* target)
{
    if(target == nullptr)
        return;

    target->iSize++;
    UpdateSize(target->parent);
}

void BST::UpdateHeight(Node* target)
{
    if(target == nullptr)
        return;

    int iLH = -1;
    int iRH = -1;

    if(target->left != nullptr)
        iLH = target->left->iHeight;

    if(target->right != nullptr)
        iRH = target->right->iHeight;

    int prevHeight = target->iHeight;

    if(iLH > iRH)
        target->iHeight = iLH + 1;
    else if(iRH > iLH)
        target->iHeight = iRH + 1;

    if(debug_g)
        printf("\nupdating node val:%d L(%d) - R(%d)\nH: %d > %d",target->iVal, iLH, iRH, prevHeight, target->iHeight);

    UpdateHeight(target->parent);
}

void BST::UpdateDepth(Node* toUpdate)
{
    int iDepthCount = 0;
    Node* pParent = toUpdate->parent;
    
    while (pParent != nullptr)
    {
    
        iDepthCount++;
        pParent = pParent->parent;
    }

    toUpdate->iDepth = iDepthCount;
    
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

    Node* iter = m_root;
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

            if(iter->left != nullptr)
            {
                iter = iter->left;
            }
            else
            {
                iter->left = CreateNode(iVal, iter); 
                
                UpdateSize(iter);
                UpdateHeight(iter);
                UpdateDepth(iter->left);
                             
            }
        }
        else if (iVal > iter->iVal)
        {
            if(debug_g)
                printf("\nValue greater than current node. %d > %d", iVal, iter->iVal);

            if(iter->right != nullptr)
            {
                iter = iter->right;
            }
            else
            {
                iter->right = CreateNode(iVal, iter);
                UpdateSize(iter);
                UpdateHeight(iter);
                UpdateDepth(iter->right);
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


BST::Node* BST::GetMinNode()
{
    if(m_root == nullptr)
        return nullptr;
    
    Node* iter = m_root;

    while(iter->left)
    {
        iter = iter->left;
    }

    return iter;
}

BST::Node* BST::GetMaxNode()
{
    if(m_root == nullptr)
        return nullptr;
    
    Node* iter = m_root;

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

void BST::PrintTreeLikeTree()
{
    //build a 2d vect of vals
    //print our vals

    std::vector<std::vector<int>> output;

    if(debug_g)
        printf("\nCalled Print Tree like Tree...");

    //recursively adds nodes to the vector until we reach all of the leaves.
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

//Uses depth to index the array
void BST::AddNodeToVector(std::vector<std::vector<int>> &output, Node* node)
{
    if(node == nullptr)
        return;

    if(output.size() <= node->iDepth)
    {
        std::vector<int> newVec;
        output.push_back(newVec);
    }

    output.at(node->iDepth).push_back(node->iVal);

    AddNodeToVector(output, node->left);
    AddNodeToVector(output, node->right);

}






