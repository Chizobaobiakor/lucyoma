/*
 * FILE: memory.c
 * Authour: OBIAKOR LUCY
 * NUATIN AYOOLA
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
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
