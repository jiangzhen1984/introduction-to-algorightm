
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#define COL 4


struct Matrix {

	int start_row;
	int start_column;
	int end_row;
	int end_column;
	int (*m)[COL];
};


#if COL == 2

int a[][COL] = 
	{
		{1, 2},
		{5, 6},
	};

int b[][COL] = 
	{
		{0, 2},
		{5, 6},
	};

int c[][COL] = 
	{
		{0, 0},
		{0, 0},
	};

#elif COL == 4
int a[][COL] = 
	{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{1, 2, 3, 4},
		{1, 2, 3, 4},
	};

int b[][COL] = 
	{
		{0, 2, 3, 4},
		{5, 6, 7, 8},
		{8, 7, 3, 4},
		{4, 1, 3, 4},
	};

int c[][COL] = 
	{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	};

#endif



void matrix_pt(struct Matrix * mat, char * str)
{
	int i,j;

	printf("   %s:\n", str);
	for(i = mat->start_row; i <= mat->end_row; i++) {
		for (j = mat->start_column; j <= mat->end_column; j++) {
			if (j == mat->start_column ) {
				printf(" | ");
			}
			printf(" %5d ", mat->m[i][j]);
			if (j == mat->end_column) {
				printf(" | ");
			}
		}
		printf("\n");
	}
	
}

/**
 *  Matrix C  = Matrix A * Matrix B:
 *  C11 = A11 * B11 + A12 * B21
 *  C12 = A11 * B12 + A12 * B22
 *  C21 = A21 * B11 + A22 * B21
 *  C22 = A21 * B12 + A22 * B22
 *
 */
void square_matrix_multiply_recursive(struct Matrix * ma, struct Matrix * mb, struct Matrix * out)
{
	struct Matrix m;
	struct Matrix a11,a12,a21,a22,b11,b12,b21,b22;
	struct Matrix c11, c12, c21, c22;
	int ma_rows, ma_columns, mb_rows, mb_columns, out_rows, out_columns;
	ma_rows = (ma->end_row - ma->start_row) / 2;
	mb_rows = (mb->end_row - mb->start_row) / 2;
	out_rows = (out->end_row - out->start_row) / 2;

	ma_columns = (ma->end_column - ma->start_column) / 2;
	mb_columns = (mb->end_column - mb->start_column) / 2;
	out_columns = (out->end_column - out->start_column) / 2;
	

	int r,col;
	r = out->start_row;
	col = out->start_column;
	if (ma->end_row == ma->start_row) {
		out->m[r][col] += (ma->m[ma->start_row][ma->start_column] * (mb->m[mb->start_row][mb->start_column]));
	} else {

		//===================calculate C11 =========================
		// Initial C11 index
		c11.start_row = out->start_row;
		c11.end_row = c11.start_row  + out_rows;
		c11.start_column = out ->start_column;
		c11.end_column = c11.start_column + out_columns;
		c11.m = out->m;
		
		// Initial A11 index
		a11.m = ma->m;
		a11.start_row = ma->start_row;
		a11.end_row = a11.start_row + ma_rows;
		a11.start_column = ma->start_column;
		a11.end_column = a11.start_column + ma_columns;

		// Initial B11 index
		b11.m = mb->m;
		b11.start_row = mb->start_row;
		b11.end_row = b11.start_row + mb_rows;
		b11.start_column = mb->start_column;
		b11.end_column = b11.start_column + mb_columns;

		square_matrix_multiply_recursive(&a11, &b11, &c11);
	
		// Initial A11 index
		a12.m = ma->m;
		a12.start_row = a11.start_row;
		a12.end_row = a11.end_row;
		a12.start_column = a11.end_column + 1;
		a12.end_column = a12.start_column + ma_columns ;

		// Initial B11 index
		b21.m = mb->m;
		b21.start_row = b11.end_row + 1;
		b21.end_row = b21.start_row + mb_rows;
		b21.start_column = b11.start_column;
		b21.end_column = b11.end_column; 

		square_matrix_multiply_recursive(&a12, &b21, &c11);


		//===================calculate C12 =========================
		// Initial C12 index
		c12.start_row = c11.start_row;
		c12.end_row = c11.end_row ;
		c12.start_column = c11.end_column + 1;
		c12.end_column = c12.start_column + out_columns;
		c12.m = out->m;

		// Initial B12 index
		b12.m = mb->m;
		b12.start_row = b11.start_row;
		b12.end_row = b11.end_row;
		b12.start_column = b11.end_column + 1;
		b12.end_column = b12.start_column + mb_columns;


		square_matrix_multiply_recursive(&a11, &b12, &c12);

		// Initial B22 index
		b22.m = mb->m;
		b22.start_row = b21.start_row;
		b22.end_row = b21.end_row;
		b22.start_column = b12.start_column ;
		b22.end_column = b12.end_column;

		square_matrix_multiply_recursive(&a12, &b22, &c12);

		//===================calculate C21 =========================
		// Initial C12 index
		c21.start_row = c11.end_row + 1 ;
		c21.end_row = c21.start_row + out_rows; 
		c21.start_column = c11.start_column;
		c21.end_column = c11.end_column;
		c21.m = out->m;

		// Initial A21 index
		a21.m = ma->m;
		a21.start_row = a11.end_row + 1;
		a21.end_row = a21.start_row + ma_rows;
		a21.start_column = ma->start_column;
		a21.end_column = a21.start_column + ma_columns ;

		square_matrix_multiply_recursive(&a21, &b11, &c21);

		// Initial A22 index
		a22.m = ma->m;
		a22.start_row = a21.start_row;
		a22.end_row = a21.end_row;
		a22.start_column = a12.start_column;
		a22.end_column = a12.end_column;

		square_matrix_multiply_recursive(&a22, &b21, &c21);

		//===================calculate C22 =========================
		// Initial C22 index
		c22.start_row = c21.start_row;
		c22.end_row = c21.end_row; 
		c22.start_column = c12.start_column;
		c22.end_column = c12.end_column;
		c22.m = out->m;

		square_matrix_multiply_recursive(&a21, &b12, &c22);


		square_matrix_multiply_recursive(&a22, &b22, &c22);
	}
}



int main(int argc, char ** argv) {
	int i, j;


	struct Matrix ma;
	ma.start_row = 0;
	ma.start_column = 0;
	ma.end_row = COL -1 ;
	ma.end_column = COL -1 ;
	ma.m = a;

	struct Matrix mb;
	mb.start_row = 0;
	mb.start_column = 0;
	mb.end_row = COL -1 ;
	mb.end_column = COL -1 ;
	mb.m = b;

	struct Matrix mc;
	mc.start_row = 0;
	mc.start_column = 0;
	mc.end_row = COL -1 ;
	mc.end_column = COL -1 ;
	mc.m = c;

	matrix_pt(&ma, "A");
	matrix_pt(&mb, "B");
	square_matrix_multiply_recursive(&ma, &mb, &mc);


	matrix_pt(&mc, "C");
	
	return 0;
}
