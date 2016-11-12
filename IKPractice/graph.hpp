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

class MyVertex
{
public:
    bool visited;
    int label;
    std::vector<MyVertex *> neighbors;
    MyVertex(int _label):label(_label),visited(false) {};
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

#endif /* graph_hpp */
