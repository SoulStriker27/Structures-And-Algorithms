/*************************************************************
 *Programer: Eduardo Leanos
 *Synopsis: Use STL set to make a set with only prime numbers
 **************************************************************/

#include <iostream>
#include <iomanip>
#include <set>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

const int ITEM_W = 4;
const int NO_ITEMS = 6;

/***************************************************************
Function: void sieve
Parameters: ( set<int>& s, const int lower, const int upper)
Returns: Nothing
Notes: Cuts off all non-prime numbers in a given set
***************************************************************/ 

void sieve( set<int>& s, const int lower, const int upper) {
	for( int i = lower ; i <= upper; i++){ //A loop to insert a range of numbers from lower
		if(i > 1)                         //to upper that are not lower than 1
			s.insert(i);
	}
	int m = 2; //Start the algorithm of with the lowest prime number
	for(int k = 2; (m*m) <= upper; k++){ //Check for (m*m) < upper
		int x = k * m; //Get x as a number to take out of set
		auto it = s.find(x); //Find x
		if( it != s.end() ) //If x is found, then it wshould not be at s.end()
			s.erase(it); //Erase x at position it
		if(x >= upper){ //Once x is greater than upper, restart for loop with m = 1 greater
			m++;
			k = ( m - 1); //k++ in for loop makes taking 1 off of  m important
		}
	}
}

/***************************************************************
Function: void print_primes
Parameters: ( const set<int>& s, const int lower, const int upper) 
Returns: Nothing
Notes: Prints out the leftover prime numbers after the fucntion sieve
was executed
***************************************************************/ 

void print_primes( const set<int>& s, const int lower, const int upper) {
	int i = 1;
	cout << endl << "There are " << s.size() << " prime numbers in between " << lower << " and " << upper << ":" << endl; 
	for(auto it = s.begin(); it != s.end(); it++, i++){ //Use iterators to loop through set
		cout << setw(ITEM_W) <<  *it << " "; // Display value by dereffrencing iterator
		if(i == NO_ITEMS){ //Only show 6 items per line
			cout << endl;
			i = 0;
		}
	}
}

/***************************************************************
Function: void run_game
Parameters: (set<int>& s)
Returns: Nothing
Notes: Asks for input from the user of an upper and lower bound'
number to calculate the prime numbers in them
***************************************************************/ 

void run_game(set<int>& s) {
	string maybe = "yes"; 
	while(maybe == "yes"){ //Loop through everytime the user says yes 
		int lower, upper;
		cout << "Please enter lower bound and uppper bound and hit Enter(e.g. 10 100): " << endl;
		cin >> lower >> upper; //Get lower and upper from user
		while(upper < lower){ //Make sure upper is not tinier than lower
			cout << " Please make sure upper bound is greater than lower bound: " << lower << endl;
			cin >> upper;
		}
		sieve(s, lower, upper); //Call sieve function
		print_primes(s, lower, upper); //Call print_primes function
		s.clear(); //once everything is done, clear the set to restart
		cout << endl  << endl << "Do you wish to continue or not? Please type yes or no and hit Enter" << endl;
		cin >> maybe; //Ask wether or not to continue
	}
}

int main() {
    set<int> s;
    run_game(s);
    return 0;
}
