//
//  RadixSort
//
//  Created by Sunil Sharma on 09/10/16.
//  Copyright © 2016 Sunil Sharma. All rights reserved.
//

#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <vector>

void radixSort(int array[], int len) {
    const int COLUMS = len + 1;
    int *storer = new int[10 * COLUMS];
    bool bNoLargerInt = false;
    int checkingRadix = 0;
    while (!bNoLargerInt) {
        bNoLargerInt = true;
        for (int i = 0; i < len; i ++) {
            int leftValueAfterMuti = (array[i] / pow(10, checkingRadix));
            int theRadix = leftValueAfterMuti % 10;
            if (leftValueAfterMuti != 0) {
                bNoLargerInt = false;
            }
            storer[theRadix * COLUMS + storer[theRadix * COLUMS] + 1] = array[i];
            storer[theRadix * COLUMS] ++;
        }
        checkingRadix ++;
        
        //set the newly sorted result backto 'array'
        int cursor = 0;
        for (int i = 0; i < 10; i ++) {
            for (int j = 1; j <= storer[i * COLUMS]; j ++) {
                array[cursor] = storer[i * COLUMS + j];
                cursor ++;
            }
            //reset the adding point of every row to 1, that means adding element to row will be started from 1, rather than 0, becuse at 0 there is the adding point record.
            storer[i * COLUMS] = 0;
        }
    }
}

int main() {
    srand(time(NULL));
    const int TESTED_ARRAY_LEN = 1000;
    const int INT_RANGE_BELOW = 100000;
    int *array = new int[TESTED_ARRAY_LEN];
    for (int i = 0; i < TESTED_ARRAY_LEN; i ++) {
        array[i] = rand() % INT_RANGE_BELOW;
    }
    
    // get the result through our way.
    radixSort(array, TESTED_ARRAY_LEN);
    
    // get the result through the standard way.
    std::vector<int> v(array, array + TESTED_ARRAY_LEN);
    std::sort(v.begin(), v.end());
    
    // compare them
    for (int i = 0; i < TESTED_ARRAY_LEN; i ++) {
        assert(v[i] == array[i]);
        std::cout << array[i] << ", ";
    }
}