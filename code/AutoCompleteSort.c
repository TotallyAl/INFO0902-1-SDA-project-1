#include <stdio.h>
#include <string.h>

#include "AutoComplete.h"
#include "Sort.h"
#include "BinarySearch.h"

/*

AutoCompleteSort.c

    1. On trie initialement la liste des termes par ordre Lexicographique
        --> Sort.h pour trier la liste de termes dans l'ordre lexicographique.
    2. On détermine les m termes dont la requête est un préfixe par une recherche binaire
        --> BinarySearch.c
    3. On trie les m termes par ordre décroissants de poids et on extrait les k premiers termes dans l'ordre obtenu.
        --> A VOIR PLUS TARD
*/

struct AC_t
{
    TermArray *ta;
};

static void printAllTerms(const TermArray *ta);
int compareTerm(const void *array, size_t i, size_t j);
void swapTerm(void *array, size_t i, size_t j);
int compareBSTerm(const void *array, size_t i, void *key);
int compareTermWeight(const void *array, size_t i, size_t j);
void swapTermWeight(void *array, size_t i, size_t j);
void printArrayTerms(Term *terms, size_t length);
size_t commonPrefix(AC *ac, char *query, size_t idx);

/*

    Helper methods

*/

void printArrayTerms(Term *terms, size_t length)
{
    for (size_t i = 0; i < length; i++)
        printf("(%ld) %s\n", terms[i].weight, terms[i].text);
}

int compareTermWeight(const void *array, size_t i, size_t j)
{
    const Term *terms = (Term *)array;

    if (terms[j].weight < terms[i].weight)
        return -1;
    if (terms[j].weight > terms[i].weight)
        return 1;
    return 0;
}

void swapTermWeight(void *array, size_t i, size_t j)
{
    Term *terms = (Term *)array;

    Term tmp = terms[i];
    terms[i] = terms[j];
    terms[j] = tmp;
}

static void printAllTerms(const TermArray *ta)
{
    for (size_t i = 0; i < ta->length; i++)
    {
        printf("(%ld) %s\n", ta->array[i].weight, ta->array[i].text);
    }
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

/*

    Implemented methods

*/

AC *acCreate(TermArray *ta)
{
    AC *ac = malloc(sizeof(AC));
    if (ac == NULL)
    {
        fprintf(stderr, "acCreate: ALLOCATION ERROR.\n");
        exit(1);
    }
    // sortAlphabeticalOrder(ta);
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
    // The elements inside *ac are sorted in alphabetical order.

    // 1. We want to find the m terms that match the prefix of query with a BinarySearch(Low)

    size_t idx = binarySearchLow(ac->ta->array, ac->ta->length, query, compareBSTerm);

    size_t m = commonPrefix(ac, query, idx);

    // There are no terms that share the prefix *query
    if (m == 0)
        return 0;

    Term *terms = (Term *)malloc(m * sizeof(Term));
    if (terms == NULL)
    {
        fprintf(stderr, "acComplete: ALLOCATION ERROR\n");
        exit(1);
    }

    /*
        BinartSearchLow will find the term that ressembles the query the most,
        we have to take the next m words to have the auto-completion.
    */
    for (size_t i = 0; i < m; i++)
        terms[i] = ac->ta->array[idx + i];

    // 2. We sort the m terms with their respective weights and we extract the k first terms.
    sort(terms, m, compareTermWeight, swapTermWeight);

    // 4. On stocke les résultats dans **results.
    size_t limit = (m < k) ? m : k;
    for (size_t i = 0; i < limit; i++)
        results[i] = terms[i].text;

    free(terms);
    return limit;
}
