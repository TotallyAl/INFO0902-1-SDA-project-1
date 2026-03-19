#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "PQ.h"

struct PQ_t
{
    void **heap;
    size_t capacity; // Size allocated for **heap
    size_t size;     // Number of elements in the Queue
    int (*compare)(const void *, const void *);
};

static void swap(PQ *pq, size_t i, size_t j)
{
    void *tmp = pq->heap[j];
    pq->heap[j] = pq->heap[i];
    pq->heap[i] = tmp;
}

static size_t parent(size_t i)
{
    return (i - 1) / 2;
}

static size_t leftChild(size_t i)
{
    return 2 * i + 1;
}

static size_t rightChild(size_t i)
{
    return 2 * i + 2;
}

static void shiftUp(PQ *pq, size_t i)
{
    while (i > 0 && pq->compare(pq->heap[i], pq->heap[parent(i)]) > 0)
    {
        size_t p = parent(i);
        swap(pq, i, p);
        i = p;
    }
}

static void shiftDown(PQ *pq, size_t i)
{
    // The element with the lowest priority is at the top of the stack.
    while (true)
    {
        size_t largest = i;
        size_t left_c = leftChild(i);
        size_t right_c = rightChild(i);
        /*
        We need to check that:
            1. The element has children.
            2. The children are larger than the element.
        As long as those conditions are true, we swap the largest element and the element itself.

        If none of the children are larger than the element -> we are done
        */
        if (left_c < pq->size && pq->compare(pq->heap[left_c], pq->heap[largest]) > 0)
            largest = left_c;

        if (right_c < pq->size && pq->compare(pq->heap[right_c], pq->heap[largest]) > 0)
            largest = right_c;

        if (largest == i)
            break;

        swap(pq, i, largest);
        i = largest;
    }
}

PQ *pqCreate(size_t capacity, int (*compare)(const void *, const void *))
{
    PQ *pq = (PQ *)malloc(sizeof(PQ));
    if (pq == NULL)
    {
        fprintf(stderr, "pqCreate: ALLOCATION ERROR FOR PQ\n");
        exit(1);
    }

    pq->heap = malloc(capacity * sizeof(void *));

    if (pq->heap == NULL)
    {
        free(pq);
        fprintf(stderr, "pqCreate: ALLOCATION ERROR FOR **data IN PQ");
        exit(1);
    }

    pq->capacity = capacity;
    pq->size = 0;
    pq->compare = compare;
    return pq;
}

void pqFree(PQ *pq)
{
    if (pq == NULL)
        return;

    free(pq->heap);
    free(pq);
}

bool pqInsert(PQ *pq, void *obj)
{
    // There isn't enough memory allocated to the priority queue.
    if (pq->capacity <= pq->size)
        return false;

    pq->heap[pq->size] = obj; // We add the new element at the end of the list.

    // We now have to check if it's at the right priority.
    shiftUp(pq, pq->size);
    pq->size++;
    return true;
}

void *pqGetMax(const PQ *pq)
{
    if (pq->size == 0)
    {
        fprintf(stderr, "pqExtractMax: THE PQ IS EMPTY");
        exit(1);
    }
    return pq->heap[0];
}

void *pqExtractMax(PQ *pq)
{
    void *max = pq->heap[0];

    if (pq->size == 0)
    {
        fprintf(stderr, "pqExtractMax: THE PQ IS EMPTY");
        exit(1);
    }
    // We put the element with the lowest priority at the top of the stack and we shift it down to the correct area.
    pq->size--; // We first need to decrement size to get the element. Otherwise, we'll get data that is outside the heap. (important bug)
    pq->heap[0] = pq->heap[pq->size];
    shiftDown(pq, 0);

    return max;
}

void pqReplaceMax(PQ *pq, void *obj)
{
    if (pq->size == 0)
    {
        fprintf(stderr, "pqReplaceMax: THE PQ IS EMPTY");
        exit(1);
    }

    pq->heap[0] = obj;
    // We need to check that the element has the right priority
    shiftDown(pq, 0);
}

size_t pqSize(const PQ *pq)
{
    return pq->size;
}

size_t pqCapacity(const PQ *pq)
{
    return pq->capacity;
}
