#include <stdio.h>
#include <stdlib.h>
#include "mat.h"
#include <math.h>



void PrintMatrix(const matrix_t* mat, size_t rows, size_t cols) 
{
	size_t i = 0;
	size_t j = 0;
    if (!mat) 
    {
        printf("Matrix is NULL\n");
        return;
    }

    for (i = 0; i < rows; ++i) 
    {
        for (j = 0; j < cols; ++j) 
        {
        	printf("%f ", MatGetElem(mat,i,j));
        }
        printf("\n");
    }
}

void TestMatCreateDestroy()
{
	float data[] = {1.0, 2.0, 3.0, 4.0};
	matrix_t* mat = MatCreate(2, 2, data);
	printf("\nTest Create and Destoy\n");
	
	if(!mat)
	{
		  printf("Create Failed\n");
		  
	}
	else
	{
		printf("Create Succeeded\n");
	}
	
	 MatDestroy(mat);

}


void TestMatAdd()
{
	
    float data1[] = {1.0, 2.0, 3.0, 4.0};
    float data2[] = {5.0, 6.0, 7.0, 8.0};
    matrix_t* mat_sum;
    matrix_t* mat1;
    matrix_t* mat2;
	
	printf("\nTest MatAdd:\n");
	
    mat1 = MatCreate(2, 2, data1);
    mat2 = MatCreate(2, 2, data2);
    
    printf("Matrix 1:\n");
    PrintMatrix(mat1,2,2);

    printf("\nMatrix 2:\n");
    PrintMatrix(mat2,2,2);
    
    mat_sum = MatAdd(mat1, mat2);
    
   	printf("\nSum of Matrix 1 and Matrix 2:\n");
    PrintMatrix(mat_sum,2,2);

    MatDestroy(mat1);
    MatDestroy(mat2);
    MatDestroy(mat_sum);

}

void TestMatScalarMult()
{

	float data[] = {1.0, 2.0, 3.0, 4.0};
	float scalar = 2.0;
	matrix_t* mat = MatCreate(2, 2, data);
	matrix_t* result;
	
	printf("\nTest MatScalarMult:\n");
	
	printf("Before :\n");
    PrintMatrix(mat,2,2);
	
	printf("Scalar mult with 2\n");
	result = MatScalarMult(mat,scalar);
	
	printf("After :\n");
    PrintMatrix(result,2,2);
    
    MatDestroy(mat);
    MatDestroy(result);

}

void TestMatCompare()
{

    float data1[] = {1.0, 2.0, 3.0, 4.0};
    float data2[] = {5.0, 6.0, 7.0, 8.0};
    matrix_t* mat1;
    matrix_t* mat2;
    
    float data3[] = {1.0, 2.0, 3.0, 4.0};
    float data4[] = {1.0, 2.0, 3.0, 4.0};
    matrix_t* mat3;
    matrix_t* mat4;
    

	
	printf("\nTest MatCompare:\n");
	
    mat1 = MatCreate(2, 2, data1);
    mat2 = MatCreate(2, 2, data2);
    mat3 = MatCreate(2, 2, data3);
    mat4 = MatCreate(2, 2, data4);
    
    printf("Non-Equal Test:\n");
    
    printf("Matrix 1:\n");
    PrintMatrix(mat1,2,2);

    printf("Matrix 2:\n");
    PrintMatrix(mat2,2,2);
    
    if(MatCompare(mat1, mat2) == 0)
    {
    	printf("Success, Matrices are not equal\n");	
    }
    else
    {
    	printf("Failed, Matrices are equal\n");		
    }
    
     
     
    printf("\nEqual Test:\n"); 
    printf("Matrix 3:\n");
    PrintMatrix(mat3,2,2);

    printf("Matrix 4:\n");
    PrintMatrix(mat4,2,2);
     

    
    if(MatCompare(mat3, mat4) == 1)
    {
    	printf("Success, Matrices are equal\n");	
    }
    else
    {
    	printf("Failed, Matrices are not equal\n");		
    }
    
    
    MatDestroy(mat1);
    MatDestroy(mat2);
    MatDestroy(mat3);
    MatDestroy(mat4);
    
	
}



void TestMatI()
{

	matrix_t* mat = MatI(2);

	
	printf("\nTest MatI\n");
	
	printf("Matrix is :\n");
    PrintMatrix(mat,2,2);
    
    MatDestroy(mat);


}

void TestMatShape()
{

	float data[] = {1.0, 2.0, 3.0, 4.0,5.0,6,0};
	matrix_t* mat = MatCreate(3, 2, data);
	size_t dim[2] = {0,0};
	
	printf("\nTest Mat Shape\n");
	PrintMatrix(mat,3,2);
	
	MatShape(mat, dim);
	printf("The dim of mat is %lu x %lu :\n" , dim[0], dim[1]);
	MatDestroy(mat);  
	
	
}

void TestMatTranspose()
{
    float data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    matrix_t* mat;
    matrix_t* mat_transposed;

    printf("\nTest MatTranspose:\n");

    mat = MatCreate(2, 3, data);
    
    printf("Original Matrix:\n");
    PrintMatrix(mat, 2, 3);

    mat_transposed = MatTranspose(mat);

    printf("\nTransposed Matrix:\n");
    PrintMatrix(mat_transposed, 3, 2);

    MatDestroy(mat);
    MatDestroy(mat_transposed);
}


void TestMatMult()
{
    float data1[] = {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    float data2[] = {
        9.0, 8.0, 7.0,
        6.0, -5.0, 4.0,
        3.0, 2.0, 1.0
    };

    matrix_t* mat1;
    matrix_t* mat2;
    matrix_t* mat_product;

    printf("\nTest MatMult:\n");

    mat1 = MatCreate(3, 3, data1);
    mat2 = MatCreate(3, 3, data2);

    printf("Matrix 1:\n");
    PrintMatrix(mat1, 3, 3);

    printf("\nMatrix 2:\n");
    PrintMatrix(mat2, 3, 3);

    mat_product = MatMult(mat1, mat2);

    printf("\nProduct of Matrix 1 and Matrix 2:\n");
    if (mat_product)
    {
        PrintMatrix(mat_product, 3, 3);
    }
    else
    {
        printf("Matrix multiplication failed due to dimension mismatch.\n");
    }

    MatDestroy(mat1);
    MatDestroy(mat2);
    MatDestroy(mat_product);
}


void TestMatSubmatrix()
{
    float data3x3[] = {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    float data1x1[] = {
        1.0
    };
    
    size_t dim[2] = {1,1};

    matrix_t* mat3x3;
    matrix_t* mat1x1;
    matrix_t* submat3x3;
    matrix_t* submat1x1;

    printf("\nTest MatSubmatrix:\n");

    
    mat3x3 = MatCreate(3, 3, data3x3);
    printf("Original 3x3 Matrix:\n");
    PrintMatrix(mat3x3, 3, 3);

    submat3x3 = MatSubmatrix(mat3x3, 1, 1);  

    printf("\n3x3 Submatrix (removing row 1, col 1):\n");
    if (submat3x3)
    {
        PrintMatrix(submat3x3, 2, 2);
    }
    else
    {
        printf("Failed to create submatrix.\n");
    }

    MatDestroy(mat3x3);
    MatDestroy(submat3x3);

    
    mat1x1 = MatCreate(1, 1, data1x1);
    printf("\nOriginal 1x1 Matrix:\n");
    PrintMatrix(mat1x1, 1, 1);

    submat1x1 = MatSubmatrix(mat1x1, 0, 0);
    MatShape(submat1x1, dim);  

    printf("\n1x1 Submatrix (removing the only element):\n");
    if (dim[0] == 0 && dim[1] == 0)
    {
         printf("As expected, submatrix is 0x0 after removing the only element.\n"); 
    }
    else
    {
        printf("Failed to get a 0x0 submat .\n");
    }

    MatDestroy(mat1x1);
    MatDestroy(submat1x1);
}


void TestMatTrace()
{
    float data3x3[] = {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    };

    float data2x2[] = {
        1.0, 2.0,
        3.0, 4.0
    };

    float dataNonSquare[] = {
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0
    };

    matrix_t* mat3x3;
    matrix_t* mat2x2;
    matrix_t* matNonSquare;
    float trace;

    printf("\nTest MatTrace:\n");

  
    mat3x3 = MatCreate(3, 3, data3x3);
    printf("3x3 Matrix:\n");
    PrintMatrix(mat3x3, 3, 3);

    trace = MatTrace(mat3x3);
    printf("Trace of the 3x3 Matrix: %f\n", trace);  

    MatDestroy(mat3x3);

    
    mat2x2 = MatCreate(2, 2, data2x2);
    printf("\n2x2 Matrix:\n");
    PrintMatrix(mat2x2, 2, 2);

    trace = MatTrace(mat2x2);
    printf("Trace of the 2x2 Matrix: %f\n", trace);  

    MatDestroy(mat2x2);

    
    matNonSquare = MatCreate(2, 3, dataNonSquare);
    printf("\nNon-square 2x3 Matrix:\n");
    PrintMatrix(matNonSquare, 2, 3);

    trace = MatTrace(matNonSquare);
    printf("Trace of the Non-square Matrix: %f (Expected: 0.0)\n", trace);

    MatDestroy(matNonSquare);
}



void TestMatDet()
{
   /* float data3x3[] = {
        1.0, 2.0, 3.0,
        0.0, 1.0, 4.0,
        5.0, 6.0, 0.0
    };*/
    
        float data3x3[] = {
        1.0, 2.0, 1.0,
        1.0, 1.0, 0.0,
        0.0, 2.0, 0.0
    };

    float data2x2[] = {
        1.0, 2.0,
        3.0, -4.0
    };

    float data1x1[] = {
        7.0
    };

    float dataSingular[] = {
        2.0, 4.0,
        1.0, 2.0
    };
    
    
    float data4[] ={
		984.956, 400.4, 986.0572, 25,
		3371.81, 707.2, 2877.913, 51.5,
		6101.737, 1992.92, 5014.7075, 152.9,
		96.663, 44.8, 92.5761, 3
	};

    matrix_t* mat3x3;
    matrix_t* mat2x2;
    matrix_t* mat1x1;
    matrix_t* mat;
    matrix_t* matSingular;
    float det;

    printf("\nTest MatDet:\n");

    
    mat3x3 = MatCreate(3, 3, data3x3);
    printf("3x3 Matrix:\n");
    PrintMatrix(mat3x3, 3, 3);

    det = MatDet(mat3x3);
    printf("Determinant of the 3x3 Matrix: %f (Expected: 2.0)\n", det);  

    MatDestroy(mat3x3);

 
    mat2x2 = MatCreate(2, 2, data2x2);
    printf("\n2x2 Matrix:\n");
    PrintMatrix(mat2x2, 2, 2);

    det = MatDet(mat2x2);
    printf("Determinant of the 2x2 Matrix: %f (Expected: -10.0)\n", det);  

    MatDestroy(mat2x2);

  
    mat1x1 = MatCreate(1, 1, data1x1);
    printf("\n1x1 Matrix:\n");
    PrintMatrix(mat1x1, 1, 1);

    det = MatDet(mat1x1);
    printf("Determinant of the 1x1 Matrix: %f (Expected: 7.0)\n", det);  

    MatDestroy(mat1x1);
	
	
	mat = MatCreate(4, 4, data4);
	printf("4x4 Matrix:\n");
    PrintMatrix(mat, 4, 4);

    det = MatDet(mat);
    if (fabs(det) < 1e-6) {
    det = 0.0;
	}
    printf("Determinant of the 4x4 Matrix: %f (Expected: 0.0)\n", det);  

    MatDestroy(mat);

    matSingular = MatCreate(2, 2, dataSingular);
    printf("\nSingular 2x2 Matrix:\n");
    PrintMatrix(matSingular, 2, 2);

    det = MatDet(matSingular);
    printf("Determinant of the Singular Matrix: %f (Expected: 0.0)\n", det);  

    MatDestroy(matSingular);
}


void TestMatInvert()
{
    float data3x3[] = {
        4.0, 7.0, 2.0,
        3.0, 6.0, 1.0,
        2.0, 5.0, 1.0
    };

    float data2x2[] = {
        1.0, -1.5,
        3.0, -4.3
    };

    float dataSingular[] = {
        2.0, 4.0,
        1.0, 2.0
    };
    
    float data1x1[] = {
        2.0    
    };
    
    

    matrix_t* mat3x3;
    matrix_t* mat2x2;
    matrix_t* mat1x1;
    matrix_t* matSingular;
    matrix_t* inverse;
    

    printf("\nTest MatInvert:\n");

   
    mat3x3 = MatCreate(3, 3, data3x3);
    printf("3x3 Matrix:\n");
    PrintMatrix(mat3x3, 3, 3);

    inverse = MatInvert(mat3x3);
    if (inverse) 
    {
        printf("Inverse of the 3x3 Matrix:\n");
        PrintMatrix(inverse, 3, 3);
        MatDestroy(inverse);
    } 
    else 
    {
        printf("3x3 Matrix is not invertible.\n");
    }
    MatDestroy(mat3x3);

    
    mat2x2 = MatCreate(2, 2, data2x2);
    printf("\n2x2 Matrix:\n");
    PrintMatrix(mat2x2, 2, 2);

    inverse = MatInvert(mat2x2);
    if (inverse) 
    {
        printf("Inverse of the 2x2 Matrix:\n");
        PrintMatrix(inverse, 2, 2);
        MatDestroy(inverse);
    } 
    else
    
    {
        printf("2x2 Matrix is not invertible.\n");
    }
    MatDestroy(mat2x2);
    
    mat1x1 = MatCreate(1, 1, data1x1);
    inverse = MatInvert(mat1x1);
    
    if (inverse) 
    {
        printf("Inverse of the 1x1 Matrix:\n");
        PrintMatrix(inverse, 1, 1);
        MatDestroy(inverse);
    } 
    else
    
    {
        printf("1x1 Matrix is not invertible.\n");
    }
    MatDestroy(mat1x1);

    
    matSingular = MatCreate(2, 2, dataSingular);
    printf("\nSingular 2x2 Matrix:\n");
    PrintMatrix(matSingular, 2, 2);

    inverse = MatInvert(matSingular);
    if (inverse) 
    {
        printf("Inverse of the Singular Matrix:\n");
        PrintMatrix(inverse, 2, 2);
        MatDestroy(inverse);
    } 
    else 
    {
        printf("Singular Matrix is not invertible (as expected).\n");
    }
    
    MatDestroy(matSingular);
}


void TestMatNorm()
{
    float data1[] = {1.0, 2.0, 3.0, 4.0};
    float data2[] = {1.0, 1.0, 1.0, 1.0};
    matrix_t* mat1;
    matrix_t* mat2;
    float norm1;
    float norm2;

    printf("\nTest MatNorm:\n");

    mat1 = MatCreate(2, 2, data1);
    mat2 = MatCreate(2, 2, data2);

    printf("Matrix 1:\n");
    PrintMatrix(mat1, 2, 2);

    norm1 = MatNorm(mat1);
    printf("Norm of Matrix 1: %f\n", norm1);

    printf("Matrix 2:\n");
    PrintMatrix(mat2, 2, 2);

    norm2 = MatNorm(mat2);
    printf("Norm of Matrix 2: %f\n", norm2);

    MatDestroy(mat1);
    MatDestroy(mat2);
}



int main() 
{


TestMatCreateDestroy();
TestMatAdd();
TestMatScalarMult();
TestMatCompare();
TestMatI();
TestMatShape();
TestMatTranspose();
TestMatMult();
TestMatSubmatrix();
TestMatTrace();
TestMatDet();
TestMatInvert();
TestMatNorm();





    return 0;
}

