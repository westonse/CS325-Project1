#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>

//#include <conio.h>
using namespace std;


//Max array size
const int MAX_ARRAY_SIZE = 100;
//printResults
/*
 *
 */
//Prints results to MSS_Results.txt
void printResults(int arrayCount, int ret, int MaxSumStart, int MaxSumEnd)
{
    //Output results to MSS_Results.txt using path given by user
    std::string filename2 = "./MSS_Results.txt";
    ofstream myfile2;
    //open new file if first array
    if(arrayCount>1)
    {
        myfile2.open (filename2.c_str(), ios::app);
    }
    //else append
    else
    {
        myfile2.open (filename2.c_str());
    }
    //print results to file
    myfile2 <<"ARRAY "<< arrayCount << " RESULTS\n\n"<<"Maximum subarray sum:"<<ret<<"\n"<<"Max Sum Start Index: " << MaxSumStart << "  Max Sum End Index : " << MaxSumEnd << "\n\n";
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
    printResults(arrayCount, ret, MaxSumStart, MaxSumEnd);
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
    printResults(arrayCount, ret, MaxSumStart, MaxSumEnd);

}


struct posHandler {
	int pos1;
	int pos2;
	int pos1max;
	int pos2max;
	int sum;
};
//METHOD 3: Divide and Conquer
/*
 *
 */
posHandler DivideAndConquer(int * a, int start, int end){
	posHandler payload;
	payload.pos1=start;
	payload.pos2=end;
	payload.pos1max=0;
	payload.pos2max=0;
	payload.sum=0;
posHandler left, right;
	int tester =0;
//BASE CASE: one element 
    	if(end - start <= 0){ 
		payload.pos1 = start;
		payload.pos2 = end;
		payload.sum = a[start];
		payload.pos1max = payload.pos1;
		payload.pos2max = payload.pos2;
		return payload; }
	if(end - start > 0){
		left = DivideAndConquer(a, start, end/2);	
		right = DivideAndConquer(a, ((start+end)/2)+1, end);
		payload.pos1 = left.pos1;
		payload.pos2 = right.pos2;
//Cases sum all elements between the two positions.
//CASE 1: LEFT1 -- RIGHT2
		for (int i = left.pos1; i <= right.pos2; i++){
			tester += a[i];
		}	
		if (tester > payload.sum){
			payload.sum = tester;
			payload.pos1max = left.pos1;
			payload.pos2max = right.pos2;
		}
//CASE 2: LEFT2 -- RIGHT2
		tester = 0;
		for (int i = left.pos2; i<= right.pos2; i++) {
			tester += a[i];
		}
		if (tester > payload.sum) {
			payload.sum = tester;
			payload.pos1max = left.pos2;
			payload.pos2max = right.pos2;
		}
//CASE 3: LEFT1 -- RIGHT1
		tester = 0;
		for (int i = left.pos1; i<= right.pos1; i++) {
			tester += a[i];
		}
		if (tester > payload.sum) {
			payload.sum = tester;
			payload.pos1max = left.pos1;
			payload.pos2max = right.pos1;
		}
//CASE 4: LEFT2 -- RIGHT1
		tester = 0;
		for (int i= left.pos2; i <= right.pos1; i++) {
			tester += a[i];
		}
		if (tester > payload.sum) {
			payload.sum = tester;
			payload.pos1max = left.pos2;
			payload.pos2max = right.pos1;
		}
//CASE 5: LEFT1 -- LEFT2
		tester = 0;
		for (int i= left.pos1; i <= right.pos1; i++) {
			tester += a[i];
		}
		if (tester > payload.sum){
			payload.sum = tester;
			payload.pos1max = left.pos1;
			payload.pos2max = left.pos2;
		}
//CASE 6: RIGHT1 -- RIGHT2
		tester = 0;
		for (int i=right.pos1; i <= right.pos2; i++) {
			tester+=a[i];
		}
		if (tester > payload.sum){
			payload.sum = tester;
			payload.pos1max = right.pos1;
			payload.pos2max = right.pos2;
		}
		return payload;
	}	
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
                    //MaxSumBruteForce(a, arraySize, arrayCount);

                    

                   /******** ALGORITHM 2 Improved Brute Force *******/
//                   MaxSumImprovedBruteForce(a, arraySize, arrayCount);
                    
                    
                    
                   /******** ALGORITHM 3 Divide and conquer ********/
		posHandler result = DivideAndConquer(a, 0, arraySize-1);
		int testsum=0;
		cout << "pos1:" << result.pos1 << "\t\tpos2:" << result.pos2 << "\n";
//		cout << "pos1=" << a[result.pos1] << "\tpos2=" << a[result.pos2] << "\n";
		cout << "pos1max:" << result.pos1max << "\tpos2max:" << result.pos2max << "\n";
		for (int k=result.pos1;k<=result.pos2;k++){
			testsum+=a[k];
		}
		cout << "array sum=" << testsum << "\talgosum=" << result.sum << "\n\n";
	   	//METHOD 4: Linear Time//
                    /*
                     *
                     */
                    //
                    
                    
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
