#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include "datastructure.h"
#include <iostream>
#include <string>
#include <stack>
#include <QString>
#include <QDebug>

using namespace std;
const int MAX = 50;


struct BNode {
    int nElems;
    BNode *parent;
    int value[MAX];
    int key[MAX];
    BNode *child[MAX];
    BNode() {
        nElems = 0;
        parent = nullptr;
        for (int i = 0; i < MAX; i++) {
            value[i] = INT_MAX;
            key[i] = INT_MAX;
            child[i] = nullptr;
        }
    }
};

template <typename K, typename V>
class BplusTree: public DataStructure<K,V>
{

private:
    bool dataFound=false;
    int T = 4; //степінь [t = t + 1]
    void splitLeaf(BNode *curr);
    void splitNonLeaf(BNode *curr);
    void insertNode(BNode* curr, int val, int k);
    void redistributeCell(BNode *left, BNode *right, bool isLeaf, int posOfLeftBlock, int isCurBlock);
    void mergeCell(BNode *left, BNode *right, bool isLeaf, int posOfRightBlock);
    void deleteNode(BNode *curr, int value, int currPos);
    void getElem(vector <BNode*> Nodes, vector<tuple<K,V>>& v);
    void graphvizRec(vector <BNode*> Nodes, const char *filename);
    V search(BNode * curr, K val);



public:
    BNode* root;

    BplusTree();
    ~BplusTree();

    BNode* getRoot() { return root; }



    // DataStructure interface
public:
    void insert(K key, V data) override;
    void remove(K key) override;
    V find(K key) override;
    void graphviz(const char *filename) override;

    vector<tuple<K, V> > getKeys() override;
};

template <typename K, typename V>
V BplusTree<K, V>::find(K key)
{
    return search(root, key);
}

template <typename K, typename V>
V BplusTree<K,V>::search(BNode * curr, K val){

        if(curr->child[0]==nullptr)
            for (int i = 0; i <= curr->nElems; i++) {
            if (val == curr->value[i])
                return curr->key[i];
        }
        for (int i = 0; i <= curr->nElems; i++) {
            if (val < curr->value[i] && curr->child[i] != nullptr)
                return search(curr->child[i], val);
        }
        return NULL;

        }




using namespace std;

template <typename K, typename V>
BplusTree<K, V>::BplusTree()
{
    root = new BNode();
}

template <typename K, typename V>
BplusTree<K, V>::~BplusTree()
{
}

template <typename K, typename V>
void BplusTree<K, V>::splitLeaf(BNode *curr) {
    int x, i, j;

    if (T % 2)
    {
        x = (T + 1) / 2;
    }
    else
    {
        x = T / 2;
    }
    BNode *right = new BNode();
    curr->nElems = x;
    right->nElems = T - x;
    right->parent = curr->parent;

    for (i = x, j = 0; i < T; i++, j++) {
        right->value[j] = curr->value[i];
        right->key[j] = curr->key[i];
        curr->value[i] = INT_MAX;
        curr->key[i] = INT_MAX;
    }
    int item = right->value[0];
    int item1 = right->key[0];

    //якщо листок це корінь
    if (curr->parent == nullptr) {
        BNode *parentNode = new BNode();
        parentNode->parent = nullptr;
        parentNode->nElems = 1;
        parentNode->value[0] = item;
        parentNode->key[0] = item1;
        parentNode->child[0] = curr;
        parentNode->child[1] = right;
        curr->parent = right->parent = parentNode;
        root = parentNode;
        return;
    }
    //якщо розбитий листок це не корінь
    else
    {
        curr = curr->parent;
        BNode *newChild = new BNode();
        newChild = right;
        for (i = 0; i <= curr->nElems; i++) {
            if (item < curr->value[i]) {
                swap(curr->value[i], item);
                swap(curr->key[i], item1);
            }
        }
        curr->nElems++;
        for (i = 0; i < curr->nElems; i++) {
            if (newChild->value[0] < curr->child[i]->value[0]) {
                swap(curr->child[i], newChild);
            }
        }
        curr->child[i] = newChild;
        for (i = 0; curr->child[i] != nullptr; i++) {
            curr->child[i]->parent = curr;
        }
    }

}

//функція для розбиття нелистового вузла
template <typename K, typename V>
void BplusTree<K, V>::splitNonLeaf(BNode *curr) {
    int x, i, j;

    x = T / 2;
    BNode *right = new BNode();
    curr->nElems = x;
    right->nElems = T - x - 1;
    right->parent = curr->parent;

    for (i = x, j = 0; i <= T; i++, j++) {
        right->value[j] = curr->value[i];
        right->key[j] = curr->key[i];
        right->child[j] = curr->child[i];
        curr->value[i] = INT_MAX;
        curr->key[i] = INT_MAX;
        if (i != x)curr->child[i] = nullptr;
    }
    int item = right->value[0];
    int item1 = right->key[0];
    memcpy(&right->value, &right->value[1], sizeof(int)*(right->nElems + 1));
    memcpy(&right->key, &right->key[1], sizeof(int)*(right->nElems + 1));
    memcpy(&right->child, &right->child[1], sizeof(root)*(right->nElems + 1));

    for (i = 0; curr->child[i] != nullptr; i++) {
        curr->child[i]->parent = curr;
    }
    for (i = 0; right->child[i] != nullptr; i++) {
        right->child[i]->parent = right;
    }

    //якщо розбитий вузол це корінь
    if (curr->parent == nullptr) {
        BNode *parentNode = new BNode();
        parentNode->parent = nullptr;
        parentNode->nElems = 1;
        parentNode->value[0] = item;
        parentNode->key[0] = item1;
        parentNode->child[0] = curr;
        parentNode->child[1] = right;

        curr->parent = right->parent = parentNode;

        root = parentNode;
        return;
    }
    //якщо розбитий вузол не корінь
    else
    {
        curr = curr->parent;
        BNode *newChild = new BNode();
        newChild = right;

        for (i = 0; i <= curr->nElems; i++) {
            if (item < curr->value[i]) {
                swap(curr->value[i], item);
                swap(curr->key[i], item1);
            }
        }
        curr->nElems++;
        for (i = 0; i < curr->nElems; i++) {
            if (newChild->value[0] < curr->child[i]->value[0]) {
                swap(curr->child[i], newChild);
            }
        }
        curr->child[i] = newChild;
        for (i = 0; curr->child[i] != nullptr; i++) {
            curr->child[i]->parent = curr;
        }
    }

}

//функція вставки
template <typename K, typename V>
void BplusTree<K, V>::insert(K key, V val) {


    insertNode(root, val, key);
}

template <typename K, typename V>
void BplusTree<K, V>::insertNode(BNode *curr, int val, int k) {
    for (int i = 0; i <= curr->nElems; i++) {
        if (k < curr->value[i] && curr->child[i] != nullptr) {
            insertNode(curr->child[i], val, k);
            if (curr->nElems == T)
                splitNonLeaf(curr);
            return;
        }
        else if (k < curr->value[i] && curr->child[i] == nullptr) {
            swap(curr->value[i], k);
            swap(curr->key[i],val);
            if (i == curr->nElems) {
                curr->nElems++;
                break;
            }
        }
    }

    if (curr->nElems == T) {
        splitLeaf(curr);
    }
}

//операція перерозроділу вузлів
template <typename K, typename V>
void BplusTree<K, V>::redistributeCell(BNode *left, BNode *right, bool isLeaf, int posOfLeftBlock, int isCurBlock) {


    if (isCurBlock == 0) {
        if (!isLeaf) {
            left->value[left->nElems] = left->parent->value[posOfLeftBlock];
            left->key[left->nElems] = left->parent->key[posOfLeftBlock];
            left->child[left->nElems + 1] = right->child[0];
            left->nElems++;
            left->parent->value[posOfLeftBlock] = right->value[0];
            left->parent->key[posOfLeftBlock] = right->key[0];
            memcpy(&right->value[0], &right->value[1], sizeof(int)*(right->nElems + 1));
            memcpy(&right->key[0], &right->key[1], sizeof(int)*(right->nElems + 1));
            memcpy(&right->child[0], &right->child[1], sizeof(root)*(right->nElems + 1));
            right->nElems--;

        }
        else
        {
            left->value[left->nElems] = right->value[0];
            left->key[left->nElems] = right->key[0];
            left->nElems++;
            memcpy(&right->value[0], &right->value[1], sizeof(int)*(right->nElems + 1));
            memcpy(&right->key[0], &right->key[1], sizeof(int)*(right->nElems + 1));
            right->nElems--;
            left->parent->value[posOfLeftBlock] = right->value[0];
            left->parent->key[posOfLeftBlock] = right->key[0];
        }
    }
    else {

        if (!isLeaf) {
            memcpy(&right->value[1], &right->value[0], sizeof(int)*(right->nElems + 1));
            memcpy(&right->key[1], &right->key[0], sizeof(int)*(right->nElems + 1));
            memcpy(&right->child[1], &right->child[0], sizeof(root)*(right->nElems + 1));
            right->value[0] = left->parent->value[posOfLeftBlock];
            right->key[0] = left->parent->key[posOfLeftBlock];
            right->child[0] = left->child[left->nElems];

            right->nElems++;
            left->parent->value[posOfLeftBlock] = left->value[left->nElems - 1];
            left->parent->key[posOfLeftBlock] = left->key[left->nElems - 1];
            left->value[left->nElems - 1] = INT_MAX;
            left->key[left->nElems - 1] = INT_MAX;
            left->child[left->nElems] = nullptr;
            left->nElems--;
        }
        else
        {
            memcpy(&right->value[1], &right->value[0], sizeof(int)*(right->nElems + 1));
            memcpy(&right->key[1], &right->key[0], sizeof(int)*(right->nElems + 1));
            right->value[0] = left->value[left->nElems - 1];
            right->key[0] = left->key[left->nElems - 1];
            right->nElems++;

            left->value[left->nElems - 1] = INT_MAX;
            left->key[left->nElems - 1] = INT_MAX;
            left->nElems--;

            left->parent->value[posOfLeftBlock] = right->value[0];
            left->parent->key[posOfLeftBlock] = right->key[0];
        }
    }
}

//операція злиття вузлів
template <typename K, typename V>
void BplusTree<K, V>::mergeCell(BNode *left, BNode *right, bool isLeaf, int posOfRightBlock) {

    if (!isLeaf) {

        left->value[left->nElems] = left->parent->value[posOfRightBlock - 1];
        left->key[left->nElems] = left->parent->key[posOfRightBlock - 1];
        left->nElems++;
    }
    memcpy(&left->value[left->nElems], &right->value[0], sizeof(int)*(right->nElems + 1));
    memcpy(&left->key[left->nElems], &right->key[0], sizeof(int)*(right->nElems + 1));
    memcpy(&left->child[left->nElems], &right->child[0], sizeof(root)*(right->nElems + 1));
    left->nElems += right->nElems;
    memcpy(&left->parent->value[posOfRightBlock - 1], &left->parent->value[posOfRightBlock], sizeof(int)*(left->parent->nElems + 1));
    memcpy(&left->parent->key[posOfRightBlock - 1], &left->parent->key[posOfRightBlock], sizeof(int)*(left->parent->nElems + 1));
    memcpy(&left->parent->child[posOfRightBlock], &left->parent->child[posOfRightBlock + 1], sizeof(root)*(left->parent->nElems + 1));

    left->parent->nElems--;
    for (int i = 0; left->child[i] != nullptr; i++) {
        left->child[i]->parent = left;
    }
}


//видалення елемента
template <typename K, typename V>
void BplusTree<K, V>::remove(K val) {
    dataFound=false;
    deleteNode(root, val, 0);
}

template <typename K, typename V>
void BplusTree<K, V>::deleteNode(BNode *curr, int value, int currPos) {

    bool isLeaf;
    if (curr->child[0] == nullptr)
    {
        isLeaf = true;
    }
    else
    {
        isLeaf = false;
    }
    int prevLeftMostVal = curr->value[0];

    for (int i = 0; dataFound == false && i <= curr->nElems; i++) {
        if (value < curr->value[i] && curr->child[i] != nullptr) {
            deleteNode(curr->child[i], value, i);
        }
        else if (value == curr->value[i] && curr->child[i] == nullptr) {
            memcpy(&curr->value[i], &curr->value[i + 1], sizeof(int)*(curr->nElems + 1));
            memcpy(&curr->key[i], &curr->key[i + 1], sizeof(int)*(curr->nElems + 1));
            curr->nElems--;
            dataFound = true;
            break;
        }
    }

    if (curr->parent == nullptr && curr->child[0] == nullptr) {
        return;
    }

    if (curr->parent == nullptr && curr->child[0] != nullptr && curr->nElems == 0) {
        root = curr->child[0];
        root->parent = nullptr;
        return;
    }

    if (curr->parent != nullptr) {
        for (int i = 0; i < curr->parent->nElems; i++) {
            if (curr == curr->parent->child[i]) {
                currPos = i;
                break;
            }
        }
    }

    if (isLeaf && curr->parent != nullptr) {
        if (currPos == 0) {
            BNode *right = new BNode();

            right = curr->parent->child[1];
            if (right != nullptr && right->nElems > (T + 1) / 2) {

                redistributeCell(curr, right, isLeaf, 0, 0);
            }
            else if (right != nullptr && curr->nElems + right->nElems < T) {
                mergeCell(curr, right, isLeaf, 1);
            }
        }
        else
        {
            BNode *left = new BNode();
            BNode *right = new BNode();

            left = curr->parent->child[currPos - 1];

            right = curr->parent->child[currPos + 1];

            if (left != nullptr && left->nElems > (T + 1) / 2) {
                redistributeCell(left, curr, isLeaf, currPos - 1, 1);
            }
            else if (right != nullptr && right->nElems > (T + 1) / 2) {
                redistributeCell(curr, right, isLeaf, currPos, 0);
            }
            else if (left != nullptr && curr->nElems + left->nElems < T) {
                mergeCell(left, curr, isLeaf, currPos);
            }
            else if (right != nullptr && curr->nElems + right->nElems < T) {
                mergeCell(curr, right, isLeaf, currPos + 1);
            }
        }
    }
    else if (!isLeaf && curr->parent != nullptr)
    {
        if (currPos == 0) {
            BNode *right = new BNode();
            right = curr->parent->child[1];

            if (right != nullptr && right->nElems - 1 >= ((T - 1) / 2)) {
                redistributeCell(curr, right, isLeaf, 0, 0);
            }
            else if (right != nullptr && curr->nElems + right->nElems < T - 1) {
                mergeCell(curr, right, isLeaf, 1);
            }
        }
        else
        {
            BNode *left = new BNode();
            BNode *right = new BNode();


            left = curr->parent->child[currPos - 1];

            right = curr->parent->child[currPos + 1];

            if (left != nullptr && left->nElems - 1 >= ((T - 1) / 2)) {
                redistributeCell(left, curr, isLeaf, currPos - 1, 1);
            }
            else if (right != nullptr && right->nElems - 1 >= ((T - 1) / 2)) {
                redistributeCell(curr, right, isLeaf, currPos, 0);
            }
            else if (left != nullptr && curr->nElems + left->nElems < T - 1) {
                mergeCell(left, curr, isLeaf, currPos);
            }
            else if (right != nullptr && curr->nElems + right->nElems < T - 1) {
                mergeCell(curr, right, isLeaf, currPos + 1);
            }
        }

    }
    BNode *temp = new BNode();
    temp = curr->parent;
    while (temp != nullptr) {
        for (int i = 0; i < temp->nElems; i++) {
            if (temp->value[i] == prevLeftMostVal) {
                temp->value[i] = curr->value[0];
                temp->key[i] = curr->key[0];
                break;
            }
        }
        temp = temp->parent;
    }

}

template <typename K, typename V>
void BplusTree<K, V>::graphviz(const char *filename)
{
    FILE *f = nullptr;
    errno_t err = fopen_s(&f, filename, "w");
    fputs("digraph G{\n", f);
    fclose(f);
    vector<BNode*> nodes={root};
    root->value[0]=12;
    graphvizRec(nodes, filename);
    err = fopen_s(&f, filename, "a");
    fputc('}', f);
    fclose(f);
}

template <typename K, typename V>
void BplusTree<K, V>::graphvizRec(vector <BNode*> Nodes, const char *filename)
{

    vector <BNode*> newCells;
    for (int i = 0; i < Nodes.size(); i++) {
        BNode *curr = Nodes[i];

        FILE *f = nullptr;
        errno_t err = fopen_s(&f, filename, "a");
        fputs("   ", f);
        string str = "\"";
        str += "[|";
        int j;
        for (j = 0; j < curr->nElems; j++) {  //проходимо синів, виводимо значення і зберігаєм всіх дітей
            str += to_string(curr->key[j]);
            str += "-";
            str += to_string(curr->value[j]);
            str += "|";
            if (curr->child[j] != nullptr)
            {
                newCells.push_back(curr->child[j]);

            }

        }
        if (curr->value[j] == INT_MAX && curr->child[j] != nullptr)
            newCells.push_back(curr->child[j]);

        str += "]\"";
        fputs(str.c_str(), f); fputs(";\n", f);
        for (j = 0; j < curr->nElems; j++)
        {
            if (curr->child[j] != nullptr)
            {
                string str2 = "\"[|";
                for (int k = 0; k < curr->child[j]->nElems; ++k)
                {

                    str2 += to_string(curr->child[j]->key[k]);
                    str2 += "-";
                    str2 += to_string(curr->child[j]->value[k]);
                    str2 += "|";
                }
                str2 += "]\"";
                fputs(str.c_str(), f);
                fputs("->", f);
                fputs(str2.c_str(), f);
                fputs(";\n", f);
            }
        }
        if (curr->child[j] != nullptr)
        {
            string str2 = "\"[|";
            for (int k = 0; k < curr->child[j]->nElems; ++k)
            {

                str2 += to_string(curr->child[j]->key[k]);
                str2 += "-";
                str2 += to_string(curr->child[j]->value[k]);
                str2 += "|";
            }
            str2 += "]\"";
            fputs(str.c_str(), f);
            fputs("->", f);
            fputs(str2.c_str(), f);
            fputs(";\n", f);
        }

        fclose(f);


    }

    if (newCells.size() == 0) { //якщо немає більше синів, закінчуєм рекурсію

        puts("");
        puts("");
        Nodes.clear();
    }
    else {                    //інакше відправляєм синів до рекурсії
        puts("");
        puts("");
        Nodes.clear();
        graphvizRec(newCells, filename);
    }
}


template <typename K, typename V>
vector<tuple<K,V>> BplusTree<K, V>::getKeys() {
    vector<tuple<K,V>> v;
    vector<BNode*> t = { root };
    getElem(t, v);
    return v;
}

template <typename K, typename V>
void BplusTree<K, V>::getElem(vector <BNode*> Nodes, vector<tuple<K,V>>& v) {

    vector <BNode*> newCells;
    for (int i = 0; i < Nodes.size(); i++) {
        BNode *curr = Nodes[i];

        int j;
        if (curr->child[0] == nullptr) {
            for (j = 0; j < MAX; j++) {  //проходимо синів, виводимо значення і зберігаєм всіх дітей
                if (curr->value[j] != INT_MAX) v.push_back(make_tuple( curr->key[j], curr->value[j]));
            }
        }
        else
            for (j = 0; j < curr->nElems; j++) {  //проходимо синів, виводимо значення і зберігаєм всіх дітей

                if (curr->child[j] != nullptr)
                    newCells.push_back(curr->child[j]);
            }
        if (curr->value[j] == INT_MAX && curr->child[j] != nullptr)
            newCells.push_back(curr->child[j]);
    }

    if (newCells.size() == 0) { //якщо немає більше синів, закінчуєм рекурсію

        Nodes.clear();
    }
    else {                    //інакше відправляєм синів до рекурсії
        Nodes.clear();
        getElem(newCells, v);
    }
}




#endif // BPLUSTREE_H
