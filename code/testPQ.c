#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PQ.h"

/* ------------------------------------------------------------------------- *
 * Compare functions
 * ------------------------------------------------------------------------- */

int compareInt(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

/* ------------------------------------------------------------------------- *
 * Test helpers
 * ------------------------------------------------------------------------- */

static int passed = 0;
static int failed = 0;

static void check(const char *test_name, bool condition)
{
    if (condition)
    {
        printf("  [PASS] %s\n", test_name);
        passed++;
    }
    else
    {
        printf("  [FAIL] %s\n", test_name);
        failed++;
    }
}

/* ------------------------------------------------------------------------- *
 * Tests
 * ------------------------------------------------------------------------- */

static void testCreateAndFree(void)
{
    printf("\n--- testCreateAndFree ---\n");

    PQ *pq = pqCreate(10, compareInt);
    check("pqCreate returns non-NULL", pq != NULL);
    check("pqSize is 0 after create", pqSize(pq) == 0);
    check("pqCapacity is 10 after create", pqCapacity(pq) == 10);

    pqFree(pq);
}

static void testInsertAndSize(void)
{
    printf("\n--- testInsertAndSize ---\n");

    PQ *pq = pqCreate(3, compareInt);
    int a = 5, b = 3, c = 8;

    check("insert into empty queue", pqInsert(pq, &a) == true);
    check("size is 1 after 1 insert", pqSize(pq) == 1);
    check("insert second element", pqInsert(pq, &b) == true);
    check("insert third element", pqInsert(pq, &c) == true);
    check("size is 3 after 3 inserts", pqSize(pq) == 3);
    check("insert into full queue returns false", pqInsert(pq, &a) == false);
    check("size stays 3 after failed insert", pqSize(pq) == 3);

    pqFree(pq);
}

static void testGetMax(void)
{
    printf("\n--- testGetMax ---\n");

    PQ *pq = pqCreate(5, compareInt);
    int a = 5, b = 3, c = 8, d = 1, e = 7;

    pqInsert(pq, &a);
    check("max is 5 after inserting 5", *(int *)pqGetMax(pq) == 5);
    pqInsert(pq, &b);
    check("max is still 5 after inserting 3", *(int *)pqGetMax(pq) == 5);
    pqInsert(pq, &c);
    check("max is 8 after inserting 8", *(int *)pqGetMax(pq) == 8);
    pqInsert(pq, &d);
    check("max is still 8 after inserting 1", *(int *)pqGetMax(pq) == 8);
    pqInsert(pq, &e);
    check("max is still 8 after inserting 7", *(int *)pqGetMax(pq) == 8);

    pqFree(pq);
}

static void testExtractMax(void)
{
    printf("\n--- testExtractMax ---\n");

    PQ *pq = pqCreate(5, compareInt);
    int values[] = {4, 2, 7, 1, 9};
    for (int i = 0; i < 5; i++)
        pqInsert(pq, &values[i]);

    check("size is 5 before extracts", pqSize(pq) == 5);
    check("first extract gives 9", *(int *)pqExtractMax(pq) == 9);
    check("size is 4 after first extract", pqSize(pq) == 4);
    check("second extract gives 7", *(int *)pqExtractMax(pq) == 7);
    check("third extract gives 4", *(int *)pqExtractMax(pq) == 4);
    check("fourth extract gives 2", *(int *)pqExtractMax(pq) == 2);
    check("fifth extract gives 1", *(int *)pqExtractMax(pq) == 1);
    check("size is 0 after all extracts", pqSize(pq) == 0);

    pqFree(pq);
}

static void testReplaceMax(void)
{
    printf("\n--- testReplaceMax ---\n");

    PQ *pq = pqCreate(3, compareInt);
    int a = 5, b = 3, c = 8;
    int replacement_high = 99;
    int replacement_low = 1;

    pqInsert(pq, &a);
    pqInsert(pq, &b);
    pqInsert(pq, &c);

    check("max is 8 before replace", *(int *)pqGetMax(pq) == 8);
    check("size stays 3 after replace", pqSize(pq) == 3);

    pqReplaceMax(pq, &replacement_high);
    check("max is 99 after replacing with 99", *(int *)pqGetMax(pq) == 99);

    pqReplaceMax(pq, &replacement_low);
    check("max is 5 after replacing 99 with 1", *(int *)pqGetMax(pq) == 5);
    check("size is still 3 after two replaces", pqSize(pq) == 3);

    pqFree(pq);
}

static void testExtractOrder(void)
{
    printf("\n--- testExtractOrder (extracts must be decreasing) ---\n");

    PQ *pq = pqCreate(10, compareInt);
    int values[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    for (int i = 0; i < 10; i++)
        pqInsert(pq, &values[i]);

    bool ordered = true;
    int prev = *(int *)pqExtractMax(pq);
    while (pqSize(pq) > 0)
    {
        int curr = *(int *)pqExtractMax(pq);
        if (curr > prev)
        {
            ordered = false;
            break;
        }
        prev = curr;
    }
    check("extracts are in decreasing order", ordered);

    pqFree(pq);
}

static void testCapacityOne(void)
{
    printf("\n--- testCapacityOne ---\n");

    PQ *pq = pqCreate(1, compareInt);
    int a = 42, b = 99;

    check("insert into capacity-1 queue", pqInsert(pq, &a) == true);
    check("second insert fails", pqInsert(pq, &b) == false);
    check("max is 42", *(int *)pqGetMax(pq) == 42);
    check("extract gives 42", *(int *)pqExtractMax(pq) == 42);
    check("size is 0 after extract", pqSize(pq) == 0);

    pqFree(pq);
}

/* ------------------------------------------------------------------------- *
 * Main
 * ------------------------------------------------------------------------- */

int main(void)
{
    printf("========== Priority Queue Tests ==========\n");

    testCreateAndFree();
    testInsertAndSize();
    testGetMax();
    testExtractMax();
    testReplaceMax();
    testExtractOrder();
    testCapacityOne();

    printf("\n==========================================\n");
    printf("Results: %d passed, %d failed\n", passed, failed);
    printf("==========================================\n");

    return failed == 0 ? 0 : 1;
}