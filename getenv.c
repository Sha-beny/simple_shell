#include "shell.h"

/**
 * custom_get_environ - returns the string array of environment
 * @info: struct containing potential arguments used to maintain
 *          const function prototype.
 * Return: 0
 */
char **custom_get_environ(info_t *info)
{
	if (!info->environ || info->environ_changed)
	{
		info->environ = list_to_strings(info->list_environ);
		info->environ_changed = 0;
	}

	return (info->environ);
}

/**
 * custom_unsetenv - removes environment variable
 * @info: struct containing potential arguments used to maintain
 *        const function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: string environment variable property
 */
int custom_unsetenv(info_t *info, char *var)
{
	list_t *node = info->list_environ;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->environ_changed = node_at_index_deleted(&(info->list_environ), i);
			i = 0;
			node = info->list_environ;
			continue;
		}
		node = node->next;
		i++;
		}
	return (info->environ_changed);
}

/**
 * custom_setenv - initializes a new environment variable,
 *             or modifies an existing one
 * @info: struct containing potential arguments used to maintain
 *        const function prototype.
 * @var: the string environment variable property
 * @value: the string environment variable value
 *  Return: 0
 */
int custom_setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(custom_strlen(var) + custom_strlen(value) + 2);
	if (!buf)
		return (1);
	custom_strcpy(buf, var);
	custom_strcat(buf, "=");
	custom_strcat(buf, value);
	node = info->list_environ;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->environ_changed = 1;
			return (0);
		}
		node = node->next;
	}
	node_end(&(info->list_environ), buf, 0);
	free(buf);
	info->environ_changed = 1;
	return (0);
}
