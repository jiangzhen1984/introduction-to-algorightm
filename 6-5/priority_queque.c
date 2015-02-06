

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define BUFF_SIZE (2)

#define ARR_PARENT(i) ((i) / 2)

#define ARR_LEFT(i) ((i) * 2 )

#define ARR_RIGHT(i) ((i) * 2 + 1)


struct MaxHeap {
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


void max_heapify(struct MaxHeap * pHeap, int index)
{

	int left, right, largest;
	int key;
	left = ARR_LEFT(index);
	right = ARR_RIGHT(index);

	pt_arrar(pHeap->n, pHeap->heap_size + 1, " fying");

	if (pHeap->heap_size >= left && pHeap->n[left] > pHeap->n[index]) {
		largest = left;
	} else {
		largest = index;
	}

	if (pHeap->heap_size >= right && pHeap->n[right] > pHeap->n[largest]) {
		largest = right;
	}

	if (largest != index) {
		key = pHeap->n[index];	
		pHeap->n[index] = pHeap->n[largest];
		pHeap->n[largest] = key;
		max_heapify(pHeap, largest);
	}
}



void build_max_heap(struct MaxHeap * pHeap)
{
	int index;
	pHeap->heap_size = pHeap->len;
	index = pHeap->heap_size / 2;
	while (index > 0) {
		max_heapify(pHeap, index);
		index--;
	}
}

int queue_maximum(struct MaxHeap * pHeap) {
	if (pHeap->heap_size == 0) {
		return -1;
	} else {
		return pHeap->n[1];
	}
}


int queue_extract_maximum(struct MaxHeap * pHeap) {
	int key;
	if (pHeap->heap_size == 0) {
		return -1;
	}

	key = pHeap->n[1];
	pHeap->n[1] = pHeap->n[pHeap->heap_size];
	pHeap->heap_size --;

	max_heapify(pHeap, 1);
	return key;
}




void max_heap_rebuild_sub(struct MaxHeap * pHeap, int index)
{
}


void queue_delete(struct MaxHeap * pHeap, int index) {

	if (pHeap->heap_size == 0 || index > pHeap->heap_size || index < 0) {
		return;
	}

	pHeap->n[index] = pHeap->n[pHeap->heap_size];
	pHeap->heap_size --;

	max_heapify(pHeap, index);
}


void queue_insert(struct MaxHeap * pHeap, int key) {
	
	int i, p;
	//Increase 
	if (pHeap->heap_size == pHeap->len) {
		int * newHeap = (int *) malloc((pHeap->len) * 2 * sizeof(int) + sizeof(int));	
		memset(newHeap, 0, (pHeap->len) * 2 * sizeof(int) + sizeof(int) );
		memcpy(newHeap, pHeap->n, (pHeap->heap_size + 1) * sizeof(int));
		free(pHeap->n);
		pHeap->n = newHeap;
		pHeap->len *= 2;
	}

	pHeap->heap_size += 1;
	i = pHeap->heap_size;
	p = ARR_PARENT(i);
	pHeap->n[i] =  key;

	while (i >=1 && (pHeap->n[p] < pHeap->n[i] && p > 0)) {
		int m = pHeap->n[p];
		pHeap->n[p] = pHeap->n[i];
		pHeap->n[i] = m;
		i = p;
		p = ARR_PARENT(i);
	}	
	
}

static struct MaxHeap * pPriQueue = NULL;


int main(int argc, char ** argv) {

	int input = 0, key;
	char buf[100];

	pPriQueue = (struct MaxHeap *) malloc(sizeof(struct MaxHeap));
	pPriQueue->n = (int *) malloc((BUFF_SIZE + 1) * sizeof(int));	
	pPriQueue->heap_size = 0;
	pPriQueue->len = BUFF_SIZE;

	queue_insert(pPriQueue, 14);
	queue_insert(pPriQueue, 24);
	queue_insert(pPriQueue, 54);
	queue_insert(pPriQueue, 24);
	queue_insert(pPriQueue, 99);

	do {
		printf("=================\n");
		printf("1 : insert new key\n");
		printf("2 : get max of queue\n");
		printf("3 : extract max of queue\n");
		printf("4 : delete key\n");
		printf("5 : print queue\n");
		printf("0 : exit\n");
		scanf("%d", &input);	
		switch (input) {
			case 1:
				printf(" Input new key:\n");
				scanf("%d", &key);	
				queue_insert(pPriQueue, key);
				break;
			case 2:
				key = queue_maximum(pPriQueue);
				printf("  =====> max key:%d\n", key);
				break;
			case 3:
				key = queue_extract_maximum(pPriQueue);
				printf("  =====> max key:%d\n", key);
				break;
			case 4:
				printf(" Input index[1-%d]:\n", pPriQueue->heap_size);
				scanf("%d", &key);	
				queue_delete(pPriQueue, key);
			case 5:
				pt_arrar(pPriQueue->n, pPriQueue->heap_size + 1, "");
				break;
				
		}

	} while (input != 0);


};
