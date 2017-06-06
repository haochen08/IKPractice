//
//  graph.hpp
//  IKPractice
//
//  Created by Hao Chen on 11/11/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <vector>

typedef enum {
    NotVisited,
    Visiting,
    Visited,
} VertexVisitStatus;


class MyVertex
{
public:
    VertexVisitStatus visitStatus;
    int label;
    std::vector<MyVertex *> neighbors;
    MyVertex(int _label):label(_label),visitStatus(NotVisited) {};
    void addEdge(MyVertex *dst);
};


class MyGraph {
public:
    std::vector<MyVertex *> adjacent_list;
    MyGraph(std::vector<int> labels);
    void addEdge(int src, int dst);
    void print();
};

void dfs(MyGraph *g);

bool hasCycle(MyGraph *g);

void graph_test();

#endif /* graph_hpp */
