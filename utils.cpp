//
//  utils.cpp
//  projet
//
//  Created by Etienne Dejoie on 05/01/2016.
//
//

#include <stdio.h>
#include <vector>
using namespace std;

float sum(vector<float> titi){
    
    float sum_of_elems = 0.0;
    for (float n : titi)
        sum_of_elems += n;
    
    return sum_of_elems;
}








