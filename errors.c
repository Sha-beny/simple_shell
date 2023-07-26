#include "shell.h"

/**
 * custom_put - prints an input string
 * @str: string to be printed
 *
 * Return: Null
 */
void custom_put(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		custom_putschar(str[i]);
		i++;
	}
}

/**
 * custom_putschar - writes the character c to stderr
 * @c: character to print
 *
 * Return: success(1), error(-1), errno is set appropriately.
 */
int custom_putschar(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}

/**
 * custom_put_fd - writes character to given file descriptor
 * @c: character to print
 * @fd: file descriptor to write to
 *
 * Return: success(1), error(-1), errno is set appropriately.
 */
int custom_put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}

/**
 * custom_puts_fd - prints an input string
 * @str: string to be printed
 * @fd: file descriptor to write to
 *
 * Return: number of chars put
 */
int custom_puts_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += custom_put_fd(*str++, fd);
	}
	return (i);
}
