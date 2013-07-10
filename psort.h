/**
 * @file psort.h
 */

#ifndef _PSORT_H_
#define _PSORT_H_

#include <iostream>
#include <vector>
#include <omp.h>
#include <stdlib.h>
using std::vector;

namespace ParallelSort
{
    /**
     * Public wrapper for the parallel sort implementation.
     * @param array The structure to sort
     */
    template <class T>
    void psort(vector<T>*);
/*    template <class T>
    vector<T> * arr;
    template <class T>
    vector<T> * help;*/
/*    template <class T>
    void merge(vector<T> *, vector<T> *,int a, int b, int c);
    template <class T>
    void mergesort(vector<T> *, vector<T> *, int, int);*/
    template <class T>
        vector<T> * psorter(vector<T> * arr);

    template <class T>
        vector<T> * quicksort(vector<T> * & arr, int a, int b, int c);
    template <class T> 
        int part(vector<T> * arr, int a, int b);
    template <class T>
        bool isSorted(vector<T> * arr);
    template <class T>
        bool isSortedpar(vector<T> * arr);
    template <class T>
        T medofthree(vector<T> * arr, int a, int b);
    template <class T>
        int partition(vector<T> * arr, int a, int b, T med);
    template <class T>
        void insertionSort(vector<T> * & arr);
template <class T>
bool isReversed(vector<T> * arr);
template <class T>
void reverse(vector<T> * arr);

    /**
     * TODO: add helper functions here.
     * Note: you can also add additional classes and/or files.
     * Make sure you follow the instructions in the Makefile.
     */

}

#include "psort.cpp"
#endif
