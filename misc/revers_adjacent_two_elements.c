

#include <stdlib.h>
#include <stdio.h>


struct link_node {
      int v;
      struct link_node * next;
};



static struct link_node * head = NULL;



void print_link(struct link_node * head) {
   struct link_node * tmp = head;
   while (tmp != NULL) {
       printf(" %d -> ", tmp->v);
       tmp = tmp->next;
   }
   printf("\n");
}


void reverse_singal_link(struct link_node * head)
{

    struct link_node * idx;
    struct link_node * idx_next;
    struct link_node * new_head = NULL;
    struct link_node * new_tail = NULL;
    struct link_node * tmp = NULL;


    if (head == NULL || head->next == NULL) {
        return;
    }

    idx = head;

    while (idx != NULL) {
       if (idx->next == NULL) {
           if (new_head == NULL) {
              new_head = idx;
              break;
           } else {
              tmp = idx->next;
              new_tail->next = idx; 
              new_tail = new_tail->next;
              new_tail->next = NULL;
           }
       } else {
            tmp = idx->next->next;
            if (new_head == NULL) {
                new_head = idx->next;
                new_tail = idx;
                new_head->next = new_tail;
            } else {
               new_tail->next = idx->next;
               new_tail = new_tail->next;
               new_tail->next = idx; 
               new_tail = new_tail->next;
               new_tail->next = NULL;
            }
       }

       idx = tmp;
    }

    printf("====aaa\n");
    print_link(new_head);
 
}


int main(int argc, char ** argv) {

    struct link_node * head = NULL;  
    struct link_node * tail = NULL;  
    struct link_node * tmp = NULL;  
    int i = 0, len = 9;
    for (i = 0; i < len; i++) {
       tmp = (struct link_node *)malloc(sizeof(struct link_node)); 
       memset(tmp, 0, sizeof(struct link_node));
       tmp->v = i + 1; 
       if (head == NULL) {
          head = tmp;
          tail = tmp;
       } 
       tail->next = tmp;
       tail = tmp;
    }
    print_link(head);
    reverse_singal_link(head);
    return 0;
}
