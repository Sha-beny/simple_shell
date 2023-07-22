#include "shell.h"

/**
 * check_delim - check if a character matches any char in the delimiter string
 * @c: char to check
 * @delim: delimiter string
 * return: 1 if character matches delimiter, 0 it does'nt
 */

unsigned int check_delim(char c, const char *delim)
{
	unsigned int i;

	for (i = 0; delim[i] != '\0'; i++)
	{
		if (c == delim[i])
			return (1);
	}
	return (0);
}

/**
 * _strtok - tokenizes a string
 * @str: string to tokenizes
 * @delim: delimter strinf
 * return: pointer to the next token or null if there are no more token
 */

char *_strtok(char *str, const char *delim)
{
	static char *ts;
	static char *nt;
	unsigned int i;

	if (str != NULL)
		nt = str;
	ts = nt;
	if (ts == NULL)
		return (NULL);
	for (i = 0; ts[i] != '\0'; i++)
	{
		if (check_delim(ts[i], delim) == 0)
			break;
	}
	if (nt[i] == '\0' || nt[i] == '#')
	{
		nt(NULL);
		return (NULL);
	}
	ts = nt + i;
	nt = ts;
	for (i = 0; nt[i] != '\0'; i++)
	{
		if (check_delim(nt[i], delim) == 1)
			break;
	}
	if (nt[i] == '\0')
		nt = NULL;
	else
	{
		nt[i] == '\0';
		nt = nt + i + 1;
		if (*nt == '\0')
			nt = NULL;
	}
	return (ts);
}
