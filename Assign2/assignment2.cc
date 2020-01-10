/********************************************************************
Programmer; Eduardo Leanos
Program: This program is to implement STL<algorithms> and familiorize
with the routines
*********************************************************************/

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <iterator>

using namespace std;

const int DATA_SIZE = 100;
const int SEARCH_SIZE = 50;
const int DATA_SEED = 11;
const int SEARCH_SEED = 7;
const int LOW = 1;
const int HIGH = 100;
const int NO_ITEMS = 10;
const int ITEM_W = 6;

/***************************************************************
Function: void genRndNums
Parameters:  vector<int>& v, int seed
Returns: Nothing
Notes: Random number generator
***************************************************************/ 

void genRndNums( vector<int>& v, int seed ) {
	srand(seed);
	for(unsigned i = 0; i < v.size(); i++){
		v.at(i) = rand() % ( HIGH -  LOW + 1) + LOW; //Set vector with random amount of numbers form LOW to HIGH
	}
}

/***************************************************************
Function: bool linearSearch
Parameters: onst vector<int>& inputVec, int x
Returns: Boolean
Notes: Does a linear search with STL function find()
***************************************************************/ 

bool linearSearch( const vector<int>& inputVec, int x) {
	auto iter = find(inputVec.begin(), inputVec.end(), x); //Use find() to search vector with a linear search
	if( iter != inputVec.end()) //If the iterator is pointing at inputVec.end() then the number was not found, so return true if it does not point at end
		return true;
	else
		return false; //Return false if iterator is pointing at inputVec.end()
}

/***************************************************************
Function: bool binarySearch
Parameters: onst vector<int>& inputVec, int x
Returns: Boolean
Notes: Does a binary search with STL function binary_search()
***************************************************************/ 

bool binarySearch( const vector<int>& inputVec, int x) {
	if(binary_search(inputVec.begin(), inputVec.end(), x)) //Use STL function binary_search
		return true; //The STL function return true if the item was found
	else
		return false;
}

/***************************************************************
Function: int search
Parameters: const vector<int>& inputVec, const vector<int>& searchVec,
            bool (*p)( const vector<int>&, int) 
Returns: Integer
Notes: Has a pointer to a function in the parameter and calls the passed in
function with the vectors provided
***************************************************************/ 

int search( const vector<int>& inputVec, const vector<int>& searchVec,
            bool (*p)( const vector<int>&, int) ){
	int j=0;	
	for(unsigned i=0; i<searchVec.size(); i++){ //For every item in searchVec use a pointer funtion to use either linear or binary search to find the item in inputVec
		if(p(inputVec, searchVec.at(i))){ //Pointer function, return true if found
			j++; //J = amount of time item was found
		}
	}
	return j;
}

/***************************************************************
Function: void sortVector (
Parameters: vector<int>& inputVec
Returns: Nothing 
Notes: Sorts the vector with STL function sort()
***************************************************************/ 

void sortVector (vector<int>& inputVec) {
	sort(inputVec.begin(), inputVec.end());//Use STL function sort() to sort inputVec
}

/***************************************************************
Function: void printStat
Parameters: int totalSucCnt, int vec_size
Returns: Nothing
Notes: Displays result(in percent) of successful tries over vector.size()
***************************************************************/ 

void printStat (int totalSucCnt, int vec_size) {
		cout << "Successful searches: " << fixed << setprecision(2) << (float)totalSucCnt/vec_size * 100 << "%" << endl; //Display results in percentage form
}

/***************************************************************
Function: void print_vec
Parameters: const vector<int>& vec 
Returns: Nothing
Notes: Prints vector with NO_ITEMS per line and a with of ITEM_W
***************************************************************/ 

void print_vec( const vector<int>& vec ){
	int k=0;
	unsigned i=0;
	int j=0;
	while(i<vec.size()){ //While loop to print all items
		cout << setw(ITEM_W) << vec.at(k); //Cout for vector
		j++;
		if(j==NO_ITEMS){ //Once NO_ITEMS is hit from j, go to next line
			cout << endl;
			j=0;
		}
		i++;
		k++;
	}
	cout  << endl; //Buffer line after print

}

int main() {
    vector<int> inputVec(DATA_SIZE);
    vector<int> searchVec(SEARCH_SIZE);
    genRndNums(inputVec, DATA_SEED);
    genRndNums(searchVec, SEARCH_SEED);

    cout << "----- Data source: " << inputVec.size() << " randomly generated numbers ------" << endl;
    print_vec( inputVec );
    cout << "----- " << searchVec.size() << " random numbers to be searched -------" << endl;
    print_vec( searchVec );

    cout << "\nConducting linear search on unsorted data source ..." << endl;
    int linear_search_count = search( inputVec, searchVec, linearSearch );
    printStat ( linear_search_count, SEARCH_SIZE );

    cout << "\nConducting binary search on unsorted data source ..." << endl;
    int binary_search_count = search( inputVec, searchVec, binarySearch );
    printStat ( binary_search_count, SEARCH_SIZE );

    sortVector( inputVec );

    cout << "\nConducting linear search on sorted data source ..." << endl;
    linear_search_count = search( inputVec, searchVec, linearSearch );
    printStat ( linear_search_count, SEARCH_SIZE );

    cout << "\nConducting binary search on sorted data source ..." << endl;
    binary_search_count = search( inputVec, searchVec, binarySearch );
    printStat ( binary_search_count, SEARCH_SIZE );

    return 0;
}

