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

int main(void)
{
    int A[] = {7, 2, 9, 4, 3, 8, 1, 6, 5};
    size_t length = sizeof(A) / sizeof(A[0]);

    printf("Before sort:\n");
    printArrayInt(A, length);

    sort(A, length, compareInt, swapInt);

    printf("After sort:\n");
    printArrayInt(A, length);

    char B[] = {'d', 'a', 'x', 'e', 'f'};
    size_t length1 = sizeof(B) / sizeof(B[0]);

    printf("Before sorting:\n");
    printArrayChar(B, length1);

    sort(B, length1, compareChar, swapChar);

    printf("After sorting: \n");
    printArrayChar(B, length1);

    return 0;
}