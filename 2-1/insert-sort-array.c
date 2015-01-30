

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void pt_arrar(int n[], int len, char * str) {
	int i = 0;

	printf("%s [", str);
	for(i = 0; i < len; i++) {
		printf("%d, ", n[i]);
	}
	printf("]\n");
}



int main(int argc, char ** argv)
{
	int n[argc-1], i, j;	
	int key;
	++argv;
	for (i = 1; i <= argc && *argv != NULL; ++argv,i++) {
		n[i - 1] = atoi(*argv);
	}

	pt_arrar(n, argc - 1, "Arrar Initialized");

	for (j = 1; j < argc - 1; j++) {
		key = n[j];	
		i = j - 1;
		while (i >= 0 && key < n[i]) {
			n[i + 1] = n[i];
			i--;
		}
		n[i + 1] = key;
		pt_arrar(n, argc - 1, "Soring ");
	}

	pt_arrar(n, argc - 1, "Sorted");
	
	return 0;
}
