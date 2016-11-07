
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define VERTIEX_NUMS (5)


struct Adj {
    int v;
    struct Adj * next;
};


struct Adj * G[VERTIEX_NUMS];


void add_edge(int v1, int v2)
{ if (v1 >= VERTIEX_NUMS || v2 >= VERTIEX_NUMS) {
        return;
    }

    struct Adj * pNewAdj = (struct Adj *) malloc(sizeof(struct Adj));
    memset(pNewAdj, 0, sizeof(struct Adj));
    pNewAdj->v = v2;
    struct Adj * pa = G[v1];

    if (pa == NULL)
    {
          G[v1] = pNewAdj;
    } else {

    while (pa->next != NULL) {
          pa = pa->next;
    }
    pa->next = pNewAdj;
    }
}


struct T_Node {
    int v;
    struct T_Node * next;
};


struct T_Node * pH;
struct T_Node * pT;

void n_bfs(int va[],  int v)
{
    while (pH != NULL) {
         if (va[pH->v] == 0) {
		 struct Adj * pa = G[pH->v];
		 while (pa != NULL) {
		     struct T_Node * pn = (struct T_Node *) malloc(sizeof(struct T_Node));
		     pn->v = pa->v;
		     pT->next = pn;
		     pT= pT->next;
		     pa = pa->next;
		     
		 }
             printf("%d ", pH->v);
         }
         va[pH->v] = 1;
         pH = pH->next;
    }

}

void bfs(int start)
{
   int va[VERTIEX_NUMS] = {0, 0,0,0,0};
   pH = (struct T_Node *) malloc(sizeof(struct T_Node));
   memset(pH, 0, sizeof(struct T_Node));
   pH->v = start;
   pT = pH;
   n_bfs(va, start); 
   printf("\n");
}

void print_g()
{
   int i = 0;
   for (i = 0; i < VERTIEX_NUMS; i++) {
      struct Adj * p = G[i];
      while (p != NULL) {
         printf(" %d -> ", p->v);
         p = p->next;
      }
      printf("\n");
   }
}

int main (int argc, char ** argv)
{

    add_edge(0, 1);
    add_edge(1, 3);
    add_edge(2, 3);
    add_edge(2, 0);
    add_edge(3, 4);
    add_edge(4, 1);
    print_g();
    bfs(2);
    return 0;
}
