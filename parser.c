/*
 * parser.c
 * Authour: OBIAKOR LUCY
 *	    NUATIN AYOOLA 
 */

#include "shell.h"

/**
 * is_cmd - It determines if a file is an executable command.
 * @info: The info of the struct.
 * @path: The path to the file.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat la;

	(void)info;
	if (!path || stat(path, &la))
		return (0);

	if (la.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - The duplication of the characters.
 * @pathstr: The PATH of the string.
 * @start: The stars of the index.
 * @stop: The stopping of the index
 *
 * Return: The pointer to a new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int d = 0, f = 0;

	for (f = 0, d = start; d < stop; d++)
		if (pathstr[d] != ':')
			buf[f++] = pathstr[d];
	buf[f] = 0;
	return (buf);
}

/**
 * find_path - Finding this cmd in the PATH string.
 * @info: The info of the struct.
 * @pathstr: The PATH of the string.
 * @cmd: the cmd to be found.
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int d = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[d] || pathstr[d] == ':')
		{
			path = dup_chars(pathstr, curr_pos, d);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[d])
				break;
			curr_pos = d;
		}
		d++;
	}
	return (NULL);
}
