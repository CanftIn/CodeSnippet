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
void SelectSort(int arr[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        int min = i;
        for(int j = i+1; j < n; ++j)
        {
            if(arr[j] < arr[min])
                min = j;
        }
        exchange(arr[min], arr[i]);
    }
}

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

void myInsert(int arr[], int n)
{
    for(int i = 1; i < n; ++i)
    {
        int temp = arr[i];
        int j = i - 1;
        while(j >= 0)
        {
            if(arr[j] > temp)
            {
                arr[j + 1] = arr[j];
            }
            else
                break;
            --j;
        }
        j += 1;
        arr[j] = temp;
    }
}

// Shell Sort
// Merge Sort
// Quick Sort
// not finish!!!
void quickSort(int arr[], int left, int right)
{
    int i = left;
    int j = right;
    int temp = arr[left];

    if(left > right)
        return ;
    /*
    // 小数组时候插入排序效率高于快排
    if(left + 10 > right)
    {
        myInsert(arr, right - left + 1);
        return ;
    }
    */
    while(i < j)
    {
        while(arr[j] >= temp)
            --j;
        while(arr[i] <= temp)
            ++i;
        if(i < j)
            exchange(arr[i], arr[j]);
    }
    arr[left] = arr[i];
    arr[i] = temp;

    quickSort(arr, left, i-1);
    quickSort(arr, i+1, right);
}

// Heap Sort
// Counting Sort
// Bucket Sort
// Radix Sort
// ...

int main()
{
    int arr[10] = { 5,6,1,3,4,2,8,7,9,0};
    //cout << sizeof(arr) / sizeof(int) << endl;
    //myInsert(arr, 10);

    quickSort(arr, 0, 10);
    for(int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}