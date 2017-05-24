//===========================================================================
//                              Infix to Postfix
//                      Developed By: Leron Julian
//               PROGRAM COMPLETED PER PROGRAM SPECIFICATION
//===========================================================================

#include <iostream>
#include <string>
#include "Stack.h"
using namespace std;

string Infix_To_Postfix(string expression);
bool is_Operand(char temp);
bool is_Operator(char temp);
int Precedence(char operator1, char operator2);
int getPrecedence(char Infix_Operator);

void evaluatePostFix(string postFix);
int do_Operation(int operand1, int operand2, char operater);
string to_base36(int val);

int main() {
    
    int choice;
    int min = 1;
    int max = 3;
    
    do{
        cout << "Enter 1 to input an infix program and convert to postfix" << endl;
        cout << "Enter 2 to input a postfix and evaluate the postfix expression" << endl;
        cout << "Enter 3 to input an infix expression, convert to postfix, and evaluate" << endl;
        cout << "Enter a choice -> ";
        cin >> choice;
        
        if (cin.fail()) {
            
            cin.clear() ;
            cin.ignore(1000, '\n');
            cout << endl << "ENTER a valid input " << endl << endl;
            continue ;
        }
        
        cin.clear();
        cin.ignore(500, '\n');
        
        if (choice < min || choice > max)
            cout << endl << "ENTER a number in the valid range " << endl << endl;
        
    } while (choice < min || choice > max);
    
    
    cout << endl;
    
    switch (choice) {
        case 1:
        {
            string infix, postfix;
            
            cout << "Enter an infix expression -> ";
            getline(cin, infix);
            
            infix.erase(remove(infix.begin(),infix.end(), ' '),infix.end());
            
            cout << endl;
            
            postfix = Infix_To_Postfix(infix);
            
            cout << "Infix expression: " << infix << endl;
            cout << "Postfix expression: " << postfix << endl << endl;
            break;
        }
            
        case 2:
        {
            string postfix;
            
            cout << "Enter a postfix expression -> ";
            getline(cin, postfix);
            
            postfix.erase(remove(postfix.begin(),postfix.end(), ' '),postfix.end());
            
            string expression;
            
            cout << endl;
            cout << "Postfix Expression: " << postfix << endl;
            cout << "Evaluated Postfix Expression: ";
            evaluatePostFix(postfix);
            
            cout << endl;
          
            break;
        }
            
        case 3:
        {
            string infix, postfix;
            
            cout << "Enter an infix expression -> ";
            getline(cin, infix);
            
            infix.erase(remove(infix.begin(),infix.end(), ' '),infix.end());
            
            cout << endl;
            
            postfix = Infix_To_Postfix(infix);
            
            cout << endl;
            cout << "Infix expression: " << infix << endl;
            cout << "Postfix expression: " << postfix << endl;
            cout << "Evaluated Postfix Expression: ";
            evaluatePostFix(postfix);
            
            cout << endl;
            
            break;
        }
    }
    
    return 0;
}

//===========================================================================
// This function is the main function that converts from infix to postfix
//===========================================================================
string Infix_To_Postfix(string expression)
{
    Stack Character_Stack;
    
    int size = expression.size();
    string result;
    
    for (int i = 0; i < (size); i++)
    {
        if (is_Operand(expression[i]))
            result += expression[i];
        
        else if (is_Operator(expression[i]))
        {
            while (!Character_Stack.is_empty() && Precedence(Character_Stack.top(), expression[i]) && Character_Stack.top() != '(')
            {
                result += Character_Stack.top();
                Character_Stack.pop();
            }
            
            Character_Stack.push(expression[i]);
        }
        
        else if (expression[i] == '(')
            Character_Stack.push(expression[i]);
        
        else if (expression[i] == ')')
        {
            while (!Character_Stack.is_empty() && Character_Stack.top() != '(')
            {
                result += Character_Stack.top();
                Character_Stack.pop();
            }
            
            if(!Character_Stack.is_empty())
                Character_Stack.pop();
        }
    }
    
    while (!Character_Stack.is_empty())
    {
        result += Character_Stack.top();
        Character_Stack.pop();
    }
    
    return result;
}

//===========================================================================
// This function determines wheter a character is an operand or not
//===========================================================================
bool is_Operand(char temp)
{
    if (temp >= '0' && temp <= '9')
        return true;
    
    if (temp >= 'a' && temp <= 'z')
        return true;
    
    if (temp >= 'A' && temp <= 'Z')
        return true;
    
    return false;
}

//===========================================================================
// This function determines whether a character is an operator or not
//===========================================================================
bool is_Operator(char temp)
{
    if (temp == '+' || temp == '-' || temp == '*' || temp == '/')
        return true;
    
    return false;
}

//===========================================================================
// This function returns the precedence of an operator
//===========================================================================
int Precedence(char operator1, char operator2)
{
    int operator1_Precedence = getPrecedence(operator1);
    int operator2_Precedence = getPrecedence(operator2);
    
    if (operator1_Precedence == operator2_Precedence)
        return true;
    else if (operator1_Precedence > operator2_Precedence)
        return true;
    else
        return false;
}

//===========================================================================
// This function gets the precedence of an operator
//===========================================================================
int getPrecedence(char Infix_Operator)
{
    switch (Infix_Operator)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0.;
    }
}

//===========================================================================
// This function does the operation on two operands in the postfix
//===========================================================================
int do_Operation(int operand1, int operand2, char operater) {
    switch (operater)
    {
        case '*':
            return (operand2 * operand1);
        case '/':
            return (operand2 / operand1);
        case '+':
            return (operand2 + operand1);
        case '-':
            return (operand2 - operand1);
        default :
            return 0;
    }
}

//===========================================================================
// This function converts an integer to a base 36 integer
//===========================================================================
string to_base36(int val)
{
    string base36 = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result;
    
    do {
        result = base36[val % 36] + result;
    } while (val /= 36);
    
    return result;
}

//===========================================================================
// This function evaluates a postfix expression
//===========================================================================
void evaluatePostFix(string postFix)
{
    Stack charStack;
    
    int value = 0;
    char ch;
    
    int i = 0;
    int size = postFix.size();
    
    while (i < size)
    {
        ch = postFix[i];
        
        if ( ch == 'A' || ch == 'B')
        {
            charStack.push(ch - '0');
        }
        
        else if (isdigit(ch))
            charStack.push(ch - '0');
        
        else
        {
            int operand1 = charStack.top();
            charStack.pop();
            
            int operand2 = charStack.top();
            charStack.pop();
            
            value = do_Operation(operand1, operand2, ch);
            charStack.push(value);
        }
        
        i++;
    }
    
    string result;
   
    if (value > 0)
    {
        result = to_base36(value);
        cout << result << endl;
    }
    
    else
        cout << value << endl;
}
