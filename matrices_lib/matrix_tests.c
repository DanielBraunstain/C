#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mat.h"

typedef enum {
    FAIL = 0,
    SUCCESS = 1
} TestResult;

TestResult TestMatCreate();
TestResult TestMatShape();
TestResult TestMatGetElem();
TestResult TestMatAdd();
TestResult TestMatScalarMult();
TestResult TestMatCompare();
TestResult TestMatTranspose();
TestResult TestMatMult();
TestResult TestMatTrace();
TestResult TestMatI();
TestResult TestMatSubmatrix();
TestResult TestMatDet();
TestResult TestMatInvert();
TestResult TestMatNorm();

/* Helper function to check matrix shape without passing a dim array*/
int CheckMatrixShape(const matrix_t* mat, size_t expected_rows, size_t expected_cols) 
{
    size_t dims[2];
    MatShape(mat, dims);
    return (dims[0] == expected_rows && dims[1] == expected_cols);
}

int main() {
    TestResult all_passed = SUCCESS;

    if (TestMatCreate() == FAIL) 
    {
        printf("ERROR IN TestMatCreate\n");
        all_passed = FAIL;
    }
    if (TestMatShape() == FAIL) 
    {
        printf("ERROR IN TestMatShape\n");
        all_passed = FAIL;
    }
    if (TestMatGetElem() == FAIL) 
    {
        printf("ERROR IN TestMatGetElem\n");
        all_passed = FAIL;
    }
    if (TestMatAdd() == FAIL) 
    {
        printf("ERROR IN TestMatAdd\n");
         all_passed = FAIL;
    }
    if (TestMatScalarMult() == FAIL) 
    {
        printf("ERROR IN TestMatScalarMult\n");
         all_passed = FAIL;
    }
    
    if (TestMatCompare() == FAIL) 
    {
        printf("ERROR IN TestMatCompare\n");
         all_passed = FAIL;
    }
    if (TestMatTranspose() == FAIL) 
    {
        printf("ERROR IN TestMatTranspose\n");
         all_passed = FAIL;
    }
    if (TestMatMult() == FAIL) {
        printf("ERROR IN TestMatMult\n");
        all_passed = FAIL;
    }
    if (TestMatTrace() == FAIL) 
    {
        printf("ERROR IN TestMatTrace\n");
         all_passed = FAIL;
    }
    if (TestMatI()  == FAIL) 
    {
        printf("ERROR IN TestMatI\n");
        all_passed = FAIL;
    }
    
    if (TestMatSubmatrix() == FAIL) 
    {
        printf("ERROR IN TestMatSubmatrix\n");
        all_passed = FAIL;
    }
    
    if ( TestMatDet() == FAIL) 
    {
        printf("ERROR IN TestMatDet\n");
        all_passed = FAIL;
    }
    
    if (TestMatInvert() == FAIL) 
    {
        printf("ERROR IN TestMatInvert\n");
        all_passed = FAIL;
    }
    if (TestMatNorm() == FAIL) 
    {
        printf("ERROR IN TestMatNorm\n");
        all_passed = FAIL;
    }

    if (all_passed) 
    {
        printf("All tests passed\n");
    }
    
    return SUCCESS;
}

TestResult TestMatCreate() 
{
    float data[6] = {1, 2, 3, 4, 5, 6};
    matrix_t* mat = MatCreate(2, 3, data);
    size_t i, j = 0;

   
    if (!mat) 
    {
        return FAIL;
    }

    if (!CheckMatrixShape(mat, 2, 3)) 
    {
        MatDestroy(mat);
        return FAIL;
    }

    for (i = 0; i < 2; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            if (MatGetElem(mat, i, j) != data[i * 3 + j]) 
            {
                MatDestroy(mat);
                return FAIL;
            }
        }
    }

    MatDestroy(mat);

    mat = NULL;
    mat = MatCreate(2, 3, NULL);

    if (!mat) 
    {
        return FAIL;
    }

    if (!CheckMatrixShape(mat, 2, 3)) 
    {
        MatDestroy(mat);
        return FAIL;
    }

    for (i = 0; i < 2; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            if (MatGetElem(mat, i, j) != 0) 
            {
                MatDestroy(mat);
                return FAIL;
            }
        }
    }

    MatDestroy(mat);
    return SUCCESS;
}



TestResult TestMatShape() 
{
    float data[6] = {1, 2, 3, 4, 5, 6};
    size_t expected_dims[2] = {2, 3}; 
    size_t actual_dims[2] = {0,0};

    matrix_t* mat = MatCreate(2, 3, data);

    MatShape(mat, actual_dims);

    if (actual_dims[0] != expected_dims[0] || actual_dims[1] != expected_dims[1]) 
    {
        MatDestroy(mat);
        return FAIL;
    }

    MatDestroy(mat);
    return SUCCESS;
}

TestResult TestMatGetElem() 
{
    
    float data[6] = {1, 2, 3, 4, 5, 6};
    matrix_t* mat = MatCreate(2, 3, data);

    float expected_value = 5;

    
    if (MatGetElem(mat, 1, 1) != expected_value) 
    {
        MatDestroy(mat);
        return FAIL;
    }

    MatDestroy(mat);
    return SUCCESS;
}


TestResult TestMatAdd() 
{
    float data1[6] = {1, 2, 3, 4, 5, 6};
    float data2[6] = {6, 5, 4, 3, 2, 1};
    float expected[6] = {7, 7, 7, 7, 7, 7};
    
    size_t i, j = 0;
    
    matrix_t* mat1 = MatCreate(2, 3, data1);
    matrix_t* mat2 = MatCreate(2, 3, data2);
    matrix_t* result = MatAdd(mat1, mat2);

    if (!result) {
        MatDestroy(mat1);
        MatDestroy(mat2);
        return FAIL;
    }

    if (!CheckMatrixShape(result, 2, 3)) {
        MatDestroy(mat1);
        MatDestroy(mat2);
        MatDestroy(result);
        return FAIL;
    }

    for (i = 0; i < 2; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            if (MatGetElem(result, i, j) != expected[i * 3 + j]) 
            {
                MatDestroy(mat1);
                MatDestroy(mat2);
                MatDestroy(result);
                return FAIL;
            }
        }
    }

    MatDestroy(mat1);
    MatDestroy(mat2);
    MatDestroy(result);
    return SUCCESS;
}

TestResult TestMatScalarMult() 
{
    float data[6] = {1, 2, 3, 4, 5, 6};
    float scalar = 2.0;
    float expected[6] = {2, 4, 6, 8, 10, 12};
    
    size_t i, j = 0;
    
    matrix_t* mat = MatCreate(2, 3, data);
    matrix_t* result = MatScalarMult(mat, scalar);


    if (!CheckMatrixShape(result, 2, 3)) 
    {
        MatDestroy(mat);
        MatDestroy(result);
        return FAIL;
    }

    for (i = 0; i < 2; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            if (MatGetElem(result, i, j) != expected[i * 3 + j]) 
            {
                MatDestroy(mat);
                MatDestroy(result);
                return FAIL;
            }
        }
    }

    MatDestroy(mat);
    MatDestroy(result);
    return SUCCESS;
}

TestResult TestMatCompare() 
{
    float data1[6] = {1, 2, 3, 4, 5, 6};
    float data2[6] = {1, 2, 3, 4, 5, 6}; 
    float data3[6] = {1, 2, 3, 4, 5, 7}; 

    matrix_t* mat1 = MatCreate(2, 3, data1);
    matrix_t* mat2 = MatCreate(2, 3, data2);
    matrix_t* mat3 = MatCreate(2, 3, data3);


    if (MatCompare(mat1, mat2) != 1) 
    {
        MatDestroy(mat1);
        MatDestroy(mat2);
        MatDestroy(mat3);
        return FAIL;
    }

 
    if (MatCompare(mat1, mat3) != 0) 
    {
        MatDestroy(mat1);
        MatDestroy(mat2);
        MatDestroy(mat3);
        return FAIL;
    }

    MatDestroy(mat1);
    MatDestroy(mat2);
    MatDestroy(mat3);

    return SUCCESS;
}

TestResult TestMatTranspose() 
{
    float data[6] = {1, 2, 3, 4, 5, 6};
    float expected[6] = {1, 4, 2, 5, 3, 6};
    
    size_t i, j = 0;
    
    matrix_t* mat = MatCreate(2, 3, data);
    matrix_t* result = MatTranspose(mat);


    if (!CheckMatrixShape(result, 3, 2)) 
    {
        MatDestroy(mat);
        MatDestroy(result);
        return FAIL;
    }

    for (i = 0; i < 3; i++) 
    {
        for (j = 0; j < 2; j++) 
        {
            if (MatGetElem(result, i, j) != expected[i * 2 + j]) 
            {
                MatDestroy(mat);
                MatDestroy(result);
                return FAIL;
            }
        }
    }

    MatDestroy(mat);
    MatDestroy(result);
    return SUCCESS;
}

TestResult TestMatMult() 
{
    float data1[6] = {1, 2, 3, 4, 5, 6};
    float data2[6] = {1, 4, 2, 5, 3, -6};
    float expected[4] = {14, -4, 32, 5};
    
    size_t i, j = 0;
    
    matrix_t* mat1 = MatCreate(2, 3, data1);
    matrix_t* mat2 = MatCreate(3, 2, data2);
    matrix_t* result = MatMult(mat1, mat2);


    if (!CheckMatrixShape(result, 2, 2)) 
    {
        MatDestroy(mat1);
        MatDestroy(mat2);
        MatDestroy(result);
        return FAIL;
    }

    for (i = 0; i < 2; i++) 
    {
        for (j = 0; j < 2; j++) 
        {
            if (MatGetElem(result, i, j) != expected[i * 2 + j]) 
            {
                MatDestroy(mat1);
                MatDestroy(mat2);
                MatDestroy(result);
                return FAIL;
            }
        }
    }

    MatDestroy(mat1);
    MatDestroy(mat2);
    MatDestroy(result);
    return SUCCESS;
}

TestResult TestMatTrace() 
{
    float data[4] = {1, 0, 0, 2};
    float expected = 3.0;
    
    matrix_t* mat = MatCreate(2, 2, data);
    float result = MatTrace(mat);

    if (fabs(result - expected) > TOLERANCE) 
    {
        MatDestroy(mat);
        return FAIL;
    }

    MatDestroy(mat);
    return SUCCESS;
}

TestResult TestMatI() 
{
    
    size_t i, j = 0;
    size_t n = 3;  

    
    matrix_t* mat = MatI(n);


    if (!CheckMatrixShape(mat, n, n)) 
    {
        MatDestroy(mat);
        return FAIL;
    }

    
    for (i = 0; i < n; i++) 
    {
        if (MatGetElem(mat, i, i) != 1) 
        {
            MatDestroy(mat);
            return FAIL;
        }
        for (j = 0; j < n; j++) 
        {
            if (i != j && MatGetElem(mat, i, j) != 0) 
            {
                
                MatDestroy(mat);
                return FAIL;
            }
        }
    }

  
    MatDestroy(mat);
    return SUCCESS;
}



TestResult TestMatSubmatrix() 
{
    
    float data3x3[] = {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    float data1x1[] = {
        1.0
    };

    float expected_3x3[] = {
        1.0, 3.0,
        7.0, 9.0
    };

    size_t i, j = 0;
    
    matrix_t* mat1x1 = NULL;
    matrix_t* submat1x1 = NULL;

    
    matrix_t* mat3x3 = MatCreate(3, 3, data3x3);
    matrix_t* submat3x3 = MatSubmatrix(mat3x3, 1, 1);

    if (!CheckMatrixShape(submat3x3, 2, 2)) 
    {
        MatDestroy(mat3x3);
        MatDestroy(submat3x3);
        return FAIL;
    } 
    else 
    {
        for (i = 0; i < 2; i++) 
        {
            for (j = 0; j < 2; j++) 
            {
                if (MatGetElem(submat3x3, i, j) != expected_3x3[i * 2 + j]) 
                {
                    MatDestroy(mat3x3);
                    MatDestroy(submat3x3);
                    return FAIL;
                }
            }
        }
    }

    MatDestroy(mat3x3);
    MatDestroy(submat3x3);

    
    mat1x1 = MatCreate(1, 1, data1x1);
    submat1x1 = MatSubmatrix(mat1x1, 0, 0);

    if (!CheckMatrixShape(submat1x1, 0, 0)) 
    {
        MatDestroy(mat1x1);
        MatDestroy(submat1x1);
        return FAIL;
    }

    MatDestroy(mat1x1);
    MatDestroy(submat1x1);

    return SUCCESS;
}




TestResult TestMatDet() 
{
    float data1[1] = {5};  
    float expected1 = 5.0;
    
    float data2[4] = {1, 2, 3, 4};  
    float expected2 = -2.0;
    
    float data3[9] = {-1, 2, 3, 0, 1, 4, 5, 6, 0};  
    float expected3 = 49.0;

    matrix_t* mat1 = MatCreate(1, 1, data1);
    matrix_t* mat2 = MatCreate(2, 2, data2);
    matrix_t* mat3 = MatCreate(3, 3, data3);
    

    float result1 = MatDet(mat1);
    float result2 = MatDet(mat2);
    float result3 = MatDet(mat3);

    if (fabs(result1 - expected1) > TOLERANCE) 
    {
        return FAIL;
    }
    if (fabs(result2 - expected2) > TOLERANCE) 
    {
        return FAIL;
    }
    if (fabs(result3 - expected3) > TOLERANCE) 
    {
        return FAIL;
    }

    MatDestroy(mat1);
    MatDestroy(mat2);
    MatDestroy(mat3);

    return SUCCESS;
}

TestResult TestMatInvert() {
    float data[9] = {
        4.0, 7.0, 2.0,
        -3.0, 6.0, 1.0,
        2.0, 5.0, -1.0
    };

    float expected[9] = {
        11/105.0, -17/105.0, 1/21.0,
        1/105.0,  8/105.0, 2/21.0,
        9/35.0,  2/35.0,  -3/7.0
    };

    size_t i, j = 0;
    
    matrix_t* mat = MatCreate(3, 3, data);
    matrix_t* result = MatInvert(mat);

    if (!result) 
    {
        MatDestroy(mat);
        return FAIL;
    }

    if (!CheckMatrixShape(result, 3, 3)) 
    {
        MatDestroy(mat);
        MatDestroy(result);
        return FAIL;
    }

    for (i = 0; i < 3; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            if (fabs(MatGetElem(result, i, j) - expected[i * 3 + j]) > TOLERANCE) 
            {
                MatDestroy(mat);
                MatDestroy(result);
                return FAIL;
            }
        }
    }

    MatDestroy(mat);
    MatDestroy(result);
    return SUCCESS;
}

TestResult TestMatNorm() 
{
    float data[6] = {1, 2, 3, 4, 5, 6};
    float expected = sqrt(1*1 + 2*2 + 3*3 + 4*4 + 5*5 + 6*6);
    
    matrix_t* mat = MatCreate(2, 3, data);
    float result = MatNorm(mat);

    if (fabs(result - expected) > TOLERANCE) 
    {
        MatDestroy(mat);
        return FAIL;
    }

    MatDestroy(mat);
    return SUCCESS;
}
