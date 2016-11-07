
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


void n_dfs(int va[],  int v)
{
    va[v] = 1;
    printf("%d ", v);
    struct Adj * pa = G[v];
    while (pa != NULL) {
         if (va[pa->v] == 0) {
             n_dfs(va, pa->v);
         }
         pa = pa->next;
    }
}

void dfs(int start)
{
   int va[VERTIEX_NUMS] = {0, 0,0,0,0};
   n_dfs(va, start); 
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
    add_edge(3, 4);
    print_g();
    dfs(2);
    return 0;
}
