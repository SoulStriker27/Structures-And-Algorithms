#ifndef ASSIGNMENT6
#define ASSIGNMENT6
#include "assignment5.h"

class BST : public binTree {
    public:
        BST() : binTree() {};
        void insert( int );
        bool search( int );
        bool remove( int );
        int sumLeaves();
    private:
        void insert( Node*&, int );
        bool search( Node*&, int );
        bool remove( Node*&, int );
        int sumLeaves(Node*&);
};

#endif
