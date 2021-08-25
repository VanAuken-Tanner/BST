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
    struct Node
    {
        Node* parent;
        Node* left;
        Node* right;
        
        int iVal;
        int iSize;
        int iHeight;
        int iDepth;//distance from root - root 0
        int iCount;//number of occurances of this value
    };

    Node*               m_root;
    int                 m_iNumNodes;
    std::string         m_sName;
    

    void Insert(int iVal);
    Node* CreateNode(int iVal, Node* pParent);
    Node* GetMinNode();
    Node* GetMaxNode();

    void UpdateSize(Node* target);
    void UpdateHeight(Node* target);
    void UpdateDepth(Node* target);

    int GetTreeHeight();
    int GetTreeSize();

    void PrintTreeLikeTree();
    void PrintNodeRecur(Node* toPrint, PrintType type);
    void PrintNode(Node* toPrint);
    
    void AddNodeToVector(std::vector<std::vector<int>> &output, Node* node);


};