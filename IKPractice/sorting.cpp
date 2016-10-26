//
//  sorting.cpp
//  Lesson-1
//
//  Created by Hao Chen on 9/9/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include "sorting.hpp"

#include <iostream>
#include <vector>
#include <regex>
#include <map>
#include <string>

using namespace std;

uint dist_square(point p, point q)
{
    return (p.x-q.x)*(p.x-q.x) + (p.y-q.y)*(p.y-q.y);
}

void swap(point &p, point &q)
{
    uint tp;
    tp = p.x;
    p.x = q.x;
    q.x = tp;
    
    tp = p.y;
    p.y = q.y;
    q.y = tp;
}

uint partition(vector<int> &elements, int low, int high)
{
    uint i = low, j = high+1;
    int pivot = elements[low];
    while (true) {
        do {
            i++;
        } while (elements[i] < pivot && i <= high);
        
        do {
            j--;
        } while (elements[j] > pivot && j >= low);
        
        if (i > j) {
            break;
        }
        
        swap(elements[i], elements[j]);
    }
    
    swap(elements[low], elements[j]);
    return j;
}

uint partition(vector<point> &elements, int low, int high, point pt)
{
    uint i = low+1;
    point pivot = elements[low];
    for (uint j=low+1; j<=high; j++) {
        if (dist_square(elements[j], pt) <= dist_square(pivot, pt)) {
            swap(elements[j], elements[i]);
            i++;
        }
    }
    
    swap(elements[low], elements[i-1]);
    
    return i-1;
}

void quick_sort(vector<int> &elements, uint low, uint high)
{
    if (low <= high) {
        int p = partition(elements, low, high);
        quick_sort(elements, low, p-1);
        quick_sort(elements, p+1, high);

    }
}

vector<int> quick_sort_k(vector<int> &elements, uint low, uint high, uint k)
{
    if (low <= high) {
        int p = partition(elements, low, high);
        if (k == p+1) {
            vector<int> res(k);
            copy(elements.begin(), elements.begin()+k, res.begin());
            return res;
        }
        
        if (k > p+1) {
            return quick_sort_k(elements, p+1, high, k);
        } else {
            return quick_sort_k(elements, low, p-1, k);
        }
    }
    
    return {};
}

vector<point> quick_sort_k_nearest(std::vector<point> &elements, uint low, uint high, point pt, uint k)
{
    if (low <= high) {
        int p = partition(elements, low, high, pt);
        if (k == p) {
            vector<point> res(k);
            copy(elements.begin(), elements.begin()+k, res.begin());
            return res;
        }
        
        if (k > p) {
            return quick_sort_k_nearest(elements, p+1, high, pt, k);
        } else {
            return quick_sort_k_nearest(elements, low, p-1, pt, k);
        }
    }
    
    return {};
}

void merge_sort(vector<int> &elements, uint l, uint h)
{
    if (l >= h) {
        return;
    } else if (l+1 == h) {
        if (elements[l] > elements[h]) {
            swap(elements[l], elements[h]);
        }
        
        return;
    }
    
    uint r = (h-l)/2+l;
    merge_sort(elements, l, r);
    merge_sort(elements, r+1, h);
    
    vector<int> left(begin(elements)+l, begin(elements)+r+1);
    vector<int> right(begin(elements)+r+1, begin(elements)+h+1);
    
    auto it_left = left.begin();
    auto it_right = right.begin();
    while (it_left != left.end() && it_right != right.end()) {
        if (*it_left < *it_right) {
            elements[l] = *it_left;
            it_left++;
        } else {
            elements[l] = *it_right;
            it_right++;
        }
        l++;
    }
    
    copy(it_left, end(left), begin(elements)+l);
    copy(it_right, end(right), begin(elements)+l);
}

void heapifyDown(vector<int> &elements, uint i, uint size)
{
    uint l = 2*i+1, r = 2*i+2;
    
    uint min = i;
    if (l < size && elements[min] > elements[l]) {
        min = l;
    }
    
    if (r < size && elements[min] > elements[r]) {
        min = r;
    }
    
    if (min != i) {
        swap(elements[min], elements[i]);
        heapifyDown(elements, min, size);
    }
}

void heapifyDown(std::vector<heap_node> &elements, uint i, uint size)
{
    uint l = 2*i+1, r = 2*i+2;
    uint min = i;
    if (l < size && elements[min].val > elements[l].val) {
        min = l;
    }
    
    if (r < size && elements[min].val > elements[r].val) {
        min = r;
    }
    
    if (min != i) {
        swap(elements[min], elements[i]);
        heapifyDown(elements, min, size);
    }
}

void heapifyUp(vector<int> &elements, int i)
{
    if (i == 0) {
        return;
    }
    
    uint p = (i-1)/2;
    if (elements[i] < elements[p]) {
        swap(elements[i], elements[p]);
        heapifyUp(elements, p);
    }
}

void heapifyUp(vector<heap_node> &elements, int i)
{
    if (i == 0) {
        return;
    }
    
    uint p = (i-1)/2;
    if (elements[i].val < elements[p].val) {
        swap(elements[i], elements[p]);
        heapifyUp(elements, p);
    }
}

void heap_insert(vector<int> &heap, int i)
{
    heap.reserve(heap.size()+1);
    heap.push_back(i);
    heapifyUp(heap, (uint)heap.size()-1);
}

void heap_insert(std::vector<heap_node> &heap, heap_node node)
{
    heap.reserve(heap.size()+1);
    heap.push_back(node);
    heapifyUp(heap, (uint)heap.size()-1);
}


vector<int> buildHeapify(vector<int> &elements)
{
    vector<int> heap;
    heap.reserve(elements.size());
    for (int item:elements) {
        heap.push_back(item);
        if (heap.size() > 1) {
            heapifyUp(heap, (int)heap.size()-1);
        }
    }
    
    return heap;
}

void heap_sort(vector<int> &elements)
{
    vector<int> heap = buildHeapify(elements);
    
    uint index = 0;
    uint heap_size = (uint)heap.size();
    while (heap_size > 0) {
        int min = heap[0];
        elements[index++] = min;
        swap(heap[0], heap[heap_size-1]);
        heap_size--;
        heapifyDown(heap, 0, heap_size);
    }
}
