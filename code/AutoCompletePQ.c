#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AutoComplete.h"
#include "Sort.h"
#include "BinarySearch.h"
#include "PQ.h"

/*

AutoCompletePQ.c

    1. On trie les terms par ordre lexicographique

    2. On détermine les m termes dont la requete est un préfixe par recherche binaire

    3. Utilisations d'une file à priorité
*/

struct AC_t
{
    TermArray *ta;
};

/*

    Helper methods

*/

int compareWeights(const void *e1, const void *e2);
size_t commonPrefix(AC *ac, char *query, size_t idx);
int compareTerm(const void *array, size_t i, size_t j);
void swapTerm(void *array, size_t i, size_t j);
int compareBSTerm(const void *array, size_t i, void *key);

int compareWeights(const void *e1, const void *e2)
{
    const Term *t1 = (const Term *)e1;
    const Term *t2 = (const Term *)e2;
    if (t1->weight < t2->weight)
        return 1;
    if (t1->weight > t2->weight)
        return -1;
    return 0;
}

size_t commonPrefix(AC *ac, char *query, size_t idx)
{
    size_t queryLen = strlen(query);
    size_t m = 0;
    while (idx + m < ac->ta->length)
    {
        if (strncmp(ac->ta->array[idx + m].text, query, queryLen) == 0)
            m++;
        else
            break;
    }
    return m;
}

int compareTerm(const void *array, size_t i, size_t j)
{
    const Term *A = array;
    return strcmp(A[i].text, A[j].text);
}

void swapTerm(void *array, size_t i, size_t j)
{
    Term *A = array;

    Term tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

int compareBSTerm(const void *array, size_t i, void *key)
{
    const Term *terms = (const Term *)array;
    const char *query = (char *)key;

    for (size_t k = 0; query[k] != '\0'; k++)
    {
        if (terms[i].text[k] == '\0')
            return -1; // term too short
        if (terms[i].text[k] < query[k])
            return -1;
        if (terms[i].text[k] > query[k])
            return 1;
    }
    return 0; // query is a prefix of term -> match
}

/*

    Implemented methods

*/

AC *acCreate(TermArray *ta)
{
    AC *ac = (AC *)malloc(sizeof(AC));

    if (ac == NULL)
    {
        fprintf(stderr, "acCreate: ALLOCATION ERROR FOR *ac");
        exit(1);
    }

    sort(ta->array, ta->length, compareTerm, swapTerm);

    ac->ta = ta;
    return ac;
}

void acFree(AC *ac)
{
    free(ac);
}

size_t acComplete(AC *ac, char *query, size_t k, char **results)
{
    // The elements inside *ac are sorted in lexicographical order.

    // 1. We want to find the m terms that match the prefix of query with a BinarySearch(Low);

    size_t idx = binarySearchLow(ac->ta->array, ac->ta->length, query, compareBSTerm);

    size_t m = commonPrefix(ac, query, idx);

    // There are no terms that share the prefix *query
    if (m == 0)
        return 0;

    /*
    2. Utiliser une file à priorité:
        - de taille limitée à k
        - en utilisant l'opposé du poids comme valeur de priorité
    */

    PQ *pq = pqCreate(k, compareWeights);
    if (pq == NULL)
    {
        fprintf(stderr, "acComplete: ALLOCATION ERROR FOR PQ\n");
        exit(1);
    }

    // for (size_t i = 0; i < m; i++)
    //     pqInsert(pq, &ac->ta->array[idx + i]);

    // for (size_t i = 0; i < m; i++)
    //     results[i] = ((Term *)pqExtractMax(pq))->text;

    for (size_t i = 0; i < m; i++)
    {
        if (pqSize(pq) < k)
            pqInsert(pq, &ac->ta->array[idx + i]);
        else if (compareWeights(&ac->ta->array[idx + i], pqGetMax(pq)) > 0)
            pqReplaceMax(pq, &ac->ta->array[idx + i]);
    }

    size_t nb = pqSize(pq);
    for (size_t i = 0; i < nb; i++)
        results[i] = ((Term *)pqExtractMax(pq))->text;

    pqFree(pq);
    return nb;
}
