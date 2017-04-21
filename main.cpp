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

//Function for Divide and Conquer Call WIP.
int dnc(int array[100], int start, int end, int *max, int *maxStart, int *maxEnd){
//This section to test inputs.
cout << "\nsize of array is " << end << "\n";
cout << "passed in value of max is " << *max << "\n";
cout << "position of max is " << max << "\n";
cout << "the first element in the array is " << array[start] << "\n\n";
cout << "\n" << *maxStart << " " << *maxEnd << "\n";

}

int main()
{
    //line of text that holds each array
    string line;
    //sum holds sum, arraySize holds size of current array
    int sum = 0, ret = 0, arrayCount=0, arraySize = 0;
    
    //subarray start and end positions
    int MaxSumStart = 0;
    int MaxSumEnd = 0;
 
    //initialize array to 0 values
    int a[MAX_ARRAY_SIZE] = {0};
    
    //open MSS_Problems.txt file (will need to change file path obvioiusly)
    ifstream myfile( "./MSS_Problems.txt" );
    
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
		//METHOD 3: Divide and Conquer
			int maxSum=0;
			dnc(a,0,arraySize-1,&maxSum, &MaxSumStart, &MaxSumEnd);
			maxSum=0;
                    //METHOD 1: Brute force//
                    //Currently only determines maximum sum
                    //Need to also determine the sub array
                    for (int i = 0; i <= arraySize-2; i++){
                        sum = 0;
                        for (int j = i; j <= arraySize - 1; j++){
                            sum = sum + a[j];
                            if (sum > ret){
                                MaxSumStart = i;
                                MaxSumEnd = j;
                                ret = sum;
                            }
                        }
                    }
                    //Currently displaying results to console (for ease)
                    //Need to display results in txt file for final submission
                    cout<<"Maximum subarray sum:"<<ret<<"\n";
                    cout<< "Max Sum Start Index: " << MaxSumStart << "  Max Sum End Index : " << MaxSumEnd << "\n";
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
