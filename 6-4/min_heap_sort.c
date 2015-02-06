
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define ARR_LEFT(i) ((i) * 2 )

#define ARR_RIGHT(i) ((i) * 2 + 1)



struct MinHeap {
	
	int heap_size;
	int len;

	int * n;
};

void pt_arrar(int n[], int len, char * str) {
	int i = 1;

	printf("%s [", str);
	for(i = 1; i < len; i++) {
		printf("%d, ", n[i]);
	}
	printf("]\n");
}

void min_heapify(struct MinHeap * pHeap, int index)
{

	int left, right, smallest;
	int key;
	left = ARR_LEFT(index);
	right = ARR_RIGHT(index);

	if (pHeap->heap_size >= left && pHeap->n[left] < pHeap->n[index]) {
		smallest = left;
	} else {
		smallest = index;
	}

	if (pHeap->heap_size >= right && pHeap->n[right] < pHeap->n[smallest]) {
		smallest = right;
	}

	if (smallest != index) {
		key = pHeap->n[index];	
		pHeap->n[index] = pHeap->n[smallest];
		pHeap->n[smallest] = key;
		min_heapify(pHeap, smallest);
	}
}



void build_min_heap(struct MinHeap * pHeap)
{
	int index;
	pHeap->heap_size = pHeap->len;
	index = pHeap->heap_size / 2;
	while (index > 0) {
		min_heapify(pHeap, index);
		index--;
	}
}



void min_heap_sort(struct MinHeap * pHeap) {
	
	int key;	

	while (pHeap->heap_size >= 1) {
		key = pHeap->n[pHeap->heap_size];
		pHeap->n[pHeap->heap_size] = pHeap->n[1];
		pHeap->n[1] = key;
		pHeap->heap_size --;
		min_heapify(pHeap, 1);
	}
	
}



int main(int argc, char ** argv) {

	int n[argc], i, j;	
	int key;
	++argv;
	for (i = 1; i <= argc && *argv != NULL; ++argv,i++) {
		n[i] = atoi(*argv);
	}

	pt_arrar(n, argc, "Initialized");
	struct MinHeap heap;
	heap.len = argc - 1;
	heap.n = n;

	build_min_heap(&heap);
	pt_arrar(n, argc, "Heap Initialized");

	min_heap_sort(&heap);
	pt_arrar(n, argc, "Min Heap Sorted");
	return 0;
}
