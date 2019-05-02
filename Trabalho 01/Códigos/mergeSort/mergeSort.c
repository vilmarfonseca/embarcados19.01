#include <stdio.h>
#include <time.h>
#define TAM 50000
#define MAX_NUMBER 50000
#define MIN_NUMBER 1

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
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

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

void printArray(int A[])
{
    int i;
    for (i=0; i < TAM; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void fillingVector(int A[])
{
    int i = 0;
    for (i=0; i < TAM; i++)
    {
        A[i] = (rand() % (MAX_NUMBER + 1 - MIN_NUMBER) + MIN_NUMBER);
    }
}

int main()
{
    int arr[TAM];
    fillingVector(arr);

    printf("Given array is \n");
    printArray(arr);

    clock_t begin = clock();

    mergeSort(arr, 0, TAM - 1);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;


    printf("\nSorted array is \n");
    printArray(arr);

    printf("\nCPU run time: %f ", time_spent*1000);
    printf("ms\n");

    return 0;
}
