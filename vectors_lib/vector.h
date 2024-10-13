#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct vector_t vector_t;

vector_t* VectorCreate(size_t init_capacity, size_t sizeof_elem);
void VectorDestroy(vector_t* vector);
int VectorPushEnd(vector_t* vector, const void* elem);

size_t VectorSize(const vector_t* vector);
size_t VectorCapacity(const vector_t* vector);
void* VectorGetElem(const vector_t* vector, size_t index);

int VectorPopEnd(vector_t* vector, void* elem);
int VectorResize(vector_t* vector, size_t num_capacity);

#endif /* VECTOR_H */

