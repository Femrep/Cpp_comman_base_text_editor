#include "intSLList.h"
#include <iostream>
#include <fstream>


IntSLList::~IntSLList() {
    for (IntSLLNode *p; !isEmpty(); ) {
        p = head->next;
        delete head;
        head = p;
    }
}

void IntSLList::addToHead(string el) {
    head = new IntSLLNode(el,head);
    if (tail == 0)
       tail = head;
	size++;
}

void IntSLList::addToTail(string el) {
    if (tail != 0) {      // if list not empty;
         tail->next = new IntSLLNode(el);
         tail = tail->next;
    }
    else head = tail = new IntSLLNode(el);
	size++;
}
void IntSLList::insert_node(string el,int pos){
    if(pos==1)
        addToHead(el);
    else{
        if(head!=NULL){
            IntSLLNode* cur=head;
            IntSLLNode* New_node=new IntSLLNode(el);
            for(int i=1;head!=NULL&&i<pos;i++){
                if((pos-1)>i){
                    if(cur->next==NULL){
                        IntSLLNode* space_node=new IntSLLNode("");
                        cur->next=space_node;
                    }
                    cur=cur->next;

                }
                else if((pos-1)==i){
                    New_node->next=cur->next;

                }

                else
                    cur=cur->next;
            }
            cur->next=New_node;
        }
    }
}


string IntSLList::getposition(int x){
	IntSLLNode *tmp = head;
	string txtline=" ";
	for(int i = 0;i<x && tmp!=NULL;i++){
		//cout << tmp->info <<endl;
		if((x-1)==i)
            txtline=tmp->info;
        tmp = tmp->next;
	}
	return txtline;
}


string IntSLList::deleteFromHead() {
    string el = head->info;
    IntSLLNode *tmp = head;
    if (head == tail)     // if only one node on the list;
         head = tail = 0;
    else head = head->next;
    delete tmp;
	size--;
    return el;
}


string IntSLList::deleteFromTail() {
    string el = tail->info;
    if (head == tail) {   // if only one node on the list;
         delete head;
         head = tail = 0;
    }
    else {                // if more than one node in the list,
         IntSLLNode *tmp; // find the predecessor of tail;
         for (tmp = head; tmp->next != tail; tmp = tmp->next);
         delete tail;
         tail = tmp;      // the predecessor of tail becomes tail;
         tail->next = 0;
    }
	size--;
    return el;
}

string IntSLList::deleteNode(int pos) {
    string deletion="";
    if (head != NULL)                     // if non-empty list;
        {
            IntSLLNode* prev=head;
            if(pos==1){
                return deleteFromHead();
            }
            for(int i=2;head!=NULL&&i<pos;i++){
                prev=prev->next;
            }
            deletion=prev->next->info;
            IntSLLNode *next=prev->next->next;
            delete prev->next;
            prev->next=next;
        }
        return deletion;
}

void IntSLList::printPage(int page, int size, int totalPageCount, int totalLineCount) {
	int i = 0;
	int lineCounter = 0;

	cout << endl;

	for (IntSLLNode* tmp = head; tmp != 0; tmp = tmp->next)
	{
		i++;
		if (((page - 1) * size) < i)
		{
			if (lineCounter < size)
			{
				lineCounter++;
				cout <<i<<")  " << tmp->info << " " << endl;
			}

			if (lineCounter == size)
				break;
		}
	}
	cout << endl << "Current Page Number : " << page << " of " << totalPageCount << " --> ( " << totalLineCount << " lines )" << endl;
}
void IntSLList::printAll() const {

    for (IntSLLNode *tmp = head; tmp != 0; tmp = tmp->next)
        cout << tmp->info << "\n";
}

void IntSLList::move_two_node(int pos1,int pos2){

   if (pos1 != pos2)
	{
		IntSLLNode* tmp = head;

		string nodeTxt = getposition(pos1);
		deleteNode(pos1);
		insert_node( nodeTxt,pos2);
	}
}




void IntSLList::save(string filename)const{
    ofstream my_file(filename);
    if(my_file.is_open()){


            for(IntSLLNode* temp=head;temp!=NULL;temp=temp->next){
            my_file<<temp->info<<""<<endl;
        }
        my_file.close();
    }
}

Undos::~Undos() {
    for (UndosNode *p; !is_Empty(); ) {
        p = bas->next;
        delete bas;
        bas = p;
    }
}


void Undos::Int_addToHead(int el) {
    bas = new UndosNode(el,bas);
    if (son == 0)
       son = bas;
	undo_size++;
}

int Undos::Int_deleteFromHead() {
    int el = bas->data;
    UndosNode *tmp = bas;
    if (bas == son)     // if only one node on the list;
         bas = son = 0;
    else bas = bas->next;
    delete tmp;
	undo_size--;
    return el;
}
