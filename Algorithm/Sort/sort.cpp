#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void exchange(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Bubble
void Sort(int *arr, int n)
{
    int len = n;//sizeof(arr);// / sizeof(int);
    //cout << len << endl;
    for(int i = 0; i < len; ++i)
    {
        for(int j = 0; j < len - 1 - i; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void Bubble(int arr[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        for(int j = i; j >= 0; --j)
        {
            if(arr[j] > arr[j+1])
            {
                exchange(arr[j], arr[j+1]);
            }
        }
    }
}

// TODO
// Selection Sort
// Insertion Sort
void InsertSort(int arr[], int n)
{
    int j;
    for(int i = 0; i < n; ++i)
    {
        if(arr[i] < arr[i - 1])
        {
            arr[0] = arr[i];
            for(j = i - 1; arr[0] < arr[j]; --j)
                arr[j + 1] = arr[j];
            arr[j + 1] = arr[0];
        }
    }
}

// Shell Sort
// Merge Sort
// Quick Sort
// Heap Sort
// Counting Sort
// Bucket Sort
// Radix Sort
// ...

int main()
{
    int arr[10] = { 5,6,1,3,4,2,8,7,9,0};
    //cout << sizeof(arr) / sizeof(int) << endl;
    InsertSort(arr, 10);
    for(int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}