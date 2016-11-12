
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define MIN(a, b) (a) < (b) ? (a) : (b)


int coin(int coins[], int n) {
   int q = 0;
   int i = 1;
   int j = 0;
   int len = sizeof(coins)/ 4;
   int count = 0;
   while (n > 0) {
      int q = 0;
      for (j = 0; j <= len; j ++) {
          if (n >= coins[j] && coins[j] > q) {
             q = coins[j];
          }
      }
      
      printf("===%d\n", q);
      count += 1;
      n -=q;
   }
   return count;
}


int main(int argc, char ** argv[])
{
   int  coins[] = {1, 3, 5};
   int count = coin(coins, 18);
   printf("MIN count:%d\n", count);
   return 0;
}
