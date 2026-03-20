#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Terms.h"
#include "AutoComplete.h"

#define K 20
#define MAX_L 10
#define REPEATS 100

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <datafile> <outputfile>\n", argv[0]);
        exit(1);
    }

    /* --- Chargement des termes --- */
    TermArray *ta = termsLoadFile(argv[1]);
    fprintf(stderr, "Read %zu terms from %s.\n", ta->length, argv[1]);

    /* --- Prétraitement --- */
    AC *ac = acCreate(ta);

    /* --- Initialisation du générateur aléatoire --- */
    srand(42);

    /* --- Fichier de sortie CSV --- */
    FILE *out = fopen(argv[2], "w");
    if (!out)
    {
        fprintf(stderr, "Cannot open output file %s\n", argv[2]);
        exit(1);
    }
    fprintf(out, "l,mean_time\n");

    char *results[K];

    for (int l = 0; l <= MAX_L; l++)
    {
        double total_time = 0.0;
        int valid_repeats = 0;

        for (int r = 0; r < REPEATS; r++)
        {
            /* Sélectionner un terme aléatoire assez long */
            const char *term = NULL;
            for (int attempt = 0; attempt < 1000; attempt++)
            {
                size_t idx = rand() % ta->length;
                if ((int)strlen(ta->array[idx].text) >= l)
                {
                    term = ta->array[idx].text;
                    break;
                }
            }

            if (term == NULL)
                continue; /* pas de terme assez long, on saute */

            /* Construire la requête de longueur l */
            char query[128];
            strncpy(query, term, l);
            query[l] = '\0';

            /* Mesurer acComplete */
            struct timespec t_start, t_end;
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            acComplete(ac, query, K, results);
            clock_gettime(CLOCK_MONOTONIC, &t_end);

            double elapsed = (t_end.tv_sec - t_start.tv_sec) + (t_end.tv_nsec - t_start.tv_nsec) * 1e-9;
            total_time += elapsed;
            valid_repeats++;
        }

        double mean = (valid_repeats > 0) ? total_time / valid_repeats : 0.0;
        fprintf(out, "%d,%.9f\n", l, mean);
        fprintf(stderr, "l=%d : mean=%.9fs (%d repeats)\n", l, mean, valid_repeats);
    }

    fclose(out);
    acFree(ac);
    termsFree(ta);
    return 0;
}
