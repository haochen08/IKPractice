//
//  my_string.cpp
//  Lesson-1
//
//  Created by Hao Chen on 10/24/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include <unordered_map>
#include <iostream>
#include "my_string.hpp"

using namespace std;


void rotateString(string &s)
{
    char tp = s[0];
    int i=0;
    for (i=0; i<s.length()-1; i++) {
        s[i] = s[i+1];
    }
    s[i] = tp;
}

void buildTrie(std::vector<std::string> &dictionary, MyTrie &trie)
{
    for (string s:dictionary) {
        MyTrie *p = &trie;
        for (int i=0; i<s.size(); i++) {
            char c = s[i]-'a';
            if (p->next[c] == NULL) {
                p->next[c] = new MyTrie();
            }
            p = p->next[c];
        }
        p->word = s;
    }
}

void findWordRecur(vector<vector<char>>& board, int i, int j, MyTrie *trie, vector<string> &res)
{
    // 2D matrix boundary
    if (i<0 || i>=board.size() || j<0 || j>=board[i].size()) {
        return;
    }
    
    char c=board[i][j];
    // visited
    if (c == '#')
        return;
    // Can't form word in dictionary
    if (trie->next[c-'a'] == NULL)
        return;

    
    trie = trie->next[c-'a'];
    if (trie->word.length() > 0) {
        res.push_back(trie->word);
        // De-dup
        trie->word = "";
        // Should not return since since longer string along the path may match
    }
    
    board[i][j] = '#';
    findWordRecur(board, i+1, j, trie, res);
    findWordRecur(board, i-1, j, trie, res);
    findWordRecur(board, i, j+1, trie, res);
    findWordRecur(board, i, j-1, trie, res);
    board[i][j] = c;
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    MyTrie trie;
    buildTrie(words, trie);
    
    vector<string> res;
    MyTrie *p = &trie;
    for (int i=0;i<board.size();i++) {
        for (int j=0;j<board[i].size();j++) {
            findWordRecur(board, i, j, p, res);
        }
    }
    
    return res;
}

bool is_delimiter(char c, string delimiter)
{
    for (char e:delimiter) {
        if (c == e) {
            return true;
        }
    }
    
    return false;
}

void split_strings(std::string s, std::vector<std::string> &string_list, std::string delimiter)
{
    string cur;
    for (char c : s) {
        if (is_delimiter(c, delimiter)) {
            if (!cur.empty()) {
                string_list.push_back(cur);
                cur.clear();
            }
            continue;
        }
        
        cur += c;
    }
    
    string_list.push_back(cur);
    
    // Another way to do it is introducing two pointers to mark the start and end of the string
}

bool wordPattern(string pattern, string str) {
    unordered_map<char, int> map1;
    unordered_map<string, int> map2;
    vector<string> splitted;
    split_strings(str, splitted, " ");
    if (pattern.size() != splitted.size()) return false;
    for (int i=0; i<pattern.size(); i++) {
        if (map1.find(pattern[i]) != map1.end() || map2.find(splitted[i]) != map2.end())   {
            if (map1[pattern[i]] != map2[splitted[i]]) {
                return false;
            }
        } else {
            map1[pattern[i]] = map2[splitted[i]] = i+1;
        }
    }
    
    return true;
}

void string_tests() {
    vector<vector<char>> board = {{'o','a', 'a','n'}, {'e','t','a','e'}, {'i','h','k','r'},{'i','f','l','v'}};
    vector<string> words = {"oath","pea","eat","rain"};
    vector<string> res = findWords(board, words);
    for (string s:res) {
        cout << s << endl;
    }
    
    cout << "pattern match = " << wordPattern("abba", "dog cat cat dog") << endl;
    

}

