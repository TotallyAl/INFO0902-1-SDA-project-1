#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinarySearch.h"

/* =========================================================================
 * Comparateur pour un tableau d'entiers
 * ========================================================================= */
int compareInt(const void *array, size_t i, void *key)
{
    const int *arr = (const int *)array;
    int k = *(int *)key;
    return arr[i] - k;
}

/* =========================================================================
 * Utilitaire d'affichage
 * ========================================================================= */
static int passed = 0;
static int failed = 0;

void checkLow(const char *label, int *array, size_t length, int key, size_t expected)
{
    size_t result = binarySearchLow(array, length, &key, compareInt);
    if (result == expected)
    {
        printf("  [PASS] %s  --> index=%zu\n", label, result);
        passed++;
    }
    else
    {
        printf("  [FAIL] %s  --> attendu=%zu  obtenu=%zu\n", label, expected, result);
        failed++;
    }
}

void checkHigh(const char *label, int *array, size_t length, int key, size_t expected)
{
    size_t result = binarySearchHigh(array, length, &key, compareInt);
    if (result == expected)
    {
        printf("  [PASS] %s  --> index=%zu\n", label, result);
        passed++;
    }
    else
    {
        printf("  [FAIL] %s  --> attendu=%zu  obtenu=%zu\n", label, expected, result);
        failed++;
    }
}

/* =========================================================================
 * Tests
 * ========================================================================= */
int main(void)
{
    printf("=== Tests BinarySearch ===\n\n");

    /* --------------------------------------------------------------------- *
     * Tableau de base : {1, 2, 3, 3, 3, 5, 7}  (indices 0..6)
     * --------------------------------------------------------------------- */
    int arr[] = {1, 2, 3, 3, 3, 5, 7};
    size_t len = 7;

    printf("Tableau : {1, 2, 3, 3, 3, 5, 7}\n");
    printf("--- binarySearchLow ---\n");

    // Clé présente en plusieurs exemplaires : doit retourner l'indice le plus à gauche
    checkLow("Low(3) dans {1,2,3,3,3,5,7}  --> attendu 2", arr, len, 3, 2);

    // Clé présente en un seul exemplaire
    checkLow("Low(1) dans {1,2,3,3,3,5,7}  --> attendu 0", arr, len, 1, 0);
    checkLow("Low(7) dans {1,2,3,3,3,5,7}  --> attendu 6", arr, len, 7, 6);

    // Clé absente (entre deux valeurs) : position quelconque sans la clé
    // La spec autorise n'importe quel indice ≠ clé, on vérifie juste que
    // l'indice retourné ne pointe PAS sur la clé.
    {
        int key = 4;
        size_t r = binarySearchLow(arr, len, &key, compareInt);
        if (arr[r] != key)
        {
            printf("  [PASS] Low(4 absent)  --> index=%zu valeur=%d (≠4)\n", r, arr[r]);
            passed++;
        }
        else
        {
            printf("  [FAIL] Low(4 absent)  --> index=%zu valeur=%d (==4 !!)\n", r, arr[r]);
            failed++;
        }
    }

    printf("\n--- binarySearchHigh ---\n");

    // Clé présente en plusieurs exemplaires : doit retourner l'indice le plus à droite
    checkHigh("High(3) dans {1,2,3,3,3,5,7}  --> attendu 4", arr, len, 3, 4);

    // Clé présente en un seul exemplaire
    checkHigh("High(1) dans {1,2,3,3,3,5,7}  --> attendu 0", arr, len, 1, 0);
    checkHigh("High(7) dans {1,2,3,3,3,5,7}  --> attendu 6", arr, len, 7, 6);

    // Clé absente : même logique, l'indice retourné ne doit pas pointer sur la clé.
    {
        int key = 4;
        size_t r = binarySearchHigh(arr, len, &key, compareInt);
        if (arr[r] != key)
        {
            printf("  [PASS] High(4 absent)  --> index=%zu valeur=%d (≠4)\n", r, arr[r]);
            passed++;
        }
        else
        {
            printf("  [FAIL] High(4 absent)  --> index=%zu valeur=%d (==4 !!)\n", r, arr[r]);
            failed++;
        }
    }

    /* --------------------------------------------------------------------- *
     * Tableau d'un seul élément
     * --------------------------------------------------------------------- */
    printf("\nTableau : {42}  (un seul élément)\n");
    int single[] = {42};

    printf("--- binarySearchLow ---\n");
    checkLow("Low(42)  --> attendu 0", single, 1, 42, 0);

    printf("--- binarySearchHigh ---\n");
    checkHigh("High(42) --> attendu 0", single, 1, 42, 0);

    /* --------------------------------------------------------------------- *
     * Tableau avec tous les éléments identiques : {5, 5, 5, 5, 5}
     * --------------------------------------------------------------------- */
    printf("\nTableau : {5, 5, 5, 5, 5}\n");
    int allSame[] = {5, 5, 5, 5, 5};

    printf("--- binarySearchLow ---\n");
    checkLow("Low(5)  --> attendu 0", allSame, 5, 5, 0);

    printf("--- binarySearchHigh ---\n");
    checkHigh("High(5) --> attendu 4", allSame, 5, 5, 4);

    /* --------------------------------------------------------------------- *
     * Clé plus petite que tous les éléments
     * Correction appliquée : right > 0 empêche l'underflow size_t.
     * Les deux fonctions doivent retourner un index ne contenant pas la clé.
     * --------------------------------------------------------------------- */
    printf("\nCas limite : clé < tous les éléments\n");
    int arr2[] = {10, 20, 30};

    printf("--- binarySearchLow ---\n");
    {
        int key = 5;
        size_t r = binarySearchLow(arr2, 3, &key, compareInt);
        if (arr2[r] != key)
        {
            printf("  [PASS] Low(5 < tous)  --> index=%zu valeur=%d (≠5)\n", r, arr2[r]);
            passed++;
        }
        else
        {
            printf("  [FAIL] Low(5 < tous)  --> index=%zu valeur=%d\n", r, arr2[r]);
            failed++;
        }
    }

    printf("--- binarySearchHigh ---\n");
    {
        int key = 5;
        size_t r = binarySearchHigh(arr2, 3, &key, compareInt);
        if (arr2[r] != key)
        {
            printf("  [PASS] High(5 < tous) --> index=%zu valeur=%d (≠5)\n", r, arr2[r]);
            passed++;
        }
        else
        {
            printf("  [FAIL] High(5 < tous) --> index=%zu valeur=%d\n", r, arr2[r]);
            failed++;
        }
    }

    /* --------------------------------------------------------------------- *
     * Clé plus grande que tous les éléments
     * --------------------------------------------------------------------- */
    printf("\nCas limite : clé > tous les éléments\n");

    printf("--- binarySearchLow ---\n");
    // left == length en sortie --> retourne length-1 (valeur ≠ clé : OK selon spec)
    {
        int key = 99;
        size_t r = binarySearchLow(arr2, 3, &key, compareInt);
        if (arr2[r] != key)
        {
            printf("  [PASS] Low(99 > tous)  --> index=%zu valeur=%d (≠99)\n", r, arr2[r]);
            passed++;
        }
        else
        {
            printf("  [FAIL] Low(99 > tous)  --> index=%zu valeur=%d\n", r, arr2[r]);
            failed++;
        }
    }

    printf("--- binarySearchHigh ---\n");
    // right == length --> retourne length-1 : OK selon spec
    {
        int key = 99;
        size_t r = binarySearchHigh(arr2, 3, &key, compareInt);
        if (arr2[r] != key)
        {
            printf("  [PASS] High(99 > tous) --> index=%zu valeur=%d (≠99)\n", r, arr2[r]);
            passed++;
        }
        else
        {
            printf("  [FAIL] High(99 > tous) --> index=%zu valeur=%d\n", r, arr2[r]);
            failed++;
        }
    }

    /* --------------------------------------------------------------------- *
     * Résumé
     * --------------------------------------------------------------------- */
    printf("\n=== Résultat : %d passés, %d échoués ===\n", passed, failed);
    return failed == 0 ? 0 : 1;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #include "BinarySearch.h"

// int compareInt(const void *array, size_t i, void *key)
// {
//     int *a = (int *)array;
//     int k = *(int *)key;

//     if (a[i] < k)
//         return -1;
//     if (a[i] > k)
//         return 1;
//     return 0;
// }

// int main()
// {

//     int a[] = {0, 1, 2, 2, 2, 2, 2, 3, 4, 6, 7, 8, 9};
//     size_t length = sizeof(a) / sizeof(a[0]);

//     int key = 9;

//     size_t result = binarySearchLow(a, length, &key, compareInt);
//     size_t result2 = binarySearchHigh(a, length, &key, compareInt);

//     printf("key: %d\n", key);
//     printf("Result low: %zu\n", result);
//     printf("Result high: %zu\n", result2);

//     return 0;
// }