//
//  tree.cpp
//  Lesson-1
//
//  Created by Hao Chen on 9/24/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include <iostream>
#include <deque>
#include <stack>
#include "tree.hpp"

using namespace std;


MyTreeNode *insert_nodes_to_tree(vector<int> nodes)
{
    if (nodes.size() == 0) {
        return NULL;
    }
    
    deque<MyTreeNode *> queue;
    MyTreeNode *root = new MyTreeNode(nodes[0]);
    MyTreeNode *node = root;
    for (int i=1; i<nodes.size(); i++) {
        MyTreeNode *new_node = new MyTreeNode(nodes[i]);
        if (!node->left) {
            node->left = new_node;
        } else if (!node->right) {
            node->right = new_node;
        } else {
            node = queue.front();
            node->left = new_node;
            queue.pop_front();
        }
        
        queue.push_back(new_node);
    }
    
    return root;
}

void preorder(MyTreeNode *root)
{
    if (root == NULL) {
        return;
    }
    
    cout << root->value << ",";
    preorder(root->left);
    preorder(root->right);
}

void preorder_iter(MyTreeNode *root)
{
    if (root == NULL) {
        return;
    }
    
    stack<MyTreeNode *> stack;
    stack.push(root);
    while (!stack.empty())
    {
        MyTreeNode *node = stack.top();
        cout << node->value << ",";
        if (node->right) {
            stack.push(node->right);
        }
        
        if (node->left) {
            stack.push(node->left);
        }
        stack.pop();
    }
}

void inorder_iter(MyTreeNode *root)
{
    inorder_iter_limited_by_k(root, INT_MAX);
}

void inorder_iter_limited_by_k(MyTreeNode *root, int k)
{
    if (root == NULL) {
        return;
    }
    
    stack<MyTreeNode *> stack;
    MyTreeNode *node = root;
    int i = 0;
    while ((!stack.empty() || node != NULL) && i < k)
    {
        if (node != NULL) {
            stack.push(node);
            node = node->left;
        } else {
            node = stack.top();
            cout << node->value << ",";
            node = node->right;
            stack.pop();
            i++;
        }
    }
}

void reverse_inorder_iter_limited_by_k(MyTreeNode *root, int k)
{
    if (root == NULL) {
        return;
    }
    
    stack<MyTreeNode *> stack;
    MyTreeNode *node = root;
    int i = 0;
    while ((!stack.empty() || node != NULL) && i < k)
    {
        if (node != NULL) {
            stack.push(node);
            node = node->right;
        } else {
            node = stack.top();
            cout << node->value << ",";
            node = node->left;
            stack.pop();
            i++;
        }
    }
}

void postorder_iter(MyTreeNode *root)
{
    if (root == NULL) {
        return;
    }
    
    stack<MyTreeNode *> stack;
    MyTreeNode *node = root, *lastVisited = NULL;
    while (!stack.empty() || node != NULL) {
        if (node != NULL) {
            stack.push(node);
            node = node->left;
        } else {
            MyTreeNode *peekNode = stack.top();
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                node = peekNode->right;
            } else {
                cout << peekNode->value << ",";
                lastVisited = peekNode;
                stack.pop();
            }
        }
    }
}

void bfs_travse(MyTreeNode *root)
{
    if (root == NULL) {
        return;
    }
    
    deque<MyTreeNode *> queue;
    queue.push_back(root);
    int level = 0;
    while (!queue.empty()) {
        MyTreeNode *node = queue.front();
        if (node->level > level) {
            level = node->level;
            cout << endl;
        }
        
        cout << node->value << ",";

        if (node->left) {
            queue.push_back(node->left);
        }
        
        if (node->right) {
            queue.push_back(node->right);
        }
        
        queue.pop_front();
    }
}

void printTreeByLevel(MyTreeNode *n)
{
    if (n == NULL)
        return;
    
    deque<MyTreeNode *> queue;
    queue.push_back(n);
    int node_count = queue.size();
    
    while (!queue.empty()) {
        while (node_count > 0) {
            MyTreeNode *cur = queue.front();
            if (cur->left) {
                queue.push_back(cur->left);
            }
            
            if (cur->right) {
                queue.push_back(cur->right);
            }
            
            cout << cur->value << " ";
            queue.pop_front();
            
            node_count--;
        }
        
        cout << endl;
        node_count = queue.size();
    }
}


//FIXME Wrong implementation
void remove_node_in_BST(MyTreeNode *node)
{
    if (!node->left && !node->right) {
        delete node;
        node = NULL;
        return;
    }
    
    if (node->left) {
        MyTreeNode *temp = node;
        node = node->left;
        delete temp;
        temp = NULL;
    }
    
    
}

MyTreeNode *createBST(std::vector<int> &array, int st, int ed, int level)
{
    if (st > ed) {
        return NULL;
    }
    int mid = st + (ed-st) / 2;
    MyTreeNode *node = new MyTreeNode(array[mid], level);
    node->left = createBST(array, st, mid-1, level+1);
    node->right = createBST(array, mid+1, ed, level+1);
    
    return node;
}

MyTreeNode *createBST(std::vector<int> array)
{
    return createBST(array, 0, (int)array.size()-1, 0);
}


int height_of_ktree(MyKTreeNode *root)
{
    if (root == NULL) {
        // This should be -1 otherwise we are calculating the number of nodes
        return -1;
    }
    
    int max = INT_MIN;
    for (int i = 0; i < N_ARY_NUM; i++) {
        MyKTreeNode *node = root->children[i];
        int val = height_of_ktree(node);
        if (val > max) {
            max = val;
        }
    }
    
    return max + 1;
}

int distance_of_ktree(MyKTreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    
    int max = INT_MIN;
    for (int i = 0; i < N_ARY_NUM; i++) {
        MyKTreeNode *node = root->children[i];
        int val = distance_of_ktree(node);
        if (node != NULL) {
            val += node->value;
        }
        
        if (val > max) {
            max = val;
        }
    }
    
    return max;
}


int diameter_of_ktree(MyKTreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    
    int max1 = INT_MIN, max2 = INT_MIN, max_d = INT_MIN;
    for (int i=0; i<N_ARY_NUM; i++) {
        MyKTreeNode *node = root->children[i];
        int val = height_of_ktree(node);
        if (val > max1) {
            max2 = max1;
            max1 = val;
        } else if (val > max2) {
            max2 = val;
        }
        
        val = diameter_of_ktree(node);
        if (val > max_d) {
            max_d = val;
        }
    }

    return max(max1+max2+2, max_d);
}

int diameter_of_weighted_ktree(MyKTreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    
    int max1 = INT_MIN, max2 = INT_MIN, max_d = INT_MIN;
    for (int i=0; i<N_ARY_NUM; i++) {
        // 1. The maxium_height1 + second_maxium_height2
        MyKTreeNode *node = root->children[i];
        int val = distance_of_ktree(node);
        if (node != NULL) {
            val += node->value;
        }
        
        // The following "if else" is to find the two largest number
        if (val > max1) {
            max2 = max1;
            max1 = val;
        } else if (val > max2) {
            max2 = val;
        }
        
        // 2. Maxium diameter of direct child
        val = diameter_of_weighted_ktree(node);
        if (val > max_d) {
            max_d = val;
        }
    }
    
    // Diameter is maxium of them
    return max(max1+max2, max_d);
}


// WRONG IMPL
bool generate_ktree_recur(MyKTreeNode * &root, std::string &input, int &index)
{
    if (index >= input.length()) {
        return false;
    }
    
    char c = input[index++];
    if (c == '(') {
        return false;
    }
    
    root = new MyKTreeNode(char(c)-48);
    for (int i=0; i< N_ARY_NUM; i++) {
        if (!generate_ktree_recur(root->children[i], input, index)) {
            break;
        }
    }
    
    return true;
}

MyKTreeNode *generate_ktree(std::string &input)
{
    MyKTreeNode *root = NULL;
    int index = 0;
    generate_ktree_recur(root, input, index);
    return root;
}

void smallest_k_in_bst(MyTreeNode *root, int k)
{
    inorder_iter_limited_by_k(root, k);
}

void largest_k_in_bst(MyTreeNode *root, int k)
{
    reverse_inorder_iter_limited_by_k(root, k);
}


MyTreeNode* flip_tree(MyTreeNode *node)
{
    if (node == NULL) {
        return NULL;
    }
    
    MyTreeNode *temp = node->left;
    node->left = flip_tree(node->right);
    node->right = flip_tree(temp);
    return node;
}

bool is_BSTInOrder(MyTreeNode *node, int &prev)
{
    if (!node) {
        return true;
    }
    
    bool res = is_BSTInOrder(node->left, prev) && (node->value > prev);
    prev = node->value;
    return res && is_BSTInOrder(node->right, prev);
}

bool is_BST(MyTreeNode *node)
{
    int prev = INT_MIN;
    return is_BSTInOrder(node, prev);
}

void printAllPaths(MyTreeNode *node, vector<int> &path) {
    if (node == NULL)
        return;
    
    path.push_back(node->value);
    if (node->left == NULL && node->right == NULL) {
        for (int i:path) {
            cout << i << " ";
        }
        cout << endl;
    } else {
        printAllPaths(node->left, path);
        printAllPaths(node->right, path);
    }
    path.pop_back();
}

void printAllPaths(MyTreeNode* root) {
    vector<int> path;
    printAllPaths(root, path);
}










