// =====================================================================================
// 
//       Filename:  Ex01_Calculator.cpp
// 
//    Description:  Program for a calculator(using only single digits)
// 
//        Version:  0.01
//        Created:  Friday 10 July 2015 01:55:39  IST
//       Revision:  none
//       Compiler:  clang 3.5
// 
//         Author:  kchary@andrew.cmu.edu
//        Company:  Carnegie Mellon University
// =====================================================================================


#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<stdlib.h>

using namespace std;

const int SIZE = 20;


char intVal[SIZE] = {0};
char value[SIZE] = {0};
int top;

void pushInt(int str)
{
    if(top == SIZE-1)
    {
        cout<<"Stack is full!"<<endl; 

    }
    else
    {
        top = top +1;
        intVal[top]=str;
    }

}
void push(char str)
{
    if(top == SIZE-1)
    {
        cout<<"Stack is full!"<<endl; 

    }
    else
    {
        top = top +1;
        value[top]=str;
    }

}

int popInt()
{
    int popped;

    if(top == 0)
    {
        cout<<"Stack is empty!"<<endl;
        return top;
    }
    else
    {
        popped = intVal[top];
        top = top - 1;
    }
    return popped;
}

char pop()
{
    char popped;

    if(top == 0)
    {
        cout<<"Stack is empty!"<<endl;
        return top;
    }
    else
    {
        popped = value[top];
        top = top - 1;
    }
    return popped;
}

bool IsOperator(char ch)
{
    if(ch == '+'||ch == '-'||ch == '*'||ch == '/'||ch == '(') 
    {
        return true;
    }
    else
    {
        return false;
    }
}

int IsOperand(char ch)
{
    //checking if it is not an operator or paranthesis
    if(!(IsOperator(ch)) && ch != ')')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// This function compares op1 and op2. It returns false if op1> op2
// indicating that the stack doesn't need to be popped.
// Otherwise it returns true which indicates that op1 < op2.
// In this case we need to pop out the operators and push them
// into the postfix expression until we get a condition op1 > op2
int CompareOps(char op1, char op2)
{

    //checking if op1 > op2
    if((op1 == '/' || op1 =='*') && (op2 == '+'|| op2 == '-'))
    {
        return 0;
    }
    //checking if op1 < op2 and returning true if it is
    else if((op1 == '-' || op1 =='+')&&(op2 == '*'|| op2 == '/'))
    {
        return 1;
    }
    else
    {
        //   do nothing 
    }

}

int Display(string &postfix)
{
    int size = 0;
    char ch = 'a';

    while( ch!= '\0')
    {
        ch = postfix[size];
        cout<<postfix[size];
        size++;
    }
    cout<<endl;
    cout<<"Size in Display:"<<size<<endl;
    return (size-1);
}


string ConvertToPostfix(string &infix,int &size)
{
    char ch, discard;
    string postfix;
    int index = 0;

    for(int i = 0;i < size; i++)
    {
        if(IsOperand(infix[i]))
        {
            postfix[index] = infix[i];
            index++;
        }
        else if(IsOperator(infix[i]))
        {
            //compares if infix[i] is less than stack[top]. It pops until infix[i] > top of the stack 
            //and adds to postfix
            //returns 1 if infix < stack[top] indicating to pop until infix > stack[top] and then 
            //push the operand onto the stack
            //returns 0 if infix > stack[top] indicating to stop popping and push the 
            //operand onto the stack


            //checking if there is some other operand in the stack to compare it to. otherwise push infix[i]
            if(value[top] != 0 && infix[i] != '(' && value[top] != '(') 
            {
                while(CompareOps(infix[i],value[top])  && (top!= 0))
                {
                    ch = pop();
                    postfix[index] = ch;
                    index++;
                }

            }   //then it pushes the operand into the stack
            push(infix[i]);


            //          cout<<"Pushed:"<<infix[i]<<endl;
        }
        else if(infix[i] == ')')
        {
            //pop values from the stack and add to postfix till we encounter a '('
            while(value[top]!= '(')
            {
                ch = pop();
                postfix[index] = ch;
                index++;
            }
            //pop the '('
            discard =  pop();
        }
    }
    //if stack is not empty, then pop all the operands
    while(top!= 0)
    {
        ch = pop();
        postfix[index] = ch;
        index++;
    }
    return postfix;

}

void Calculate(string &postfix,int &size)
{
    int i,op1,op2,result, op;
    int temp;
    char str;
    result = 0;

    cout<<"Size in cal:" <<size<<endl;
    for(i = 0; i < size; i++)
    {
        if(IsOperand(postfix[i]))
        {
            str = postfix[i];
            temp = str - '0';
            cout<<"pushed value is:"<<temp<<endl;
            pushInt(temp);
        }
        else
        {
            op2 = popInt();
            cout<<"Popped:"<<op2<<endl;
            op1 = popInt();
            cout<<"Popped:"<<op1<<endl;
            cout<<"Operator is:"<<postfix[i]<<endl;

            switch(postfix[i])
            {
                case '+':
                    result = op1 + op2;
                    cout<<"Result = "<<result<<endl;
                    pushInt(result);
                    break;

                case '-':
                    result = op1 - op2;
                    cout<<"Result = "<<result<<endl;
                    pushInt(result);
                    break;

                case '*':
                    result = op1 * op2; 
                    cout<<"Result = "<<result<<endl;
                    pushInt(result);
                    break;

                case '/':
                    result = (op1 / op2);
                    cout<<"Result = "<<result<<endl;
                    pushInt(result);
                    break;

                default:
                    cout<<"Not an operand"<<endl;
                    break;
            }
        }
    }

    cout<<"Result is:"<<result<<endl;
}

int main()
{
    string infix;

    cout<<"Enter operation to evaluate:(single digits only)";
    cin>> infix;

    int size = infix.size();
    string postfix;

    postfix = ConvertToPostfix(infix,size);
    size = Display(postfix);
    cout<<"Size after Display:"<<size<<endl;
    Calculate(postfix,size); 

    return 0;
}
