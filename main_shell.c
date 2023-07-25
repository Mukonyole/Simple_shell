#include "shell.h"

/**
 * main - entry point of program
 * @ac: argument count
 * @av: argument vector
 * Return: 0 success, 1 error
 */
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT};
	/* single element struct */
	int fd = 2;
	/* int variable */
	asm ("mov %1, %0\n\t"
		/* perform bitwise op to fd */
		"add $3, %0"
		/* moves val of fd into o/p register and adds 3 to it */
		: "=r" (fd)
		: "r" (fd));
	/* specifies I/p and O/p operands */
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		/* open file */
		if (fd == -1)
		{
			if (errno == EACCES)
				/* check if file can be openeded */
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(":0: Can't open ");
				/* error message */
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
				/* exit code */
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
		/* storing fd after openning file */
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
	/* populate env var list, cmd list*/
}
