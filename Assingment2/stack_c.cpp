#include "stack_c.h"
#include <iostream>
    Stack_C::Stack_C(){
        try{
        stk=new List();
        } catch (std::bad_alloc const&) {
            throw std::runtime_error("Out of Memory");
        }
    }

    // Destructor
    Stack_C::~Stack_C(){
        delete stk;
    }

    void Stack_C::push(int data){
        stk->insert(data);
    }

    int Stack_C::pop(){
        if(!(stk->get_size()))throw std::runtime_error("Empty Stack");
        return stk->delete_tail();
    }

    int Stack_C::get_element_from_top(int idx){
        int q=stk->get_size();
        if(idx>q-1)
        throw std::runtime_error("Index out of range");
        return this->get_element_from_bottom(stk->get_size()-idx-1);
    }

    int Stack_C::get_element_from_bottom(int idx){
        if(idx>stk->get_size()-1)throw std::runtime_error("Index out of range");
        Node* i=stk->get_head()->next;
        for(;i;i=i->next){
            if(idx==0)return i->get_value();
            idx--;
        }
        return i->get_value();
    }

    void Stack_C::print_stack(bool top_or_bottom){
        Node* i=stk->get_head()->next;
        if(!(i->next)){std::cout<<std::endl;return;}
        if(top_or_bottom){
            while(i->next)i=i->next;
            i->prev;
            for(;i->prev;i=i->prev){
                std::cout<<i->get_value()<<std::endl;
            }
        }
        else{
            for(;i->next;i=i->next){
                std::cout<<i->get_value()<<std::endl;
            }
        }
    }

    int Stack_C::add(){
        if(stk->get_size()<2)throw std::runtime_error("Not Enough Arguments");
        int a=this->pop()+this->pop();
        this->push(a);
        return a;
    }

    int Stack_C::subtract(){
        if(stk->get_size()<2)throw std::runtime_error("Not Enough Arguments");
        int c=this->pop(),b=this->pop();
        int a=b-c;
        this->push(a);
        return a;
    }

    int Stack_C::multiply(){
        if(stk->get_size()<2)throw std::runtime_error("Not Enough Arguments");
        int a=this->pop()*this->pop();
        this->push(a);
        return a;
    }

    int Stack_C::divide(){
        if(stk->get_size()<2)throw std::runtime_error("Not Enough Arguments");
        int a=this->pop(),b=this->pop();
        if(a==0)throw std::runtime_error("Division by zero");
        int c=b/a;
        if(b%a!=0&&1.0*b/a<0)
        {this->push(c-1);return c-1;}
        this->push(c);
        return c;
    }

    List* Stack_C::get_stack(){
        return stk;
    } // Get a pointer to the linked list representing the stack

    int Stack_C::get_size(){
        return stk->get_size();
    } // Get the size of the stack
