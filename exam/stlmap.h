#ifndef STLMAP_H
#define STLMAP_H
#include "datastructure.h"
#include <map>
#include <algorithm>



template<typename K, typename V>
class StlMap: public DataStructure<K,V>{


    std::map<K,V> l;

    // DataStructure interface
public:
    void insert(K key, V data) override;
    void remove(K key) override;
    V find(K key) override;
    void graphviz(const char *filename) override;
    vector<tuple<K, V> > getKeys() override;

    StlMap();
};

template<typename K, typename V>
StlMap<K, V>::StlMap()
{

}

template<typename K, typename V>
void StlMap<K, V>::insert(K key, V data)
{
    l[key]=data;
}

template<typename K, typename V>
void StlMap<K, V>::remove(K key)
{
    l.erase(key);
}

template<typename K, typename V>
V StlMap<K, V>::find(K key)
{
    typename std::map<K,V>::iterator it;
    if(it!= l.end()) return l[key];
}

template<typename K, typename V>
void StlMap<K, V>::graphviz(const char *filename)
{
    ofstream fout(filename);
    fout << "digraph {\n";
    for (auto const& i : l) {
         fout << '\"' << get<0>(i) << " - " << get<1>(i)<< '\"';
    }
    fout << ";\n}";
    fout.close();
}

template<typename K, typename V>
vector<tuple<K, V> > StlMap<K, V>::getKeys()
{
    vector<tuple<K, V> > v;
    for (auto const& i : l) {
        v.push_back(i);
    }
    return v;
}
#endif // STLMAP_H
