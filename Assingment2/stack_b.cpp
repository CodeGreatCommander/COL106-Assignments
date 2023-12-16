#include "stack_b.h"
#include <iostream>
int max(int a, int b)
{
    return a > b ? a : b;
}
Stack_B::Stack_B()
{
    try{
    size = -1;
    capacity = 1024;
    stk = new int[capacity];
    } catch (std::bad_alloc const&) {
        throw std::runtime_error("Out of Memory");
    }
}

// Destructor
Stack_B::~Stack_B()
{
    delete[] stk;
}

void Stack_B::push(int data)
{
    try{
    if (size == capacity - 1)
    {
        capacity *= 2;
        int *temp = new int[capacity];
        for (int i = 0; i <= size; i++)
            temp[i] = stk[i];
        delete[] stk;
        stk = temp;
    }
    stk[++size] = data;}
    catch (std::bad_alloc const&) {
        throw std::runtime_error("Out of Memory");
    }
}
int Stack_B::pop()
{
    try{
    if (size == -1)
        throw std::runtime_error("Empty Stack");
    int a = stk[size--];
    if (size < capacity / 4)
    {
        capacity = max((int)(0.5 * capacity), 1024);
        int *temp = new int[capacity];
        for (int i = 0; i <= size; i++)
            temp[i] = stk[i];
        delete[] stk;
        stk = temp;
    }
    return a;
    }catch (std::bad_alloc const&) {
        throw std::runtime_error("Out of Memory");
    }
}

int Stack_B::get_element_from_top(int idx)
{
    if (idx > size)
        throw std::runtime_error("Index out of range");
    return stk[size - idx];
}

int Stack_B::get_element_from_bottom(int idx)
{
    if (idx > size)
        throw std::runtime_error("Index out of range");
    return stk[idx];
}

void Stack_B::print_stack(bool top_or_bottom)
{
    if (top_or_bottom)
    {
        int i = size;
        while (i >= 0)
            std::cout << stk[i--] << std::endl;
    }
    else
    {
        int i = 0;
        while (i <= size)
            std::cout << stk[i++] << std::endl;
    }
}

int Stack_B::add()
{
    if (size < 1)
        throw std::runtime_error("Not Enough Arguments");
    this->push(this->pop() + this->pop());
    return stk[size];
}
int Stack_B::subtract()
{
    if (size < 1)
        throw std::runtime_error("Not Enough Arguments");
    int a = this->pop(), b = this->pop();
    this->push(b - a);
    return stk[size];
}
int Stack_B::multiply()
{
    if (size < 1)
        throw std::runtime_error("Not Enough Arguments");
    this->push(this->pop() * this->pop());
    return stk[size];
}
int Stack_B::divide()
{
    if (size < 1)
        throw std::runtime_error("Not Enough Arguments");
    int a = this->pop(), b = this->pop();
    if (a == 0)
        throw std::runtime_error("Division by zero");
    if (b%a!=0&&1.0*b/a< 0)
        this->push(b/a-1);
    else
        this->push(b/a);
    return stk[size];
}

int *Stack_B::get_stack()
{
    return stk;
} // Get a pointer to the array

int Stack_B::get_size()
{
    return size + 1;
} // Get the size of the stack
