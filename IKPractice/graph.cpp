//
//  graph.cpp
//  IKPractice
//
//  Created by Hao Chen on 11/11/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include "graph.hpp"

using namespace std;

void MyVertex::addEdge(MyVertex *dst)
{
    this->neighbors.push_back(dst);
}


MyGraph::MyGraph(vector<int> labels)
{
    for (int l:labels) {
        MyVertex *v = new MyVertex(l);
        this->adjacent_list.push_back(v);
    }
}

void MyGraph::addEdge(int src, int dst)
{
    MyVertex *src_vertex = NULL, *dst_vertex = NULL;
    for (MyVertex *v : this->adjacent_list)
    {
        if (v->label == src) {
            src_vertex = v;
        }
        
        if (v->label == dst) {
            dst_vertex = v;
        }
    }
    
    if (src_vertex && dst_vertex) {
        src_vertex->addEdge(dst_vertex);
    }
}

void MyGraph::print()
{
    for (MyVertex *v: this->adjacent_list) {
        cout << v->label << ":";
        for (MyVertex *n:v->neighbors) {
            cout << n->label << " ";
        }
        cout << endl;
    }
}

void dfs_recur(MyVertex *v)
{
    cout << v->label << " ";
    for (MyVertex *n: v->neighbors) {
        if (!n->visited) {
            n->visited = true;
            dfs_recur(n);
        }
    }
}

void dfs(MyGraph *g)
{
    for (MyVertex *v:g->adjacent_list) {
        if (!v->visited) {
            v->visited = true;
            dfs_recur(v);
        }
    }
    
    cout << endl;
}

void dfs(bool adj[][26], bool visited[], vector<string> &order)
{
    
    
}

// leetcode 269
vector<string> alienDict(vector<string> &dict)
{
    bool adj[26][26];
    bool visited[26];
    
    memset(visited, false, 26);
    // build graph
    for (int i=0; i<dict.size(); i++) {
        string word1 = dict[i];
        for (char c:word1) {
            visited[c-'a'] = false;
        }
        
        if (i > 0) {
            string word0 = dict[i-1];
            int len = min(word0.length(), word1.length());
            for (int j=0; j<len; j++) {
                adj[word0[j]-'a'][word1[j]-'a'] = true;
            }
        }
    }
    
    vector<string> res;
    dfs(adj, visited, res);
}
