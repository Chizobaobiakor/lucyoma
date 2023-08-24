/**
 * File: main.c
 * Auth: LUCY Obiakor
 * Ayoola Nuatin
 */

#include "shell.h"

/**
 * main - beginning of the point.
 * @ac: counting argument.
 * @av: vector of the argument.
 *
 * Return: if success 0, if it fails 1
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int ca = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (ca)
			: "r" (ca));

	if (ac == 2)
	{
		ca = open(av[1], O_RDONLY);
		if (ca == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readca = ca;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
