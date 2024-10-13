#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mat.h"

struct matrix_t
{
    size_t n_rows;
    size_t n_cols;
    float* data;
};






float MatGetElem(const matrix_t* mat, size_t row, size_t col) 
{
    if (row >= mat->n_rows || col >= mat->n_cols) 
    {
        return 0.0;
    }
    return mat->data[row * mat->n_cols + col];
}

matrix_t* MatCreate(size_t n_rows, size_t n_cols, const float* data) 
{
    matrix_t* mat = (matrix_t*)malloc(sizeof(matrix_t));
    
    if (!mat) 
    {
        return NULL;
    }
    mat->n_rows = n_rows;
    mat->n_cols = n_cols;
    mat->data = (float*)malloc(n_rows * n_cols * sizeof(float));
    
    if (!mat->data) 
    {
        free(mat);
        return NULL;
    }

    if (data) 
    {
        memcpy(mat->data, data, n_rows * n_cols * sizeof(float));
    } 
    else 
    {
        memset(mat->data, 0, n_rows * n_cols * sizeof(float));
    }

    return mat;
}

void MatDestroy(matrix_t* mat) 
{
    free(mat->data);
    free(mat);
}

static void MatSetElem(matrix_t* mat, size_t row, size_t col, float value) 
{
    if (row < mat->n_rows && col < mat->n_cols) 
    {
        mat->data[row * mat->n_cols + col] = value;
    }
}


static void SwapRows(matrix_t* mat, size_t row1, size_t row2) 
{
    size_t j;
    for (j = 0; j < mat->n_cols; j++) 
    {
        float tmp = MatGetElem(mat, row1, j);
        MatSetElem(mat, row1, j, MatGetElem(mat, row2, j));
        MatSetElem(mat, row2, j, tmp);
    }
}


static void ScaleRow(matrix_t* mat, size_t row, float factor) 
{
    size_t j;
    for (j = 0; j < mat->n_cols; j++) 
    {
        MatSetElem(mat, row, j, MatGetElem(mat, row, j) * factor);
    }
}


static void SubtractRows(matrix_t* mat, size_t target_row, size_t source_row, float factor) 
{
    size_t j;
    for (j = 0; j < mat->n_cols; j++) 
    {
        MatSetElem(mat, target_row, j, MatGetElem(mat, target_row, j) - factor * MatGetElem(mat, source_row, j));
    }
}



matrix_t* MatAdd(const matrix_t* mat1, const matrix_t* mat2) 
{
    matrix_t* result;
    size_t i = 0;
    size_t j = 0;
    if (mat1->n_rows != mat2->n_rows || mat1->n_cols != mat2->n_cols) 
    {
        return NULL;
    }

    result = MatCreate(mat1->n_rows, mat1->n_cols, NULL);
    if (!result) 
    {
        return NULL;
    }

    for (i = 0; i < mat1->n_rows; i++) 
    {
        for (j = 0; j < mat1->n_cols; j++) 
        {
            MatSetElem(result, i, j, MatGetElem(mat1, i, j) + MatGetElem(mat2, i, j));
        }
    }

    return result;
}

matrix_t* MatScalarMult(matrix_t* mat, float scalar)
{
    matrix_t* result = MatCreate(mat->n_rows, mat->n_cols, NULL);
    size_t i = 0;
    size_t j = 0;
    if (!result) 
    {
        return NULL;
    }
    
    for (i = 0; i < mat->n_rows; i++) 
    {
        for (j = 0; j < mat->n_cols; j++) 
        {
            MatSetElem(result, i, j, scalar * MatGetElem(mat, i, j));
        }
    }

    return result;
}

int MatCompare(const matrix_t* mat1, const matrix_t* mat2)
{
	size_t i = 0;
	size_t j = 0;
    if (mat1->n_rows != mat2->n_rows || mat1->n_cols != mat2->n_cols) 
    {
        return 0;
    }
    
    for (i = 0; i < mat1->n_rows; i++) 
    {
        for (j = 0; j < mat1->n_cols; j++) 
        {
            if(fabs(MatGetElem(mat1, i, j) - MatGetElem(mat2, i, j)) > TOLERANCE)
            {
                return 0;
            }
        }
    }
    
    return 1;  
}


matrix_t* MatI(size_t n) 
{
	size_t i = 0;
    matrix_t* mat = MatCreate(n, n, NULL);

    for (i = 0; i < n; i++) 
    {
        MatSetElem(mat, i, i, 1.0);
    }

    return mat;
}

void MatShape(const matrix_t* mat, size_t dims[2]) 
{ 
    dims[0] = mat->n_rows;
    dims[1] = mat->n_cols;
}

matrix_t* MatTranspose(const matrix_t* mat) 
{
    matrix_t* result = MatCreate(mat->n_cols, mat->n_rows, NULL);
    size_t i = 0;
    size_t j = 0;
    if (!result) 
    {
        return NULL;
    }

    for (i = 0; i < mat->n_rows; i++) 
    {
        for (j = 0; j < mat->n_cols; j++) 
        {
            MatSetElem(result, j, i, MatGetElem(mat, i, j));
        }
    }

    return result;
}

matrix_t* MatMult(const matrix_t* mat1, const matrix_t* mat2) 
{
    matrix_t* result = NULL;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    
    if (mat1->n_cols != mat2->n_rows) 
    {
        return NULL;
    }

    result = MatCreate(mat1->n_rows, mat2->n_cols, NULL);
    if (!result) 
    {
        return NULL;
    }

    for (i = 0; i < mat1->n_rows; i++) 
    {
        for (j = 0; j < mat2->n_cols; j++) 
        {
            float sum = 0.0;
            
            for (k = 0; k < mat1->n_cols; k++) 
            {
                sum += MatGetElem(mat1, i, k) * MatGetElem(mat2, k, j);
            }
            
            MatSetElem(result, i, j, sum);
        }
    }

    return result;
}

float MatTrace(const matrix_t* mat) 
{
    float trace = 0.0;
    size_t i = 0;
    if (mat->n_rows != mat->n_cols) 
    {
        return 0.0;
    }

    for (i = 0; i < mat->n_rows; i++) 
    {
        trace += MatGetElem(mat, i, i);
    }

    return trace;
}

matrix_t* MatSubmatrix(const matrix_t* mat, size_t row, size_t col) 
{
    matrix_t* submat = NULL;
    size_t i, j, sub_i, sub_j = 0;

    if (row >= mat->n_rows || col >= mat->n_cols) 
    {
        return NULL;
    }

    submat = MatCreate(mat->n_rows - 1, mat->n_cols - 1, NULL);
    if (!submat) 
    {
        return NULL;
    }

    for (i = 0, sub_i = 0; i < mat->n_rows; i++) 
    {
        if (i == row) 
        {
            continue;
        }
        
        for (j = 0, sub_j = 0; j < mat->n_cols; j++) 
        {
            if (j == col) 
            {
                continue;
            }
            
            MatSetElem(submat, sub_i, sub_j, MatGetElem(mat, i, j));
            sub_j++;
        }
        sub_i++;
    }

    return submat;
}

float MatDet(const matrix_t* mat) 
{
    size_t i, k = 0;
    float det = 1.0;
    size_t n = mat->n_rows;
    matrix_t* temp = NULL;
	
    if (mat->n_rows != mat->n_cols) 
    {
        return 0.0;
    }

    temp = MatCreate(n, n, mat->data);

    if (!temp) 
    {
        return 0.0;
    }
	
    /*bring the matrix to upper diagnoal form so det  = (-1)^(number of row swaps + 1)*(main diagnoal elements multiplication) */
    for (i = 0; i < n; i++) 
    {
        /* find zero value on the diagnoal */
        if (fabs(MatGetElem(temp, i, i)) < TOLERANCE) 
        {
            for (k = i + 1; k < n; k++) 
            {
                if (fabs(MatGetElem(temp, k, i)) > TOLERANCE) 
                {
                    SwapRows(temp, i, k); /*switch it with the first non-zero elment in his col*/
                    det = -det; 
                    break; 
                }
            }

            
            if (k == n) /* we go in here only if there is a 0 in diagonal in the upper triangular form*/
            {
                MatDestroy(temp); 
                return 0.0; 
            }
        }

        det *= MatGetElem(temp, i, i); /*update det as multipication of main diagnoal elements*/

        for (k = i + 1; k < n; k++) /* make sure that it is all 0 below the non-zero element in the diagnoal */
        {
            float factor = MatGetElem(temp, k, i) / MatGetElem(temp, i, i);
            SubtractRows(temp, k, i, factor);
        }
    }

    MatDestroy(temp);
    return det;
}

matrix_t* MatInvert(const matrix_t* mat) 
{
    size_t i, k = 0;
    size_t n = 0 ;
    matrix_t* inverse = NULL;
    matrix_t* temp;

    if (mat->n_rows != mat->n_cols) 
    {
        return NULL;  
    }

    n = mat->n_rows;
    inverse = MatI(n);  
    temp = MatCreate(n, n, mat->data);  

    if (!temp || !inverse) 
    {
        MatDestroy(temp);
        MatDestroy(inverse);
        return NULL; 
    }

    for (i = 0; i < n; i++) 
    {
    	float pivot = MatGetElem(temp, i, i); 
        /* find zero value on the diagnoal */
        if (fabs(MatGetElem(temp, i, i)) < TOLERANCE) 
        {
            
            for (k = i + 1; k < n; k++) /*switch it with the first non-zero elment in his col*/
            {
                if (fabs(MatGetElem(temp, k, i)) > TOLERANCE) 
                {
                    SwapRows(temp, i, k);  
                    SwapRows(inverse, i, k);  
                    break;
                }
            }
            if (k == n) /* we go in here only if there is a 0 in diagonal in the upper triangular form*/
            {
                MatDestroy(temp);
                MatDestroy(inverse);
                return NULL;  
            }
        }

        
        ScaleRow(temp, i, 1.0f / pivot); /*make the pivot be 1 */
        ScaleRow(inverse, i, 1.0f / pivot);

        /*make everything (above and below) in the current pivot col to be 0*/
        for (k = 0; k < n; k++) 
        {
            if (k != i) 
            {
                float factor = MatGetElem(temp, k, i);
                SubtractRows(temp, k, i, factor);
                SubtractRows(inverse, k, i, factor);
            }
        }
    }

    MatDestroy(temp);
    return inverse;
}




float MatNorm(const matrix_t* mat) 
{
    float sum = 0.0;
    size_t i,j = 0; 
    
    for (i = 0; i < mat->n_rows; i++) 
    {
        for (j = 0; j < mat->n_cols; j++) 
        {
            float elem = MatGetElem(mat, i, j);
            sum += elem * elem;
        }
    }
    
    return sqrt(sum);
}
