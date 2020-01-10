/****************************************************************
FILE: Assignment 8 
AUTHOR: Eduardo Leanos
PURPOSE: Closed Hashing
*****************************************************************/

#include <iostream>
#include <ostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>


#include "assignment8.h"

using namespace std;

// key is in form of letter-letter-digit
// compute sum <-- ascii(pos1)+ascii(pos2)+ascii(pos3)
// compute sum%htable_size
int HT::hashing(const string& key) {
   return ((int)key[0] + (int)key[1] + (int)key[2])%table_size;
}

//public

/***************************************************************
Function:HT::HT(int s=11
Parameters:(int s=11
Returns:Builds onject
Notes:Constructor
***************************************************************/ 
HT::HT(int s=11){ //Initilizes s at 11
	item_count = 0;
	table_size = s;
	hTable = new vector<Entry>(s);
}

/***************************************************************
Function:HT::~HT()
Parameters:Nothing
Returns:Nothing
Notes:Deconstructer
***************************************************************/ 
HT::~HT(){
	delete hTable; //Deletes hTable
}

/***************************************************************
Function:bool HT::insert(const Entry& e)
Parameters:(const Entry& e)
Returns:boolean
Notes:Inserts into vector
***************************************************************/ 
bool HT::insert(const Entry& e){
	for(int i =0; i < table_size; i++){
		if((*hTable)[i].key == e.key){
			cout << "Key already exists, please try another key" << endl; //Checks if key is used
			return false;
		}
	}
	if(table_size+1 < item_count){
		cout << "Hash table limit has been reached" << endl; //Checks it table is maxed out
		return false;
	}
	else{
		int index = hashing(e.key);
		if((*hTable)[index].key == "---"){
			(*hTable)[index].key = e.key;
			(*hTable)[index].description = e.description;
		}
		else{
			while((*hTable)[index].key != "---" && (*hTable)[index].key != "+++"){ //checks for "---" or "+++"
				index++;
			}
			(*hTable)[index].key = e.key;
			(*hTable)[index].description = e.description;
		}
		item_count++;
		return true;
	}
}

/***************************************************************
Function:int HT::search(const std::string& key)
Parameters:(const std::string& key)
Returns:integer
Notes:searches vector
***************************************************************/ 
int HT::search(const std::string& key){ 
	int index = hashing(key);
	if( (*hTable)[index].key == "---" && (*hTable)[index].key == "+++"){ //checks for "---" and "+++"
		return -1;
	}
	bool loop = false;
	for(int i = index ; i < table_size; i++){ //checks entire table for 1 full rotation
		if ((*hTable)[i].key == key)
			return i;
		if(i == (table_size-1) && loop == false){
			loop = true;
			i = 0;
		}
		if(i == (table_size-1) && loop == true)
			return -1;
	}
	return index;
}

/***************************************************************
Function:bool HT::remove(const std::string& s)
Parameters:(const std::string& s)
Returns:boolean
Notes:Removes key and description from table
***************************************************************/ 
bool HT::remove(const std::string& s){ //checks all keys and removes if matches
	for(int i = 0; i < table_size; i++){
		if((*hTable)[i].key == s){
			(*hTable)[i].key = "+++"; //sets key to "+++"
			(*hTable)[i].description = ""; //sets description to "" 
			item_count--;
			return true;			
		}
	}
	return false;
}

/***************************************************************
Function:void HT::print()
Parameters:Nothing
Returns:void
Notes:Prints the current table
***************************************************************/ 
void HT::print(){
	cout << endl << "----Hash Table-----" << endl; //Prints out the hash table
	for(int i = 0; i < table_size; i++){ //The iterations 
		if((*hTable)[i].key != "---" && (*hTable)[i].key != "+++")
			cout <<  setw(2) << i << ": " << (*hTable)[i].key << " " << (*hTable)[i].description << endl; 
	}
	cout << "-------------------" << endl << endl;
}

/***************************************************************
Function:Entry* get_entry(const string& line)
Parameters:(const string& line)
Returns:Entry* object
Notes:Good luck keeping track of chars and strings
***************************************************************/ 
Entry* get_entry(const string& line){ //Get entry*
	Entry* e = new Entry(); 
	char *cstr = new char[line.length() + 1]; //make a char*
	strcpy(cstr, line.c_str());  //convert line to char * and copy to cstr
	char* pch = strtok( cstr, ":"); //string token cstr and hold token in pch
	pch = strtok(NULL, ":"); //one more loop of strtok to get 2nd item in line
	(*e).key = string(pch); //convert char* to string and put in key
	pch = strtok(NULL, ":");
	(*e).description = string(pch); //put in description
	return e;//return entry

}

/***************************************************************
Function:string get_key (const string& line)
Parameters:(const string& line)
Returns:string
Notes:Gets the key
***************************************************************/ 
string get_key (const string& line){
	if(line[0] == 'P') //check if P is at line 0
		return "a"; 
	char *cstr = new char[line.length() + 1];
	strcpy(cstr, line.c_str());
	char* pch = strtok( cstr, ":");
	pch = strtok(NULL, ":");
	string str = pch; //convert char* to string
	return str; //return string
}

//MAIN::

int main(int argc, char** argv ) {
    if ( argc < 2 ) {
        cerr << "argument: file-name\n";
        return 1;
    }
    HT ht;
    ifstream infile(argv[1], ios::in);
    string line;
    infile >> line;    
    while ( !infile.eof() ) {
        if ( line[0] == 'A' ) { 
            Entry* e = get_entry( line );
            ht.insert( *e );
            delete e;
        }
        else {
            string key = get_key(line);
            if ( line[0] == 'D' ) {
                cout << "Removing " << key << "...\n";
                bool removed = ht.remove( key );
                if ( removed )
                    cout << key << " is removed successfully...\n\n";
                else
                    cout << key << " does not exist, no key is removed...\n\n";
            }
            else if ( line[0] == 'S' ) {
                int found = ht.search( key );
                if ( found < 0 ) 
                    cout << key << " does not exit in the hash table ..." << endl << endl;
                else
                   cout << key << " is found at table position " << found << endl << endl;
            }
            else if ( line[0] == 'P' ) {
                cout << "\nDisplaying the table: " << endl;
                ht.print();
            }
            else
                cerr << "wrong input: " << line << endl;
        }
        infile >> line;
 
    }

    infile.close();
    return 0;
}
