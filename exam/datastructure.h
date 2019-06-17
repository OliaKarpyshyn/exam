#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#include <vector>
#include <tuple>

using namespace std;

template<typename K,typename V>
class DataStructure{
public:

    enum Type{BplusTree,RedBlack,LinkedList,HashTable,StlList,StlMap,StlVector};

    virtual void insert(K key,V data) = 0;
    virtual void remove(K key) = 0;
    virtual V find(K key) = 0;
    virtual void writeGv(const char* filename) = 0;
    int getType(){return static_cast<int>(type);}

    virtual DataStructure<K,V>* Union( DataStructure<K,V>*s) = 0;

    virtual DataStructure<K,V>* Intersection( DataStructure<K,V>*s) = 0;

    virtual DataStructure<K,V>* SymDiff( DataStructure<K,V>*s) = 0;

    virtual DataStructure<K,V>* Diff( DataStructure<K,V>*s) = 0;

    virtual vector<tuple<K,V>> getKeys() = 0;

    virtual void sort() = 0;

    virtual void clear() = 0;
protected:
    Type type;
};

#endif // DATASTRUCTURE_H
