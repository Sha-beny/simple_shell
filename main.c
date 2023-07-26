#include "shell.h"

/**
 * main - start point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: success(0), error(1)
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				custom_puts(av[0]);
				custom_puts(": 0: Can't open ");
				custom_puts(av[1]);
				custom_putchar('\n');
				custom_putchar(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_fd = fd;
	}
	custom_populate_env_list(info);
	load_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
