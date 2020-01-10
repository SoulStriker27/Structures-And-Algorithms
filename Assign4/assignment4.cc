/***********************************************************

Progammer: Eduardo Leanos

Purpose: Use Stack STL to make a Queue
************************************************************/ 

#include <iostream>
#include <iomanip>
#include <algorithm>

#include "assignment4.h"

using namespace std;

/***************************************************************
Function: Queue::empty() const
Parameters: Nothing
Returns: Bool
Notes: Returns if both stacks are empty
***************************************************************/ 

bool Queue::empty() const{
	 if(s1.empty() && s2.empty())
		 return true;
	 else
		 return false;
}

/***************************************************************
Function: Queue::size() const
Parameters: None
Returns: int
Notes: Return size of both stacks together
***************************************************************/ 

int Queue::size() const{
	return (s1.size() + s2.size());
}

/***************************************************************
Function: Queue::front()
Parameters: None
Returns: Int
Notes: Returns the front of "Queue" by moving everything to s2 
and using s2.top()
***************************************************************/ 

int Queue::front(){
	if(s2.empty()){
		while( !s1.empty()){
			s2.push(s1.top());
			s1.pop();
		}
	}
	return s2.top();	

}

/***************************************************************
Function: Queue::back()
Parameters: None
Returns: Int
Notes: Returns the back of the "Queue"
***************************************************************/ 

int Queue::back(){
	if(s1.empty()){
		while(!s2.empty()){
				s1.push(s2.top());
				s2.pop();
		}
	}
	return s1.top();
}

/***************************************************************
Function:  Queue::push(const int& val)
Parameters:  const int& val
Returns: Nothing
Notes: Pushing value into s1
***************************************************************/ 

void Queue::push(const int& val){
	s1.push(val);
}

/***************************************************************
Function: Queue::pop()
Parameters: None
Returns: Nothing
Notes: Pops the Front of "Queue"
***************************************************************/ 

void Queue::pop(){
	front();
	s2.pop();	
	}


int main() {
    Queue q;
    string op;
    int val = 0;
 
   cout << "operation -- size front end" << endl;
   cin >> op;
   while ( !cin.eof() ) {
        if ( op == "push" ) {
            cin >> val;
            q.push( val );
            cout << op << " " << val << "    -- ";
        }
        else if ( op == "pop" ) {
            q.pop();
            cout << op << "       -- ";
        }
        else {
            cerr << "Error input: " << op << endl;
            return 1;
        }
        if ( q.size() > 0 )
            cout << setw(3) << q.size() << setw(5) << q.front() << setw(5) << q.back() << endl;
        else
            cout << setw(3) << q.size() << endl;

        cin >> op;
    }

    while ( !q.empty() )
        q.pop();

    return 0;
}
