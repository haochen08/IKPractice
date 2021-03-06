//
//  linked_list.cpp
//  Lesson-1
//
//  Created by Hao Chen on 10/23/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include <vector>
#include <iostream>
#include <assert.h>
#include "linked_list.hpp"


using namespace std;

SkipList::SkipList()
{
    srand(time(NULL));
    head = new Node(0, WORD_BIT);
    cur_level = 1;
}

void SkipList::insert(int x)
{
    int level = randomLevel();
    if (level > cur_level) {
        cur_level = level;
    }
    
    Node *new_node = new Node(x, level);
    Node *cur = head;
    for (int i=level-1; i>=0; i--) {
        while (cur->next[i]) {
            if (cur->next[i]->val > x) {
                break;
            }
            
            cur = cur->next[i];
        }
        new_node->next[i] = cur->next[i];
        cur->next[i] = new_node;
    }
}

bool SkipList::isContains(int x)
{
    Node *cur = head;
    
    for (int i = cur_level-1; i>=0; i--) {
        while (cur->next[i]) {
            if (cur->next[i]->val == x) {
                return true;
            }
            
            if (cur->next[i]->val > x) {
                break;
            }
            
            cur = cur->next[i];
        }
    }
    
    return false;
}

void SkipList::remove(int x)
{
    Node *cur = head;
    for (int i = cur_level-1; i >= 0; i--) {
        while (cur->next[i]) {
            if (cur->next[i]->val == x) {
                cur->next[i] = cur->next[i]->next[i];
                break;
            }
            
            if (cur->next[i]->val > x) {
                // Go to next level
                break;
            }
            cur = cur->next[i];
        }
    }
}

void SkipList::print()
{
    for (int i=0; i<cur_level; i++) {
        cout << i << ":";
        Node *cur = head;
        while (cur->next[i]) {
            cout << cur->next[i]->val << " ";
            cur = cur->next[i];
        }
        
        cout << endl;
    }
    cout << endl;

}


int SkipList::randomLevel()
{
    int r = rand();
    int level = 1;
    while ((r & 1) == 1) {
        level++;
        r >>= 1;
    }
    
    return level;
}

MyLinkedListNode *cycleStart(MyLinkedListNode *l)
{
    MyLinkedListNode *f, *s;
    f = s = l;
    while (f != NULL && f->next != NULL) {
        s = s->next;
        f = f->next->next;
        if (s == f)
            break;
    }
    
    if (f == NULL) {
        return NULL;
    }
    
    int cycle_len = 0;
    while (s != f) {
        s = s->next;
        cycle_len++;
    }
    
    s = f = l;
    for (int i=0; i<cycle_len; i++) {
        f = f->next;
    }
    
    while (s != f) {
        s = s->next;
        f = f->next;
    }
    return s;
}

MyLinkedListNode *find_intersection_no_cycle(MyLinkedListNode *l1, MyLinkedListNode *l2)
{
    // traverse the l1, get |l1|
    // traverse the l2, get |l2|
    // Compute the ||l2|-|l1||(=diff), get the longer one.
    // Assume l1 is the longer one, traverse l1 again using p by {diff} steps
    // Then traverse l1 and l2 at the same speed by p and q.
    // If {p == q}; found the first intersection node
    // else no intersection
    int len1=0, len2=0;
    MyLinkedListNode *p, *q;
    p = l1;
    while (p != NULL) {
        len1++;
        p = p->next;
    }
    
    p = l2;
    while (p != NULL) {
        len2++;
        p = p->next;
    }
    
    int diff = abs(len1-len2);
    if (len1 > len2) {
        p = l1; q = l2;
    } else {
        q = l1; p = l2;
    }
    
    for (int i=0; i<diff; i++) {
        p = p->next;
    }
    while (p != NULL && q != NULL) {
        if (p == q) {
            return p;
        }
        p = p->next;
        q = q->next;
    }
    
    return NULL;
}

// Not clearly defined problem
MyLinkedListNode *find_intersection(MyLinkedListNode *l1, MyLinkedListNode *l2)
{
    // The different from above is we have to check if both have cycles and the cycles are identical.
    // 1. If both have no cycle, fall back to above
    // 2. If one has cycle and the other has no cycle, no intersection.
    // 3. If both have cycles
    //  Identify if both have the same cycle
    //     This can be done by starting from the one cycle start and check if the other cycle start node is same or
    //    can be reached by traverse into the cycle
    //  a. If yes, return both cycle starts
    // ?? This will ensure to find one intersection but not the one intersect first in the traverse?? 
    //  b. If no, no intersection
    MyLinkedListNode *cycleStartNode1 = cycleStart(l1), *cycleStartNode2 = cycleStart(l2);
    if (!cycleStartNode1 && !cycleStartNode2) {
        return find_intersection_no_cycle(l1, l2);
    }
    
    if (cycleStartNode1 && cycleStartNode2) {
        MyLinkedListNode *p=cycleStartNode1;
        while (p != cycleStartNode1) {
            if (p == cycleStartNode2) {
                return p;
            }
            p = p->next;
        }
    }
    
    return NULL;
    
}

// FIXME: 1-2-3-4-5-6 => 1-3-5
MyLinkedListNode *reorderInEvenOdd(MyLinkedListNode *n)
{
    return NULL;
}


// 1->2->3->2->1
bool isPalindromeList(MyLinkedListNode *L)
{
    
    return false;
}


// 1->2(Node)->3(->NULL)<-4<-5(h)
// 1->2-><-3<-4<-5(h)
// 1->2(->NULL)<-3<-4<-5(h)
// Node will be traversed from start to the end
// h will the the new header after hitting the end and all the way pass back through recursion
MyLinkedListNode *reverse_linkedlist_recur(MyLinkedListNode *node)
{
    MyLinkedListNode *h;
    if (node->next == NULL)
        return node;
    h = reverse_linkedlist_recur(node->next);
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


MyLinkedListNode *reverseLinkedlistInGroup(MyLinkedListNode *n, int k)
{
    if (k == 1 || n->next == NULL) {
        return n;
    }
    
    MyLinkedListNode *prev, *current, *tp;
    current = n;
    prev = tp = NULL;
    int cnt = 0;
    while (current != NULL && cnt < k) {
        tp = current->next;
        current->next = prev;
        prev = current;
        current = tp;
        cnt++;
    }
    
    if (current) {
        n->next = reverseLinkedlistInGroup(current, k);
    }
    
    return prev;
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

MyLinkedListNode *findInMyLinkedList(MyLinkedListNode *st, int val)
{
    MyLinkedListNode *p = st;
    while (p != NULL) {
        if (p->val == val) {
            return p;
        }
        
        p = p->next;
    }
    
    return p;
}

void removeInMyLinkedList(MyLinkedListNode *h, int val)
{
    if (h->next == NULL) {
        if (h->val == val) {
            delete h;
            h = NULL;
        }
        
        return;
    }
    
    MyLinkedListNode *p, *q;
    p = h;
    q = h->next;
    while (q != NULL) {
        if (q->val == val) {
            p->next = q->next;
            delete q;
            q = NULL;
            return;
        }
        
        p = p->next;
        q = q->next;
    }
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

void splitLinkedList2(MyLinkedListNode *h, MyLinkedListNode **n1)
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
    while (p != NULL && q != NULL && p->next != NULL) {
        p->next = q->next;
        p = q;
        q = q->next;
    }
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
    splitLinkedList2(h, &h2);
    h2 = reverse_linkedlist(h2);
    MyLinkedListNode *p = h;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = h2;
    return h;
}

MySpecialLinkedListNode *copyAndInsertNode(MySpecialLinkedListNode *h)
{
    MySpecialLinkedListNode *p = h;
    while (p != NULL) {
        MySpecialLinkedListNode *n = new MySpecialLinkedListNode(p->val);
        n->next = p->next;
        p->next = n;
        p = n->next;
    }
    
    return h;
}

void splitSpecialLinkedList(MySpecialLinkedListNode *h, MySpecialLinkedListNode **n1)
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
    MySpecialLinkedListNode *p, *q;
    p = h; q = *n1;
    while (p != NULL && q != NULL && q->next != NULL) {
        MySpecialLinkedListNode *tmp = q->next;
        p->next = q->next;
        q->next = q->next->next;
        p = tmp;
        q = q->next;
    }
    
    p->next = NULL;
}

MySpecialLinkedListNode *clone(MySpecialLinkedListNode *h)
{
    h = copyAndInsertNode(h);
    MySpecialLinkedListNode *p=h;
    while (p != NULL && p->next != NULL) {
        if (p->arbit) {
            p->next->arbit = p->arbit->next;
        } else {
            p->next->arbit = NULL;
        }
        
        p = p->next->next;
    }
    
    MySpecialLinkedListNode *h1;
    splitSpecialLinkedList(h, &h1);
    return h1;
}

MySpecialLinkedListNode *buildSpecialLinkedList()
{
    MySpecialLinkedListNode *n1 = new MySpecialLinkedListNode(-1);
    n1->arbit = n1;
   // MySpecialLinkedListNode *n2 = new MySpecialLinkedListNode(1);
    //n1->next = n2; //n1->arbit = n1;
    //n2->arbit = n2;
    return n1;
}

MyLinkedListNode *evenOddList(MyLinkedListNode *h)
{
    MyLinkedListNode *odd_cur=NULL, *cur=h, *even_h=NULL, *even_cur=NULL, *odd_h=NULL;
    while (cur != NULL) {
        if (cur->val % 2 == 0) {
            // Connect the even nodes
            if (even_cur) {
                even_cur->next = cur;
            }
            even_cur = cur;
            // Even_h will point the first even node if any
            if (!even_h) {
                even_h = cur;
            }

        } else {
            // Connect the odd nodes
            if (odd_cur) {
                odd_cur->next = cur;
            }
            odd_cur = cur;
            // Odd_h will point the first odd node if any
            if (!odd_h) {
                odd_h = cur;
            }
        }
        
        cur = cur->next;
    }
    
    // Connect the next of even node to the header of odd list
    if (even_cur) {
        even_cur->next = odd_h;
    }
    
    // Point the next of end odd node to NULL
    if (odd_cur) {
        odd_cur->next = NULL;
    }
    
    // If there is any even node return the head of even list, otherwise return header of origin
    return even_h ? even_h : h;
}

// Leetcode 328
MyLinkedListNode* evenOddList2(MyLinkedListNode *node)
{
    if (node == NULL || node->next == NULL) {
        return node;
    }
    
    MyLinkedListNode *even, *odd, *even_h, *cur;
    cur = node;
    even = NULL;
    odd = NULL;
    even_h = node->next;
    
    int index = 1;
    while (cur) {
        if (cur->val % 2) {
            if (odd) {
                odd->next = cur;
            }
            odd = cur;
        } else {
            if (even) {
                even->next = cur;
            }
            even = cur;
        }
        
        index++;
        cur = cur->next;
    }
    
    if (even) {
        even->next = node;
    }

    if (odd) {
        odd->next = NULL;
    }

    return even_h;
}

MyLinkedListNode *swapNodeInLinkedList(MyLinkedListNode *l, int val1, int val2)
{
    MyLinkedListNode n(INT_MAX);
    n.next = l;
    MyLinkedListNode *p, *q, *prev, *cur;
    p = q = NULL;
    prev = &n; cur = l;
    while (cur) {
        if (cur->val == val1) {
            p = prev;
        } else if (cur->val == val2) {
            q = prev;
        }
        
        prev = cur;
        cur = cur->next;
    }
    
    if (p && q) {
        MyLinkedListNode *cur1 = p->next, *cur2 = q->next;
        // Swap the target by change their prevs 
        p->next = cur2;
        q->next = cur1;
        // Swap the next of swap target
        MyLinkedListNode *tp = cur1->next;
        cur1->next = cur2->next;
        cur2->next = tp;
    }
    
    return n.next;
}

void skipList_test()
{
    cout << "Skip tests ---" << endl;
    SkipList sl;
    sl.insert(5);
    sl.insert(3);
    sl.insert(2);
    sl.print();
    sl.insert(1);
    sl.insert(6);
    sl.insert(4);
    sl.print();
    sl.remove(4);
    sl.print();
    assert(sl.isContains(4) == false);
    assert(sl.isContains(3) == true);
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
    
    cout << "Remove val 3 ---" << endl;
    removeInMyLinkedList(h, 3);
    printLinkedList(h);
    
    cout << "Reverse linked list ---" << endl;
    h = reverse_linkedlist(h);
    printLinkedList(h);
    
    h = reverseLinkedlistInGroup(h, 2);
    printLinkedList(h);
    
    h = zip(h);
    cout << "Zip h ---" << endl;
    printLinkedList(h);
    h = unzip(h);
    cout << "Unzip h ---" << endl;
    printLinkedList(h);
    
    cout << "Clone special linked list ===" << endl;
    MySpecialLinkedListNode *sh = buildSpecialLinkedList();
    MySpecialLinkedListNode *cloned = clone(sh);
    MySpecialLinkedListNode *p;
    p = cloned;
    while (p != NULL) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;
    
    p = cloned;
    while (p != NULL) {
        if (!p->arbit) {
            cout << "# ";
        } else {
            cout << p->arbit->val << " ";
        }
        p = p->next;
    }
    cout << endl;
    
    cout << "even odd reorg ---" << endl;
    h = buildLinkedListRecur(a, 0);
    printLinkedList(evenOddList(h));
    a = {1,3,5,7,9};
    h = buildLinkedListRecur(a, 0);
    printLinkedList(evenOddList(h));
    a = {2,4,6,8,10};
    h = buildLinkedListRecur(a, 0);
    printLinkedList(evenOddList(h));
    a = {2,4,6,8,10,1,3,5,7,9};
    h = buildLinkedListRecur(a, 0);
    printLinkedList(evenOddList(h));
    a = {1,3,5,7,9,2,4,6,8,10};
    h = buildLinkedListRecur(a, 0);
    printLinkedList(evenOddList(h));
    h = buildLinkedListRecur(a, 0);
    printLinkedList(h);
    h = swapNodeInLinkedList(h, 10, 3);
    cout << "Swap 3 and 4 --- " << endl;
    printLinkedList(h);
    skipList_test();
}
