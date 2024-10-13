#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>
#define TOLERANCE 0.001F



typedef struct matrix_t matrix_t;



/** 
*   MatrixCreate
*   ------------
*   Creates a new matrix according to the user specifications.
*
*   Params
*   ------
*   rows - number of rows in the matrix.
*	cols - number of columns in the matrix.
*	data - an array of the elements that will be inserted into the matrix.
*   if data is NULL, a zero matrix will be created.
*
*   Return
*   ------
*   A pointer to the new matrix. NULL on failure.
*/
matrix_t* MatCreate(size_t n_rows, size_t n_cols, const float* data);


/** 
*   MatDestroy
*   ----------
*   Clears a matrix from memory.
*   
*   Params
*   ------
*   mat - a pointer to the matrix.
*
*/
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
*	cols - the column which won't be included in the submatrix.
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
*   Adds two matrices.
*
*   Params
*   ------
*   mat1 - the 1st matrix of the calculation.
*	mat2 - the 2nd matrix of the calculation.
*
*   Return
*   ------
*   A pointer to the result matrix.
*   Returns NULL if the matrices dimensions don't match.
*/
matrix_t* MatAdd(const matrix_t* mat1, const matrix_t* mat2);

/** 
*   MatMult
*   -------
*   Multiplies two matrices.
*
*   Params
*   ------
*   mat1 - the 1st matrix of the calculation.
*	mat2 - the 2nd matrix of the calculation.
*
*   Return
*   ------
*   A pointer to the result matrix.
*   Returns NULL on failure.
*/
matrix_t* MatMult(const matrix_t* mat1, const matrix_t* mat2);

/** 
*   MatScalarMult
*   -------------
*   multiplies a matrix by scalar.
*
*   Params
*   ------
*   mat - a pointer to the matrix.
*	scalar - the scalar.
*
*   Return
*   ------
*   A pointer to the newly created matrix that holds the result.
*   NULL on failure.
*/
matrix_t* MatScalarMult(matrix_t* mat, float scalar);

/** 
*   MatMult
*   -------
*   Compares mat1 to mat2.
*
*   Params
*   ------
*   mat1 - the 1st matrix of the comparison
*	mat1 - the 2nd matrix of the comparison
*
*   Return
*   ------
*   0 if the matrices are equal, nonzero otherwise.
*/
int MatCompare(const matrix_t* mat1, const matrix_t* mat2);

/**   
 *  MatTranspose
 *  ------------
 *  flips a matrix over its diagonal
 * 
 *  Params
 *  ------
 *  mat - a pointer to the matrix.
 * 
 *  Return
 *  ------
 *  Transposed matrix. NULL on failure.
 */
matrix_t* MatTranspose(const matrix_t* mat);

/** 
*   MatTrace
*   -------
*   Calculates the trace of the given matrix.
*
*   Params
*   ------
*   mat - a pointer to the matrix.
*
*   Return
*   ------
*   Trace of given matrix.
*/
float MatTrace(const matrix_t* mat);

/** 
*   MatInvert
*   ---------
*   returns the inverse of a matrix.
*
*   Params
*   ------
*   mat - a pointer to the matrix.
*
*   Return
*   ------
*   pointer to inverted matrix. NULL on failure.
*   Undefined behavior if the matrix is not square.
*/
matrix_t* MatInvert(const matrix_t* mat);

/** 
*   MatDet
*   ------
*   calculates the determinant of given matrix.
*
*   Params
*   ------
*   mat - a pointer to the matrix.
*
*   Return
*   ------
*   float - value of matrices determinant.
*   Undefined behavior if the matrix is not square.
*/
float MatDet(const matrix_t* mat);

/** 
*   MatNorm
*   --------
*   calculates the frobinius norm (l2) of the matrix.
*
*   Params
*   ------
*   mat - a pointer to the matrix.
* 
*   Return
*   ------
*   The norm of the matrix.
*/
float MatNorm(const matrix_t* mat);

/** 
*   MatShape
*   --------
*   Get the shape of a matrix.
*
*   Params
*   ------
*   mat - a pointer to the matrix.
*   dims - a buffer where the result will be stored.
*   dims[0] will be the number of rows.
*   dims[1] will be the number of columns.
*
*/
void MatShape(const matrix_t* mat, size_t dims[2]);

/** 
*   MatGetElem
*   ----------
*   Get a value from a matrix.
*
*   Params
*   ------
*   mat - a pointer to the matrix.
*   row - the value's row.
*   col - the value's column.
*
*   Return
*   ------
*   The value at the intersection of the row and column.
*/
float MatGetElem(const matrix_t* mat, size_t row, size_t col);



#endif
