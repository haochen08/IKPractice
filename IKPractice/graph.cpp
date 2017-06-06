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
        if (n->visitStatus == NotVisited) {
            n->visitStatus = Visited;
            dfs_recur(n);
        }
    }
}

void dfs(MyGraph *g)
{
    for (MyVertex *v:g->adjacent_list) {
        if (v->visitStatus == NotVisited) {
            v->visitStatus = Visited;
            dfs_recur(v);
        }
    }
    
    cout << endl;
}

bool hasCycleRecur(MyVertex *v)
{
    v->visitStatus = Visiting;
    for (MyVertex *n:v->neighbors) {
        if (n->visitStatus == Visiting) {
            return true;
        } else if (n->visitStatus == NotVisited){
            if (hasCycleRecur(n)) {
                return true;
            }
            
            // Should not return if we haven't found any cycle
            // since we haven't reached the end of dfs starting from root
        }
    }
    
    v->visitStatus = Visited;
    return false;
}

bool hasCycle(MyGraph &g)
{
    for (MyVertex *v: g.adjacent_list) {
        if (v->visitStatus == NotVisited) {
            if (hasCycleRecur(v)) {
                return true;
            }
        }
    }
    
    return false;
}

// visited = -1 // Not a valid node
// visited = 0 // Not visited
// visited = 1 // Visited
// Visited = 2 // visiting
bool dfs(bool adj[][26], int *visited, string &order, int root)
{
    visited[root] = 2;
    for (int i=0; i<26; i++) {
        if (adj[root][i]) {
            if (visited[i] == 2) {
                return false;
            } else if (visited[i] == 0) {
                if (!dfs(adj, visited, order, i)) {
                    return false;
                }
            }
        }
    }
    
    visited[root] = 1;
    order += root+'a';
    return true;
}

// leetcode 269
string alienDict(vector<string> &dict)
{
    static int N=26;
    bool adj[N][26];
    int visited[N];
    
    for (int i=0; i<N; i++) {
        visited[i] = -1;
        for (int j=0; j<26; j++) {
            adj[i][j] = false;
        }
    }

    // build graph
    for (int i=0; i<dict.size(); i++) {
        string word1 = dict[i];
        for (char c:word1) {
            visited[c-'a'] = 0;
        }
        
        if (i > 0) {
            string word0 = dict[i-1];
            int len = min(word0.length(), word1.length());
            for (int j=0; j<len; j++) {
                char c1 = word0[j]-'a';
                char c2 = word1[j]-'a';
                if (c1 != c2) {
                    adj[c1][c2] = true;
                    // This is key step "wke" -> "wla"
                    // k->l is right, but e->a is wrong
                    break;
                }
            }
        }
    }
    
    string res;
    for (int i=0; i<N; i++) {
        if (visited[i] == 0) {
            if (!dfs(adj, visited, res, i)) {
                return "";
            }
        }
    }
    
    std::reverse(res.begin(), res.end());
    return res;
}

void graph_test() {
    vector<int> labels = {0,1,2,3};
    MyGraph g(labels);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.print();
    //dfs(&g);
    hasCycle(g) ? cout << "has cycle" << endl : cout << "not have cycle" << endl;
}
