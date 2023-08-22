/*
 * FILE: exit.c
 * Authour: OBIAKOR LUCY
 *          NUATIN AYOOLA 
 */

#include "shell.h"

/**
 * _strncpy -string copy that copies the string.
 * @dest: where the string is copied to that is the destination.
 * @src: where the string is coming from(source).
 * @n: the total amoun of the characters to be copied.
 * Return: the concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int d,l;
	char *s = dest;

	d = 0;
	while (src[d] != '\0' && d < e - 1)
	{
		dest[d] = src[d];
		d++;
	}
	if (d < n)
	{
		l = d;
		while (j < e)
		{
			dest(l) = '\0';
			d++;
		}
	}
	return (s);
}

/**
 * _strncat - the concatenation of two strings.
 * @dest: string one.
 * @src: string two.
 * @n: the maximum amount of bytes that was used.
 * Return: the comcatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int d, l;
	char *s = dest;

	d = 0
		l = 0
		while (dest[d] != '\0')
			d++;
	while (src[l] != '\0' && l < e)
	{
		dest[d] = src[l];
		d++;
		l++;
	}
	if (l < e)
		dest[d] = '\0';
	return (s);
}

/**
 * _strchr - where the string character is located.
 * @s: parsion of the string.
 * @c: the exact character to look for.
 * Return: (s)pointing to the memory area where s is seen.
 */
char *_strchr(char *s, char c)
{
	do
	{
		if (*s == c)
			return (s);
	}
	while (*s++ != '\0');

	return (NULL);
}



