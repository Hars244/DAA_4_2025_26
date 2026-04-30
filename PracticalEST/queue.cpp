#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

class Queue {
    Node* front;
    Node* rear;
    int count;  

public:
    Queue() {
        front = rear = NULL;
        count = 0;
    }

    void enqueue(int x) {
        Node* temp = new Node(x);

        if (rear == NULL) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }

        count++;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }

        Node* temp = front;
        front = front->next;

        if (front == NULL)
            rear = NULL;

        delete temp;
        count--;
    }

    int getFront() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return -1;
        }
        return front->data;
    }

    bool isEmpty() {
        return front == NULL;
    }

    int size() {
        return count;
    }

    void display() {
        Node* temp = front;
        while (temp != NULL) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

int main() {
    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    q.display();                

    cout << "Front: " << q.getFront() << endl;  
    cout << "Size: " << q.size() << endl;       

    q.dequeue();

    cout << "Front: " << q.getFront() << endl; 
    cout << "Is Empty: " << q.isEmpty() << endl; 

    return 0;
}