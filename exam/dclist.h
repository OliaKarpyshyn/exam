#ifndef DCLIST_H
#define DCLIST_H

#include "datastructure.h"
#include<iostream>
#include <vector>
#include <QtGlobal>
using namespace std;


template<typename K,typename V>

class DCList: public DataStructure<K,V>
{
	
public:
	DCList();

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

    // DataStructure interface
public:
    void insert(K data,V value)override;
    void remove(K key)override;
    V find(K key)override;
    void graphviz(const char *filename);
    vector<tuple<K,V>> getKeys()override;

};

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
        
        if (head->getKey() == val) {
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
        while (prev->getNext()->getKey() != val) {
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
            if (temp->getKey() == val)
                return true;
            temp = temp->getNext();
        } while (temp != head);
        return NULL;
    }

    template<typename K, typename V>
    void DCList<K,V>::graphviz(const char *filename)
    {
        if (head == nullptr) {
            return;
        }
        Node<K,V>*cur = head;

        std::ofstream fout(filename);
        fout << "digraph{node[shape=record]\n" << std::endl;


        do {
                fout << "      " << (quintptr)cur;
                fout << "[label=\"";
                fout << "{key: " << cur->getKey() << "|val:" << cur->getVal() << "}";
                fout << "\"];" << std::endl;
                cur = cur->getNext();
        } while (cur!=head);
        fout << "\n\n";

        cur = head;

        fout << (quintptr)cur;
        cur = cur->getNext();

        while (cur!=head) {
            fout << "->" << (quintptr)cur << ";\n";
            fout << (quintptr)cur;
            cur = cur->getNext();
        }

        fout << "->" << (quintptr)cur << ";\n";
        cur = head;

        fout << (quintptr)cur;
        cur = cur->getPrev();
        while (cur!=head) {
            fout << "->" << (quintptr)cur << ";\n";
            fout << (quintptr)cur;
            cur = cur->getPrev();
        }

fout << "->" << (quintptr)cur << ";\n";

        fout << "}";
    }



    template<typename K, typename V>
    vector<tuple<K, V> > DCList<K,V>::getKeys()
    {
        vector<tuple<K,V>> res;
        if (head == nullptr) {
            return res;
        }

        Node<K,V>*cur = head;
        do {
           // tuple<K,V> = make_tuple()
                res.push_back(make_tuple(cur->getKey(), cur->getVal()));
                cur = cur->getNext();
        } while (cur!=head);

    }
    
#endif // DCLIST_H
