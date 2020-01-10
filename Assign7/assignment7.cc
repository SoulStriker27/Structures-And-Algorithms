/****************************************************************
FILE:Assignment 7
AUTHOR: Eduardo Leanos

PURPOSE:Make a heap from a vector
*****************************************************************/
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

const int HEAP_SIZE = 50;

/***************************************************************
Function-Prototypes
***************************************************************/ 

void build_heap (vector<int>&, int, bool(*)(int, int));
void heapify(vector<int>&, int, int , bool (*) (int, int));
bool less_than(int, int);
bool greater_than(int, int);
void heap_sort(vector<int>&, int, bool(* )(int, int));
int extract_heap(vector<int>&, int& , bool(*)(int,int));
void print_vector(vector<int>&, int, int);



int main(int argc, char** argv) {
    // ------- creating input vector --------------
    vector<int> v;
    v.push_back(-1000000);    // first element is fake
    for (int i=1; i<=HEAP_SIZE; i++)
        v.push_back( i );
    random_shuffle( v.begin()+1, v.begin()+HEAP_SIZE+1 );

    cout << "\nCurrent input numbers: " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing min heap ------------------
    cout << "\nBuilding a min heap..." << endl;
    build_heap(v, HEAP_SIZE, less_than);
    cout << "Min heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, less_than);
    cout << "Heap sort result (in ascending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing max heap ------------------
    cout << "\nBuilding a max heap..." << endl;
    build_heap(v, HEAP_SIZE, greater_than);
    cout << "Max heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, greater_than);
    cout << "Heap sort result (in descending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    return 0;
}

/***************************************************************
Function:void build_heap
Parameters:(vector<int>& v, int heap_size, bool(*compar)(int, int))
Returns:void
Notes:Builds the heap
***************************************************************/ 

void build_heap (vector<int>& v, int heap_size, bool(*compar)(int, int)){
	for( int i = heap_size/2; i >= 1; i--){    //Take half od heap_size and hepify the parents
		heapify(v, heap_size, i, compar);
	}
}

/***************************************************************
Function:void heapify
Parameters:(vector<int>& v, int heap_size, int r, bool (*compar) (int, int))
Returns:void
Notes:Heapifies the vector
***************************************************************/ 

void heapify(vector<int>& v, int heap_size, int r, bool (*compar) (int, int)){
	int scale = 0;
	int L = 2*r;    //This looks through the right and left shildren to pull up
	int R = 2*r+1;
	if( L <= heap_size and compar(v[L], v[r]))//Returns < less tnan, > greater than
		scale = L;
	else
		scale = r;
	if( R <= heap_size  and compar(v[R], v[scale]))//Returns < lesstnan, > greater than
	       	scale = R;
	if( scale != r){
		int temp = v[r]; //Switches v[r] with v[scale] and calls hepify
		v[r] = v[scale];
		v[scale] = temp;
		heapify(v, heap_size, scale, compar);
	}	
	return;
}

/***************************************************************
Function:bool less_than
Parameters:(int e1, int e2)
Returns:boolean
Notes:checks for less than equaluality
***************************************************************/ 

bool less_than(int e1, int e2){ //Checks if for less than
	if( e1 < e2 )
		return true;
	else
		return false;
}

/***************************************************************
Function:bool greater_than
Parameters:(int e1, int e2)
Returns:boolean
Notes:checks for greater than equaluality
***************************************************************/ 

bool greater_than(int e1, int e2){ //checks for greater than
	if( e1 > e2 )
		return true;
	else 
		return false;
}

/***************************************************************
Function:void heap_sort(
Parameters:(vector<int>& v, int heap_size, bool(*compar )(int, int))
Returns:void
Notes:sorts the heap
***************************************************************/ 

void heap_sort(vector<int>& v, int heap_size, bool(*compar )(int, int)){
	extract_heap(v, heap_size, compar);
	for(int i = heap_size; i >= 2; i--){ //Sorts the heap starting from the leafs to the root
		int temp = v[1];
		v[1] = v[i]; 
		v[i] = temp;
		heap_size = heap_size - 1; //shrinks heap size as it progresses
		heapify(v, heap_size, 1,  compar);		
	}
	reverse(v.begin()+1, v.end()); //Calls reverse funstion to allow descending and ascending order
}

/***************************************************************
Function:int extract_heap
Parameters:(vector<int>& v, int& heap_size, bool(*compar)(int,int))
Returns:integer
Notes:extracts the lowest/higest number of heap
***************************************************************/ 

int extract_heap(vector<int>& v, int& heap_size, bool(*compar)(int,int)){
	int val = 0;
	if(heap_size < 1)
		throw "Heap underflow"; //throws error if heap size is under 1
	val = v[1];
	v[1] = v[heap_size]; //puts highest index into index 1
	v[heap_size] = val;
	heap_size = heap_size -1;
	heapify(v, heap_size, 1, compar);	
	return 	val; //return value
}

/***************************************************************
Function:void print_vector
Parameters:(vector<int>& v, int pos, int size)
Returns:void
Notes:prints heap
***************************************************************/ 

void print_vector(vector<int>& v, int pos, int size){ //prints the heap
	int i = 0;
	for(auto it = v.begin()+1; it != v.end(); it++){ //Uses iterators to traverse vector
		cout << setw(5) << *it;
		i++;
		if(i == 8){ //Allows for 8 integers in a line
			cout << endl;
			i = 0;
		}
	}
	cout << endl;
}




