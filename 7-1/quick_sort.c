
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pt_arrar(int n[], int len, char * str) {
	int i = 1;

	printf("%s [", str);
	for(i = 1; i < len; i++) {
		printf("%d, ", n[i]);
	}
	printf("]\n");
}



int quick_sort(int n[], int p, int r)
{
	int key = n[r];
	int i = p - 1;
	int j;
	int q;
	if (p >= r) {
		return;
	}

	for (j = p; j <= r - 1; j++) {
		if (n[j] <= key) {
			i = i+1;
			int tmp = n[i];
			n[i] = n[j];
			n[j] = tmp;
		}
	}

	int tmp = n[i+1];
	n[i+1] = n[r];
	n[r]= tmp;

	pt_arrar(n, r + 1, "Sorting");

	q = i + 1;
	quick_sort(n, p, q - 1);
	quick_sort(n, q + 1, r);
}


int main(int argc, char ** argv) {

	int n[argc + 1], i, j;	
	int key;
	++argv;
	for (i = 1; i <= argc && *argv != NULL; ++argv,i++) {
		n[i] = atoi(*argv);
	}

	pt_arrar(n, argc , "Initialized");
	quick_sort(n, 1, argc - 1);
	pt_arrar(n, argc , "Sorted");

}
