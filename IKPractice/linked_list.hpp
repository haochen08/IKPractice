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

class MyLinkedList {
public:
    MyLinkedList *next;
    int val;
    MyLinkedList(int _val):next(NULL),val(_val) {}
};


// l1 or l2 may have loop
int find_intersection(MyLinkedList *l1, MyLinkedList *l2);

// Given p points to arbitary pointer in sorted linkedlist,
// return median
// Find the start point of linked list
int find_median(MyLinkedList *p);

MyLinkedList *reverse_linkedlist(MyLinkedList *h);



#endif /* linked_list_hpp */
