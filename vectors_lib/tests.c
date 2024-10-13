#include <stdio.h>
#include <string.h>
#include "vector.h"



void PrintVector(vector_t* vector, void (*print_elem)(const void*))
{
    size_t i = 0;
    printf("Vector elements: ");
    for (; i < VectorSize(vector); ++i) {
        print_elem(VectorGetElem(vector, i));
    }
    printf("\n");
}

void PrintInt(const void* elem)
{
    printf("%d ", *(const int*)elem);
}

void PrintChar(const void* elem)
{
    printf("%c ", *(const char*)elem);
}

void PrintString(const void* elem)
{
    printf("%s ", *(const char**)elem);
}

void TestCreateVector()
{
    vector_t *int_vector = VectorCreate(2, sizeof(int));
    vector_t *char_vector = VectorCreate(2, sizeof(char));
    vector_t *string_vector = VectorCreate(1, sizeof(char*));
    
    printf("\nTesting VectorCreater:\n");

    if (int_vector == NULL) 
    {
        perror("Failed to create int vector");
    } 
    else 
    {
        printf("Int Vector created.\n");
        VectorDestroy(int_vector);
    }


    if (char_vector == NULL) 
    {
        perror("Failed to create char vector");
    } 
    else 
    {
        printf("Char Vector created.\n");
        VectorDestroy(char_vector);
    }

    if (string_vector == NULL) 
    {
       perror("Failed to create string vector");
    } 
    else 
    {
        printf("String Vector created.\n");
        VectorDestroy(string_vector);
    }
    
}

void TestPushEndVector()
{
    size_t i = 0;
    vector_t* int_vector = VectorCreate(2, sizeof(int));
    vector_t* char_vector = VectorCreate(2, sizeof(char));
    vector_t* string_vector = VectorCreate(1, sizeof(char*));
    int nums[] = {10, 20, 30, 40};
    char chars[] = {'A', 'B', 'C', 'D'};
    char *strings[] = {"Hello", "World", "Test", "Vec", "End"};
    
    
    printf("\nTesting VectorPushEnd:\n");


    for (i = 0; i < 4; i++) 
    {
        VectorPushEnd(int_vector, &nums[i]);
        VectorPushEnd(char_vector, &chars[i]);
    }

    for (i = 0; i < 5; i++) 
    {
        VectorPushEnd(string_vector, &strings[i]);
    }

    printf("Int Vector:\n");
    PrintVector(int_vector, PrintInt);

    printf("Char Vector:\n");
    PrintVector(char_vector, PrintChar);

    printf("String Vector:\n");
    PrintVector(string_vector, PrintString);

    VectorDestroy(int_vector);
    VectorDestroy(char_vector);
    VectorDestroy(string_vector);
}

void TestVectorSize()
{
    size_t i = 0;
    vector_t *int_vector = VectorCreate(2, sizeof(int));
    int nums[] = {11, 12, 13, 14};
    
    for (i = 0; i < 4; i++) 
    {
        VectorPushEnd(int_vector, &nums[i]);
    }

    printf("\nTesting VectorSize:\n");
    PrintVector(int_vector, PrintInt);
    printf("Vector Size: %lu\n", VectorSize(int_vector));

    VectorDestroy(int_vector);
}

void TestVectorCapacity()
{
    size_t i = 0;
    vector_t *int_vector = VectorCreate(1, sizeof(int));
    int nums[] = {140, -20};
   
    printf("\nTesting VectorCapacity:\n");
   
    for (i = 0; i < 2; i++) 
    {
        VectorPushEnd(int_vector, &nums[i]);
    }
    PrintVector(int_vector, PrintInt);
    printf("Vector Capacity: %lu\n", VectorCapacity(int_vector));


    VectorPushEnd(int_vector, &nums[0]); 
   
    printf("Capacity after pushing one more element : %lu\n", VectorCapacity(int_vector));

    VectorDestroy(int_vector);
}

void TestVectorGetElem()
{
    size_t i = 0;
    vector_t *int_vector = VectorCreate(2, sizeof(int));
    int nums[] = {11, 12, 31, 22};


    for (i = 0; i < 4; i++) 
    {
        VectorPushEnd(int_vector, &nums[i]);
    }

    printf("\nTesting VectorGetElem:\n");
    PrintVector(int_vector, PrintInt);
    printf("Element at index 1 : %d\n", *(int*)VectorGetElem(int_vector, 1));
    printf("Element at index 2 : %d\n", *(int*)VectorGetElem(int_vector, 2));

    VectorDestroy(int_vector);
}

void TestVectorPopEnd()
{	
    size_t i = 0;
    vector_t* int_vector = VectorCreate(2, sizeof(int));
    vector_t* char_vector = VectorCreate(2, sizeof(char));
    vector_t* string_vector = VectorCreate(1, sizeof(char*));
    int nums[] = {1, 20, 55, 11, -5, -2};
    char chars[] = {'X', 'Y', 'Z', 'W', 'V', 'U'};
    char *strings[] = {"Alpha", "Beta", "Gamma", "Delta", "Epsilon"};
    int popped_value = 0;
    char *popped_str = NULL;
    
    for (i = 0; i < 6; i++) 
    {
        VectorPushEnd(int_vector, &nums[i]);
    }
    for (i = 0; i < 6; i++) 
    {
        VectorPushEnd(char_vector, &chars[i]);
    }

    for (i = 0; i < 5; i++) 
    {
        VectorPushEnd(string_vector, &strings[i]);
    }
    printf("\nTesting VectorPopEnd:\n");
    
    printf("Int Vector:\n");
    PrintVector(int_vector, PrintInt);
    for (i = 0; i < 6; i++) 
    {
        if (VectorPopEnd(int_vector, &popped_value) == 0) 
        {
            printf("Popped value: %d\n", popped_value);
        } 
        else 
        {
            printf("Failed to pop value\n");
        }
    }

    if (VectorPopEnd(int_vector, &popped_value) != 0) 
    {
        printf("Failed to pop from an empty vector (expected)\n");
    }
    printf("Int Vector Size After Pops: %lu\n", VectorSize(int_vector));




    printf("Char Vector:\n");
    PrintVector(char_vector, PrintChar);
    for (i = 0; i < 6; i++) 
    {
        if (VectorPopEnd(char_vector, &popped_value) == 0) 
        {
            printf("Popped value: %c\n", (char)popped_value);
        } 
        else 
        {
            printf("Failed to pop value\n");
        }
    }
    printf("Char Vector Size After Pops: %lu\n", VectorSize(char_vector));




    printf("String Vector:\n");
    PrintVector(string_vector, PrintString);
    if (VectorPopEnd(string_vector, &popped_str) == 0) 
    {
    	printf("Popped value: %s\n", popped_str);
    } 
    else 
    {
    	printf("Failed to pop value\n");
    }  
    printf("Print String Vector After PopEnd 1 Element:\n");
    PrintVector(string_vector, PrintString);



    VectorDestroy(int_vector);
    VectorDestroy(char_vector);
    VectorDestroy(string_vector);
}



void TestVectorResize()
{
    size_t i;
    vector_t *int_vector = VectorCreate(2, sizeof(int));
    int nums[] = {1, 2, 3, 4, 5};
    int new_capacity = 10; 
    int shrink_capacity = 3; 
    

    
    for (i = 0; i < 5; i++) {
        VectorPushEnd(int_vector, &nums[i]);
    }
    
    printf("\nTesting VectorResize:\n");

   
    printf("Initial Vector Size: %lu, Capacity: %lu\n", VectorSize(int_vector), VectorCapacity(int_vector));
    printf("Before resizing: ");
    PrintVector(int_vector, PrintInt);

     printf("\nIncrease capacity to %d :\n", new_capacity);
    if (VectorResize(int_vector, new_capacity) == 0) 
    {
    	printf("Size : %lu\n", VectorSize(int_vector));
    	printf("Capacity : %lu\n", VectorCapacity(int_vector));
    	printf("After resizing: ");
    	PrintVector(int_vector, PrintInt);   
    } 
    
    else 
    {
        printf("Failed to resize vector to new capacity.\n");
    }


    printf("\nDecrease capacity to %d :\n", shrink_capacity);
    if (VectorResize(int_vector, shrink_capacity) == 0) 
    {
        printf("Size: %lu\n", VectorSize(int_vector));
    	printf("Capacity : %lu\n", VectorCapacity(int_vector));
   		printf("After resizing: ");
    	PrintVector(int_vector, PrintInt);
    } 
    else 
    {
        printf("Failed to resize vector to new capacity.\n");
    }


	if (VectorResize(int_vector, 0) == 0) 
    {
    	
    } 
    else 
    {
        printf("\nFailed to resize vector to 0\n");
        PrintVector(int_vector, PrintInt);
    }


    
    VectorDestroy(int_vector);
}









int main()
{
    TestCreateVector();
    TestPushEndVector();
    TestVectorSize();
    TestVectorCapacity();
    TestVectorGetElem();
    TestVectorPopEnd();
    TestVectorResize();
    
    return 0;
}
