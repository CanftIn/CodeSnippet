#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Bubble
void Sort(int *arr)
{
    int len = 10;//sizeof(arr);// / sizeof(int);
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

// TODO
// Selection Sort
// Insertion Sort
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
    Sort(arr);
    for(int i = 0; i < 10; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}