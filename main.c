#include "shell.h"

/**
 * main - Entry point of the program.
 * @ac: Count of command-line arguments.
 * @av: Vector of command-line arguments.
 *
 * Description: This function is the entry point of the program.
 * It takes command line arguments and returns an exit status.
 *
 * Return: If successful, returns 0. If it fails, returns 1.
 */
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT};
	int fd = 2;

	__asm__("mov %1, %0\n\t"
			"add $3, %0"
			: "=r"(fd)
			: "r"(fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
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
		info->readfd = fd;
	}

	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
