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

// start impl of MyTreeNodeIterator
MyTreeNodeIterator::MyTreeNodeIterator(MyTreeNode *root) {
    this->pushAlongLeftEdge(root);
}

bool MyTreeNodeIterator::hasNext() {
    return !this->nodeStack.empty();
}

MyTreeNode* MyTreeNodeIterator::next() {
    MyTreeNode *cur = this->nodeStack.top();
    this->nodeStack.pop();
    MyTreeNode *n = cur->right;
    this->pushAlongLeftEdge(n);
    return cur;
}

void MyTreeNodeIterator::pushAlongLeftEdge(MyTreeNode *node) {
    while (node) {
        this->nodeStack.push(node);
        node = node->left;
    }
}
// End impl of MyTreeNodeIterator


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
            // Condition1: No right subtree, just stop
            // Condition2: We already finish the right subtree
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

MyTreeNode *createBST(std::vector<int> &array, int st, int ed)
{
    if (st > ed) {
        return NULL;
    }
    int mid = st + (ed-st) / 2;
    MyTreeNode *node = new MyTreeNode(array[mid]);
    node->left = createBST(array, st, mid-1);
    node->right = createBST(array, mid+1, ed);
    
    return node;
}

MyTreeNode *createBST(std::vector<int> array)
{
    return createBST(array, 0, (int)array.size()-1);
}

// T(n) = KT(n/k)+o(1) => O(n)
int height_of_ktree(MyKTreeNode *root)
{
    if (root == NULL) {
        // This should be -1 otherwise we are calculating the level of nodes
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

// T(n) = 2KT(n/k)+O(1) =
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

// It must be (MyTreeNode * &) in reference to update prev throughout different level of recursions.
bool isValidBSTRecur(MyTreeNode *root, MyTreeNode * &prev) {
    if (!root)
        return true;
    bool isValid = isValidBSTRecur(root->left, prev);
    if (!isValid)
        return false;
    if (prev && root->value <= prev->value) {
        return false;
    }
    
    prev = root;
    return isValidBSTRecur(root->right, prev);
}

bool isValidBST(MyTreeNode* root) {
    MyTreeNode *prev = NULL;
    return isValidBSTRecur(root, prev);
}

int largest_BST_recur(MyTreeNode *node, int &min, int &max, bool &isBST, int &maxBSTNo) {
    min = INT_MAX;
    max = INT_MIN;
    if (!node) {
        isBST = true;
        return 0;
    }
    
    int tpMin, tpMax;
    tpMin = tpMax = node->value;
    int left_no = largest_BST_recur(node->left, min, max, isBST, maxBSTNo);
    bool isLeftBST = isBST && node->value >= max;
    tpMin = (min < tpMin) ? min : tpMin;
    tpMax = (max > tpMax) ? max : tpMax;
    int right_no = largest_BST_recur(node->right, min, max, isBST, maxBSTNo);
    bool isRightBST = isBST && node->value <= min;
    min = (tpMin < min) ? tpMin: min;
    max = (tpMax > max) ? tpMax: max;
    if (isLeftBST && isRightBST) {
        int cur = left_no + right_no+1;
        if (cur > maxBSTNo) {
            maxBSTNo = cur;
        }
        
        isBST = true;
        return cur;
    }
    
    isBST = false;
    return -1;
}

int largest_BST(MyTreeNode *root)
{
    int min;
    int max;
    int max_bst_no = INT_MIN;
    bool isBST;
    largest_BST_recur(root, min, max, isBST, max_bst_no);
    return max_bst_no;
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

// Similar to find all TreePathSum
void printAllPaths(MyTreeNode* root) {
    vector<int> path;
    printAllPaths(root, path);
}

void pathSumRecur(MyTreeNode *root, vector<vector<int>> &res, vector<int> &sol, int sum) {
    if (!root) {
        return;
    }
    
    sol.push_back(root->value);
    if (!root->left && !root->right && sum == root->value) {
        res.push_back(sol);
    } else {
        pathSumRecur(root->left, res, sol, sum-root->value);
        pathSumRecur(root->right, res, sol, sum-root->value);
    }
    sol.pop_back();
}

// leetcode 113 similar to printAllPath
vector<vector<int>> pathSum(MyTreeNode* root, int sum) {
    vector<vector<int>> res;
    vector<int> sol;
    pathSumRecur(root, res, sol, sum);
    return res;
}

int myfind(vector<int> &vec, int val, int st, int ed)
{
    for (int i=st; i<=ed; i++) {
        if (vec[i] == val) {
            return i;
        }
    }
    
    return -1;
}

MyTreeNode *rebuild_tree_recur(std::vector<int> &preorder, std::vector<int> &inorder, int st, int ed, int preStart)
{
    if (st > ed) {
        return NULL;
    }
    
    MyTreeNode *node = new MyTreeNode(preorder[preStart]);
    int indexInOrder = myfind(inorder, node->value, st, ed);
    int leftTreeNo = indexInOrder - st;
    node->left = rebuild_tree_recur(preorder, inorder, st, indexInOrder-1, preStart+1);
    //preStart moves along preOrder by number of leftTreeNo which can be computed in inorder array
    node->right = rebuild_tree_recur(preorder, inorder, indexInOrder+1, ed, leftTreeNo+preStart+1);
    return node;
}

MyTreeNode* rebuild_tree(std::vector<int> &preorder, std::vector<int> &inorder)
{
    return rebuild_tree_recur(preorder, inorder, 0, preorder.size()-1, 0);
}

// root is subtree's root recursively
MyTreeNode* find_LCA(MyTreeNode *root, MyTreeNode *n1, MyTreeNode *n2)
{
    if (root == NULL) {
        return NULL;
    }
    
    if (root->value == n1->value || root->value == n2->value)
        return root;
    
    MyTreeNode *left = find_LCA(root->left, n1, n2);
    MyTreeNode *right = find_LCA(root->right, n1, n2);
    // If we found both in this subtree's left and right, then root is the LCA
    if (left && right) {
        return root;
    }
    
    // If the left has the node, we return left node
    if (left) {
        return left;
    }
    
    if (right) {
        return right;
    }
    
    // We found nothing in this root's subtree, return NULL
    return NULL;
}

void sibling_connect(MyTreeNode *node)
{
    if (!node)
        return;
    
    if (node->left) {
        node->left->nextSibling = node->right;
    }
    
    if (node->right) {
        node->right->nextSibling = node->nextSibling ? node->nextSibling->left : NULL;
    }
                                    
    sibling_connect(node->left);
    sibling_connect(node->right);
}

void k_nearest_inorder(MyTreeNode *root, std::stack<int> &s, int val, bool reverse)
{
    if (!root) {
        return;
    }
    
    k_nearest_inorder(reverse ? root->right : root->left, s, val, reverse);
    if ((root->value > val && !reverse) || (root->value <= val && reverse)) {
        return;
    }
    
    s.push(root->value);
    k_nearest_inorder(reverse ? root->left : root->right, s, val, reverse);
}

vector<int> k_nearest(MyTreeNode *root, int val, int k)
{
    stack<int> s1,s2;
    vector<int> res;
    k_nearest_inorder(root, s1, val, true);
    k_nearest_inorder(root, s2, val, false);
    while (k > 0) {
        if (!s1.empty() && !s2.empty()) {
            int val1 = s1.top();
            int val2 = s2.top();
            if (abs(val1-val) < abs(val2-val)) {
                res.push_back(val1);
                s1.pop();
            } else {
                res.push_back(val2);
                s2.pop();
            }
            k--;
        } else {
            if (!s1.empty()) {
                res.push_back(s1.top());
                s1.pop();
                k--;
            } else if (!s2.empty()){
                res.push_back(s2.top());
                s2.pop();
                k--;
            } else {
                break;
            }
        }
    }
    
    return res;
}

bool findSingleValueTreesRecur(MyTreeNode *node, int &count) {
    if (node == NULL) {
        return true;
    }
    
    bool isLeftValid = findSingleValueTreesRecur(node->left, count);
    bool isRightValid = findSingleValueTreesRecur(node->right, count);
    if (!isLeftValid || !isRightValid) {
        return false;
    }
    
    if (node->left && node->right && node->value == node->left->value && node->value == node->right->value) {
        count++;
        return true;
    } else if (node->left && node->right == NULL && node->value == node->left->value) {
        count++;
        return true;
    } else if (node->right && node->left == NULL && node->value == node->right->value) {
        count++;
        return true;
    } else if (node->left == NULL && node->right == NULL) {
        count++;
        return true;
    }
    
    return false;
}

int findSingleValueTrees(MyTreeNode* node) {
    int count = 0;
    findSingleValueTreesRecur(node, count);
    return count;
}

void tree_tests() {
    vector<int> a = {1,2,3,4,5,6,7,8};
    MyTreeNode *root = createBST(a);
    smallest_k_in_bst(root, 4);
    cout << endl;
    largest_k_in_bst(root, 4);
    cout << endl;
    printTreeByLevel(root);
    
    cout << "Test tree iterator" << endl;
    MyTreeNodeIterator *it = new MyTreeNodeIterator(root);
    while (it->hasNext()) {
        MyTreeNode *n = it->next();
        cout << n->value << " ";
    }
    cout << endl;
    
    cout << "Populate Sibling " << endl;
    sibling_connect(root);
    MyTreeNode *q = root;
    cout << root->value << endl;
    while (q) {
        MyTreeNode *p = q->left;
        while (p) {
            cout << p->value << " ";
            p = p->nextSibling;
        }
        cout << endl;
        q = q->left;
    }
    
    MyKTreeNode *node = new MyKTreeNode(0);
    node->children[0] = new MyKTreeNode(5);
    node->children[1] = new MyKTreeNode(5);
    node->children[2] = new MyKTreeNode(5);
    node->children[0]->children[0] = new MyKTreeNode(8);
    node->children[0]->children[1] = new MyKTreeNode(7);
    node->children[1]->children[0] = new MyKTreeNode(9);
    node->children[1]->children[1] = new MyKTreeNode(8);
    node->children[2]->children[0] = new MyKTreeNode(10);
    node->children[2]->children[1] = new MyKTreeNode(9);
    
    
    cout << "Height = " << height_of_ktree(node) << endl;
    cout << "Diameter = " << diameter_of_ktree(node) << endl;
    cout << "Distance = " << distance_of_ktree(node) << endl;
    cout << "Diameter weighted = " << diameter_of_weighted_ktree(node) << endl;
    
    cout << "Largest BST:" ;
    MyTreeNode *node1 = new MyTreeNode(1);
    cout << largest_BST(node1) << endl;
    
    cout << "k closest nodes ---" << endl;
    root = createBST(a);
    vector<int> res = k_nearest(root, 3, 2);
    for (auto i:res) {
        cout << i << " ";
    }
    cout << endl;
    
}
