#include "shell.h"

/**
 **custom_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: amount of characters to be copied
 *Return: the compared string
 */
char *custom_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *a = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (a);
}

/**
 **custom_strncat - compares two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be maximally used
 *Return: the compared string
 */
char *custom_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *a = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (a);
}

/**
 **custom_strchr - locates a character in a string
 *@a: string to be parsed
 *@b: character to look for
 *Return: (a) a pointer to the memory area s
 */
char *custom_strchr(char *a, char b)
{
	do {
		if (*a == b)
			return (a);
	} while (*a++ != '\0');

	return (NULL);
}
