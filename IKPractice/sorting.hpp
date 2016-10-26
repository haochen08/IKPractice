//
//  sorting.hpp
//  Lesson-1
//
//  Created by Hao Chen on 9/9/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#ifndef sorting_hpp
#define sorting_hpp

#include <vector>
#include <sys/types.h>

struct heap_node {
    uint x,y;
    int val;
};

class point {
public:
    int x,y;
    point():x(0),y(0){};
    point(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

std::vector<int> quick_sort_k(std::vector<int> &elements, uint low, uint high, uint k);
std::vector<point> quick_sort_k_nearest(std::vector<point> &elements, uint low, uint high, point pt, uint k);
void quick_sort(std::vector<int> &elements, uint low, uint high);
void merge_sort(std::vector<int> &elements, uint low, uint high);
void heap_sort(std::vector<int> &elements);
void heap_insert(std::vector<int> &heap, int i);
void heap_insert(std::vector<heap_node> &heap, heap_node node);

void heapifyDown(std::vector<int> &elements, uint i, uint size);
void heapifyDown(std::vector<heap_node> &elements, uint i, uint size);

#endif /* sorting_hpp */
