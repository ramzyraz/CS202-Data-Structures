#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{

}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)
{
	ListItem<T> *curr = otherQueue.list.getHead();
    while (curr != NULL)
    {
        list.insertAtTail(curr->value);
        curr = curr->next;
    }
}

template <class T>
Queue<T>::~Queue()
{

}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
	T topMost = list.getHead()->value;
	return topMost;
}

template <class T>
T Queue<T>::dequeue()
{
	T topVal = list.getHead()->value;
	list.deleteHead();
	return topVal;
}

template <class T>
int Queue<T>::length()
{
	return (list.length());
}

template <class T>
bool Queue<T>::isEmpty()
{
	if (list.length() > 0)
        return false;

    return true;
}


#endif
