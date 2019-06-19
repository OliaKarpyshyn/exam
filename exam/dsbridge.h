#ifndef DSBRIDGE_H
#define DSBRIDGE_H
#include "datastructure.h"
#include "stllist.h"
#include "stlmap.h"
#include "stlvector.h"
#include "dclist.h"
#include "rbtree.h"
#include "bplustree.h"
#include "sorting.h"
#include <vector>
#include <tuple>

using namespace std;


template <typename K, typename V>
class DSBridge{

public:
    DSBridge();
    Sorting<K,V> s;
    vector< DataStructure<K,V>*> ds;
    int currentStructure;
    void changeType(int);

    void insert(K key,V data);
    void remove(K key);
    V find(K key);
    void createPicture();
    QString getKeys();

    vector<tuple<K,V>> unionSet();
    vector<tuple<K,V>> intersection();
    vector<tuple<K,V>> difference();
    vector<tuple<K,V>> symDifference();

    vector<tuple<K,V>> sort(int);



};

#endif // DSBRIDGE_H

template<typename K, typename V>
DSBridge<K,V>::DSBridge()
{

    ds.push_back( new StlList<K,V>());
    ds.push_back( new StlList<K,V>());
    //ds[1] = new StlList<K,V>();
    currentStructure = 0;
}

template<typename K, typename V>
void DSBridge<K,V>::changeType(int t)
{
    switch (t) {
    case 0:
        ds[currentStructure] = new StlList<int,int>;
        break;
    case 1:
        ds[currentStructure] = new StlMap<int,int>;
        break;
    case 2:
        ds[currentStructure] = new StlVector<int,int>;
        break;
    case 3:
        ds[currentStructure] = new DCList<int,int>;
        break;
    case 4:
        ds[currentStructure] = new RBTree<int,int>;
        break;
    case 5:
        ds[currentStructure] = new BplusTree<int,int>;
        break;
    default:
        break;
    }
}

template<typename K, typename V>
void DSBridge<K,V>::insert(K key, V data)
{
    ds[currentStructure]->insert(key, data);

}

template<typename K, typename V>
void DSBridge<K,V>::remove(K key)
{
    ds[currentStructure]->remove(key);

}

template<typename K, typename V>
V DSBridge<K,V>::find(K key)
{
    return ds[currentStructure]->find(key);

}

template<typename K, typename V>
void DSBridge<K,V>::createPicture()
{

}

template<typename K, typename V>
QString DSBridge<K,V>::getKeys()
{
    vector<tuple<K, V> > v = ds[currentStructure]->getKeys();
    QString s;
    s = "Keys list:\t";

    for (int i = 0; i<v.size(); i++) {
          s += QString::number(get<0>(v[i]))+'\t';
    }

    s+="\n\nValues list:\t";
    for (int i = 0; i<v.size(); i++) {
         s+= QString::number(get<1>(v[i]))+'\t';
    }

    s+="\n\nKey-Values:\t";
    for (int i = 0; i<v.size(); i++) {
         s+= QString::number(get<0>(v[i]))+'-'+QString::number(get<1>(v[i]))+'\t';
    }

    return s;

}

template<typename K, typename V>
vector<tuple<K, V> > DSBridge<K,V>::unionSet()
{

}

template<typename K, typename V>
vector<tuple<K, V> > DSBridge<K,V>::intersection()
{

}

template<typename K, typename V>
vector<tuple<K, V> > DSBridge<K,V>::difference()
{

}

template<typename K, typename V>
vector<tuple<K, V> > DSBridge<K,V>::symDifference()
{

}

template<typename K, typename V>
vector<tuple<K, V> > DSBridge<K,V>::sort(int)
{

}
