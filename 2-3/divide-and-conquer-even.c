
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void pt_arrar(int n[], int len, char * str) {
	int i = 0;

	printf("%s [", str);
	for(i = 0; i < len; i++) {
		printf("%d, ", n[i]);
	}
	printf("]\n");
}



void merge(int n[], int p, int q, int r)
{
	int n1,n2, i, j, k;
	n1 = q - p + 1;
	n2 = r - q;
	int L[n1];
	int R[n2];	
	for (i = 0; i < n1; i++) {
		L[i] = n[p + i];
	}

	for (i = 0; i < n2; i++) {
		R[i] = n[q + i + 1];
	}

	for (k=p,i = 0, j = 0; k <= r; k++) {
		// check left array is end
		if (i >= n1) {
			n[k] = R[j];
			j ++;
			continue;
		}
		// check right array is end
		if (j >= n2) {
			n[k] = L[i];
			i ++;
			continue;
		}
		if (L[i] <= R[j]) {
			n[k] = L[i];
			i++;
		} else {
			n[k] = R[j];
			j++;
		}
	}	

	pt_arrar(n + p, (r - p + 1), "sorting");
	
}


void merge_sort(int n[], int p, int r)
{
	int q = (r + p ) / 2;
	if (r > p  && q >= p) {
		merge_sort(n, p, q);
		merge_sort(n, q + 1, r);
		merge(n, p, q, r);
	}

}

int main(int argc, char ** argv)
{
	int n[argc - 1], i, j;	
	int key;
	++argv;
	for (i = 1; i <= argc && *argv != NULL; ++argv,i++) {
		n[i - 1] = atoi(*argv);
	}

	pt_arrar(n, argc - 1 , "Arrar Initialized");
	merge_sort(n, 0, argc - 2);
	pt_arrar(n, argc - 1 , "");

}
