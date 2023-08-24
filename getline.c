#include "shell.h"

/*
 * file: getline.c
 * Authour: OBIAKOR LUCY(lucyobiakor@gmail.com)
 * NUATIN AYOOLA
 *
 * input_buf - Buffers chained commands and processes input.
 * @info: Parameter struct containing program information.
 * @buf: Address of buffer to store input.
 * @len: Address of length variable for buffer.
 *
 * Return: Bytes read from input.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* If nothing left in the buffer, fill it */
	{
		free(*buf); /* Free previous buffer */
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* Remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* Check if it's a command chain (semicolon-separated) */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - Gets a line of input from the user.
 * @info: Parameter struct containing program information.
 *
 * Return: Bytes read from input.
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* Buffer for command chain separated by ';' */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* Commands left in the chain buffer */
	{
		j = i; /* Initialize new iterator to current buf position */
		p = buf + i; /* Get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* Iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* Increment past nulled ';' */
		if (i >= len) /* Reached end of buffer? */
		{
			i = len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* Pass back pointer to current command position */
		return (_strlen(p)); /* Return length of current command */
	}

	*buf_p = buf; /* Not a chain, pass back buffer from _getline() */
	return (r); /* Return length of buffer from _getline() */
}

/**
 * read_buf - Reads from a buffer.
 * @info: Parameter struct containing program information.
 * @buf: Buffer to read from.
 * @i: Size.
 *
 * Return: r.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - Gets the next line of input from STDIN.
 * @info: Parameter struct containing program information.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: s.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* Memory allocation failure */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Handles SIGINT signal (Ctrl-C).
 * @sig_num: The signal number.
 *
 * Return: void.
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
