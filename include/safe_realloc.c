#include "safe_realloc.h"

void* safe_realloc(void* ptr, size_t size)
{
    void* temp = realloc(ptr, size);
    
    if (temp == NULL) free(ptr);
    return temp;
}