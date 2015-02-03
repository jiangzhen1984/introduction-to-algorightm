

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void pt_arrar(int n[], int len, char * str) {
	int i = 0;

	printf("%s [", str);
	for(i = 0; i < len; i++) {
		printf("%d, ", n[i]);
	}
	printf("]\n");
}


void find_maximum_subarray_corss(int n[], int low, int mid, int high, int * out_low, int * out_high, int * out_sum)
{
	int left_sum = 0xFFFFFFFF, right_sum = 0xFFFFFFFF, sum = 0;
	int i;
	for (i = mid, sum = 0; i >= low; i--) {
		sum += n[i];
		if (sum > left_sum) {
			left_sum = sum;
			*out_low = i;
		}
	}

	for (i = mid  + 1, sum = 0; i <= high; i++) {
		sum += n[i];
		if (sum > right_sum) {
			right_sum = sum;
			*out_high = i;
		}
	}

	*out_sum = left_sum + right_sum;
}

void find_maximum_subarray(int n[], int low, int high, int * out_low, int * out_high, int * out_sum)
{
	int left_low,left_high,left_sum;
	int right_low,right_high,right_sum;
	int cross_low, cross_high, cross_sum;

	int mid = (low + high) / 2;
	if (low == high) {
		*out_low = low;
		*out_high = high;
		*out_sum = n[low];
	} else {
		find_maximum_subarray(n, low, mid, &left_low, &left_high, &left_sum);
		find_maximum_subarray(n, mid + 1, high, &right_low, &right_high, &right_sum);
		find_maximum_subarray_corss(n, low, mid, high, &cross_low,  &cross_high, &cross_sum);
		if (left_sum > right_sum && left_sum > cross_sum) {
			*out_low = left_low;
			*out_high = left_high;
			*out_sum = left_sum;
		} else if (right_sum > left_sum && right_sum > cross_sum) {
			*out_low = right_low;
			*out_high = right_high;
			*out_sum = right_sum;
		} else {
			*out_low = cross_low;
			*out_high = cross_high;
			*out_sum = cross_sum;
		}
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

	pt_arrar(n, argc - 1, "Initialized");

	int low, high, sum;
	find_maximum_subarray(n, 0, argc - 2, &low, &high, &sum);
	printf("    ====>[low-index %d, high-index %d, sum %d]\n", low, high, sum);
	pt_arrar(n+low, (high - low + 1), " Maximum:");

	return 0;
}
