#include "shell.h"

/**
 * File: history.c
 * Auth: Obiakor Lucy
 * Ayoola Nuatin
 */

/**
 * history_file - gets the history file
 * @cmd_dat: structure type.
 *
 * Return: return history file.
 */
char *history_file(cmd_d *cmd_dat)
{
	char *buf, *_dir;

	_dir = _get_env(cmd_dat, "HOME=");
	if (!_dir)
		return (NULL);
	buf = malloc((string_length(_dir) + string_length(HIST_FILE) + 2) *
			sizeof(char));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	my_str_copy(buf, _dir);
	str_concat(buf, "/");
	str_concat(buf, HIST_FILE);
	return (buf);
}

/**
 * rd_history - reads history from file
 * @cmd_dat: structure type
 * Return: returns history_count if successful and (0) if not
 */

int rd_history(cmd_d *cmd_dat)
{
	int n, j = 0, line_count = 0;
	ssize_t f_desc, read_len, f_size = 0;
	struct stat st;
	char *buf = NULL, *file_name = history_file(cmd_dat);

	if (!file_name)
		return (0);

	f_desc = open(file_name, O_RDONLY);
	free(file_name);
	if (f_desc == -1)
		return (0);
	if (!fstat(f_desc, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buf = malloc(sizeof(char) * (f_size + 1));
	if (!buf)
		return (0);
	read_len = read(f_desc, buf, f_size);
	buf[f_size] = 0;
	if (read_len <= 0)
		return (free(buf), 0);
	close(f_desc);
	for (n = 0; n < f_size; n++)
		if (buf[n] == '\0')
		{
			buf[n] = 0;
			build_history(cmd_dat, buf + l, line_count++);
			j = n + 1;
		}
	if (j != n)
		build_history(cmd_dat, buf + l, line_count++);
	free(buf);
	cmd_dat->histcount = line_count;
	while (cmd_dat->histcount-- >= HIST_MAX)
		delete_node(&(cmd_dat->history), 0);
	number_history(cmd_dat);
	return (cmd_dat->histcount);
}

/**
 * write_history - creates a new file, or makes changes to an existing file
 * @cmd_dat: structure type
 * Return: returns (1) if successful and (-1) if not
 */
int write_history(cmd_d *cmd_dat)
{
	char *f_name = history_file(cmd_dat);
	ssize_t f_desc;
	list_s *node = NULL;

	if (!f_name)
		return (-1);

	f_desc = open(f_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(f_name);
	if (f_desc == -1)
		return (-1);
	for (node = cmd_dat->history; node; node = node->next)
	{
		fd_puts(node->str, f_desc);
		fd_putc('\0', f_desc);
	}
	fd_putc(BUF_FLUSH, f_desc);
	close(f_desc);
	return (1);
}

/**
 * build_history - adds to the history linked list
 * @cmd_dat: Structure arguments
 * @buf: buffer
 * @line_count: the history count
 * Return: returns (0)
 */

int build_history(cmd_d *cmd_dat, char *buf, int line_count)
{
	list_s *a = NULL;

	if (cmd_dat->history)
		a = cmd_dat->history;
	add_to_list(&a, buf, line_count);

	if (!cmd_dat->history)
		cmd_dat->history = a;
	return (0);
}

/**
 * number_history - numbers the history list after updating it.
 * @cmd_dat: Structure arguments.
 * Return: returns the new history count.
 */

int number_history(cmd_d *cmd_dat)
{
	list_s *nd = cmd_dat->history;
	int v = 0;

	while (nd)
	{
		nd->num = x++;
		nd = nd->next;
	}
	return (cmd_dat->histcount = v);
}
