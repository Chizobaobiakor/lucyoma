/*
 * File: builtin1.c
 * Auth: Lucy Obiakor
 *Ayoola Nuatin
 */

#include "shell.h"

/**
 * unset_alias - the setting of an alias to string
 * @info: the parameter of the struct
 * @str: the string of the alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *n, l;
	int ret;

	n = _strchr(str, '=');
	if (!n)
		return (1);
	l = *n;
	*n = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*n = l;
	return (ret);
}

/**
 * set_alias - the setting of an alias to string.
 * @info: the parameter of a struct.
 * @str: the string of an alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *n;

	n = _strchr(str, '=');
	if (!n)
		return (1);
	if (!*++n)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - printing an alias of the string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *n = NULL, *l = NULL;

	if (node)
	{
		n = _strchr(node->str, '=');
		for (l = node->str; l <= n; l++)
			_putchar(*l);
		_putchar('\'');
		_puts(n + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myhistory - displaying the history list, one command to another line,
 *		preceded with line numbers, starts at 0.
 * @info: Structure contains the potential arguments.
 *		It is used to maintain constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * _myalias - mimicry of the alias builtin (man alias).
 * @info: the structure contains potential arguments.
 *		It is used in maintaining the constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int num = 0;
	char *n = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (num = 1; info->argv[num]; num++)
	{
		n = _strchr(info->argv[num], '=');
		if (n)
			set_alias(info, info->argv[num]);
		else
			print_alias(node_starts_with(info->alias, info->argv[num], '='));
	}

	return (0);
}
