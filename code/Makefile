.PHONY: all clean run benchmarks

CC     = gcc
CFLAGS = -g -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

# ─── Exécutables principaux ───────────────────────────────────────────────────

all: autocompletelinear autocompletesort_qs autocompletesort_ms autocompletepq_qs autocompletepq_ms

clean:
	rm -f *.o \
	      autocompletelinear autocompletesort_* autocompletepq_* \
	      benchmarklinear benchmarksort_qs benchmarksort_ms \
	      benchmarkpq_qs benchmarkpq_ms

run: autocompletelinear
	./autocompletelinear -i Data/baby-names.txt 20

autocompletelinear: main.o Terms.o AutoCompleteLinear.o
	$(CC) -o $@ $^ $(LDFLAGS) -lncurses

autocompletesort_qs: main.o Terms.o QuickSort.o AutoCompleteSort.o BinarySearch.o
	$(CC) -o $@ $^ $(LDFLAGS) -lncurses

autocompletesort_ms: main.o Terms.o MergeSort.o AutoCompleteSort.o BinarySearch.o
	$(CC) -o $@ $^ $(LDFLAGS) -lncurses

autocompletepq_qs: main.o Terms.o QuickSort.o AutoCompletePQ.o BinarySearch.o PQ.o
	$(CC) -o $@ $^ $(LDFLAGS) -lncurses

autocompletepq_ms: main.o Terms.o MergeSort.o AutoCompletePQ.o BinarySearch.o PQ.o
	$(CC) -o $@ $^ $(LDFLAGS) -lncurses

# ─── Exécutables de benchmark (question 4) ───────────────────────────────────

benchmarks: benchmarklinear benchmarksort_qs benchmarksort_ms benchmarkpq_qs benchmarkpq_ms

benchmarklinear: benchmark.o Terms.o AutoCompleteLinear.o BinarySearch.o MergeSort.o
	$(CC) -o $@ $^ $(LDFLAGS)

benchmarksort_qs: benchmark.o Terms.o AutoCompleteSort.o BinarySearch.o QuickSort.o
	$(CC) -o $@ $^ $(LDFLAGS)

benchmarksort_ms: benchmark.o Terms.o AutoCompleteSort.o BinarySearch.o MergeSort.o
	$(CC) -o $@ $^ $(LDFLAGS)

benchmarkpq_qs: benchmark.o Terms.o AutoCompletePQ.o BinarySearch.o QuickSort.o PQ.o
	$(CC) -o $@ $^ $(LDFLAGS)

benchmarkpq_ms: benchmark.o Terms.o AutoCompletePQ.o BinarySearch.o MergeSort.o PQ.o
	$(CC) -o $@ $^ $(LDFLAGS)

# ─── Règles de compilation des objets ────────────────────────────────────────

AutoCompleteSort.o:  AutoCompleteSort.c  AutoComplete.h Terms.h Sort.h BinarySearch.h
AutoCompletePQ.o:    AutoCompletePQ.c    AutoComplete.h Terms.h Sort.h BinarySearch.h PQ.h
AutoCompleteLinear.o: AutoCompleteLinear.c AutoComplete.h Terms.h
Terms.o:       Terms.c       Terms.h
main.o:        main.c        Terms.h AutoComplete.h
MergeSort.o:   MergeSort.c   Sort.h
QuickSort.o:   QuickSort.c   Sort.h
BinarySearch.o: BinarySearch.c BinarySearch.h
PQ.o:          PQ.c          PQ.h
benchmark.o:   benchmark.c   Terms.h AutoComplete.h