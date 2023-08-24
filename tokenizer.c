#include "shell.h"

/**
 * token - Splits a string into words based on delimiters.
 * @str: The input string to tokenize.
 * @delim: The delimiter characters.
 *
 * Return: returns the address to a string array.
 */
char *token(char *str, char *delim)
{
	int n, o, d, l;
	int word_num = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (n = 0; str[n] != '\n'; n++)
		if (!is_delim(str[n], delim) && (is_delim(str[n + 1], delim)
					|| !str[n + 1]))
			word_num++;

	if (word_num == 0)
		return (NULL);
	s = malloc((1 + word_num) * sizeof(char *));
	if (!s)
		return (NULL);
	for (n = 0, o = 0; o < word_num; o++)
	{
		while (is_delim(str[n], delim))
			n++;
		d = 0;
		while (!is_delime(str[n + d], delim) && str[n + d])
			d++;
		s[o] = malloc((d + 1) * sizeof(char));
		if (!s[o])
		{
			for (d = 0; d < o; d++)
				free(s[d]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < d; l++)
			s[o][l] = str[n++];
		s[o][l] = 0;
	}
	s[o] = NULL;
	return (s);
}
