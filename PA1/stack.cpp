#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
}
    
template <class T>
Stack<T>::Stack(Stack<T>& otherStack)
{
	ListItem<T> *curr = otherStack.list.getHead();
    while (curr != NULL)
    {
        list.insertAtTail(curr->value);
        curr = curr->next;
    }
}

template <class T>
Stack<T>::~Stack()
{
}

template <class T>
void Stack<T>::push(T item)
{
	list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
	T topVal = list.getHead()->value;
	return topVal;
}

template <class T>
T Stack<T>::pop()
{
	T topVal = list.getHead()->value;
	list.deleteHead();
	return topVal;
}

template <class T>
int Stack<T>::length()
{
	return (list.length());
}

template <class T>
bool Stack<T>::isEmpty()
{
	if (list.length() > 0)
        return false;

    return true;
}

#endif
