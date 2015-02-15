

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void print_array(int n[], int len, char * str)
{
	int i = 1;
	printf(" %s [", str);
	for (i = 1; i <= len; i++) {
		printf(" %d,", n[i]);
	}
	printf("]\n");
	
}


int partition(int n[], int p, int q)
{
	int key = n[q];
	int i = p - 1;
	int j = 1;

	for (j = 1; j < q; j++) {
		if (n[j] < key) {
			i = i + 1;
			int tmp = n[i];
			n[i] = n[j];
			n[j] = tmp;
		}
	}
	
	n[q] = n[i + 1];
	n[i + 1] = key;
	return i + 1;
	
}


int selection(int n[], int p, int r, int i)
{
	int k, q;
	if (p == r) {
		return n[p];
	}
	q = partition(n, p, r);
	k = q - p + 1;

	if (k == i) {
		return n[k];
	}

	if (i < k) {
		return selection(n, p, q - 1, i);
	} else {
		return selection(n, q + 1, r, i - k);
	}
	
}



int main(int argc, char ** argv)
{
	int len = argc - 1;
	int n[argc];
	int i = 0;
	++ argv;
	while ( ++i <= len && argv != NULL && *argv != NULL) {
		n[i] = atoi(*argv++);
	}

	print_array(n, len, "Array Initialized");
	for (i = 1; i < len; i++ ) {
		int min = selection(n, 1, len, i);
		printf("==========%dth minimum is %d\n", i, min);
	}
	return 0;
}
