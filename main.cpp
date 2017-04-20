/*
 * C++ Program to Find the maximum subarray sum O(n^2)
 * time(naive method)
 */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>

//#include <conio.h>
using namespace std;

//Max array size is 26 based on txt file
const int MAX_ARRAY_SIZE = 100;

int main()
{
    //line of text that holds each array
    string line;
    //sum holds sum, arraySize holds size of current array
    int sum = 0, ret = 0, arrayCount=0, arraySize = 0;
    
    //initialize array to 0 values
    int a[MAX_ARRAY_SIZE] = {0};
    
    //open MSS_Problems.txt file (will need to change file path obvioiusly)
    ifstream myfile( "/Users/westonse/Library/Autosave Information/Project1/Project1/MSS_Problems.txt" );
    
    //if file is valid open it
    if(myfile)
    {
        //parse the file line by line
        while(getline(myfile,line))
        {
            //increment arrayCount in case we need to keep track
            arrayCount++;
            //convert line to a stream object
            std::stringstream stream(line);
            //parse each array to determine size
            while(1) {
                int n;
                stream >> n;
                //once size of array is found parse the current array and determine max subarray
                if(!stream)
                {
                    //METHOD 1: Brute force//
                    //Currently only determines maximum sum
                    //Need to also determine the sub array
                    for (int i = 0; i <= arraySize-2; i++)
                    {
                        sum = 0;
                        for (int j = i; j <= arraySize - 1; j++)
                        {
                            sum = sum + a[j];
                            if (sum > ret)
                            {
                                
                                ret = sum;
                            }
                        }
                    }
                    //Currently displaying results to console (for ease)
                    //Need to display results in txt file for final submission
                    cout<<"Maximum subarray sum:"<<ret<<"\n";
                    std::fill_n(a, arraySize, 0);
                    sum = 0;
                    ret = 0;
                    arraySize = 0;
                    break;
                    
                }
                a[arraySize] = n;
                arraySize++;
                
            }

        }
    }
    myfile.close();
    return 0;
}