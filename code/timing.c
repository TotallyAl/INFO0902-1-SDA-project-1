#include <stdio.h>
#include <time.h>
#include <string.h>

#include "Sort.h"
#include "Terms.h"

static int compareTerm(const void *array, size_t i, size_t j);
static void swapTerm(void *array, size_t i, size_t j);
static int compareTermWeight(const void *array, size_t i, size_t j);
static void swapTermWeight(void *array, size_t i, size_t j);
static double measureSort(char *filename, int byWeight);

/*

    Comparateurs lexicographiques

*/

static int compareTerm(const void *array, size_t i, size_t j)
{
    const Term *A = array;
    return strcmp(A[i].text, A[j].text);
}

static void swapTerm(void *array, size_t i, size_t j)
{
    Term *A = array;

    Term tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

static int compareTermWeight(const void *array, size_t i, size_t j)
{
    const Term *terms = (Term *)array;

    if (terms[j].weight < terms[i].weight)
        return -1;
    if (terms[j].weight > terms[i].weight)
        return 1;
    return 0;
}

static void swapTermWeight(void *array, size_t i, size_t j)
{
    Term *terms = (Term *)array;

    Term tmp = terms[i];
    terms[i] = terms[j];
    terms[j] = tmp;
}

/*

    Mesure du temps de tri

*/

static double measureSort(char *filename, int byWeight)
{

    TermArray *ta = termsLoadFile(filename);

    clock_t start = clock();
    if (byWeight)
        sort(ta->array, ta->length, compareTermWeight, swapTermWeight);
    else
        sort(ta->array, ta->length, compareTerm, swapTerm);

    clock_t end = clock();

    double time = (double)(end - start) / CLOCKS_PER_SEC;
    termsFree(ta);
    return time;
}

int main(void)
{
    const char *files[] = {"Data/actors_25k.txt", "Data/actors_250k.txt", "Data/actors_250k.txt"};
    const int nb_f = 3;

    printf("%-25s | %15s | %15s\n", "Fichier", "Lexico", "Poids");
    printf("%-25s-+-%15s-+-%15s\n", "-------------------------", "---------------", "---------------");

    for (int i = 0; i < nb_f; i++)
    {
        // printf("Timing lexico\n");
        double t_lexico = measureSort((char *)files[i], 0);
        // printf("Timing weight\n");
        double t_weight = measureSort((char *)files[i], 1);
        printf("%-25s | %15.6f | %15.6f\n", files[i], t_lexico, t_weight);
    }
    return 0;
}
