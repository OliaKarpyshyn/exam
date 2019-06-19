#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include <vector>
#include <tuple>
#include <fstream>
#include <utility>
#include <stack>

using namespace std;

template<typename K,typename V>
class DataStructure{
public:


    virtual void insert(K key,V data) = 0;
    virtual void remove(K key) = 0;
    virtual V find(K key) = 0;
    virtual void graphviz(const char *filename)=0;

    virtual vector<tuple<K,V>> getKeys() = 0;

};

#endif // DATASTRUCTURE_H
