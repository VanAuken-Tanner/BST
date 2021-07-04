#pragma once

#include <vector>
#include <string>

class BST{
public:
    BST();
    BST(std::string sName);
    ~BST();

    enum PrintType
    {
        Ascending,
        Descending,
        Tree
    };

    void Build(std::vector<int> vec);
    void Print(PrintType type);
    void PrintTreeDetails();

private:
    struct node
    {
        node* parent;
        node* left;
        node* right;
        
        int iVal;
        int iSize;
        int iHeight;
        int iCount;//number of occurances of this value
    };

    node*               m_root;
    int                 m_iNumNodes;
    std::string         m_sName;
    

    void Insert(int iVal);
    node* CreateNode(int iVal, node* pParent);
    node* GetMinNode();
    node* GetMaxNode();

    void UpdateSize(node* target);
    void UpdateHeight(node* target);

    int GetTreeHeight();
    int GetTreeSize();

    void PrintTreeLikeTree();
    void PrintNodeRecur(node* toPrint, PrintType type);
    
    void AddNodeToVector(std::vector<std::vector<int>> &output, node* node);


};