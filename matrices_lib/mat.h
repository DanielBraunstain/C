#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>

#define TOLERANCE 0.001F


typedef struct matrix_t matrix_t;


matrix_t* MatCreate(size_t n_rows, size_t n_cols, const float* data);


void MatDestroy(matrix_t* mat);

/** 
*   MatSubmatrix
*   ------------
*   Creates a new submatrix by removing a row and col from a given matrix.
*
*   Params
*   ------
*   mat - a pointer to the matrix.
*   row - the row which won't be included in the submatrix.
*	  col - the column which won't be included in the submatrix.
*
*   Return
*   ------
*   A pointer to the submatrix. NULL on failure.
*/
matrix_t* MatSubmatrix(const matrix_t* mat, size_t row, size_t col);

/** 
*   MatI
*   ----
*   Creates an identity matrix of size n * n.
*
*   Params
*   ------
*   n - size of created identity matrix.
*
*   Return
*   ------
*   A pointer to the created identity matrix. NULL on failure.
*/
matrix_t* MatI(size_t n);
/** 
*   MatAdd
*   ------
*   Return
*   ------
*   A pointer to the result matrix.
*/

matrix_t* MatAdd(const matrix_t* mat1, const matrix_t* mat2);

/** 
*   MatMult
*   ------
*   Return
*   ------
*   A pointer to the result matrix.
*   Returns NULL on failure.
*/
matrix_t* MatMult(const matrix_t* mat1, const matrix_t* mat2);

/** 
*   MatScalarMult
*   ------
*   Return
*   ------
*   A pointer to the newly created matrix that holds the result.
*   NULL on failure.
*/
matrix_t* MatScalarMult(matrix_t* mat, float scalar);

/** 
*   MatCompare
*   ------
*   Return
*   ------
*   0 if the matrices are equal, nonzero otherwise.
*/
int MatCompare(const matrix_t* mat1, const matrix_t* mat2);

/**   
 *  MatTranspose
 *  -------
 *  Return
 *  ------
 *  Transposed matrix. NULL on failure.
 */
matrix_t* MatTranspose(const matrix_t* mat);

/** 
*   MatTrace
*   ------
*   Return
*   ------
*   Sum of diagnoal elements.
*/
float MatTrace(const matrix_t* mat);

/** 
*   MatInvert
*   ------
*   Return
*   ------
*   pointer to inverted matrix. NULL on failure.
*   Undefined behavior if the matrix is not square.
*/
matrix_t* MatInvert(const matrix_t* mat);

/** 
*   MatDet
*   ------
*   Return
*   ------
*   float - value of matrices determinant.
*   Undefined behavior if the matrix is not square.
*/
float MatDet(const matrix_t* mat);

/** 
*   MatNorm
*   ------
*   Return
*   ------
*   The  frobinius norm (l2) of the matrix.
*/
float MatNorm(const matrix_t* mat);

/** 
*   MatShape
*   ------
*   Return
*   ------
*   dims[0] will be the number of rows.
*   dims[1] will be the number of columns.
*
*/
void MatShape(const matrix_t* mat, size_t dims[2]);

/** 
*   MatGetElem
*   ------
*   Return
*   ------
*   The value at the at mat[row][col].
*/
float MatGetElem(const matrix_t* mat, size_t row, size_t col);



#endif
