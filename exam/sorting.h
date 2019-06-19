#ifndef SORTING_H
#define SORTING_H
#include <iostream>
#include <list>
#include <math.h>
#include <vector>
#include <tuple>

using namespace std;

template<typename K, typename V>
class Sorting
{
public:
    Sorting();
    void sort(vector<tuple<K,V>> &, int);
private:
    int partition_qs(vector<tuple<K,V>> &arr, int low, int high);
    void quickSort1(vector<tuple<K,V>> &arr, int low, int high);
    void quickSort(vector<tuple<K,V>> &arr);

    int Parent(int i);
    int Left (int i);
    int Right(int i);
    void Heapify(vector<tuple<K,V>> &A, int i, int heap_size);
    void Build_Heap(vector<tuple<K,V>> &A, int heap_size, int ASize);
    void Heap_Sort(vector<tuple<K,V>> &A, int heap_size);

    void SelectionSort(vector<tuple<K,V>> &A);

};

template<typename K, typename V>
Sorting<K,V>::Sorting()
{
}

template<typename K, typename V>
void Sorting<K,V>::sort(vector<tuple<K, V> > &v, int choice)
{
    switch (choice) {
        case 1: quickSort(v); break;
        case 2: Heap_Sort(v,4); break;
        case 3: SelectionSort(v); break;
    default: break;
    }
}

// BEG QUICKSORT
template<typename K, typename V>
int Sorting<K,V>::partition_qs(vector<tuple<K,V>> &arr, int low, int high)
{
    tuple<K,V> pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        if (get<0>(arr[j]) <= get<0>(pivot))
        {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

template<typename K, typename V>
void Sorting<K,V>::quickSort1(vector<tuple<K,V>> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition_qs(arr, low, high);
        quickSort1(arr, low, pi - 1);
        quickSort1(arr, pi + 1, high);
    }
}

template<typename K, typename V>
void Sorting<K,V>::quickSort(vector<tuple<K,V>> &arr){
    quickSort1(arr, 0, arr.size()-1);
}
// END QUICKSORT



// BEG HEAPSORT

template<typename K, typename V>
int Sorting<K,V>::Parent(int i)
{
    if (i % 2 == 0) return i / 2 - 1 ;
    else return i / 2;
}

template<typename K, typename V>
int Sorting<K,V>::Left(int i)
{
    return 2 * i + 1;
}

template<typename K, typename V>
int Sorting<K,V>::Right(int i)
{
    return 2 * i + 2;
}

template<typename K, typename V>
void Sorting<K,V>::Heapify(vector<tuple<K,V>> &A, int i, int heap_size)
{
    int l = Left(i), r = Right(i), largest = i;
    if (l < heap_size && get<0>(A[l]) > get<0>(A[i]))
        largest = l;
    if (r < heap_size && get<0>(A[r]) > get<0>(A[largest]))
        largest = r;
    if (largest != i)
    {
        swap(A[i], A[largest]);
        Heapify(A, largest, heap_size);
    }
}

template<typename K, typename V>
void Sorting<K,V>::Build_Heap(vector<tuple<K,V>> &A, int heap_size, int ASize)
{
    for (int i = ASize / 2 - 1; i >= 0; --i)
        Heapify(A, i, heap_size);
}

template<typename K, typename V>
void Sorting<K,V>::Heap_Sort(vector<tuple<K,V>> &A, int heap_size)
{
    Build_Heap(A, heap_size, A.size());
    for (int i = A.size() - 1; i > 0; --i)
    {
        swap(A[0], A[i]);
        Heapify(A, 0, --heap_size);
    }
}

// END HEAPSORT



// BEG SELECTIONSORT

template<typename K, typename V>
void Sorting<K,V>::SelectionSort(vector<tuple<K,V>> &A){
    int i, j, min_index;

    for (i = 0; i < A.size() - 1; i++)
    {
        min_index = i;
        for (j = i+1; j < A.size(); j++)
            if (get<0>(A[j]) < get<0>(A[min_index]))
                min_index = j;

        swap(A[min_index], A[i]);
     }
}

// END SELECTIONSORT


#endif // SORTING_H
