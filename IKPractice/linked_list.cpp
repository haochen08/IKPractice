//
//  linked_list.cpp
//  Lesson-1
//
//  Created by Hao Chen on 10/23/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include <vector>
#include <iostream>
#include "linked_list.hpp"

using namespace std;
int find_intersection(MyLinkedListNode *l1, MyLinkedListNode *l2)
{
    if (l1 == NULL || l2 == NULL) {
        return -1;
    }
    
    MyLinkedListNode *p2 = l2;
    while (p2->next != NULL) {
        p2 = p2->next;
    }
    
    p2->next = l1;
    
    // It converts to cycle finding problem.
    MyLinkedListNode *s = l2, *f= l2;
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

MyLinkedListNode *reverse_linkedlist_recur(MyLinkedListNode *node)
{
    MyLinkedListNode *h;
    if (node->next == NULL)
        return node;
    h = reverse_linkedlist(node->next);
    node->next->next = node;
    node->next = NULL;
    return h;
}


MyLinkedListNode *reverse_linkedlist(MyLinkedListNode *h)
{
    if (h == NULL || h->next == NULL) {
        return h;
    }
    
    return reverse_linkedlist_recur(h);
}

MyLinkedListNode *insert(MyLinkedListNode *h, int a)
{
    MyLinkedListNode *node = new MyLinkedListNode(a);
    node->next = h;
    h = node;
    return h;
}

MyLinkedListNode *buildLinkedListReverse(vector<int> &array)
{
    MyLinkedListNode *h=NULL;
    for (int x:array) {
        h = insert(h, x);
    }
    
    return h;
}

MyLinkedListNode *buildLinkedListRecur(vector<int> &array, int i) {
    if (i == array.size()) {
        return NULL;
    }
    
    MyLinkedListNode *node = new MyLinkedListNode(array[i]);
    node->next = buildLinkedListRecur(array, i+1);
    return node;
}

void printLinkedList(MyLinkedListNode *h)
{
    MyLinkedListNode *p=h;
    while (p != NULL) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
}


// 1-2-3-4  5-6-7-8 => 1-5-2-6-3-7-4-8
MyLinkedListNode *weaveLinkedList(MyLinkedListNode *n1, MyLinkedListNode *n2, int i)
{
    if (n1 == NULL && n2 == NULL) {
        return NULL;
    }
    
    if (n1 == NULL) {
        return n2;
    }
    
    if (n2 == NULL) {
        return n1;
    }
    
    if (i % 2==0) {
        n1->next = weaveLinkedList(n1->next, n2, i+1);
        return n1;
    } else {
        n2->next = weaveLinkedList(n1, n2->next, i+1);
        return n2;
    }
}

// 1-5-2-6-3-7-4-8 => 1-2-3-4  5-6-7-8
void splitLinkedList(MyLinkedListNode *h, MyLinkedListNode **n1)
{
    if (h == NULL || h->next == NULL) {
        *n1 = NULL;
        return;
    }

    if (h->next->next == NULL) {
        *n1 = h->next;
        h->next = NULL;
        return;
    }
    
    *n1 = h->next;
    MyLinkedListNode *p, *q;
    p = h; q = *n1;
    while (p != NULL && q != NULL && q->next != NULL) {
        MyLinkedListNode *tmp = q->next;
        p->next = q->next;
        q->next = q->next->next;
        p = tmp;
        q = q->next;
    }
    
    p->next = NULL;
}

MyLinkedListNode* zip(MyLinkedListNode* pList) {
    if (pList == NULL || pList->next == NULL || pList->next->next == NULL)
        return pList;
    
    MyLinkedListNode *p, *q, *head1, *head2;
    p = q = head1 = pList;
    int cnt = 0;
    while (p != NULL) {
        cnt++;
        p = p->next;
    }
    
    // Note: we should find the node i.e. p before mid node
    // since we want to break the first list linking to second one
    // by setting p->next == NULL after we reverse the second list
    // Take {1 2 3 4 5} as example, it is 2.
    // Then we reverse p->next which starts from mid
    for (int i=0; i<cnt/2-1; i++) {
        q = q->next;
    }
    // The following order does matter
    head2 = reverse_linkedlist(q->next);
    q->next = NULL;
    return weaveLinkedList(head1, head2, 0);
}

MyLinkedListNode *unzip(MyLinkedListNode *h)
{
    if (h == NULL) {
        return NULL;
    }
    
    MyLinkedListNode *h2;
    splitLinkedList(h, &h2);
    h2 = reverse_linkedlist(h2);
    MyLinkedListNode *p = h;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = h2;
    return h;
}

void linkedlist_test()
{
    vector<int> a = {1,2,3,4,5};
    MyLinkedListNode *h = buildLinkedListReverse(a);
    cout << "Build linked list by insertion ---" << endl;
    h = buildLinkedListReverse(a);
    printLinkedList(h);
    
    cout << "Reverse linked list ---" << endl;
    h = reverse_linkedlist(h);
    printLinkedList(h);
    
    cout << "Build linked list by recursion ---" << endl;
    h = buildLinkedListRecur(a, 0);
    printLinkedList(h);
    
    cout << "Reverse linked list ---" << endl;
    h = reverse_linkedlist(h);
    printLinkedList(h);
    
    h = zip(h);
    cout << "Zip h ---" << endl;
    printLinkedList(h);
    h = unzip(h);
    cout << "Unzip h ---" << endl;
    printLinkedList(h);
    

    
}
