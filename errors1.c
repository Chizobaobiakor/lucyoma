/**
 * File: errors1.c
 * Auth: Lucy Obiako
 * Ayoola Nuatin
 */

#include "shell.h"

/**
 * _erratoi - conversion of a string to an integer
 * @s: the converting string
 *
 * This function converts a string to an integer. If the string does not
 * contain any valid numbers, it returns 0. If the conversion encounters
 * an error, it returns -1
 *
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int _erratoi(char *s)
{
	int d = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: does this make main return 255? */
	for (d = 0;  s[d] != '\0'; d++)
	{
		if (s[d] >= '0' && s[d] <= '9')
		{
			result *= 10;
			result += (s[d] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - an error message will be printed.
 * @info: the parameter & return the info of the struct.
 * @estr: string containing specific error type.
 *
 * Return: 0 if no numbers in string, converted number otherwise -1 on error
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - a decimal (integer) number (base 10) printing function
 * @input: the inputation
 * @fd: the filedescriptor to writen to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int d, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (d = 1000000000; d > 1; d /= 10)
	{
		if (_abs_ / d)
		{
			__putchar('0' + current / d);
			count++;
		}
		current %= d;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converting function, the cloning of an itoa
 * @num: number saved(lucy phone number)
 * @base: base of coversion
 * @flags: flagged arguments
 *
 * Return: string after processing
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do      {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replacement for instance '#' with '\0'
 * @buf: modification of the address of the string.
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int d;

	for (d = 0; buf[d] != '\0'; d++)
		if (buf[d] == '#' && (!d || buf[d - 1] == ' '))
		{
			buf[d] = '\0';
			break;
		}
}
