#include "shell.h"

/**
 * custom_interactive - true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int custom_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->read_fd <= 2);
}

/**
 * custom_delimeter - checks if a character is a delimeter
 * @c: character to check
 * @delim: delimeter string
 * Return: 1 on true, 0 on false
 */
int custom_delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * custom_alphabet - checks for alphabetic characters
 * @c: character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int custom_alphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * custom_string_to_int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int custom_string_to_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
