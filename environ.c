#include "shell.h"

/**
 * custom_env - prints the current environment variables
 * @info: struct containing potential arguments used to maintain
 *        the const function prototype.
 * Return: 0
 */
int custom_env(info_t *info)
{
	print_list_string(info->list_environ);
	return (0);
}

/**
 * custom_getenv - gets the value of an environent variable
 * @info: Struct containing potential arguments
 * @name: environment variable name
 *
 * Return: the value
 */
char *custom_getenv(info_t *info, const char *name)
{
	list_t *node = info->list_environ;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * custom_set_env - initializes a new environment variable,
 *                  or modifies an existing one
 * @info: struct containing potential arguments
 * Return: 0
 */
int custom_set_env(info_t *info)
{
	if (info->argc != 3)
	{
		custom_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (custom_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * custom_unset_env - removes an environments variable
 * @info: structure containing potential arguments used to maintain
 *        const function prototype.
 * Return: Always 0
 */
int custom_unset_env(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		custom_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		custom_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * custom_populate_env_list - populates environment linked list
 * @info: Structure containing potential arguments used to maintain
 *          constant function prototype.
 * Return: 0
 */
int custom_populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		node_end(&node, environ[i], 0);
	info->list_environ = node;
	return (0);
}
