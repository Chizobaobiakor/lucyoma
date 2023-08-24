/*
 * FILE: realloc.c
 * Authour:OBIAKOR LUCY
 * NUATIN AYOOLA
 */

#include "shell.h"

/**
 * _memset - setting memory with a byte that is constant.
 * @s: memory pointer area.
 * @b: filling pointer string to the byte.
 * @n: the exact amount of byte to be filled.
 * Return: a pointer that has a memory area of s (s)
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int d;

	for (d = 0; d < n; d++)
		s[d] = b;
	return (s);
}

/**
 * ffree - a string of strings that needed to be free.
 * @pp:  the actual string of strings.
 */
void ffree(char **pp)
{
	char **h = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(h);

}

/**
 * _realloc - block a memory reallocation.
 * @ptr: blocking the already allocated(malloc).
 * @old_size: the original byte size of the block.
 * @new_size: the newest byte size of block.
 *
 * Return: the pointer will be returned.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
		return (free(ptr), NULL);

	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return NULL;

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);

	return (p);
}
