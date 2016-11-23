//
//  main.cpp
//  Lesson-1
//
//  Created by Hao Chen on 8/28/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include <vector>
#include <stack>
#include <iostream>

#include "sorting.hpp"
#include "sorting_app.hpp"
#include "recursion.hpp"
#include "array_problem.hpp"
#include "tree.hpp"
#include "dp.hpp"
#include "linked_list.hpp"
#include "my_string.hpp"
#include "graph.hpp"


using namespace std;
void print_array_element(vector<int> &elements)
{
    for (int item: elements) {
        cout << item << " ";
    }
    cout << endl;
}

void print_points_array(vector<point> &elements)
{
    for (point pt: elements) {
        cout << pt.x << "," << pt.y << " ";
    }
    cout << endl;
}

void map_string_test(string &s)
{
    vector<uint> buckets;
    buckets.reserve(256); // ASCII
    for (char item:s)
    {
        buckets[item]++;
    }
    
    uint k = 0;
    for (uint i=0; i<256; i++)
    {
        for (uint j=0; j<buckets[i]; j++) {
            s[k++] = i;
        }
    }
}



int findDuplicateFromPermutation(vector < int > intArray) {
    uint len = intArray.size();
    int buckets[len];
    memset(buckets, 0, sizeof(int)*len);
    for (uint i:intArray) {
        buckets[i-1]++;
    }
    
    for (uint i=0; i<len; i++) {
        if (buckets[i] > 1) {
            return i+1;
        }
    }
    
    return -1;
}

void print_permutation(vector<int> set, uint i)
{
    if (i == set.size()-1) {
        print_array_element(set);
        return;
    }
    
    for (uint j=i; j<set.size(); j++) {
        // ? When j==i, it will swap itself. Is this necessary?  
        swap(set[i],set[j]);
        print_permutation(set, i+1);
        swap(set[i],set[j]);
    }
}

vector < int > topK(vector < int > iStream, int iK) {
    vector<int> heap,res;
    for (int i:iStream) {
        heap_insert(heap, i);
    }
    
    for (uint i=0; i<iK; i++) {
        res.push_back(heap[0]);
        swap(heap[0], heap[heap.size()-i-1]);
        heapifyDown(heap, 0, heap.size()-i-1);
    }
    
    return res;
}

vector<int> topK2(vector<int> iStream, int iK) {
    return quick_sort_k(iStream, 0, (uint)iStream.size()-1, iK);
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
}

void recursive_tests() {
    cout << "()=3" << endl;
    genBrackets(2);
    cout << "Tree count number is " << countTreesNum(3) << endl;
    vector<int> a = {-1,3,-4,5,6,7};
    if (groupSum(a, 0, 4)) {
        cout << "Found sum to target " << endl;
    } else {
        cout << "Not found sum to target " << endl;
    }
    
    string s = "12345";
    vector<char> expr;
    addOperators(s, expr, 0, 12345);
    
    cout << "Permutation(N): N=5" << endl;
    permutation(5);

    cout << "NQueen(14): Number of solutions=" << NQueen(14) << endl;

}

void dp_test() {
    vector<int> dem = {1,11,13};
    int min_change = coinchange(46, dem);
    vector<int> seq = {-7,1,0,2,0,3,0,4,5};
    cout << min_change << endl;
    cout << "lis = " << find_lis(seq) << endl;
    vector<vector<int>> matrix = {{1,1,1,1},{1,1,1,1},{1,1,1,1}};
    int num_of_paths = numberOfPaths(matrix);
    cout << "number of paths:" << num_of_paths << endl;
    cout << "Maxium Product Cut (15) = " << maxProductFromCutPieces(15) << endl;
        
}

void sorting_test() {
    vector<vector<int>> a = {{1,3,5,7}, {2,4,5,8}, {3,4,5,6}};
    vector<int> result = k_merge_sort(a, 3);
    print_array_element(result);
}

void hanoi(int n, int source, int target, int middle) {
    if (n == 0)
        return;
    hanoi(n-1, source, middle, target);
    cout << source << " -> " << target << endl;
    hanoi(n-1, middle, target, source);
    
}

void linked_list_test() {
    MyLinkedList *n1 = new MyLinkedList(0);
    MyLinkedList *n2 = new MyLinkedList(1);
    MyLinkedList *n3 = new MyLinkedList(2);
    MyLinkedList *n4 = new MyLinkedList(3);
    n1->next = n2; n2->next = n3;
    n3->next = n4;
    MyLinkedList *h = n1;
    cout << "Reverse linked list ---" << endl;
    h = reverse_linkedlist(h);
    MyLinkedList *p = h;
    while (p != NULL) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}

void graph_test() {
    vector<int> labels = {0,1,2,3};
    MyGraph g(labels);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
    g.print();
    dfs(&g);
}

int main(int argc, const char * argv[]) {
    recursive_tests();

    return 0;
}
