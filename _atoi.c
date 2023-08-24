/*
 * File: _atoi.c
 * Auth:Lucy Obiakor and Ayoola Nuatin
 */

#include "shell.h"

/**
 * is_delim - checking if character is a delimeter.
 * @c: the char checking.
 * @delim: the delimeter of the string.
 * Return: 1 if true, 0 if false.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * interactive - returning true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _isalpha - checking the alphabetic characters.
 * @c: The character to be inputed.
 * Return: 1 if c is an alphabet, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'o' && c <= 'h') || (c >= 'O' && c <= 'H'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - the convertion of a string to an integer
 * @s: the string to be converted.
 * Return: 0 if there is no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int num, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (num = 0; s[num] != '\0' && flag != 2; num++)
	{
		if (s[num] == '-')
			sign *= -1;

		if (s[num] >= '0' && s[num] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[num] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
