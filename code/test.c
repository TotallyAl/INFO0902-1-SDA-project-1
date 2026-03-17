#include <stdio.h>
#include <stdlib.h>
#include "Sort.h"

/* comparaison de deux éléments du tableau */
int compareInt(const void *array, size_t i, size_t j)
{
    const int *A = array;

    if (A[i] < A[j])
        return -1;
    if (A[i] > A[j])
        return 1;
    return 0;
}

int compareChar(const void *array, size_t i, size_t j)
{
    const char *A = array;

    if (A[i] < A[j])
        return -1;
    if (A[i] > A[j])
        return 1;
    return 0;
}

int compareStr(const void *array, size_t i, size_t j)
{
    const char **A = (const char **)array;

    // We need to compare the strings here.
    for (size_t k = 0; A[i][k] != '\0' || A[j][k] != '\0'; k++)
    {
        if (A[i][k] < A[j][k])
            return -1;
        if (A[i][k] > A[j][k])
            return 1;
    }
    return 0;
}

/* échange de deux éléments */
void swapInt(void *array, size_t i, size_t j)
{
    int *A = array;

    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void swapChar(void *array, size_t i, size_t j)
{
    char *A = array;
    char tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void swapStr(void *array, size_t i, size_t j)
{
    char **A = array;
    char *tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void printArrayInt(int *A, size_t length)
{
    for (size_t i = 0; i < length; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void printArrayChar(char *A, size_t length)
{
    for (size_t i = 0; i < length; i++)
        printf("%c ", A[i]);
    printf("\n");
}

void printArrayStr(char **A, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = 0; A[i][j] != '\0'; j++)
            printf("%c", A[i][j]);
        printf(" ");
    }
    printf("\n");
}

int main(void)
{
    int A[] = {7, 2, 9, 4, 3, 8, 1, 6, 5};
    size_t length = sizeof(A) / sizeof(A[0]);

    printf("Before sort:\n");
    printArrayInt(A, length);

    sort(A, length, compareInt, swapInt);

    printf("After sort:\n");
    printArrayInt(A, length);

    printf("\n");

    char B[] = {'d', 'a', 'x', 'e', 'f'};
    size_t length1 = sizeof(B) / sizeof(B[0]);

    printf("Before sorting:\n");
    printArrayChar(B, length1);

    sort(B, length1, compareChar, swapChar);

    printf("After sorting: \n");
    printArrayChar(B, length1);

    char *C[] = {"Alexandre", "Zoe", "Frederic", "Alexandre"};
    size_t length2 = sizeof(C) / sizeof(C[0]);

    sort(C, length2, compareStr, swapStr);

    printArrayStr(C, length2);

    char test[] = {'c', 'a', 'd', 'b'};
    size_t length3 = sizeof(test) / sizeof(test[0]);
    sort(test, length3, compareChar, swapChar);
    printArrayChar(test, length);

    int arr[] = {38, 27, 43, 3, 9, 82, 10, -4, 7, 16, 5, 12, 1, 99, 54, -20, 33, 2, 18, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Before sorting: \n");
    printArrayInt(arr, n);

    sort(arr, n, compareInt, swapInt);

    printf("After sorting: \n");
    printArrayInt(arr, n);

    return 0;
}