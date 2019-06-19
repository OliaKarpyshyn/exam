#ifndef STLVECTOR_H
#define STLVECTOR_H
#include "datastructure.h"
#include <vector>
#include <algorithm>



template<typename K, typename V>
class StlVector: public DataStructure<K,V>{


    vector<tuple<K,V>> l;

    // DataStructure interface
public:
    void insert(K key, V data) override;
    void remove(K key) override;
    V find(K key) override;
    void graphviz(const char *filename) override;
    vector<tuple<K, V> > getKeys() override;

    StlVector();
};

template<typename K, typename V>
StlVector<K, V>::StlVector()
{

}

template<typename K, typename V>
void StlVector<K, V>::insert(K key, V data)
{
    l.emplace_back(make_tuple(key, data));
}

template<typename K, typename V>
void StlVector<K, V>::remove(K key)
{
    auto element = std::find_if(l.begin(),l.end(),[key](const tuple<K,V>&pair){return get<0>(pair) == key;});
    if(element !=l.end())
    {
        l.erase(element);
    }
}

template<typename K, typename V>
V StlVector<K, V>::find(K key)
{
    for (auto const& i : l) {
        if(get<0>(i)==key) return get<1>(i);
    }
}

template<typename K, typename V>
void StlVector<K, V>::graphviz(const char *filename)
{
    ofstream fout(filename);
    fout << "digraph {\n";
    fout << '\"' << get<0>(l.front()) << " - " << get<1>(l.front())<< '\"';
    for (auto const& i : l) {
        if(i!=l.front()) fout << "->" << '\"' << get<0>(i) << " - " << get<1>(i)<< '\"';
    }
    fout << ";\n}";
    fout.close();
}

template<typename K, typename V>
vector<tuple<K, V> > StlVector<K, V>::getKeys()
{
    vector<tuple<K, V> > v;
    for (auto const& i : l) {
        v.push_back(i);
    }
    return v;
}
#endif // STLVECTOR_H
