/********************************************************************
 *Name:Eduardo Leanos
 *Program 6: Implemenenting Binary Search Tree with assignment 5 
 ********************************************************************/


#include <iostream>
#include "assignment5.h"
#include "assignment6.h"

using namespace std;

//Public version of insert function, used to call private

void BST::insert(int val){
	insert(root, val);
};

//Public version of  search function, used to call private

bool BST::search(int val){
	return search(root, val);
};

//Public version of remove function, used to call private

bool BST::remove(int val){
	return remove(root, val);
};

//Public version of sumLeaves function, used to call private

int BST::sumLeaves(){
	return sumLeaves(root);
};

//==========================================================================================

/***************************************************************
Function:void BST::insert
Parameters:(Node*& n, int val)
Returns:void
Notes:Inserts into treee
***************************************************************/ 


void BST::insert(Node*& n, int val){
	if(n == nullptr){ //If there it is null, make new node and assigne value
		n = new Node;
		n->data = val;
	}
	else if(val < n->data){
		insert(n->left, val); //smaller? go left
	}
	else{
		insert(n->right, val);//larger? go right
	}
};

/***************************************************************
Function:bool BST::search
Parameters:(Node*& n, int val
Returns:boolean
Notes:Returns true if number was found
***************************************************************/ 

bool BST::search(Node*& n, int val){
	if(n ==  nullptr) //If it is not found, return false
		return false;
	if(val == n->data) //Compare n->data with value
		return true;
	if(val < n->data){
		return	search(n->left, val);
	}
	if(val > n->data){
		return search(n->right, val);
	}
};

/***************************************************************
Function:bool BST::remove
Parameters:(Node*& n, int val)
Returns:boolean
Notes:Removes node from tree
***************************************************************/ 

bool BST::remove(Node*& n, int val){
	if( n== nullptr){
		return true; //If n == nullptr, return true
	}
	else if(n->data > val){
		return remove(n->left, val); //value less than n->data? go left
	}
	else if(n->data < val){
		return remove(n->right, val);//value greater than n->data? go right
	}
	else{
	if(n->left != nullptr and n->right != nullptr){ //If 2 leaves
		Node* temp = n->left; // Make temp node equal to n->left
		
						
		while(temp->right != nullptr) //Finds predessecor
			temp = temp->right;

		n->data = temp->data; 
		return	remove(n->left, n->data); //Removes continuing down the line
	}
	else if(n->left == nullptr and n->right == nullptr){//If 0 leaves
		delete n;
		n = nullptr;
	}
	else{ //If 1 leaf
		if(n->left == nullptr){ //Has n->right
			Node* temp = n;	
			n = n->right;
			delete temp;
		}
		else{ //Has n->left
			Node* temp = n;
			n = n->left;
			delete temp;
		}
	}
	return true; //After everything return true
	}
};

/***************************************************************
Function:int BST::sumLeaves
Parameters:(Node*& n
Returns:integer
Notes:Returns sum of tree leaves
***************************************************************/ 

int BST::sumLeaves(Node*& n){
	int sum = 0; //assign sum
	if(n == nullptr)
		return 0;
	if(n->left == nullptr && n->right == nullptr) //If a leaf, return data
		return n->data;
	return sumLeaves(n->left) + sumLeaves(n->right); //If not, return sum of left and right
};
