
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX(a, b) (a) > (b) ? (a) :(b)


int bottom_up_cut_rod(int p[], int n)
{
   int r[n];
   int i = 0;
   int j = 0;
   memset(r, 0, sizeof(r));
   for(i = 1; i <= n; i++) {
      int q = 0;
      for (j = 1; j <= i; j++) {
         q = MAX(q,  p[j] + r[i-j]);
      }
      r[i] = q;
   }
   return r[n];
}

int main(int argc, char ** argv)
{
   int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
   int n = 0;
   int q = 0;
   printf("Please input rod length(1-10):");
   scanf("%d", &n);
   q = bottom_up_cut_rod(p, n);
   printf(" Max value %d\n", q);
   

   return 0;
}
