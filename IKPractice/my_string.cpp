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

void reverse_recur(string &s, int i, int j)
{
    if (i >= j) {
        return;
    }
    
    reverse_recur(s, i+1, j-1);
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
}

void reverse_str(string &s)
{
    reverse_recur(s, 0, s.length()-1);
}

// "god is good" => "good is god"
string reverse_words(string & sentence)
{
    reverse_str(sentence);
    int i=0, j=0;
    for (i=0; i<sentence.length(); i++) {
        if (sentence[i] == ' ') {
            if (i-1 > j) {
                reverse_recur(sentence, j, i-1);
            }
            j = i+1;
        }
    }
    
    if (i-1 > j) {
        reverse_recur(sentence, j, i-1);
    }
    
    return sentence;
}

// The idea is
// Two hashmaps
// One from pattern->last occurence pos
// One from string->last occurence pos
// If str matches the pattern,
// 1. the size of the two maps should be identical.
// 2. when we linearly scan the string, the last pos should be identical
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

// substring start at st, len is ed-st
std::pair<string, int> encodeString(std::string &str, std::vector<std::vector<std::pair<string, int>>> &result, std::vector<std::vector<bool>> &mem, int st, int ed)
{
    if (st > ed) {
        return {"", -1};
    }
    
    if (mem[st][ed]) {
        return result[st][ed];
    }
    
    if (st == ed) {
        mem[st][ed] = true;
        result[st][ed] = {str.substr(st,1), 1};
        return result[st][ed];
    }
    
    int min_len = INT_MAX;
    for (int i=st; i<ed; i++) {
        pair<string, int> tmp;
        pair<string, int> left = encodeString(str, result, mem, st, i);
        pair<string, int> right = encodeString(str, result, mem, i+1, ed);
        if (left.first.length()>0 && right.first.length()>0) {
            if (left.first == right.first) {
                tmp = {left.first, left.second+right.second};
            } else {
                tmp = {left.first+right.first, 1};
            }
        } else if (left.first.length() == 0) {
            tmp = right;
        } else {
            tmp = left;
        }
        
        if (tmp.first.length() > 0 && tmp.first.length() < min_len) {
            min_len = tmp.first.length();
            result[st][ed] = tmp;
        }
    }
    
    mem[st][ed] = true;
    return result[st][ed];
}

void string_tests() {
    vector<vector<char>> board = {{'o','a', 'a','n'}, {'e','t','a','e'}, {'i','h','k','r'},{'i','f','l','v'}};
    vector<string> words = {"oath","pea","eat","rain"};
    vector<string> res = findWords(board, words);
    for (string s:res) {
        cout << s << endl;
    }
    
    vector<vector<bool>> mem;
    vector<vector<pair<string, int>>> result;
    string test_string = "abcabcabccdfcdfcdf";
    int size = test_string.length();
    result.resize(size);
    for (auto &e:result) {
        e.resize(size);
    }
    mem.resize(size);
    for (auto &e:mem) {
        e.resize(size);
    }
    
    pair<string, int> res2 = encodeString(test_string, result, mem, 0, size-1);
    cout << "encode string:" << res2.second << res2.first << endl;
    
    cout << "pattern match = " << wordPattern("abba", "dog cat cat dog") << endl;
    string sentence = "There is good way to do this stuff";
    cout << "reverse words in sentence of 'There is good way to do this stuff' is '" << reverse_words(sentence) << "'" << endl;

}

