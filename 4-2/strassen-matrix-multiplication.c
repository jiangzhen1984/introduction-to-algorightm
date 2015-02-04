

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
 * col index      0  1  2  3
 *            0  | 0  1  2  3|
 *            1  | 0  1  2  3|
 *            2  | 0  1  2  3|
 *            3  | 0  1  2  3|
 *
 * A11 = row 0 ~ 1  col 0 ~ 1
 * A12 = row 2 ~ 3  col 2 ~ 3
 * A21 = row 2 ~ 3  col 0 ~ 1
 * A22 = row 2 ~ 3  col 2 ~ 3
 *
 */
void cal_sub_matrix_index(struct Matrix  * m, 
	struct Matrix * a11, struct Matrix * a12, struct Matrix * a21, struct Matrix * a22)
{
	int rows, columns;
	rows = (m->end_row - m->start_row) / 2;
	columns = (m->end_column - m->start_column) / 2;

	// Initial A11 index
	a11->m = m->m;
	a11->start_row = m->start_row;
	a11->end_row = a11->start_row + rows;
	a11->start_column = m->start_column;
	a11->end_column = a11->start_column + columns;

	// Initial A12 index
	a12->m = m->m;
	a12->start_row = a11->start_row;
	a12->end_row = a11->end_row;
	a12->start_column = a11->end_column + 1;
	a12->end_column = a12->start_column + columns ;

	// Initial A21 index
	a21->m = m->m;
	a21->start_row = a11->end_row + 1;
	a21->end_row = a21->start_row + rows;
	a21->start_column = m->start_column;
	a21->end_column = a21->start_column + columns ;


	// Initial A22 index
	a22->m = m->m;
	a22->start_row = a21->start_row;
	a22->end_row = a21->end_row;
	a22->start_column = a12->start_column;
	a22->end_column = a12->end_column;
}


void matrix_add(struct Matrix * ma, struct Matrix * mb, struct Matrix * out)
{
	struct Matrix a11, a12, a21, a22;
	struct Matrix b11, b12, b21, b22;
	struct Matrix c11, c12, c21, c22;
	int row = ma->end_row - ma->start_row;
	int col = ma->end_column - ma->end_column;
	if (ma->start_row == ma->end_row && ma->start_column == ma->end_column) {
		out->m[out->start_row][out->start_column] = 
			ma->m[ma->start_row][ma->start_column] + mb->m[mb->start_row][mb->start_column];
	} else {
		cal_sub_matrix_index(ma, &a11, &a12, &a21, &a22);

		cal_sub_matrix_index(mb, &b11, &b12, &b21, &b22);

		cal_sub_matrix_index(out, &c11, &c12, &c21, &c22);


		matrix_add(&a11, &b11, &c11);
		matrix_add(&a12, &b12, &c12);
		matrix_add(&a21, &b21, &c21);
		matrix_add(&a22, &b22, &c22);
	}
}

void matrix_sub(struct Matrix * ma, struct Matrix * mb, struct Matrix * out)
{
	struct Matrix a11, a12, a21, a22;
	struct Matrix b11, b12, b21, b22;
	struct Matrix c11, c12, c21, c22;
	int row = ma->end_row - ma->start_row;
	int col = ma->end_column - ma->end_column;
	if (ma->start_row == ma->end_row && ma->start_column == ma->end_column) {
		out->m[out->start_row][out->start_column] = 
			ma->m[ma->start_row][ma->start_column] - mb->m[mb->start_row][mb->start_column];
	} else {
		cal_sub_matrix_index(ma, &a11, &a12, &a21, &a22);

		cal_sub_matrix_index(mb, &b11, &b12, &b21, &b22);

		cal_sub_matrix_index(out, &c11, &c12, &c21, &c22);


		matrix_sub(&a11, &b11, &c11);
		matrix_sub(&a12, &b12, &c12);
		matrix_sub(&a21, &b21, &c21);
		matrix_sub(&a22, &b22, &c22);
	}
}


/**
 *
 */
void square_matrix_multiply_recursive(struct Matrix * ma, struct Matrix * mb, struct Matrix * out)
{
	struct Matrix s[11];
	struct Matrix p[8];
	struct Matrix a11, a12, a21, a22;
	struct Matrix b11, b12, b21, b22;
	struct Matrix c11, c12, c21, c22;
	int rows = (ma->end_row - ma->start_row) / 2 + 1 ;
	int cols = (ma->end_column - ma->start_column ) / 2 + 1;
	int i;

	// Initialized array for matrix from s1 to s10
	for (i = 1; i < 11; i++) {
		s[i].start_row = 0;
		s[i].end_row = rows - 1;
		s[i].start_column = 0;
		s[i].end_column = cols - 1;
		s[i].m = malloc(sizeof(int) * rows * cols);
	}

	// Initialized array for matrix from s1 to s10
	for (i = 1; i < 8; i++) {
		p[i].start_row = 0;
		p[i].end_row = rows - 1;
		p[i].start_column = 0;
		p[i].end_column = cols - 1;
		p[i].m = malloc(sizeof(int) * rows * cols);
	}
	
	cal_sub_matrix_index(ma, &a11, &a12, &a21, &a22);

	cal_sub_matrix_index(mb, &b11, &b12, &b21, &b22);

	cal_sub_matrix_index(out, &c11, &c12, &c21, &c22);

	//calculate s1 = b12 - b22
	matrix_sub(&b12, &b22, &s[1]);

	//calculate s2 = a11 + a12
	matrix_add(&a11, &a12, &s[2]);


	//calculate s3 = a21 + a22
	matrix_add(&a21, &a22, &s[3]);

	//calculate s4 = b21 - b11 
	matrix_sub(&b21, &b11, &s[4]);

	//calculate s5 = a11 + a22
	matrix_add(&a11, &a22, &s[5]);

	//calculate s6 = b11 + b22
	matrix_add(&b11, &b22, &s[6]);

	//calculate s7 = a12 - a22
	matrix_sub(&a12, &a22, &s[7]);

	//calculate s8 = b21 + b22
	matrix_add(&b21, &b22, &s[8]);

	//calculate s9 = a11 - a21
	matrix_sub(&a11, &a21, &s[9]);

	//calculate s10 = b11 + b12
	matrix_add(&b11, &b12, &s[10]);

	//If matrix is 2*2, we can not recursive any more
	if (ma->end_row - ma->start_row == 1  && ma->end_column - ma->start_column == 1) {

		//calculate p1 = a11 * s1
		p[1].m[0][0] = a11.m[a11.start_row][a11.start_column] * s[1].m[0][0]; 

		//calculate p2 = s2  * b22
		p[2].m[0][0] = s[2].m[0][0] * b22.m[b22.start_row][b22.start_column];

		//calculate p3 = s3  * b11
		p[3].m[0][0] = s[3].m[0][0] * b11.m[b11.start_row][b11.start_column];

		//calculate p4 = a22 * s4
		p[4].m[0][0] =  a22.m[a22.start_row][a22.start_column] * s[4].m[0][0];

		//calculate p5 = s5  * s6
		p[5].m[0][0] =  s[5].m[0][0] * s[6].m[0][0];

		//calculate p6 = s7  * s8
		p[6].m[0][0] =  s[7].m[0][0] * s[8].m[0][0];

		//calculate p7 = s9  * s10
		p[7].m[0][0] =  s[9].m[0][0] * s[10].m[0][0];
		
	} else {
		//calculate p1 = a11 * s1
		square_matrix_multiply_recursive(&a11, s + 1, p + 1);

		//calculate p2 = s2  * b22
		square_matrix_multiply_recursive(&s[2], &b22, &p[2]);

		//calculate p3 = s3  * b11
		square_matrix_multiply_recursive(s + 3, &b11, &p[3]);

		//calculate p4 = a22 * s4
		square_matrix_multiply_recursive(&a22, &s[4], &p[4]);

		//calculate p5 = s5  * s6
		square_matrix_multiply_recursive(&s[5], &s[6], &p[5]);

		//calculate p6 = s7  * s8
		square_matrix_multiply_recursive(&s[7], &s[8], &p[6]);

		//calculate p7 = s9  * s10
		square_matrix_multiply_recursive(&s[9], &s[10], &p[7]);
	}

	// c11 = p5 + p4 - p2 + p6
	matrix_add(&p[5], &p[4], &c11);
	matrix_sub(&c11, &p[2], &c11);
	matrix_add(&c11, &p[6], &c11);
	
	// c12 = p1 + p2
	matrix_add(&p[1], &p[2], &c12);

	// c21 = p3 + p4
	matrix_add(&p[3], &p[4], &c21);

	// c22 = p5 + p1 - p3 - p7
	matrix_add(&p[5], &p[1], &c22);
	matrix_sub(&c22, &p[3], &c22);
	matrix_sub(&c22, &p[7], &c22);

	
	//==============release memeory
	for (i = 1; i < 11; i++) {
		free(s[i].m);
	}

	for (i = 1; i < 8; i++) {
		free(p[i].m);
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
