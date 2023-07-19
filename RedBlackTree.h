#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#define COLOR_RED 1
#define COLOR_BLACK 0

#include <iostream> // use for the throw exception
#include <vector>

using namespace std;

struct RBTNode{
    int data;
    unsigned short int color; // 0 = black, 1 = red
    RBTNode *left = nullptr;
    RBTNode *right = nullptr;
    RBTNode *parent = nullptr;
};

class RedBlackTree {
    public:
        RedBlackTree() {};
        RedBlackTree(const RedBlackTree &other);
        ~RedBlackTree();

        void Insert(int value);
        void Remove(int value);
        bool Contains(int value);
        int GetMin(); // returns the minimum value in the tree
        int GetMax(); // returns the maximum value in the tree
        int Size(); // number of nodes

        string ToPrefixString() const {return ToPrefixString(root);};
        string ToInfixString() const {return ToInfixString(root);};
        string ToPostfixString() const {return ToPostfixString(root);};

    private:
        unsigned long long int numItems = 0;
        RBTNode *root = nullptr;
        vector<int> values;

        string ToPrefixString(RBTNode *node) const;
        string ToInfixString(RBTNode *node) const;
        string ToPostfixString(RBTNode *node) const;
        void InsertFixup(RBTNode *node);
        void RemoveFixup(RBTNode *node);
        void RotateLeft(RBTNode *node);
        void RotateRight(RBTNode *node);

        void copyTree(RBTNode *root, RBTNode *node);
        void deleteTree(RBTNode *curr);
        RBTNode *getSuccessor(RBTNode *node);
};


#endif