
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void lcs(char x[], char y[], char t[][6], int c[][6]) {
     int lenx = strlen(x);
     int leny = strlen(y);
     int i  = 1;
     int j = 1;
     for (i = 0; i <= lenx; i++) {
         for (j = 0; j <= leny; j++) {
             t[i][j] = '0';
         }
     }
     printf("===%d  %d\n", lenx, leny);
     for (i = 0; i <= lenx; i++) {
         for (j = 0; j <= leny; j++) {
             if (x[i] == y[j]) {
                 c[i][j] = c[i-1][j-1] + 1;
                 t[i][j] = 's';
             } else if (c[i-1][j] >= c[i][j-1]) {
                 c[i][j] = c[i-1][j];
                 t[i][j] = 'u';
             } else { 
                 c[i][j] = c[i][j-1];
                 t[i][j] = 'l';
             }
         }
     }

     for (i = 0; i <= lenx; i++) {
         for (j = 0; j <= leny; j++) {
             printf(" %c", t[i][j]);
         }
         printf("\n");
     }
}


void print_lcs(char t[6][6],  int i, int j, char x[]) {
    if (i < 0 || j < 0) {
          return;
    }
    if (t[i][j] =='s') {
        print_lcs(t, i-1, j-1, x); 
        printf(" %c", x[i]);
    } else if(t[i][j] == 'u') {
      print_lcs(t, i-1, j, x); 
    } else {
      print_lcs(t, i, j-1, x); 
    }

}


int main(int argc, char ** argv)
{
   char x[] ={'A','B','C','C','B', '\0'};
   char y[] ={'A','C','C','D','B', '\0'};
   char t[6][6];
   int c[6][6];
   lcs(x, y, t, c);
   print_lcs(t, 5, 5, x);
   printf("\n");
   return 0;
}

