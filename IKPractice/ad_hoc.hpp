//
//  ad_hoc.hpp
//  Lesson-1
//
//  Created by Hao Chen on 10/23/16.
//  Copyright © 2016 HaoChen. All rights reserved.
//

#ifndef ad_hoc_hpp
#define ad_hoc_hpp

#include <stdio.h>

// Given the array, shuffle the array so that every element is with equally likely
// ? Random generator
// Brutal
// 1. Generate all perm
// 2. User random generator [0..N!] to get the index
// T: N!
// S: N*N!
void shuffle_array_in_equally_likely(int a[], int m);

// Merge the interval


#endif /* ad_hoc_hpp */
