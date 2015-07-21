// =====================================================================================
// 
//       Filename:  Ex02_QueueArray.cpp
// 
//    Description:  Implementation of a regular queue using array
// 
//        Version:  0.01
//        Created:  Wednesday 22 July 2015 01:10:26  IST
//       Revision:  none
//       Compiler:  clang 3.5
// 
//         Author:  Vanya (SYSU-CMU), kchary@andrew.cmu.edu
//        Company:  Carnegie Mellon University
// =====================================================================================

#include<iostream>

using namespace std;

class Queue{

    private:   
        
        int queue[10];
        int front,end;

    public:
        Queue()
        {
            front = 0;
            end = -1;
        }
        ~Queue()
        {

        }
        void Insert(int ele);
        int Delete();
        void Display();

};

void Queue::Insert(int ele)
{
    if(end == 9)
    {
        cout<<"Cannot insert more elements into the queue"<<endl;
    }
    else
    {
        queue[end] = ele;
        end = end + 1;
    }
}

int Queue::Delete()
{
    int ele;

    if(front == end)
    {
        cout<<"Queue is empty"<<endl<<endl;
    }
    else
    {
        ele = queue[front];
        front = front + 1;
    }

    return ele;
}

void Queue::Display()
{
    cout<<"Elements in the queue are now:";
    for (unsigned int i = front; i < end; i++)
    {
        cout<<queue[i]<< "\t";
    }
    cout<<endl;

}

int main()
{
    Queue q;
    int choice,ele;

    cout<<"Choose an operation to perform on the Queue"<<endl;
    cout<<"1.Insert element"<<endl;
    cout<<"2.Delete element"<<endl;
    cout<<"3.Display Queue"<<endl<<endl;

    cout<<"Enter Choice(q to quit):"<<endl;
    while(cin>>choice)
    {

        switch(choice)
        {
            case 1:
                cout<<"Enter element:";
                cin>>ele;
                q.Insert(ele);
                break;
            case 2:
                ele = q.Delete();
                cout<<"Deleted element is:"<<ele<<endl;
                break;
            case 3:
                q.Display();
                break;
            default:
                cout<<"Invalid option. Please enter another choice:"<<endl;
                break;

        }
        cout<<endl;
        cout<<"Enter Choice:(q to quit)";
    }

    cout<<"Bye!\n";
    return 0;
}
