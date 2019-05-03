#include <stdio.h>
#include <stdlib.h>
#define TAM 25000
#define MAX_NUMBER 25000

void merge(int arr[], int l, int m, int r)
{
    int i, j, k, x, y;
    int n1,n2;
    int L[TAM], R[TAM];
    
    x = m;
    y = r;
    n1 = (int) m - l + 1;
    n2 =  (int) r - m;

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0; 
    j = 0; 
    k = l; 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

int main()
{
    int arr[TAM];
    int i = 0;

    for (i=0; i < TAM; i++){
        arr[i] = (rand() % (MAX_NUMBER + 1));
    }

    mergeSort(arr, 0, TAM - 1);
    return 0;
}