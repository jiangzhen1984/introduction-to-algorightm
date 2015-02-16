

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct array_queue {

	int * p_queue;
	int queue_size;
	int head;
	int tail;
};



int check_queue_full(struct array_queue * pqueue)
{
	return (pqueue->tail == pqueue->queue_size ? 0 : pqueue->tail + 1)  == pqueue->head;
}


int check_queue_empty(struct array_queue * pqueue)
{
	return pqueue->head == pqueue->tail;
}

int array_queue_enqueue(struct array_queue * pqueue, int key)
{
	int ret;
	ret = check_queue_full(pqueue);
	if(ret) {
		return -1;
	}

	pqueue->p_queue[pqueue->tail] = key;
	if (pqueue->tail == pqueue->queue_size) {
		pqueue->tail = 0;
	} else {
		pqueue->tail++;
	}
	return 0;
}


int array_queue_dequeue(struct array_queue * pqueue)
{
	int key;
	if (check_queue_empty(pqueue)) {
		return -1;
	}
	
	key = pqueue->p_queue[pqueue->head];

	if (pqueue->head == pqueue->queue_size) {
		pqueue->head = 0;
	} else {
		pqueue->head++;
	}
	return key;
}



int main(int argc, char ** argv)
{
	struct array_queue * pQ = NULL;
	int cmd;

	do {
		printf(" 1 : Initialize Queue \n");
		printf(" 2 : DeQueue \n");
		printf(" 3 : EnQueue \n");
		printf(" 4 : Destroy Queue \n");
		printf(" 0 : Exit \n");
		printf(" Please Input command:  ");
		scanf("%d", &cmd);

		switch(cmd) {
			case 0:
				break;
			case 1:
				if (pQ != NULL) {
					printf("   [WARNING] Queue is initialized, please destroy first\n");
					break;
				}
				int size = 0;
				printf("  Please input queue size:");
				scanf("%d", &size);
				if (size <= 0) {
					printf("   [WARNING] Incorrect queue Size\n");
				} else {
					pQ = (struct array_queue *) malloc(sizeof(struct array_queue));
					pQ->head =pQ->tail= 0;
					pQ->queue_size = size;
					pQ->p_queue = (int *) malloc(sizeof(int) * (size + 1));
				}
				break;
			case 2:
				if (pQ != NULL) {
					int key = array_queue_dequeue(pQ);
					if (key != -1) {
						printf("   [Get value of queue] %d\n", key);
					} else {
						printf("   [WARNING] Queue is empty \n");
					}
				} else {
					printf("   [WARNING] Queue is not initialized yet \n");
				}
				break;
			case 3:
				if (pQ != NULL) {
					int key;
					printf("  Please Input key:");
					scanf("%d", &key);
					if (key == -1) {
						printf("   [ERROR] -1 is key word, can not be value\n");
						break;
					}
					int ret = array_queue_enqueue(pQ, key);
					if (ret == -1) {
						printf("   [WARNING] Queuej is full \n");
					}
					
				} else {
					printf("   [WARNING] QUeue is not initialized yet \n");
				}
				break;
			case 4:
				if (pQ != NULL) {
					free(pQ->p_queue);
					free(pQ);
				}
				pQ = NULL;
				break;
		}

	} while (cmd != 0);

	if (pQ != NULL) {
		free(pQ->p_queue);
		free(pQ);
	}

	return 0;
}
