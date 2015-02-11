

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct bucket {
	float f;
	struct bucket * next;
};



void print_arr(float f[], int len, char * str)
{
	int i = 0;
	printf("%s [", str);
	for (i = 0; i < len; i++) {
		printf("%.2f,", f[i]);
	}
	printf("]\n", str);
}


void bucket_sort(float f[], int len)
{
	int n = 10;
	int i = 0, j = 0;
	struct bucket  * b[n];

	for(i = 0; i < n; i++) {
		b[i] = NULL;
	}

	for(i = 0; i < len; i++) {
		int x = f[i] * n;

		// Use Inserting sort to sort 
		struct bucket * new = NULL;
		struct bucket * pb = b[x];
		struct bucket * head = b[x];
		struct bucket * pre = b[x];
		if (pb == NULL) {
			new = (struct bucket *)malloc(sizeof(struct bucket));
			b[x] = new;
			new->f = f[i];
			new->next =  NULL;
		} else {
			while (pb != NULL) {
				if (pb->f > f[i]) {
					break;
				}
				if (pb != pre) {
					pre = pre->next;
				}
				pb = pb->next;
			}

			new = (struct bucket *)malloc(sizeof(struct bucket));
			new->f = f[i];
			if (pb == pre) {
				head = new;
				new->next = pb;
				b[x] = head;
			} else {
				pre->next = new;
				new->next = pb;
			}
		}
	}

	//connect all bucket 
	for (i = 0, j = 0; i < n; i++) {
		struct bucket * head = b[i];
		while (head != NULL) {
			struct bucket * tmp;
			f[j++] = head->f;
			tmp = head;
			head = head->next;
			free(tmp);
		}
	}
}


int main(int argc, char ** argv)
{
	int len = argc - 1;
	float f[len];
	int i = 0;
	++ argv;
	for (i = 0; i < argc && *argv != NULL; i++, argv++) {
		f[i] = atof(*argv);	
	}
	

	print_arr(f, len, "Array Initialized");
	bucket_sort(f, len);
	print_arr(f, len, "Array Sorted");
	return 0;
}
