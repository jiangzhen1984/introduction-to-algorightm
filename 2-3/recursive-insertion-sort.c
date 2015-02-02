

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


void insertion_sort(int n[], int len, int index)
{
	int i = index - 1;
	int key = n[index];
	if (index < len) {
		while ( i >=0 && n[i] >= key) {
			n[i + 1] = n[i];	
			i--;
		}
		n[i + 1] = key;
		insertion_sort(n, len, index + 1);
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

	insertion_sort(n, argc - 1, 1);
	pt_arrar(n, argc - 1 , "Arrar Sorted");
	return 0;
}
