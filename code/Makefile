.PHONY: all clean run

CC = gcc
CFLAGS = -g -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: autocompletelinear autocompletesort_qs autocompletesort_ms autocompletepq_qs autocompletepq_ms

clean:
	rm -f *.o autocompletelinear autocompletesort_* autocompletepq_*

run: autocompletelinear
	./autocompletelinear -i Data/baby-names.txt 20

autocompletelinear: main.o Terms.o AutoCompleteLinear.o
	$(CC) -o $@ $^ $(LDFLAGS) -g -lncurses

autocompletesort_qs: main.o Terms.o QuickSort.o AutoCompleteSort.o BinarySearch.o
	$(CC) -o $@ $^ $(LDFLAGS) -g -lncurses

autocompletesort_ms: main.o Terms.o MergeSort.o AutoCompleteSort.o BinarySearch.o
	$(CC) -o $@ $^ $(LDFLAGS) -g -lncurses

autocompletepq_qs: main.o Terms.o QuickSort.o AutoCompletePQ.o BinarySearch.o PQ.o
	$(CC) -o $@ $^ $(LDFLAGS) -g -lncurses

autocompletepq_ms: main.o Terms.o MergeSort.o AutoCompletePQ.o BinarySearch.o PQ.o
	$(CC) -o $@ $^ $(LDFLAGS) -g -lncurses

AutoCompleteSort.o: AutoCompleteSort.c AutoComplete.h Terms.h Sort.h BinarySearch.h
AutoCompletePQ.o: AutoCompletePQ.c AutoComplete.h Terms.h Sort.h BinarySearch.h
AutoCompleteLinear.o: AutoCompleteLinear.c AutoComplete.h Terms.h
Terms.o: Terms.c Terms.h
main.o: main.c Terms.h
MergeSort.o: MergeSort.c Sort.h
QuickSort.o: QuickSort.c Sort.h
BinarySearch.o: BinarySearch.c BinarySearch.h
PQ.o: PQ.c PQ.h
