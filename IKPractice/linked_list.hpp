//
//  linked_list.hpp
//  Lesson-1
//
//  Created by Hao Chen on 10/23/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#ifndef linked_list_hpp
#define linked_list_hpp

#include <stdio.h>

class MyLinkedListNode {
public:
    MyLinkedListNode *next;
    int val;
    MyLinkedListNode(int _val):next(NULL),val(_val) {}
};


// l1 or l2 may have loop
int find_intersection(MyLinkedListNode *l1, MyLinkedListNode *l2);

// Given p points to arbitary pointer in sorted linkedlist,
// return median
// Find the start point of linked list
int find_median(MyLinkedListNode *p);

MyLinkedListNode *reverse_linkedlist(MyLinkedListNode *h);
MyLinkedListNode *reverseLinkedlistInGroup(MyLinkedListNode *h, int k);

MyLinkedListNode *buildLinkedListReverse(std::vector<int> &array);
MyLinkedListNode *buildLinkedListRecur(std::vector<int> &array, int i);

// Zip the linked list from both end
// Zip 1-2-3-4-5-6 => 1-6-2-5-3-4
MyLinkedListNode* zip(MyLinkedListNode* h);

// opposite of zip
MyLinkedListNode* unzip(MyLinkedListNode* h);

void linkedlist_test();


#endif /* linked_list_hpp */
