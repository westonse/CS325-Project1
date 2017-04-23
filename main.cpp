#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

//Max array size
const int MAX_ARRAY_SIZE = 100;


//struct to hold the sum, left index, and right index for
//the maximum sub array
struct maxSumTuple {
    int sum;
    int left;
    int right;
};

//printResults
/*
 *
 */
//Prints results to MSS_Results.txt
void printResults(int arrayCount, int ret, int MaxSumStart, int MaxSumEnd, int method, int * a)
{
    //Output results to MSS_Results.txt in current directory
    std::string filename2 = "./MSS_Results.txt";
    ofstream myfile2;
    //open new file if first array
    if(arrayCount==1 && method==1)
    {
        myfile2.open (filename2.c_str());
    }
    //else append
    else
    {
        myfile2.open (filename2.c_str(), ios::app);
    }
    //print results to file
    myfile2 <<"ARRAY "<< arrayCount << " RESULTS (method "<<method<<")\n\n"<<"Maximum subarray sum:"<<ret<<"\n"<<"Max Sum Start Index: " << MaxSumStart << "  Max Sum End Index : " << MaxSumEnd << "\nSub-Array: \n";

    for(int i = MaxSumStart; i < MaxSumEnd; i++)
    {
	if(i == MaxSumStart)
        {
		myfile2<<"["<<a[i]<<",";
        }
	else if(i == MaxSumEnd-1)
	{
		myfile2<<a[i]<<"]\n\n";	
	}
	else
	{
		myfile2<<a[i]<<",";
    	}
    }
    myfile2.close();

}


//METHOD 1: Brute force//

/*
MaxSumBruteForce(path, a, arraySize, arrayCount);
Determines max sub array and sub array indices by
holding the current best sum and testing against every possible subarray
*/

void MaxSumBruteForce(int * a, int size, int arrayCount)
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
    printResults(arrayCount, ret, MaxSumStart, MaxSumEnd,1,a);
}


//METHOD 2: Improved Brute force//
/*
 *
 */
void MaxSumImprovedBruteForce(int * a, int size, int arrayCount)
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
    printResults(arrayCount, ret, MaxSumStart, MaxSumEnd,2,a);

}

//METHOD 3: Divide and Conquer


//helper function to find the max sub array that includes
//the middle value of an array
maxSumTuple maxCrossing (int values[], int left, int right, int middle) {
    int leftSum = 0;
    int sum = 0;
    maxSumTuple max;

    for (int i = middle; i >= left; i--) {
        sum += values[i];
        if (sum > leftSum) {
            leftSum = sum;
            max.left = i;
        }
    }

    int rightSum = 0;
    sum = 0;
    for (int i = middle + 1; i <= right; i++) {
        sum += values[i];
        if (sum > rightSum) {
            rightSum = sum;
            max.right = i;
        }
    }

    max.sum = leftSum + rightSum;
    return max;
}

//recursive Divide and Conquer function used to compute the
//maximum sub array of an array of values
maxSumTuple divideConquer(int values[], int left, int right) {
    if (left == right) {
        maxSumTuple max;
        max.sum = values[left];
        max.left = left;
        max.right = right;
        return max;
    }

    int middle = (left + right) / 2;
    maxSumTuple leftSum = divideConquer(values, left, middle);
    maxSumTuple rightSum = divideConquer(values, middle + 1, right);
    maxSumTuple crossing = maxCrossing(values, left, right, middle);

    if (leftSum.sum >= rightSum.sum && leftSum.sum >= crossing.sum) {
        return leftSum;
    } else if (rightSum.sum >= leftSum.sum && rightSum.sum >= crossing.sum) {
        return rightSum;
    } else {
        return crossing;
    }
}

//function to call the divide and conquer algorithm. Sends
//the sum and indices of the max sub array to the print function
void MaxDivideAndConquer (int values[], int valuesLen, int arrayCount) {
    maxSumTuple max = divideConquer(values, 0, valuesLen - 1);
    printResults(arrayCount, max.sum, max.left, max.right,3,values);
}

//METHOD 4: Linear Time
void LinearTime (int values[], int valuesLen, int arrayCount) {
    std::ofstream output;
    output.open("results", std::ios::app);
    int maxInitIndex = 0; //starting index for the max sub array sum
    int maxEndIndex = 0; //last index for the max sub array sum
    int curInitIndex = 0; //current initial index for sub array whose sum is being computed
    int maxSum = 0;
    int curSum = 0;

    for (int i = 0; i < valuesLen; i++) {
        curSum = curSum + values[i];

        if (curSum > maxSum) {
            maxSum = curSum;
            maxInitIndex = curInitIndex;
            maxEndIndex = i;
        } else if (curSum <= 0) {
            //if all the values are negative, curSum will be set
            //to the least negative value
            if (values[i] > maxSum) {
                maxSum = values[i];
            }

            //set curSum to 0 and curInitIndex to i + 1 to start
            //computing the sum of a new sub array
            curSum = 0;
            curInitIndex = i + 1;
        }
    }
    printResults(arrayCount, maxSum, maxInitIndex, maxEndIndex,4,values);
}


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
    std::string filename = "./MSS_Problems.txt";
    ifstream myfile(filename.c_str());
    //ifstream myfile( "./MSS_Problems.txt" );
    
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
                    /******** ALGORITHM 1 Brute Force *******/
                    MaxSumBruteForce(a, arraySize, arrayCount);

                    

                    /******** ALGORITHM 2 Improved Brute Force *******/
                    MaxSumImprovedBruteForce(a, arraySize, arrayCount);
                    
                    
                    
                    //METHOD 3: Divide and conquer//
                    MaxDivideAndConquer(a, arraySize, arrayCount);
                    
                    //METHOD 4: Linear Time//
                    LinearTime(a, arraySize, arrayCount);
                    
                    
                    //Output results to MSS_Results.txt using printResults function
                    //printResults(path, arrayCount, ret, MaxSumStart, MaxSumEnd);
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
