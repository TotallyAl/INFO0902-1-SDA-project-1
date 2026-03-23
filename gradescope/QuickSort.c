#include <stdio.h>
#include <stdlib.h>
#include "Sort.h"

static void quickSort(void *array, size_t start, size_t end, int (*compare)(const void *, size_t i, size_t j), void (*swap)(void *array, size_t i, size_t j));

static void quickSort(void *array, size_t start, size_t end, int (*compare)(const void *, size_t i, size_t j), void (*swap)(void *array, size_t i, size_t j))
{
    if (end - start <= 1)
        return;

    size_t pivot = end - 1;

    size_t j = start;
    size_t i = start;

    while (j != pivot)
    {
        if (compare(array, j, pivot) <= 0)
        {
            swap(array, i, j);
            i++;
        }
        j++;
    }

    swap(array, i, pivot);
    pivot = i;

    quickSort(array, start, pivot, compare, swap);
    quickSort(array, pivot + 1, end, compare, swap);
}

void sort(void *array, size_t length, int (*compare)(const void *, size_t i, size_t j), void (*swap)(void *array, size_t i, size_t j))
{
    quickSort(array, 0, length, compare, swap);
}
