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
#include "recursion.hpp"

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

MyTrieForPalins buildTrieOnReverseOfStrings(vector<string> &strings)
{
    MyTrieForPalins trie;
    for (int i=0; i<strings.size(); i++) {
        string s = strings[i];
        MyTrieForPalins *cur = &trie;
        for (int j=s.length()-1; j>=0; j--) {
            // check the suffix of string is palindrome or not
            if (isPalindrome(s, 0, j)) {
                cur->palins.push_back(i);
            }
            
            int idx = s[j]-'a';
            if (!cur->next[idx]) {
                cur->next[idx] = new MyTrieForPalins();
            }

            cur = cur->next[idx];
        }
        cur->pos = i;
        // "" is also palindrome
        // This is to match abcd and dcba
        cur->palins.push_back(i);
    }
    
    return trie;
}

vector<pair<int, int>> palindromePairs(vector<string> &strings)
{
    // 1. Scan the strings and build trie on the reverse of string
    // 1.1 Store the index where the palindrome substring begins
    // 2. Scan the strings
    // 2.1 Scan each string from the start, attemp to match another element on trie
    // 2.2 Check if the remainder is palindrome (it could be empty here); if yes add both string index into vector
    // O(nk^2)
    MyTrieForPalins trie = buildTrieOnReverseOfStrings(strings);
    vector<pair<int, int>>  res;
    for (int i=0; i<strings.size(); i++) {
        string s = strings[i];
        int j = 0;
        MyTrieForPalins *cur = &trie;
        while (cur && j < s.length()) {
            // If we hit a word in list and the word is NOT the one being scanned
            // and the remainder of scanned one is palindrome
            // e.g. abc[xyx]  => cba(abc in trie)
            if (cur->pos >=0 && cur->pos != i && isPalindrome(s, j, s.length()-1)) {
                res.push_back({i,cur->pos});
            }
            cur = cur->next[s[j]-'a'];
            j++;
        }
        
        if (cur) {
            for (int pos:cur->palins) {
                if (pos != i) {
                    res.push_back({i, pos});
                }
            }
        }
    }
    
    return res;
}

string getOneLine(vector<string> &strings, int L, int st, int ed)
{
    if (st > ed) {
        // strings is empty
        return string(L, ' ');
    }
    
    if (st == ed) {
        // the only word on the line
        return strings[st]+string(L - strings[st].length(),' ');
    }
    
    string s;
    int len_of_all_strings = 0;
    for (int i = st; i <= ed; i++) {
        len_of_all_strings += strings[i].length();
    }
    
    int extra_spaces_no = (L-len_of_all_strings) / (ed-st);
    int pos_to_add_one_extra_space = (L-len_of_all_strings) % (ed-st);
    if (ed == strings.size()-1) {
        extra_spaces_no = 1;
        pos_to_add_one_extra_space = -1;
    }
    
    s += strings[st];
    for (int i=st+1; i<=ed; i++) {
        s += string(extra_spaces_no, ' ');
        if (i - st <= pos_to_add_one_extra_space) {
            s += ' ';
        }
        s += strings[i];
    }
    
    //  Special logic for the last line processing
    if (ed == strings.size()-1) {
        s += string(L-s.length(), ' ');
    }
    return s;
}

vector<string> textJustify(vector<string> &strings, int L)
{
    // 1. Scan strings
    // a. s
    // Edge cases
    // a. Add all spaces to the end for last line
    // b. If there is only one word in line, add all spaces after it to the end
    int prev=0, len=-1;
    vector<string> res;
    for (int i=0; i<strings.size(); i++) {
        // Why +1 always, how about the last word without space
        if (len+1+strings[i].length() <= L) {
            len += 1+strings[i].length();
        } else {
            // get the line
            res.push_back(getOneLine(strings, L, prev, i-1));
            len = strings[i].length();
            prev = i;
        }
    }
    
    // The last line
    res.push_back(getOneLine(strings, L, prev, strings.size()-1));
    
    return res;
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

    vector<string> strings = {"", "daad", "lls", "s", "sssll"};
    vector<pair<int, int>> res1 = palindromePairs(strings);
    cout << "res of palindromePairs is:";
    for (auto &e:res1) {
        cout << "{" << e.first << "," << e.second << "}";
    }
    
    cout << endl;
    
    strings = {"This", "is", "an", "example", "of", "text", "justification."};
    res = textJustify(strings, 16);
    for (string &e:res) {
        cout << e << "," << endl;
    }
}

