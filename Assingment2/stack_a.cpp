#include "stack_a.h"
#include <iostream>
Stack_A::Stack_A()
{
    size = -1;
}

void Stack_A::push(int data)
{
    if (size == 1023)
        throw std::runtime_error("Stack Full");
    stk[++size] = data;
}

int Stack_A::pop()
{
    if (size == -1)
        throw std::runtime_error("Empty Stack");
    return stk[size--];
}

int Stack_A::get_element_from_top(int idx)
{
    if (idx > size)
        throw std::runtime_error("Index out of range");
    return stk[size - idx];
}

int Stack_A::get_element_from_bottom(int idx)
{
    if (idx > size)
        throw std::runtime_error("Index out of range");
    return stk[idx];
}

void Stack_A::print_stack(bool top_or_bottom)
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

int Stack_A::add()
{
    if (size < 1)
        throw std::runtime_error("Not Enough Arguments");
    this->push(this->pop() + this->pop());
    return stk[size];
}

int Stack_A::subtract()
{
    if (size < 1)
        throw std::runtime_error("Not Enough Arguments");
    int a = this->pop(), b = this->pop();
    this->push(b - a);
    return stk[size];
}

int Stack_A::multiply()
{
    if (size < 1)
        throw std::runtime_error("Not Enough Arguments");
    this->push(this->pop() * this->pop());
    return stk[size];
}

int Stack_A::divide()
{
    if (size < 1)
        throw std::runtime_error("Not Enough Arguments");
    int a = this->pop(), b = this->pop();
    if (b == 0)
        throw std::runtime_error("Division by zero");
    if (b%a!=0&&1.0*b/a<0)
        this->push(b/a-1);
    else
        this->push(b/a);
    return stk[size];
}

int *Stack_A::get_stack()
{
    return stk;
} // Get a pointer to the array

int Stack_A::get_size()
{
    return size + 1;
} // Get the size of the stack
