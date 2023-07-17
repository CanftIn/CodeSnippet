#include <iostream>

using namespace std;

int maxsequence(int arr[], int len)  
{  
    int max = arr[0];
    for (int i=0; i<len; i++) {  
        int sum = 0; 
        for (int j=i; j<len; j++) {
            sum += arr[j];   
            if (sum > max)  
                max = sum;  
        }  
    }  
    return max;  
}

int main()
{
    
}