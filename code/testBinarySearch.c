#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BinarySearch.h"

int compareInt(const void *array, size_t i, void *key)
{
    int *a = (int *)array;
    int k = *(int *)key;

    if (a[i] < k)
        return -1;
    if (a[i] > k)
        return 1;
    return 0;
}

int main()
{

    int a[] = {0, 1, 2, 2, 2, 2, 2, 3, 4, 6, 7, 8, 9};
    size_t length = sizeof(a) / sizeof(a[0]);

    int key = 9;

    size_t result = binarySearchLow(a, length, &key, compareInt);
    size_t result2 = binarySearchHigh(a, length, &key, compareInt);

    printf("key: %d\n", key);
    printf("Result low: %zu\n", result);
    printf("Result high: %zu\n", result2);

    return 0;
}