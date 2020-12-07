#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
	head = NULL;
	ListItem<T> *cop = otherLinkedList.head;
	while (cop != NULL){
        insertAtTail(cop->value);
        cop = cop->next;
	}

}

template <class T>
LinkedList<T>::~LinkedList()
{
        ListItem<T> *traverse = head;
        ListItem<T> *del;

        while (traverse != NULL){
            del = traverse;
            traverse = traverse->next;
            delete del;
        }
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	ListItem<T> *n = new ListItem<T>(item);

	if (head != NULL){
		n->next = head;
		head->prev = n;
		head = n;
	}
	else {
        head = new ListItem<T>(item);
		head = n;
	}
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
    ListItem<T> *n = new ListItem<T>(item);

    if (head != NULL){
        ListItem<T> *curr = head;
        while (curr->next != NULL){
            curr = curr->next;
        }
        n->prev = curr;
        curr->next = n;
        curr = n;
    }
    else {
        head = n;
    }
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
    ListItem<T> *n = new ListItem<T>(toInsert);
    ListItem<T> *curr = head;

    while(curr->value != afterWhat){
        curr = curr->next;
    }

    if (curr == getTail()){
        insertAtTail(toInsert);
    }
    else {
        n->next = curr->next;
        n->prev = curr;
        curr->next->prev = n;
        curr->next = n;
    }
}


template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
	return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
    if (head != NULL){
        ListItem<T> *curr = head;
        while (curr->next != NULL){
            curr = curr->next;
        }
        return curr;
    }
    else {
        return NULL;
    }
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
    if (head != NULL){
        ListItem<T> *search_item = head;
        while (search_item != NULL){

            if (search_item->value == item){
                return search_item;
            }
                search_item = search_item->next;
        }
    }
    else {
        return NULL;
    }
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
 	if (head != NULL){
 		ListItem<T> *cur = head;
 		ListItem<T> *curPre = head;

 		while (cur->next != NULL && cur->value != item){
 			curPre = cur;
 			cur = cur->next;
 		}
 		if (cur->value == item){

			if (cur == head){
				deleteHead();
			}
			else if (cur->next == NULL)
			{
				deleteTail();
			}
			else {
				curPre->next = cur->next;
				cur->next->prev = curPre;
				delete cur;	
				cur = NULL;		
			}
 		}
 		else {
 			return;
 		}
 	}

 	else {
 		return;
 	}
}

template <class T>
void LinkedList<T>::deleteHead()
{
    if (head != NULL){
        ListItem<T> *mover = head;
        head = head->next;
        delete mover;
        mover = NULL;
    }
    else if (head->next != NULL){
    	delete head;
    	head = NULL;
    }
    else {
        return;
    }
}

template <class T>
void LinkedList<T>::deleteTail()
{
    ListItem<T> *toBedel = head;

    if (head != NULL){

	    while (toBedel->next != NULL){
	        toBedel = toBedel->next;
	    }
	    if (toBedel == head){
	    	deleteHead();
	    }
	    else {
		    toBedel->prev->next = NULL;
		    delete toBedel;
		    toBedel = NULL;
		  	}
		  }
	else{
		return;
	}

}

template <class T>
int LinkedList<T>::length()
{
    ListItem<T> *traverse = head;
    int counter = 0;

    while (traverse != NULL){
        counter++;
        traverse = traverse->next;
    }
    return counter;
}

#endif
