//
//  my_string.hpp
//  Lesson-1
//
//  Created by Hao Chen on 10/24/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#ifndef my_string_hpp
#define my_string_hpp

#include <string>
#include <vector>

class MyTrie {    
public:
    MyTrie *next[26];
    std::string word;
    MyTrie()
    {
        for (int i=0;i<26;i++) {
            next[i] = NULL;
        }
        word = "";
    }
};

class MyTrieForPalins : public MyTrie {
public:
    std::vector<int> palins;
    int pos;
    MyTrieForPalins *next[26];
    MyTrieForPalins() {
        MyTrie();
        for (int i=0;i<26;i++) {
            next[i] = NULL;
        }
        pos = -1;
    }
};


void rotateString(std::string &s);
MyTrie buildTrie(std::vector<std::string> dictionary);
// leetcode 212
std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words);
void split_strings(std::string s, std::vector<std::string> &string_list, std::string delimiter);
bool wordPattern(std::string pattern, std::string str);
void string_tests();
#endif /* my_string_hpp */
