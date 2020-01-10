/**********************************************************************
Name: Eduardo Leanos
Assignment 5: Nodes
***********************************************************************/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <iterator>
#include "assignment5.h"

using namespace std;

const int MAX_SIZE = 40;
const int MAX_COUNT = 40;
const int WIDTH = 5;
const int ROW_SIZE = 8;

int mcount = 0;
int rcount = 0;

void display(int d) {
    if ( mcount < MAX_COUNT ) {
        cout << setw(WIDTH) << d;
        mcount++;
        rcount++;
        if ( rcount == ROW_SIZE ) {
            cout << endl;
            rcount = 0;
        }
    }
}

/**********************************************************************
Function:binTree::binTree
Parameters:None
Return:None
Extra information:Constructor, public member
***********************************************************************/

binTree::binTree(){
	root = nullptr; //sets protected member as nullptr for insert	
};

/**********************************************************************
Function:virtual void binTree::insert
Parameters:int 
Return:None
Extra information:Virtual function, public member
***********************************************************************/

void binTree::insert(int x){
	insert(root, x); //calls private version with root node
};

/**********************************************************************
Function:int binTree::height const
Parameters:None
Return:int
Extra information:Returns height of tree, public member
***********************************************************************/

int binTree::height() const{
	return height(root); //calls private version with root node
};

/**********************************************************************
Function:unsigned binTree::size() const
Parameters:None
Return:unsigned
Extra information:returns size of tree, public member
***********************************************************************/

unsigned binTree::size() const{
	return size(root); //calls private version with root node
};

/**********************************************************************
Function:void binTree::inorder
Parameters:void(*)(int)
Return:Nothing
Extra information:LNR, public member
***********************************************************************/

void binTree::inorder( void(*p)(int) ){
	inorder(root, p); //calls private version with root
};

/**********************************************************************
Function:void binTree::preorder
Parameters:void(*)(int)
Return:Nothing
Extra information:NLR, public member
***********************************************************************/

void binTree::preorder( void(*p)(int) ){
	preorder(root, p); //cals private version with root node
};

/**********************************************************************
Function:void binTree::postorder
Parameters:void(*)(int)
Return:Nothing
Extra information:LRN, public member
***********************************************************************/

void binTree::postorder( void(*p)(int) ){
	postorder(root, p); //calls private version with root node
};


//====================================================================//


/**********************************************************************
Function:virtual void binTree::insert
Parameters: Node*& n, int val
Return:None
Extra information:Virtual function, private member
***********************************************************************/

void binTree::insert( Node*& n, int val ){
	if(n == nullptr){//if the node is nullptr, makes new node
		n  = new Node;
		n->data = val; //inserts val into data
	}
	else if(height(n->left) >  height(n->right)) //This sorts nubers put in with n->data
		insert(n->right, val);//Go left if right height is smaller
	else
		insert(n->left, val);//Go right if left height is greater
};


/**********************************************************************
Function:int binTree::height const
Parameters:Node* n
Return:int
Extra information:Returns height of tree, private member
***********************************************************************/

int binTree::height( Node* n) const{
	
	if (n == nullptr) //if there isnt a node, return -1
		return -1;
	else{
		int leftDepth = height(n->left); //get total of all left nodes
		int rightDepth = height(n->right); //get total of all right nodes
	
		if(leftDepth > rightDepth) //compare values returned
			return(leftDepth + 1); //if left > right, return left +1
		else
			return(rightDepth + 1); //else return right +1
	}
};

/**********************************************************************
Function:unsigned binTree::size() const
Parameters:Node* n
Return:unsigned
Extra information:returns size of tree, private member
***********************************************************************/

unsigned binTree::size( Node* n) const{
	if (n == nullptr) //check if nullptr, return 0
		return 0; 
	else{
		int leftDepth = size(n->left); //gather total all left nodes
		int rightDepth = size(n->right);//gather total of all right nodes
		return leftDepth + rightDepth + 1; //return total of all +1
	}
};


/**********************************************************************
Function:void binTree::inorder
Parameters:Node* root, void(*)(int)
Return:Nothing
Extra information:LNR, private member
***********************************************************************/

void binTree::inorder( Node* n, void(*p)(int)){
	if(n != NULL){//if not nullptr do L, N, R
		inorder(n->left, p);
		p(n->data);
		inorder(n->right, p);
	}
};

/**********************************************************************
Function:void binTree::preorder
Parameters:Node* root, void(*)(int)
Return:Nothing
Extra information:NLR, private member
***********************************************************************/

void binTree::preorder( Node* n, void(*p)(int)){
	if(n != NULL){//if not nullptr do, N, L, R
		p(n->data);
		preorder(n->left, p);
		preorder(n->right, p);
	}
};


/**********************************************************************
Function:void binTree::postorder
Parameters:Node* root, void(*)(int)
Return:Nothing
Extra information:LRN, private member
***********************************************************************/

void binTree::postorder( Node* n, void(*p)(int)){
	if(n != NULL){//if not nullptr do L, R, N
		postorder(n->left, p);
		postorder(n->right, p);
		p(n->data);
	}
};


/*#define BINTREE_MAIN
#ifdef BINTREE_MAIN
int main() {
    vector<int> v(MAX_SIZE);
    for (int i=1; i<MAX_SIZE; i++)
        v[i] = i;
    random_shuffle( v.begin(), v.end() );

    cout << endl;
    binTree bt;
    vector<int>::iterator it;
    for (it=v.begin(); it!=v.end(); it++)
        bt.insert( *it );
    	
    cout << "Height: " << bt.height() << endl;
    cout << "Size: " << bt.size() << endl;
    cout << "In order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.inorder( display );
    cout << "\n\nPre order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.preorder( display );
    cout << "\n\nPost order traverse (displaying first " << MAX_COUNT << " numbers): " << endl;
    mcount = rcount = 0;
    bt.postorder( display );

    cout << endl;
    return 0;
}

#endif*/
