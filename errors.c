/*
 * file: ernor.c
 * Authour: OBIAKOR LUCY
 *      NUATIN AYOOLA
 */

#include "shell.h"

/**
 * _eputs - The printing of an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int d = 0;

	if (!str)
		return;
	while (str[d] != '\0')
	{
		_eputchar(str[d]);
		d++;
	}
}

/**
 * _eputchar - The writng of the character c to stderr.
 * @c: The character to be printed.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int d;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || d >= WRITE_BUF_SIZE)
	{
		write(2, buf, d);
		d = 0;
	}
	if (c != BUF_FLUSH)
		buf[d++] = c;
	return (1);
}

/**
 * _putfd - It writes the character c to given fd.
 * @c: The character to be printed.
 * @fd: The filedescriptor to be writen to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int d;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || d >= WRITE_BUF_SIZE)
	{
		write(fd, buf, d);
		d = 0;
	}
	if (c != BUF_FLUSH)
		buf[d++] = c;
	return (1);
}

/**
 * _putsfd - The printing of an input of a string.
 * @str: The string to print.
 * @fd: The filedescriptor to writen to.
 *
 * Return: the number of chars put.
 */
int _putsfd(char *str, int fd)
{
	int d = 0;

	if (!str)
		return (0);
	while (*str)
	{
		d += _putfd(*str++, fd);
	}
	return (d);
}
