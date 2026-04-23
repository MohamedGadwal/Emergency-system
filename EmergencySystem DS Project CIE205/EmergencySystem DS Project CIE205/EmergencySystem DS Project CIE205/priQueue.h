#pragma once
#include "priNode.h"

template <typename T> class priNode;
    //This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
protected:
    priNode<T>* head;
    int queueSize;
   // priQueue<T> clone; // just to use it in printing, nothing else.
public:
    priQueue() : head(nullptr) {
        queueSize = 0;
    }
    priQueue(const priQueue<T>& pQ) {

        head = nullptr;
        priNode<T>* ptrNode = pQ.head;
        int priority;
        while (ptrNode) {
            enqueue(ptrNode->getItem(priority), ptrNode->getPri());
            ptrNode = ptrNode->getNext();
        }
    }

   


    void printQ() {
        priQueue<T> ClonedQ = priQueue(*this);
        T x;
        int pri;
        while (ClonedQ.dequeue(x, pri))
            cout << *x << ", ";
    }


    



    int getSize() {
        return queueSize;
    }



    virtual ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp,p));
    }

    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);
        queueSize++;
        if (head == nullptr || priority > head->getPri()) {
            
            newNode->setNext(head);
            head = newNode;
            return;
        }
       
        priNode<T>* current = head;        
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext( current->getNext());
        current->setNext( newNode);  
        
    }

    bool dequeue(T& topEntry, int& pri) {
      
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        queueSize--;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        pri = head->getPri();
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
};

template <typename T>
class CancelationQueue : public priQueue<T> {

public:
    CancelationQueue() : priQueue<T>() {
        
    }
    
    void cancel(T cancelInput, int Inputpri) {
        /*priNode<T>* tmp = this->head;
        while(tmp == cancelInput)*/
        priQueue<T> clone = priQueue<T>(*this);
        T x;
        int pri;
        while (this->dequeue(x, pri)) { continue; }

        
        while (clone.dequeue(x, pri)) {
            if (x == cancelInput && Inputpri == pri) {
                continue;
            }

            this->enqueue(x, pri);

        }
    }
};