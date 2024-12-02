#ifndef DOUBLYLL_DOUBLYLL_H
#define DOUBLYLL_DOUBLYLL_H
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

template <class T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};


template <class T>
class DoublyLL {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    DoublyLL() : head(nullptr), tail(nullptr), size(0) {}

    DoublyLL(const DoublyLL<T>& b) {
        head = tail = nullptr;
        size = 0;

        Node<T>* current = b.head;
        while (current != nullptr) {
            insert_at_end(current->data);
            current = current->next;
        }
    }

    ~DoublyLL() {
        clear();
    }

    Node<T>* getHead(){
        return head;
    }

    Node<T>* getTail(){
        return tail;
    }

    void traverse() const {
        if(size == 0){
            cout << "Empty!\n";
            return;
        }
        int smallWidth = 8, bigWidth = 20;
        int id = 0;
        Node<T>* current = head;
        while (current != nullptr) {
            cout << "| "<< setw(smallWidth) << id << current->data << " |\n";
            current = current->next;
            id++;
        }
    }

    void reverse_traverse() const {
        Node<T>* current = tail;
        while (current != nullptr) {
            cout << current->data;
            current = current->prev;
        }
        cout << endl;
    }

    bool search(T val) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == val) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int getSize() const {
        return size;
    }

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current->next;
            delete current;
            current = temp;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    T& getElement(int index){
        Node<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    void insert_at_begin(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void insert_at_end(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insert_at(T val, int index) {
        if (index > size || index < 0) {
            cout << "Invaild Index! Out of Range\n";
            SleepForSecond();
            return;
        }

        if (index == 0) {
            insert_at_begin(val);
        } else if (index == size) {
            insert_at_end(val);
        } else {
            Node<T>* newNode = new Node<T>(val);
            Node<T>* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;

            size++;
        }
    }

    void delete_at_begin() {
        if (head == nullptr) {
            cout << "Empty list" << endl;
            return;
        }
        Node<T>* temp = head;
        if (head == tail) { // Only one element
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
        size--;
    }

    void delete_at_end() {
        if (tail == nullptr) {
            cout << "Empty list" << endl;
            return;
        }
        Node<T>* temp = tail;
        if (head == tail) { // Only one element
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
        size--;
    }

    void delete_at(int index) {
        if (index >= size || index < 0) {
            cout << "Invaild ID! Doesn't Exist ...\n";
            SleepForSecond();
            return;
        }

        if (index == 0) {
            delete_at_begin();
        } else if (index == size - 1) {
            delete_at_end();
        } else {
            Node<T>* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            size--;
        }
    }

    void shuffle() {
        if (size <= 1) return;

        vector<T> values;
        Node<T>* current = head;
        while (current != nullptr) {
            values.push_back(current->data);
            current = current->next;
        }

        srand(time(0));
        for (int i = values.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(values[i], values[j]);
        }

        current = head;
        int index = 0;
        while (current != nullptr) {
            current->data = values[index++];
            current = current->next;
        }
    }

};



#endif //DOUBLYLL_DOUBLYLL_H
