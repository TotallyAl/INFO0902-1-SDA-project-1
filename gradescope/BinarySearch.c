#include <stdio.h>
#include "BinarySearch.h"

size_t binarySearchLow(void *array, size_t length, void *key, int (*compare)(const void *, size_t i, void *))
{
    if (length == 0)
        return 0;

    size_t left = 0;
    size_t right = length;

    while (left < right)
    {
        size_t middle = (size_t)(left + right) / 2;

        if (compare(array, middle, key) < 0) // if array[middle] < key --> search the right
            left = middle + 1;
        else // if array[middle] >= key --> search the left
            right = middle;
    }

    // Two cases:

    // First cas: We found an element of *array that matches the *key.
    if (left < length && compare(array, left, key) == 0)
        return left;

    // Second case: We didn't find an element of *array that matches the *key.
    if (left < length)
        return left;
    else
        return length - 1;
}

size_t binarySearchHigh(void *array, size_t length, void *key, int (*compare)(const void *, size_t i, void *))
{

    if (length == 0)
        return 0;

    size_t left = 0;
    size_t right = length;

    while (left < right)
    {

        size_t middle = (size_t)(left + right) / 2;
        int cmp = compare(array, middle, key);

        if (cmp <= 0) // if array[middle] < key --> search the right
            left = middle + 1;
        else // if array[middle] > key --> search the left
            right = middle;
    }

    if (right < length && compare(array, right - 1, key) == 0)
        return right - 1;

    if (right < length)
        return right;
    else
        return length - 1;
}
