

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) (a) > (b) ? (b) : (a)


int coin(int coins[], int n) {
   int i = 2;
   int len = sizeof(coins) / 4;
   int j = 0;
   int r[n + 1];
   memset(r, 0, sizeof(r));
   for (i = 1; i <= n; i++) {
        int q = 1000;
        for (j = 0; j <= len; j++) {
            if (i >= coins[j]) {
                q = MIN(q, r[i - coins[j]] + 1);
            }
        }
        printf("n(%d) : %d\n", i, q);
        r[i] = q;
   }

   return r[n]; 
   
}


int main(int argc, char ** argv)
{
    int coins[]={1, 3, 5};
    int n = 0;
    scanf("%d", &n);
    int count = coin(coins, n);
    printf("%d\n", count);
}
