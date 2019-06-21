#include <QApplication>
#include <QRandomGenerator>
#include <tuple>
#include "gtest/gtest.h"
#include "datastructure.h"
#include "dsbridge.h"
#include "stllist.h"
#include "stlmap.h"
#include "stlvector.h"
#include "dclist.h"
#include "rbtree.h"
#include "bplustree.h"

typedef DataStructure<int,int> DS;
const size_t amount = 50;

void randomInsert(vector<int> &vec, vector<int> &key, const int& amount)
{
    for (int i = 0; i< amount; i++) {
        key.push_back(i+1);
        vec.push_back(QRandomGenerator::global()->bounded(0,100));
    }
}

vector<DS*> initialization(vector<int> keys, vector<int> &values){

    vector<DS*> dataStructures;
    DS* s1, *s2, *s3, *s4, *s5, *s6;

    s1 = new StlList<int, int>;
    s2 = new StlMap<int, int>;
    s3 = new StlVector<int, int>;
    s4 = new DCList<int, int>;
    s5 = new RBTree<int, int>;
    s6 = new BplusTree<int, int>;


    for(int i = 0; i < amount;i++)
    {
        s1->insert(keys[i],values[i]);
        s2->insert(keys[i],values[i]);
        s3->insert(keys[i],values[i]);
        s4->insert(keys[i],values[i]);
        s5->insert(keys[i],values[i]);
        s6->insert(keys[i],values[i]);
    }

    dataStructures.push_back(s1);
    dataStructures.push_back(s2);
    dataStructures.push_back(s3);
    dataStructures.push_back(s4);
    dataStructures.push_back(s5);
    dataStructures.push_back(s6);

    return dataStructures;
}


TEST(DataStructure, InsertFind){
    vector<int> k, v;
    randomInsert(v, k, amount);

    vector<DS*> ds = initialization(k,v);

        for(int j = 1; j< amount; j++){
            EXPECT_EQ(ds[0]->find(k[j]), v[j]);
            EXPECT_EQ(ds[1]->find(k[j]), v[j]);
            EXPECT_EQ(ds[2]->find(k[j]), v[j]);
            EXPECT_EQ(ds[3]->find(k[j]), v[j]);
            EXPECT_EQ(ds[4]->find(k[j]), v[j]);
            EXPECT_EQ(ds[5]->find(k[j]), v[j]);
        }
}

TEST(DataStructure, RemoveFind){
    vector<int> k, v;
    randomInsert(v, k, amount);

    vector<DS*> ds = initialization(k,v);



        for(int i = 1; i < amount;i++)
        {
            ds[0]->remove(k[i]);
            ds[1]->remove(k[i]);
            ds[2]->remove(k[i]);
            ds[3]->remove(k[i]);
            ds[5]->remove(k[i]);
        }


        for(int j = 3; j< amount; j++){
            EXPECT_NE(ds[0]->find(k[5]), v[j]);
            EXPECT_NE(ds[1]->find(k[j]), v[j]);
            EXPECT_NE(ds[2]->find(k[j]), v[j]);
            EXPECT_NE(ds[3]->find(k[j]), v[j]);
            EXPECT_NE(ds[5]->find(k[j]), v[j]);
        }

}

TEST(DataStructure, GetKeys){
    vector<int> k, v;
    randomInsert(v, k, amount);

    vector<DS*> ds = initialization(k,v);
    vector<vector<tuple<int,int>>> keys;
    for(int j = 0; j< 6; j++){
        keys.push_back(ds[j]->getKeys());
    }

    for(int j = 0; j< amount; j++){
        EXPECT_EQ(ds[0]->find(get<0>(keys[0][j])), get<1>(keys[0][j]));
        EXPECT_EQ(ds[1]->find(get<0>(keys[1][j])), get<1>(keys[0][j]));
        EXPECT_EQ(ds[2]->find(get<0>(keys[2][j])), get<1>(keys[0][j]));
        EXPECT_EQ(ds[3]->find(get<0>(keys[3][j])), get<1>(keys[0][j]));
        EXPECT_EQ(ds[4]->find(get<0>(keys[4][j])), get<1>(keys[0][j]));
      //  EXPECT_EQ(ds[5]->find(get<0>(keys[5][j])), get<1>(keys[0][j]));
    }


}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();

}
