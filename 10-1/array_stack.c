

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct array_stack {

	int * p_stack;
	int stack_size;
	int top;
};



int check_stack_full(struct array_stack * pstack)
{
	return pstack->top == pstack->stack_size;
}


int check_stack_empty(struct array_stack * pstack)
{
	return pstack == NULL || pstack->top == 0;
}

int array_stack_push(struct array_stack * pstack, int key)
{
	int ret;
	ret = check_stack_full(pstack);
	if(ret) {
		return -1;
	}

	pstack->p_stack[++pstack->top] = key;
	return 0;
}


int array_stack_pop(struct array_stack * pstack)
{
	if (check_stack_empty(pstack)) {
		return -1;
	}
	
	return pstack->p_stack[pstack->top--];
	
}



int main(int argc, char ** argv)
{
	struct array_stack * pStack = NULL;
	int cmd;

	do {
		printf(" 1 : Initialize Stack \n");
		printf(" 2 : Pop Stack \n");
		printf(" 3 : Push Stack \n");
		printf(" 4 : Destroy Stack \n");
		printf(" 0 : Exit \n");
		printf(" Please Input command:  ");
		scanf("%d", &cmd);

		switch(cmd) {
			case 0:
				break;
			case 1:
				if (pStack != NULL) {
					printf("   [WARNING] Stacked is initialized, please destroy first\n");
					break;
				}
				int size = 0;
				printf("  Please input stack size:");
				scanf("%d", &size);
				if (size <= 0) {
					printf("   [WARNING] Incorrect Stack Size\n");
				} else {
					pStack = (struct array_stack *) malloc(sizeof(struct array_stack));
					pStack->top = 0;
					pStack->stack_size = size;
					pStack->p_stack = (int *) malloc(sizeof(int) * (size + 1));
				}
				break;
			case 2:
				if (pStack != NULL) {
					int key = array_stack_pop(pStack);
					if (key != -1) {
						printf("   [Get value of stack] %d\n", key);
					} else {
						printf("   [WARNING] Stacke is empty \n");
					}
				} else {
					printf("   [WARNING] Stack is not initialized yet \n");
				}
				break;
			case 3:
				if (pStack != NULL) {
					int key;
					printf("  Please Input key:");
					scanf("%d", &key);
					if (key == -1) {
						printf("   [ERROR] -1 is key word, can not be value\n");
						break;
					}
					int ret = array_stack_push(pStack, key);
					if (ret == -1) {
						printf("   [WARNING] Stacke is full \n");
					}
					
				} else {
					printf("   [WARNING] Stack is not initialized yet \n");
				}
				break;
			case 4:
				if (pStack != NULL) {
					free(pStack->p_stack);
					free(pStack);
				}
				pStack = NULL;
				break;
		}

	} while (cmd != 0);

	if (pStack != NULL) {
		free(pStack->p_stack);
		free(pStack);
	}

	return 0;
}
