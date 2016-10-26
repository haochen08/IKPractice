//
//  my_string.cpp
//  Lesson-1
//
//  Created by Hao Chen on 10/24/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#include "my_string.hpp"

using namespace std;

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
