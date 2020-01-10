#include <algorithm>  //Include all usable libraries
#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <string>


using namespace std;

const int DATA_SIZE = 200;
const int DATA_RANGE = 200;
const int DATA_SEED = 9;
const int SEARCH_SEED = 17;
const int NO_ITEMS = 8; //Number of items per line
const int ITEM_W = 4; //Width of printed vector items


/**************************************************************
Function Name: int linear_search
Parameters: const vector<int>& inputVec, const int x, int& comparisons
Returns: int
Functionality: Linear search algorithm of vector
**************************************************************/

int linear_search(const vector<int>& inputVec, const int x, int& comparisons) {
	comparisons=0; //Reset comparisons everytime the function is called
	for(unsigned i=0;i<inputVec.size(); i++){
		comparisons++; //Increase the number of compares each time x is compared
		if(x==inputVec.at(i))
			return i;
	}
	return -1; //Return -1 if item was not found
}

/**************************************************************
Function Name: int binary_search
Parameters: const vector<int>& inputVec, const int x, int& comparisons
Returns: int
Functionality: Binary search algorithm of vector
**************************************************************/

int binary_search(const vector<int>& inputVec, const int x, int& comparisons) {
	int low=0;
	int high=(int)inputVec.size()-1; //set mid/high/low for binary search
	int mid;;
	comparisons=0;

	while(low<=high){ //Binary search

		comparisons++;

		mid=(low+high)/2; //Splits vector in half

		if(x==inputVec[mid])
			return mid;
		if(x<inputVec[mid])
			high=mid-1;
		else
			low=mid+1;
	}
	return -1; //Return -1 if nothing found
}

/**************************************************************
Function Name: void print_vec
Parameters: const vector<int>& vec
Returns: Nothing
Functionality: Print function for vectors
**************************************************************/

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
	

void average_comparisons(const vector<int>& inputVec, const vector<int>& searchVec, int (*search)(const vector<int>&, const int, int&) ) {
    int i, comparison = 0, sum = 0, found = 0;
    int res = 0;
    for (i = 0; i < (int)searchVec.size(); i++){
        res = search( inputVec, searchVec[i], comparison );
        sum += comparison;
        if ( res >= 0 )
           found++;
    }
    cout << found << " numbers are found. The average number of comparisons in each search: " << (double)sum/(double)searchVec.size() << endl << endl;
}

int random_number() {
    return rand()%DATA_RANGE + 1;
}


int main () {

    // -------- create unique random numbers ------------------//
    vector<int> inputVec(DATA_SIZE);
    srand(DATA_SEED);
    generate(inputVec.begin(), inputVec.end(), random_number);
    sort(inputVec.begin(), inputVec.end());
    vector<int>::iterator it = unique(inputVec.begin(), inputVec.end());
    inputVec.resize( it - inputVec.begin() );
    random_shuffle( inputVec.begin(), inputVec.end() );

    cout << "------ Data source: " << inputVec.size() << " unique random numbers ------" << endl; 
    print_vec(inputVec);
    cout << endl;

    // -------- create random numbers to be searched ---------//
    vector<int> searchVec(DATA_SIZE/2);
    srand(SEARCH_SEED);
    generate(searchVec.begin(), searchVec.end(), random_number);

    cout << "------ " << searchVec.size() << " random numbers to be searched: ------" << endl;
    print_vec(searchVec);
    cout << endl;

    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    sort(inputVec.begin(), inputVec.end());
    cout << "------- numbers in data source are now sorted ---------" << endl << endl;
    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    return 0;

}


