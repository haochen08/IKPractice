//
//  tree.hpp
//  Lesson-1
//
//  Created by Hao Chen on 9/24/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <vector>

#define N_ARY_NUM 10

class MyTreeNode {
public:
    MyTreeNode *left, *right, *nextSibling;
    int value;
    MyTreeNode(int _value):left(NULL), right(NULL), nextSibling(NULL), value(_value){}
//    MyTreeNode(int _value)
//    {
//        MyTreeNode(_value, -1);
//    }
};

class MyTreeNodeIterator {
public:
    MyTreeNodeIterator(MyTreeNode *root);
    bool hasNext();
    MyTreeNode *next();
    
private:
    std::stack<MyTreeNode *> nodeStack;
    void pushAlongLeftEdge(MyTreeNode *node);
};

class MyKTreeNode {
public:
    MyKTreeNode *children[N_ARY_NUM];
    int value;
    MyKTreeNode(int _value)
    {
        value = _value;
        for (int i=0; i<N_ARY_NUM; i++) {
            children[i] = NULL;
        }
    }
};

//---- 09/24/2016
void bfs_travse(MyTreeNode *root);
void printTreeByLevel(MyTreeNode *n);
MyTreeNode *insert_nodes_to_tree(std::vector<int> nodes);

void preorder(MyTreeNode *root);
void inorder(MyTreeNode *root);
void postorder(MyTreeNode *root);

void preorder_iter(MyTreeNode *root);
void inorder_iter(MyTreeNode *root);
void inorder_iter_limited_by_k(MyTreeNode *root, int k);
void postorder_iter(MyTreeNode *root);

MyTreeNode *createBST(std::vector<int> array);
void remove_node_in_BST(MyTreeNode *root);

// For the following two, bst is in ascending order
void smallest_k_in_bst(MyTreeNode *root, int k);
void largest_k_in_bst(MyTreeNode *root, int k);


// Height of unweighted K-ary tree
// Height is defined as the length of longest path from root to leaf node
// NOT the node number
int height_of_ktree(MyKTreeNode *root);

// Distance of weighted K-ary tree
// Distance is defined as the maxium summary of weight from root to leaf node
int distance_of_ktree(MyKTreeNode *root);

int diameter_of_ktree(MyKTreeNode *root);
int diameter_of_weighted_ktree(MyKTreeNode *root);

// Input is like 123)4))
MyKTreeNode *generate_ktree(std::string &input);

// Reverse the tree from right to left
MyTreeNode* flip_tree(MyTreeNode *node);

bool is_BST(MyTreeNode *node);

// Find the number of nodes of largest BST in given binary tree
int largest_BST(MyTreeNode *root);

// print all paths for Binary Tree
void printAllPaths(MyTreeNode* root);

// Given preorder and inorder of tree, rebuild the tree
MyTreeNode* rebuild_tree(std::vector<int> &preorder, std::vector<int> &inorder);

// Find least common ancestor
MyTreeNode* find_LCA(MyTreeNode *root, MyTreeNode *n1, MyTreeNode *n2);

// Populate the right sibling in full binary tree
void sibling_connect(MyTreeNode *node);

// Given binary tree, find total number of subtree which has the same value
bool findSingleValueTreesRecur(MyTreeNode *node, int &count);

#endif /* tree_hpp */
