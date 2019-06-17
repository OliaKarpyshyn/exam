#ifndef DCLIST_H
#define DCLIST_H

#include<iostream>
#include <vector>
using namespace std;


template<typename K,typename V>

class DCList
{
	
public:
	DCList();

    void insert(K data,V value);
    void remove(K key);
    V find(K key);
    void randomInsert();
    void writeGV(const char* filename);
    vector<K> getKeys()override;
    void sort();
    
private:
    
    template<typename T1, typename T2>
    class Node{
        K key;
        V value;
        Node *prev;
        Node *next;
    public:
        
        Node(T1 data = T1(), T2 value = T2(), Node*next=NULL)
        {
            this->key = data;
            this->value = value;
            this->next = next;
            prev = nullptr;
            next = nullptr;
        }
        K getKey() {
            return key;
        }
        
        V getVal() {
            return key;
        }
        void setData(int data) {
            this->key = data;
        }
        Node* getPrev() {
            return prev;
        }
        Node* getNext() {
            return next;
        }
        void setPrev(Node*prev) {
            this->prev = prev;
        }
        void setNext(Node*next) {
            this->next = next;
        }
    };
        
    Node<K,V>* head;
    int size = 0;
};


#endif // DCLIST_H
    
    template<typename K, typename V>
    DCList<K,V>::DCList() {
        head = nullptr;
        size = 0;
    }
    
    template<typename K, typename V>    
    void DCList<K,V>::insert(K data,V value) {
        Node<K,V> *newNode = new Node<K,V>(data, value);
        if (newNode == nullptr) {
            return;
        }
        
        if (head == nullptr) {
            head = newNode;
            head->setNext(head);
            head->setPrev(head);
            return;
        }
        
        Node<K,V>* last = head->getPrev();
        newNode->setNext(head);
        newNode->setPrev(last);
        last->setNext(newNode);
        head->setPrev(newNode);
        size++;
        return;
    }
    
    template<typename K, typename V>        
    void DCList<K,V>::remove(K val) {
        if (head == nullptr)
            return;
        
        if (head->getData() == val) {
            if (head->getNext() == head) {
                delete head;
                head = nullptr;
                size--;
                return;
            }
            Node<K,V>* last = head->getPrev();
            Node<K,V>* del = head;
            head = head->getNext();
            last->setNext(head);
            head->setPrev(last);
            delete del;
            size--;
            return;
        }
        
        Node<K,V>* prev = head;
        while (prev->getNext()->getData() != val) {
            if (prev->getNext() == head)
                return;
            prev = prev->getNext();
        };
        Node<K,V>* del = prev->getNext();
        prev->setNext(del->getNext());
        del->getNext()->setPrev(prev);
        delete del;
        size--;
        return;
    }
    
    template<typename K, typename V>        
    V DCList<K,V>::find(K val) {
        Node<K,V>*temp = head;
        do{
            if (temp->getData() == val)
                return true;
            temp = temp->getNext();
        } while (temp != head);
        return nullptr;
    }
    
    template<typename K, typename V>
    void DCList<K,V>::randomInsert()
    {
        
    }
    
    template<typename K, typename V>        
    void DCList<K,V>::writeGV(const char* filename) {
        if (head == nullptr) {
            return;
        }
        Node<K,V>* temp = head;
        do {
            cout << temp->getData()<<" ";
            temp = temp->getNext();
        } while (temp!=head);
    }
    
