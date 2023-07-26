#include "shell.h"

/**
 * buffer_free - frees a pointer and Null's the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 on freed, otherwise 0.
 */
int buffer_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
