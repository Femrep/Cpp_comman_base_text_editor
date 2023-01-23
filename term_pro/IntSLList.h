//************************  intSLList.h  **************************
//           singly-linked list class to store integers

#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST
#include <iostream>
using namespace std;
class IntSLLNode {
public:
    IntSLLNode() {
        next = 0;
    }

    IntSLLNode(string el, IntSLLNode *ptr = 0) {
        info = el; next = ptr;
    }

    string info;
    IntSLLNode *next;
};

class IntSLList {
public:

    IntSLList() {
        head = tail = 0;
    }
    ~IntSLList();

    bool isEmpty() {
        return head == 0;
    }

	string getposition(int);
    void addToHead(string);
    void addToTail(string);
    void insert_node(string,int);// int variable position , string variable is entering info
    string  deleteFromHead(); // delete the head and return its info;
    string  deleteFromTail(); // delete the tail and return its info;
    string deleteNode(int);// using this method add to stack
    void move_two_node(int,int);
    void printPage(int,int,int,int) ;
    void printAll() const;
    void save(string) const;
private:
    IntSLLNode *head, *tail;
	int size;
};



class UndosNode {
public:
    UndosNode() {
        next = 0;
    }
    UndosNode(int el, UndosNode *ptr = 0) {
        data = el; next = ptr;
    }
    int data;
    UndosNode *next;
};

class Undos {
public:

    Undos() {
        bas = son = 0;
    }
    ~Undos();

    bool is_Empty() {
        return bas == 0;
    }

    void Int_addToHead(int);
    int  Int_deleteFromHead(); // delete the head and return its info;

private:
    UndosNode *bas, *son;
	int undo_size;
};

#endif
