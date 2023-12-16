#include "list.h"

#include <iostream>
List::List() : size(0), sentinel_head(new Node(true)), sentinel_tail(new Node(true))
{
    sentinel_head->next = sentinel_tail;
    sentinel_tail->prev = sentinel_head;
}

List::~List()
{
    Node *i = sentinel_tail;
    while (i != sentinel_head)
    {
        Node *temp = i->prev;
        delete (i);
        i = temp;
    }
    delete (i);
}
// Insert an element at the tail of the linked list
void List::insert(int v)
{
    try{
    size++;
    Node *temp = new Node(v, sentinel_tail, sentinel_tail->prev);
    sentinel_tail->prev->next = temp;
    sentinel_tail->prev = temp;
    }catch (std::bad_alloc const&) {
        throw std::runtime_error("Out of Memory");
    }
}

// Delete the tail of the linked list and return the value
// You need to delete the valid tail element, not the sentinel
int List::delete_tail()
{
    if (size == 0)
        throw std::runtime_error("Empty Stack");
    int a = sentinel_tail->prev->get_value();
    size--;
    sentinel_tail->prev = sentinel_tail->prev->prev;
    delete (sentinel_tail->prev->next);
    sentinel_tail->prev->next = sentinel_tail;
    return a;
}

// Return the size of the linked list
// Do not count the sentinel elements
int List::get_size()
{
    return size;
}

// Return a pointer to the sentinel head of the linked list
Node *List::get_head()
{
    return sentinel_head;
}