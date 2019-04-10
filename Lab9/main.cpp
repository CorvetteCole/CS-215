#include <iostream>
using namespace std;

// CLASS NODE INTERFACE
class node {
public:
    friend class stack; // allow methods of class stack to access private members
    node(){
        data = 0;
        next = nullptr;
    };			    // give initial values to data members
private:
    int  data;			// data for this node
    node * next;		// pointer to the next node in the list
};

// CLASS NODE IMPLEMENTATION (write the constructor here)



// CLASS STACK INTERFACE
class stack {
public:
    stack(){
        top = nullptr;
    };			// init stack to empty stack
    void push(int x){
        node * n = new node;
        n -> data = x;
        n -> next = top;
        top = n;
    };	// allocate a new node, copy x into it, put it on the top of the stack
    int  pop(){
        int oldData = top -> data;
        node * n = top;
        top = top -> next;
        delete n;
        return oldData;
    };			// deallocate the top node and return the data that was in it.
    // print "Stack empty" and return 0 when the stack is empty.
    void print(){
        cout << "STACK (top first): " << endl;
        node * tmp = top;
        for (;tmp; tmp = tmp -> next){
            cout << tmp -> data << endl;
        }

    };		// print the data of all nodes, left to right, starting with the top.
private:
    node * top;			// pointer to top node of the stack, or NULL when stack is empty
};

// CLASS STACK IMPLEMENTATION (write methods here)



// MAIN
int main() {
    stack s;
    int data, opt = 0;
    const int exit = 4;
    while (opt != exit) {
        cout << "\n1. Push\n2. Pop\n3. Print\n4. Exit\n===> ";
        cin >> opt;
        switch (opt) {
            case 1: cout << "Enter data to push: ";
                cin >> data;
                s.push(data);
                break;
            case 2: data = s.pop();
                cout << "Popped: " << data << endl;
                break;
            case 3: s.print(); break;
            case exit: cout << "Bye!\n"; break;
            default:   cout << "Invalid option, try again\n";
        }
    }
    system("pause");
    return 1;
}