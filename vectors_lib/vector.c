#include "vector.h"
#include <stdlib.h> /*realloc malloc free size_t */
#include <stdio.h> /*perror*/
#include <string.h> /*memcpy*/

#define MAX_VECTOR_CAPACITY 10000000


struct vector_t
{
    size_t size;       
    size_t capacity;    
    size_t sizeof_elem; 
    void* first_elem;   
};

vector_t* VectorCreate(size_t init_capacity, size_t sizeof_elem)
{	
	vector_t *vect;
	if (init_capacity == 0 || sizeof_elem == 0) 
	{
        return NULL;
        }
    
    
    vect = (vector_t*)malloc(sizeof(vector_t));
    if (vect == NULL) 
    {
        return NULL;
    }
    
    vect->size = 0;
    vect->capacity = init_capacity;
    vect->sizeof_elem = sizeof_elem;
    vect->first_elem = malloc(sizeof_elem * init_capacity);
    if (vect->first_elem == NULL) {
        free(vect); 
        return NULL; 
    }

    return vect;
}

void VectorDestroy(vector_t* vector)
{
    if(vector == NULL)
    {
      perror("Vector is Null");
    }
    else
    {
      free(vector->first_elem);
      free(vector);
    }  
}


int VectorPushEnd(vector_t* vector, const void* elem)
{

    if(vector == NULL)
    {
      perror("Vector is Null");
      return 1;
    }
    if (vector->size == vector->capacity)  
    {
    	size_t new_capacity = 0;
    	void* new_first;
        if (vector->capacity >= MAX_VECTOR_CAPACITY) 
        {
            printf("Error: Cannot exceed maximum vector capacity of %u\n, which is current capacity", MAX_VECTOR_CAPACITY);
            return 1; 
        }

        new_capacity = vector->capacity * 2; 
        if (new_capacity > MAX_VECTOR_CAPACITY) 
        {
            new_capacity = MAX_VECTOR_CAPACITY;
        }

        new_first = realloc(vector->first_elem, vector->sizeof_elem * new_capacity); 
        if (new_first == NULL) 
        {
            perror("Error reallocating memory");
            return 1; 
        }

        vector->first_elem = new_first;
        vector->capacity = new_capacity;

        
        
    }

    memcpy((char*)vector->first_elem + (vector->size * vector->sizeof_elem), elem, vector->sizeof_elem);
    vector->size++;
    return 0; 
}


size_t VectorSize(const vector_t* vector)
{
    if(vector == NULL)
    {
      perror("Vector is Null");
      return 0; 
    }
    return vector->size;
}

size_t VectorCapacity(const vector_t* vector)
{
    if(vector == NULL)
    {
      perror("Vector is Null");
    }
    return vector->capacity;
}

void* VectorGetElem(const vector_t* vector, size_t index)
{
    if(vector == NULL)
    {
      perror("Vector is Null");
    }
    
    if (index >= vector->size) 
    {
        perror("Index out of bounds");
        return NULL;
    }
    return (void*)((char*)vector->first_elem + (index * vector->sizeof_elem));
}



int VectorPopEnd(vector_t* vector, void* elem)
{
    void* last_elem_addr;
    
    if(vector == NULL)
    {
      perror("Vector is Null");
      return 1;
    }
    
   
    if (vector->size == 0) 
    {
        return 1; 
    }

    
    vector->size--;

    
    last_elem_addr = (char*)vector->first_elem + (vector->size * vector->sizeof_elem);

    
    memcpy(elem, last_elem_addr, vector->sizeof_elem);

    
    return 0; 
}



int VectorResize(vector_t* vector, size_t new_capacity)
{
    void* new_first_elem = NULL;
    
    if(vector == NULL)
    {
      perror("Vector is Null");
      return 1;
    }
    
    
    if (new_capacity == 0) 
    {
        return 1; 
    }
    
    new_first_elem = realloc(vector->first_elem, vector->sizeof_elem * new_capacity);
    if (new_first_elem == NULL) 
    {
        perror("Error reallocating memory");
        return 1; 
    }

    if (new_capacity < vector->size) 
    {
        
        vector->size = new_capacity;
    }



    vector->first_elem = new_first_elem;
    vector->capacity = new_capacity;

    return 0; 
  }

