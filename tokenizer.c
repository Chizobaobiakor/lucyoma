#include "shell.h"

/**
 * tokenize_string - Splits a string into words based on delimiters.
 * @str: The input string to tokenize.
 * @delim: The delimiter characters.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **tokenize_string(char *str, char *delim)
{
	int i, j, k, m, num_words = 0;
	char **tokens;

	if (!str || str[0] == '\0')
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	tokens = malloc((1 + num_words) * sizeof(char *));
	if (!tokens)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delim) && str[i + k])
			k++;
		tokens[j] = malloc((k + 1) * sizeof(char));
		if (!tokens[j])
		{
			for (k = 0; k < j; k++)
				free(tokens[k]);
			free(tokens);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			tokens[j][m] = str[i++];
		tokens[j][m] = '\0';
	}
	tokens[j] = NULL;
	return (tokens);
}
