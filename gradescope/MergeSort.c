#include <stdio.h>
#include <stdlib.h>

#include "Sort.h"

static void merge(void *array, size_t *tmp, size_t start, size_t middle, size_t end, int (*compare)(const void *, size_t i, size_t j));
static size_t *mergeS(void *array, size_t *tmp, size_t start, size_t end, int (*compare)(const void *, size_t i, size_t j));
static void mergeSort(void *array, size_t length, int (*compare)(const void *, size_t i, size_t j), void (*swap)(void *array, size_t i, size_t j));

static void merge(void *array, size_t *tmp, size_t start, size_t middle, size_t end, int (*compare)(const void *, size_t i, size_t j))
{
    size_t sorted_size = end - start;
    size_t *sorted = (size_t *)malloc(sorted_size * sizeof(size_t));

    if (sorted == NULL)
    {
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(1);
    }

    size_t i = start;
    size_t j = middle;

    size_t h = 0;

    while (i < middle && j < end)
    {

        if (compare(array, tmp[i], tmp[j]) <= 0)
        {
            sorted[h] = tmp[i];
            i++;
            h++;
        }
        else
        {
            sorted[h] = tmp[j];
            j++;
            h++;
        }
    }

    while (i < middle)
    {
        sorted[h] = tmp[i];
        h++;
        i++;
    }

    while (j < end)
    {
        sorted[h] = tmp[j];
        h++;
        j++;
    }

    for (size_t k = 0; k < sorted_size; k++)
        tmp[start + k] = sorted[k];

    free(sorted);
}

static size_t *mergeS(void *array, size_t *tmp, size_t start, size_t end, int (*compare)(const void *, size_t i, size_t j))
{
    if (end - start > 1)
    {

        size_t middle = (start + end) / 2;
        // printf("%zu\n", middle);

        mergeS(array, tmp, start, middle, compare);
        mergeS(array, tmp, middle, end, compare);
        merge(array, tmp, start, middle, end, compare);
    }
    return tmp;
}

static void mergeSort(void *array, size_t length, int (*compare)(const void *, size_t i, size_t j), void (*swap)(void *array, size_t i, size_t j))
{
    // tmp stores the permutation produced by mergeS
    size_t *tmp = (size_t *)malloc(length * sizeof(size_t));
    // idx stores the current state of the *array
    size_t *idx = (size_t *)malloc(length * sizeof(size_t));
    // inv_idx stores the inverse mapping of idx
    size_t *inv_idx = (size_t *)malloc(length * sizeof(size_t));

    if (tmp == NULL || idx == NULL || inv_idx == NULL)
    {
        fprintf(stderr, "MEMORY ALLOCATION ERROR !\n");
        exit(1);
    }

    for (size_t i = 0; i < length; i++)
    {
        idx[i] = i;
        tmp[i] = i;
        inv_idx[i] = i;
    }

    mergeS(array, tmp, 0, length, compare);

    for (size_t i = 0; i < length - 1; i++)
    {
        // tmp[i] = index of the element (in the original array) that should be placed at position i in the sorted array
        size_t orig = tmp[i];
        // inv_idx[origin] = current position of this element in the array
        size_t j = inv_idx[orig];

        if (j != i)
        {
            swap(array, j, i);

            size_t displaced = idx[i];

            idx[j] = displaced;
            idx[i] = orig;
            inv_idx[displaced] = j;
            inv_idx[orig] = i;
        }
    }
    free(tmp);
    free(inv_idx);
    free(idx);
}
void sort(void *array, size_t length, int (*compare)(const void *, size_t i, size_t j), void (*swap)(void *array, size_t i, size_t j))
{
    mergeSort(array, length, compare, swap);
}
