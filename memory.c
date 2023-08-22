/*
 * FILE: memory.c
 * Authour: OBIAKOR LUCY
 *          NUATIN AYOOLA 
 */

#include "shell.h"

/**
 * bfree - pointers and NULL te address will be free
 * @ptr: pointer address to free
 *
 * Return: when free = 1, otherwise 0.
 */
int bfree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);  // Free the memory pointed to by the pointer
        *ptr = NULL; // Set the pointer to NULL
        return (1);  // Return 1 to indicate success
    }
    return (0);  // Return 0 if the pointer was already NULL or if it was invalid
}
