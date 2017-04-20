#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>

//#include <conio.h>
using namespace std;

//Max array size is 26 based on txt file
const int MAX_ARRAY_SIZE = 100;

int main(int argc, char** argv)
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
    
    //open MSS_Problems.txt file (user inputs file name from command line)
    std::string path = argv[1];
    std::string filename = path + "MSS_Problems.txt";
    ifstream myfile(filename);
    
    //if file is valid open it
    if(myfile)
    {
        //parse the file line by line
        while(getline(myfile,line))
        {
            //increment arrayCount to keep track of number of arrays in file 
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
                     /*
                     * C++ Program to Find the maximum subarray sum O(n^2)
                     * time(naive method)
                     */
                     //Determines max sub array and sub array indices
                    for (int i = 0; i <= arraySize-2; i++)
                    {
                        sum = 0;
                        for (int j = i; j <= arraySize - 1; j++)
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
                    
                    //Output results to MSS_Results.txt using path given by user
                    std::string path = argv[1];
                    std::string filename2 = path + "MSS_Results.txt";
                    ofstream myfile2;
                    if(arrayCount>1)
                    {
                        myfile2.open (filename2, ios::app);
                    }
                    else
                    {
                        myfile2.open (filename2);
                    }
                    myfile2 <<"ARRAY "<< arrayCount << " RESULTS\n\n"<<"Maximum subarray sum:"<<ret<<"\n"<<"Max Sum Start Index: " << MaxSumStart << "  Max Sum End Index : " << MaxSumEnd << "\n\n";
                    myfile2.close();
    
                    //reset variables to 0 and break
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
    else
    {
        myfile.close();
        cout<<"File not valid exiting program\n";
        return -1;
    }
    myfile.close();
    return 0;
}
