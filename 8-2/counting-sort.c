
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


void counting_sort(int a[], int b[], int k, int len)
{
	int c[k + 1];
	int i;
	for (i = 0; i <= k; i++) {
		c[i] = 0;
	}

	for (i = 1; i <= len; i++) {
		c[a[i]] = c[a[i]] + 1;
	}

	printf("        C[");
	for(i = 0; i <= k; i++) {
		printf("%d, ", c[i]);
	}
	printf("]\n");

	for (i = 1; i <= k; i++) {
		c[i] = c[i] + c[i - 1];
	}

	printf(" Merged C[");
	for(i = 0; i <= k; i++) {
		printf("%d, ", c[i]);
	}
	printf("]\n");

	for (i = len; i > 0; i--) {
		b[c[a[i]]] = a[i];
		c[a[i]] = c[a[i]] - 1;
	}

}


int main(int argc, char ** argv) {

	int len = argc;
	int n[len], b[len], i, j;	
	int max = 0;
	++argv;
	for (i = 1; i <= len && *argv != NULL; ++argv,i++) {
		n[i] = atoi(*argv);
		if (n[i] < 0) {
			printf(" [ERROR] Counting-Sort doesn't support negetive\n");
			return;
		}
		if (n[i] > max) {
			max = n[i];
		}
	}

	pt_arrar(n, len , "Initialized");
	counting_sort(n, b, max, len - 1);
	pt_arrar(b, len , "Sorted");

}


