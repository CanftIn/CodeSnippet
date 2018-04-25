#include <iostream>

using namespace std;

int binary_search(int arr[], int key)
{
    int low = 0, mid, high = 7;
    cout << high << endl;

    while(low <= high)
    {
        mid = (low + high) / 2;
        if(arr[mid] == key)
        {
            return mid;
        }
        else if(arr[mid] > key)
        {
            high = mid - 1;
        }
        else if(arr[mid] < key)
        {
            low = mid + 1;
        }
    }
    return -1;
}

int main()
{
    int arr[7] = {1,2,3,4,5,6,7};
    cout << binary_search(arr, 3);

    return 0;
}