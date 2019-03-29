#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

template <typename ItemType>
class LinkedList {
public:
    /*
    class Node {
        public:
        ItemType value;
        Node *next;
        
        Node(ItemType val) {
            value = val;
            next = NULL
        }
    }
    */
    ~LinkedList() {
        cout << "The linked list deconstructor was called" << endl;
        
        while (length > 0) {
            remove(0);
        }
    }
    struct Node { //KIND OF LIKE A CLASS (BABY CLASS) CAN USE ABOVE CODE. EVERYTHING IS PUBLIC IN A STRUCT
        ItemType value;
        Node *next; //integer that points to a new thing which is the same type as me
        
        Node(ItemType val) {
            value = val;
            next = NULL;
        }
    };
    
    LinkedList () {
        head = NULL;
        length = 0;
    }
    void append(ItemType val) {
        //case 1: head == Null and length = 0
        if (head == NULL) {
            head = new Node(val);
            length++;
        }
        //case 2: otherwise
        else {
            Node *cur = head; //pointer to a Node. Local variable.
            for (int i = 0; i < length-1; i++) {
                cur = cur->next; //current pointer is now at whatever it was pointing to and pointing to the next. Eventually points to last item
            }
            cur->next = new Node(val);
            length++;
        }
    }
    void insert (int index, ItemType val) {
        if (index > length) {
            cout << "index out of range" << endl;
            return;
        }
        else if(index == length) {
            append(val);
        }
        else if (index == 0) {
            Node *n = new Node(val);
            n->next = head;
            head = n;
            length++;
        }
        else {
            Node *cur = head;
            for (int i = 0; i < index-1; i++) {
                cur = cur->next;
            }
            Node *beta = new Node(val);
            beta->next = cur->next;
            cur->next = beta;
            length++;
        }
    }
    void remove(int index) {
        if (index >= length) {
            cout << "index out of range" << endl;
            return;
        }
        if (index == 0) { //deleting something at head
            Node *head2 = head;
            head = head->next;
            delete head2;
            length--;
        }
        else if (index == length-1) { //deleting last item
            
        }
        else { //deleting something from the middle
            Node *cur = head;
            for (int i = 0; i < index-1; i++) {
                cur = cur->next;
            }
            Node *goner = cur->next;
            cur->next = cur->next->next;
            delete goner;
            length--;
        }
        
    }
    
    int size() {
        return length;
    }
    ItemType get(int index) {
        return NULL;
    }
    void set(int index, ItemType val) {
        
    }
    void print () {
        Node *cur = head;
        while (cur != NULL) {
            cout << cur->value << " ";
            cur = cur->next;
        }
        cout << endl;
    }
private:
    Node *head;
    int length;
};

#endif