//===========================================================================
//                              Infix to Postfix
//                      Developed By: Leron Julian
//               PROGRAM COMPLETED PER PROGRAM SPECIFICATION
//===========================================================================

#ifndef Stack_h
#define Stack_h
#include <string>
#include <iostream>

using namespace std;
typedef int XType;
#define ERROR INT_MIN

class Stack
{
public:
    Stack();
    ~Stack();
    
    bool is_empty() const;
    bool is_full() const;
    
    XType top() const;
    
    int size() const;
    
    void push(XType);
    void pop();
    
private:
    struct Struct_Node
    {
        XType element;
        
        Struct_Node *Next;
    };
    
    typedef Struct_Node *Struct_Ptr;
    Struct_Ptr TOS;
    
};

Stack::Stack()
{
    TOS = NULL;
}

Stack::~Stack()
{
    TOS = NULL;
}

bool Stack:: is_empty() const
{
    return (TOS == NULL);
}

bool Stack::is_full() const
{
    return (false);
}

XType Stack::top() const
{
    if (!this->is_empty())
        return (TOS->element);
    else
    {
        cout << "This stack is empty " << endl;
        return ERROR;
    }
    
}

int Stack::size() const
{
    int i = 0;
    Struct_Ptr temp = TOS;
    
    while (temp != NULL)
    {
        i++;
        temp = temp->Next;
    }
    
    return(i);
}

void Stack::push(XType item)
{
    if (!this->is_full())
    {
        Struct_Ptr temp = new Struct_Node;
        
        temp->element = item;
        temp->Next = TOS;
        TOS = temp;
    }
    
}

void Stack::pop()
{
    if (!this->is_empty())
        TOS = TOS->Next;    
}


#endif /* Stack_h */
