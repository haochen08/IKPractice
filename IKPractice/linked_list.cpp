//
//  linked_list.cpp
//  Lesson-1
//
//  Created by Hao Chen on 10/23/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include "linked_list.hpp"

int find_intersection(MyLinkedList *l1, MyLinkedList *l2)
{
    if (l1 == NULL || l2 == NULL) {
        return -1;
    }
    
    MyLinkedList *p2 = l2;
    while (p2->next != NULL) {
        p2 = p2->next;
    }
    
    p2->next = l1;
    
    // It converts to cycle finding problem.
    MyLinkedList *s = l2, *f= l2;
    while (s != NULL && f->next != NULL && s != f) {
        s = s->next;
        f = f->next->next;
    }
    
    if (s != f) {
        return -1;
    }
    
    s = l2;
    int cnt = 1;
    while (s != f) {
        cnt++;
        s = s->next;
        f = f->next;
    }
    
    return cnt;
}

MyLinkedList *reverse_linkedlist_recur(MyLinkedList *node)
{
    MyLinkedList *h;
    if (node->next == NULL)
        return node;
    h = reverse_linkedlist(node->next);
    node->next->next = node;
    node->next = NULL;
    return h;
}


MyLinkedList *reverse_linkedlist(MyLinkedList *h)
{
    if (h == NULL || h->next == NULL) {
        return h;
    }
    
    return reverse_linkedlist_recur(h);
}
