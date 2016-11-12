
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))



int cut_rod(int p[], int n)
{
    int q = 0;
    int i = 0;
    if (n == 0) {
        return q;
    }

    for (i = 1; i <= n; i++) {
        q = MAX(q, p[i] + cut_rod(p, n - i));
    }
    return q;
}


int main(int argc, char ** argv)
{
   int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
   int n = 0;
   int q = 0;
   printf("Please input rod length(1-10):");
   scanf("%d", &n);
   q = cut_rod(p, n);
   printf(" Max value %d\n", q);
   

   return 0;
}
