/**
 * @file psort.cpp
 */

/**
 * Public wrapper for the parallel sort implementation.
 * @param array The structure to sort
 */
using namespace std;
template <class T>
void ParallelSort::psort(vector<T>* array)
{
    if (isSorted(array)) return;
    if (isReversed(array)) {reverse(array); return;}
    if (array->size()<=100) {insertionSort(array); return;}
    psorter(array);
}

template <class T>
bool ParallelSort::isReversed(vector<T> * arr)
{
    for (int i = 1; i<arr->size(); i++)
        if ((*arr)[i] > (*arr)[i-1])
            return false;
    return true;
}

template <class T>
void ParallelSort::reverse(vector<T> * arr)
{
    for (int i = 0; i < arr->size()/2; i++)
    {
        T temp = (*arr)[i];
        (*arr)[i] = (*arr)[arr->size()-1-i];
        (*arr)[arr->size()-1-i] = temp;
    }
}

template <class T>
bool ParallelSort::isSortedpar(vector<T> * arr)
{
    bool a = true;
#pragma omp parallel for
    for (int i = 1; i < arr->size(); i++)
    {
        if ((*arr)[i] < (*arr)[i-1])
            a = false;
    }
    return a;
}

template <class T>
bool ParallelSort::isSorted(vector<T> * arr)
{
    for (int i = 1; i < arr->size()/2+1; i++)
    {
        if ((*arr)[i] < (*arr)[i-1] || (*arr)[arr->size()-i]<(*arr)[arr->size()-i-1])
            return false;
    }
    return true;
}

template <class T>
vector<T> * ParallelSort::psorter(vector<T> * arr)
{
    vector <T> * result = new vector<T>;
#   pragma omp parallel
    {
#   pragma omp single
        result = quicksort(arr, 0, arr->size()-1, 1);
    }
    return result;
}

template <class T>
vector<T> * ParallelSort::quicksort(vector<T> * & arr, int a, int b, int c)
{
    if (b>a)
    {
//      int pivot = part(arr, a, b);
        int pivot = partition(arr, a, b, medofthree(arr, a, b));
        if (b-a >= 1250 && c<=8)
        {
#pragma omp task shared(arr, pivot)
            arr = quicksort(arr, a, pivot-1, c*2);
            arr = quicksort(arr, pivot+1, b, c*2);
        }
        else
        { 
            arr = quicksort(arr, a, pivot-1, c*2);
            arr = quicksort(arr, pivot+1, b, c*2);
        }
    }
    return arr;
}

template <class T>
T ParallelSort::medofthree(vector<T> * arr, int a, int b)
{
    int med = (a + b)/2;
    if ((*arr)[a]>(*arr)[med])
    {
        T swapper = ((*arr)[a]);
        ((*arr)[a]) = ((*arr)[med]);
        ((*arr)[med]) = swapper;
    }
    if ((*arr)[a]>(*arr)[b])
    {
        T swapper = ((*arr)[a]);
        ((*arr)[a]) = ((*arr)[b]);
        ((*arr)[b]) = swapper;
    }
    if ((*arr)[med]>(*arr)[b])
    {
        T swapper = ((*arr)[med]);
        ((*arr)[med]) = ((*arr)[b]);
        ((*arr)[b]) = swapper;
    }
    T swap = ((*arr)[med]);
    ((*arr)[med]) = ((*arr)[b-1]);
    ((*arr)[b-1]) = swap;
    return (*arr)[b-1];
}

template <class T>
int ParallelSort::partition(vector<T> * arr, int a, int b, T med)
{
    int left = a;
    int right = b-1;
    while (left<right)
    {
        while ((*arr)[++left]<med);
        while ((*arr)[--right]>med);
        if (left<right)
        {
            T swapp = ((*arr)[left]);
            ((*arr)[left]) = ((*arr)[right]);
            ((*arr)[right]) = swapp;
        }      
    }
    T swa = ((*arr)[left]);
    ((*arr)[left]) = ((*arr)[b-1]);
    ((*arr)[b-1]) = swa;
    return left;
}

template <class T>
void ParallelSort::insertionSort(vector<T> * & arr)
{
    for (int i = 1; i < arr->size(); i++)
    {
        T val = (*arr)[i];
        int j = i;
        while (j>=1 && (*arr)[j-1] > val)
        {
            (*arr)[j] = (*arr)[j-1];
            j--;
        }
        (*arr)[j] = val;
    }
}

template <class T>
int ParallelSort::part(vector<T> * arr, int a, int b)
{
    int left = a;
    int right = b;
    int pivot = a;
    T pivoter = (*arr)[a];
    while (left<right)
    {
        while ((*arr)[left] <= pivoter)
            left++;
        while ((*arr)[right] > pivoter)
            right--;
        if (left < right)
        {
            T swapper = (*arr)[left];
            (*arr)[left] = (*arr)[right];
            (*arr)[right] = swapper;
        }
    }
    (*arr)[a] = (*arr)[right];
    (*arr)[right] = pivoter;
    return right;
}
