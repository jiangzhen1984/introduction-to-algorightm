

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct is_node {
	int i;
	struct is_node * next;
};


void print_arr(struct is_node * head)
{
	struct is_node * thead = head;
	printf("[");
	while (thead != NULL) {
		printf("%d,", thead->i);
		thead = thead->next;
	}
	printf("]\n");
}

int main(int argc, char ** argv)
{
	int i,j;
	struct is_node * head = NULL;
	struct is_node * tmp = NULL;
	struct is_node * thead = NULL;
	struct is_node * newHead = NULL;
	++argv;
	for (i = 1; i <= argc && argv != NULL && *argv != NULL; ++argv,i++) {
		if (head == NULL) {
			head = malloc(sizeof(struct is_node));	
			head->i = atoi(*argv);
			thead = head;
		} else {
			tmp = malloc(sizeof(struct is_node));
		        tmp->i = atoi(*argv);	
			thead->next = tmp;
			thead = thead -> next;
		}
	}

	if (head == NULL || head->next == NULL) {
		printf("[error] only one element in arrary\n");
		printf("[Usage] ./insert-sort-list   3  54  1 4 5 6\n");
		return 0;
	}

	print_arr(head);

	// do sort
	struct is_node * sorted_current;
	struct is_node * sorted_pre;
	struct is_node * current;
	struct is_node * sorted_tail;
	current = head->next;
	sorted_tail = head;
	while (current != NULL) {
		sorted_current = head;
		sorted_pre = sorted_current;
		while (sorted_current != NULL && sorted_current != current && sorted_current->i <=current-> i) {
			if (sorted_current != sorted_pre) {
				sorted_pre = sorted_pre->next;
			}
			sorted_current = sorted_current->next;
		}
		struct is_node * hn = current->next;

		if (sorted_current->i > current->i) {
			sorted_tail->next = hn;
			if (sorted_current == sorted_pre) {
				head = current;
				current->next = sorted_current;
			} else {
				sorted_pre->next = current;
				current->next = sorted_current;
			}
			
		} else {
			sorted_tail = current;
		}
		
		

		current = hn;	
		print_arr(head);
	}
	print_arr(head);
	
	
	while(head != NULL) {
		struct is_node * no = head;
		free(no);
		head = head->next;
	}

	return 0;
}


