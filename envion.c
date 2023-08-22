/*
 * File: envion.c
 * Auth: Lucy Obiakor
 *       Ayoola Nuatin 
 */

#include "shell.h"

/**
 * _myenv - Thia prints the current environment.
 * @info: The structure that contains potential arguments.It maintains
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
        print_list_str(info->env);
        return (0);
}

/**
 * _getenv - getting the value of an environ variable.
 * @info: Containing potential arguments. for maintenance
 * @name: The env of the var name.
 *
 * Return: the exact value
 */
char *_getenv(info_t *info, const char *name)
{
list_t *node = info->env;
        char *c;

        while (node)
        {
                c = starts_with(node->str, name);
                if (c && *c)
                        return (c);
                node = node->next;
        }
        return (NULL);
}

/**
 * _mysetenv - Initialization of the new env var,or modify an existing one
 * @info:containing potential arguments. Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
        if (info->argc != 3)
        {
                _eputs("Incorrect number of arguements\n");
                return (1);
        }
        if (_setenv(info, info->argv[1], info->argv[2]))
                return (0);
	        return (1);
}

/**
 * _myunsetenv - Removal of an environment variable
 * @info: contains potential arguments. Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
        int d;

        if (info->argc == 1)
        {
                _eputs("Too few arguements.\n");
                return (1);
        }
        for (d = 1; d <= info->argc; d++)
                _unsetenv(info, info->argv[d]);

        return (0);
}

/**
 * populate_env_list - the population env linked list
 * @info: houses the potential arguments.maintains constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
        list_t *node = NULL;
        size_t d;

        for (d = 0; environ[d]; d++)
                add_node_end(&node, environ[d], 0);
        info->env = node;
        return (0);
}
