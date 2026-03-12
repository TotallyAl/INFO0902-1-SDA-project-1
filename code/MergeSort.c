#include <stdio.h>
#include <stdlib.h>

void merge(void *array, size_t *tmp, size_t start, size_t middle, size_t end, int (*compare)(const void *, size_t i, size_t j))
{
    size_t sorted_size = end - start;
    size_t *sorted = (size_t *)malloc(sorted_size * sizeof(size_t));

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

size_t *mergeS(void *array, size_t *tmp, size_t start, size_t end, int (*compare)(const void *, size_t i, size_t j))
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

void mergeSort(void *array, size_t length, int (*compare)(const void *, size_t i, size_t j), void (*swap)(void *array, size_t i, size_t j))
{

    size_t *tmp = (size_t *)malloc(length * sizeof(size_t));

    for (size_t i = 0; i < length; i++)
        tmp[i] = i;

    // tmp sorted
    mergeS(array, tmp, 0, length, compare);

    printf("tmp = ");
    for (size_t i = 0; i < length; i++)
        printf("%zu ", tmp[i]);
    printf("\n");

    // We need to finish here !
    // TMP is in the correct order. I just need to find a way to swap the values in array. I am too tired for that now.

    free(tmp);
}

void sort(void *array, size_t length, int (*compare)(const void *, size_t i, size_t j), void (*swap)(void *array, size_t i, size_t j))
{
    mergeSort(array, length, compare, swap);
}