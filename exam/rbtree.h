#ifndef RBTREE_H
#define RBTREE_H
#include "datastructure.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <utility>
#include <cstdio>

using namespace std;

enum colors { red, black };


template <typename K, typename V>
struct Node {
    Node<K,V>(K,V);

    K key;
    V data;
    Node<K,V> *father;
    Node<K,V> *left;
    Node<K,V> *right;
    int color;


    K get_key()
    {
        return key;
    }

    V get_value()
    {
        return data;
    }

    Node* get_parent()
    {
        return father;
    }

    Node* get_left()
    {
        return left;
    }

    Node* get_right ()
    {
        return right;
    }

    bool get_is_black()
    {
        return color == 0;
    }
};

template <typename K, typename V>
class RBTree: public DataStructure<K,V>
{
    RBTree(Node<K,V>*);
    Node<K,V>* successor(Node<K,V>*);
    Node<K,V> *root;

    /*!
     * \brief rotateLeft
     * \brief rotateRight
     * Changes the structure without interfering with the order of the elements
     * Moves one Node<K,V> up in the tree and one Node<K,V> down
     */
    void rotateLeft(Node<K,V>*);
    void rotateRight(Node<K,V>*);

    /*!
     * \brief insertFix
     * \brief deleteFix
     * Restores all tree properties using right and left otation
     */
    void insertFix(Node<K,V>*);
    void deleteFix(Node<K,V>*);

    void getElementsRecursion(Node<K,V> *x, vector<tuple<K, V>> &elements);

public:
    RBTree();
    RBTree(const RBTree &);
    void show();
    Node<K,V> *search(K);

    /*!
     * \brief blackHeight
     * \return number of black Node<K,V>s from current Node<K,V> to leaves
     */
    int blackHeight();
    int blackHeight(Node<K,V>*);

    /*!
     * \brief minValueNode<K,V>
     * \return Node<K,V> winh minimum key after current
     */
    Node<K,V>* minValueNode(Node<K,V>*&);

    /*!
     * \brief maxValueNode<K,V>
     * \return Node<K,V> winh maximum key after current
     */
    Node<K,V>* maxValueNode(Node<K,V>*&);
    void writeToGV(ofstream &fout, Node<K,V>* p);



    // DataStructure interface
public:
    void insert(K key, V data) override;
    void remove(K key) override;
    V find(K key) override;
    void graphviz(const char *filename) override;
    vector<tuple<K, V> > getKeys() override;
};


template <typename K, typename V>
Node<K,V>::Node(K input, V inp)
{
    key = input;
    data=inp;
    left = nullptr;
    right = nullptr;
    father = nullptr;
    color = red;

}


template <typename K, typename V>
RBTree<K,V>::RBTree()
{
    root=nullptr;
}


template <typename K, typename V>
RBTree<K,V>::RBTree(const RBTree<K,V> &tree)
{

    if (tree.root == nullptr) root = nullptr;
    else
    {
        root = new Node<K,V>(tree.root->key, tree.root->data);
        root->color = tree.root->color;

        root->left = RBTree(RBTree(tree.root->left)).root;
        root->right = RBTree(RBTree(tree.root->right)).root;
    }

}

template <typename K, typename V>
RBTree<K,V>::RBTree(Node<K,V> * in)
{
    if (in == nullptr) root = nullptr;
    else
    root = in;
}


template <typename K, typename V>
void RBTree<K,V>::insert(K input, V inp) {
    Node<K,V> *p, *q;
    Node<K,V> *create = new Node<K,V>(input, inp);
    p = root;
    q = nullptr;
    if (root == nullptr)
    {
        root = create;
        create->father = nullptr;
    }
    else
    {
        while (p != nullptr)
        {
            q = p;
            if (p->key > create->key) p = p->left;
            else if (p->key < create->key) p = p->right;
            else return;
        }
        create->father = q;
        if (q->key < create->key) q->right = create;
        else if (q->key > create->key)q->left = create;
        else return;
    }

    insertFix(create);

}


template <typename K, typename V>
void RBTree<K,V>::insertFix(Node<K,V> *create)
{
    Node<K,V> *x = create;
    while (x != root && x->father->color == red)
    {
        if (x->father == x->father->father->left) //если отец - левый сын
        {
            Node<K,V> *uncle = x->father->father->right;
            if ((uncle != nullptr) && (uncle->color == red)) //если дядя - красный
            {
                x->father->color = black;
                uncle->color = black;
                x->father->father->color = red;
                x = x->father->father;
            }
            else
            {
                if (x->father->right == x)  //если х - правый сын
                {
                    x = x->father;
                    rotateLeft(x);
                }
                x->father->color = black;
                x->father->father->color = red;
                rotateRight(x->father->father);
            }
        }
        else  //если отец - правый сын
        {
            Node<K,V> *uncle = x->father->father->left;
            if ((uncle != nullptr) && (uncle->color == red)) // если дядя - красный
            {
                x->father->color = black;
                uncle->color = black;
                x->father->father->color = red;
                x = x->father->father;
            }
            else  //если дядя - черный
            {
                if (x->father->left == x)
                {
                    x = x->father;
                    rotateRight(x);
                }
                x->father->color = black;
                x->father->father->color = red;
                rotateLeft(x->father->father);
            }
        }
    }
    root->color = black;
}


template <typename K, typename V>
void RBTree<K,V>::rotateRight(Node<K,V>* in)
{
    if (in->left == nullptr)
        return;
    else
    {
        Node<K,V> *y = in;
        Node<K,V> *x = y->left;
        Node<K,V> *b = x->right;
        Node<K,V> *f = y->father;
        if (f == nullptr)
        {
            x->father = nullptr;
            root = x;
        }
        else
        {
            x->father = f;
            if (f->left == y)
                f->left = x;
            if (f->right == y)
                f->right = x;
        }
        x->right = y;
        y->father = x;
        y->left = b;
        if (b != nullptr)
            b->father = y;
    }
}


template <typename K, typename V>
void RBTree<K,V>::rotateLeft(Node<K,V>* x)
{
    if (x->right == nullptr)
        return;
    else
    {
        Node<K,V> *y = x->right;
        Node<K,V> *b = y->left;
        Node<K,V> *f = x->father;
        if (f == nullptr)
        {
            y->father = nullptr;
            root = y;
        }
        else
        {
            y->father = f;
            if (f->left == x)
                f->left = y;
            if (f->right == x)
                f->right = y;
        }
        y->left = x;
        x->father = y;
        x->right = b;
        if (b != nullptr)
            b->father = x;
    }
}



template <typename K, typename V>
V RBTree<K,V>::find(K in)
{
    Node<K,V> *t;
    t = root;
    while (t != nullptr)
    {
        if (t->key == in)   break;
        if (in > t->key)    t = t->right;
        else if (in < t->key)    t = t->left;
    }
    if (t == nullptr)
        return NULL;
    else if (t->key == in)
        return t->data;
    return NULL;
}


template <typename K, typename V>
int RBTree<K,V>::blackHeight() {
    Node<K,V> *p;
    p = root;
    int num = 0;
    while (p != nullptr) {
        if (p->color == black) num++;
        p = p->left;
    }
    return num;
}

template <typename K, typename V>
int RBTree<K,V>::blackHeight(Node<K,V>* node) {
    Node<K,V> *p;
    p = node;
    int num = 0;
    while (p != nullptr) {
        if (p->color == black) num++;
        p = p->left;
    }
    return num;
}


template <typename K, typename V>
void ShowMy(Node<K,V>* node)
{
    if (node->left != nullptr) ShowMy(node->left);
    if (node != nullptr) cout << node->key << " " << node->color << '\n';
    if (node->right != nullptr) ShowMy(node->right);
}

template <typename K, typename V>
void RBTree<K,V>::show()
{
    if (root != nullptr) {
        cout << "\n\nRoot: " << root->key << " " << (root->color == black ? "black" : "red") << "\n";
        ShowMy(root);
    }
}


template <typename K, typename V>
Node<K,V>* RBTree<K,V>::successor(Node<K,V> *p)
{
    Node<K,V> *y = nullptr;
    if (p->left != nullptr)
    {
        y = p->left;
        while (y->right != nullptr)
            y = y->right;
    }
    else
    {
        y = p->right;
        while (y->left != nullptr)
            y = y->left;
    }
    return y;
}


template <typename K, typename V>
void RBTree<K,V>::remove(K x)
{
    if (root == nullptr)
    {
        cout << "\nEmpty Tree.";
        return;
    }
    Node<K,V> *p;
    p = root;
    Node<K,V> *y = nullptr;
    Node<K,V> *q = nullptr;
    int found = 0;
    while (p != nullptr && found == 0)
    {
        if (p->key == x)
            found = 1;
        if (found == 0)
        {
            if (p->key < x)
                p = p->right;
            else
                p = p->left;
        }
    }

    if (found == 0)return;
    else
    {
        cout << "\nDeleted Element: " << p->key;
        cout << "\nColour: ";
        if (p->color == black)
            cout << "Black\n";
        else
            cout << "Red\n";
        if (p->left == nullptr || p->right == nullptr)
            y = p;
        else
            y = successor(p);
        if (y->left != nullptr)
            q = y->left;
        else
        {
            if (y->right != nullptr)
                q = y->right;
            else
                q = nullptr;
        }
        if (q != nullptr)
            q->father = y->father;
        if (y->father == nullptr)
            root = q;
        else
        {
            if (y == y->father->left)
                y->father->left = q;
            else
                y->father->right = q;
        }
        if (y != p)
        {
            p->color = y->color;
            p->key = y->key;
            p->data = y->data;
        }
        if (y->color == black)
            deleteFix(q);
        root->color = black;


    }
}

template <typename K, typename V>
void RBTree<K,V>::deleteFix(Node<K,V> *p)
{
    if (p != nullptr)
    {
        Node<K,V> *s;
        while (p != root && p->color == black)
        {
            if (p->father->left == p)
            {
                s = p->father->right;
                if (s->color == red)    //если брат - красный
                {
                    s->color = black;     //красим брата в черный
                    p->father->color = red;  //отца - в красный
                    rotateLeft(p->father);
                    s = p->father->right;
                }

                if (s->right->color == black && s->left->color == black)  //если оба ребенка брата черные
                {
                    s->color = red;  //красим брата в красный
                    p = p->father;   //и рассматриваем далее отца верншины
                }
                else
                {
                    if (s->right->color == black) //если правый - черный, левый - красный
                    {
                        s->left->color = black;
                        s->color = red;
                        rotateRight(s);
                        s = p->father->right;
                    }
                    s->color = p->father->color;
                    p->father->color = black;
                    s->right->color = black;
                    rotateLeft(p->father);
                    p = root;
                }
            }
            else
            {
                s = p->father->left;
                if (s->color == red)
                {
                    s->color = red;
                    p->father->color = red;
                    rotateRight(p->father);
                    s = p->father->left;
                }
                if (s->left->color == black && s->right->color == black)
                {
                    s->color = red;
                    p = p->father;
                }
                else
                {
                    if (s->left->color == black)
                    {
                        s->right->color = black;
                        s->color = red;
                        rotateLeft(s);
                        s = p->father->left;
                    }
                    s->color = p->father->color;
                    p->father->color = black;
                    s->left->color = black;
                    rotateRight(p->father);
                    p = root;
                }
            }
        }
        p->color = black;
        root->color = black;
    }
    root->color = black;
}


template <typename K, typename V>
void RBTree<K,V>::graphviz(const char *fileName){
    ofstream fout(fileName);
    fout << "digraph {\n";
    writeToGV(fout, root);
    fout << "}";
    fout.close();
}

template<typename K, typename V>
vector<tuple<K, V> > RBTree<K,V>::getKeys()
{
    vector<tuple<K, V>> elements;
    getElementsRecursion(root, elements);
    return elements;
}

template<typename K, typename V>
void RBTree<K,V>::getElementsRecursion(Node<K,V> *x, vector<tuple<K, V>> &elements)
{
    if (x)
    {
        getElementsRecursion(x->left, elements);
        elements.push_back(make_tuple(x->key, x->data));
        getElementsRecursion(x->right, elements);
    }
}

template <typename K, typename V>
void RBTree<K,V>::writeToGV(ofstream &fout, Node<K,V>* p)
{
    if (p != nullptr) {
        fout << '"' << p->key << " - " << p->data << "\" [color=" << (p->color == black ? "black];\n" : "red];\n");
        if (p->left != nullptr) fout << '"' << p->key << " - " << p->data << "\" -> \"" << p->left->key << " - " << p->left->data << "\";\n";
        else
            fout << '"' << p->key << " - " << p->data << "\" -> \"NULL\";\n";

        if (p->right != nullptr) fout << '"' << p->key << " - " << p->data << "\" -> \"" << p->right->key << " - " << p->right->data << "\";\n";
        else
            fout << '"' << p->key << " - " << p->data << "\" -> \"NULL\";\n";

    }

    if (p->left != nullptr) {
        writeToGV(fout, p->left);
    }
    if (p->right != nullptr) {
        writeToGV(fout, p->right);
    }

}


template <typename K, typename V>
Node<K,V> *RBTree<K,V>::minValueNode(Node<K,V> *&node) {

    Node<K,V> *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

template <typename K, typename V>
Node<K,V>* RBTree<K,V>::maxValueNode(Node<K,V> *&node) {
    Node<K,V> *ptr = node;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}



#endif // RBTREE_H
