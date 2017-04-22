//
//  main.cpp
//  Project1Experiments
//
//  Created by Seth Weston on 4/21/17.
//  Copyright © 2017 Seth Weston. All rights reserved.
//

#include <iostream>



//METHOD 1: Brute force//

/*
 MaxSumBruteForce(path, a, arraySize, arrayCount);
 Determines max sub array and sub array indices by
 holding the current best sum and testing against every possible subarray
 */

void MaxSumBruteForce(int * a, int size)
{
    int ret = a[0];
    int sum = 0;
    int MaxSumStart = 0;
    int MaxSumEnd = 0;
    
    for (int i = 0; i <= size-2; i++)
    {
        sum = 0;
        for (int j = i; j <= size - 1; j++)
        {
            sum = sum + a[j];
            if (sum > ret)
            {
                MaxSumStart = i;
                MaxSumEnd = j;
                ret = sum;
            }
        }
    }
}

//METHOD 2: Improved Brute force//
/*
 *
 */
void MaxSumImprovedBruteForce(int * a, int size)
{
    
    int ret = a[0];
    int MaxSumStart = 0, MaxSumEnd = 0;
    
    for( int i = 1; i < size; i++)
    {
        int sum = 0;
        int j = i;
        int tempStart = MaxSumStart;
        while(j>=tempStart)
        {
            sum += a[j];
            if ( sum > ret )
            {
                ret = sum;
                MaxSumStart = j;
                MaxSumEnd = i;
            }
            j--;
        }
    }
    
}
int main(int argc, const char * argv[]) {
    
    int arraySize = 1000;
    int numTrials = 10;
    int a[arraySize];
    clock_t t;
    
    //seed random number generator 
    srand (time(NULL));
    //generate array of random numbers of size arraySize
    for (int i = 0; i<arraySize; i++) {
        a[i] = rand();
    }
    
    for(int j = 0; j<numTrials; j++)
    {
        t = clock();
        //insert function here for timing analysis
        MaxSumBruteForce(a, arraySize);
        t = clock() - t;
        //print time to determine max sub array
        std::cout<<((float)t)/CLOCKS_PER_SEC<<"\n\n";
    }


    return 0;
}
