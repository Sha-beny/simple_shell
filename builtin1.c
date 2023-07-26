#include "shell.h"

/**
 * custom_history - displays history list
 * @info: struct containing potential arguments used to maintain
 *        const function prototype.
 *  Return: 0
 */
int custom_history(info_t *info)
{
	list_print(info->list_history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: string alias
 *
 * Return: success(0), error(1)
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = custom_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = node_at_index_deleted(&(info->list_alias),
		node_index(info->list_alias, start_node_with(info->list_alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: string alias
 *
 * Return: success(0), error(1)
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = custom_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (node_end(&(info->list_alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: success(0), error(1)
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = custom_strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		custom_putchar(*a);
		custom_putchar('\'');
		custom_puts(p + 1);
		custom_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * custom_alias - imitates the alias builtin (man alias)
 * @info: struct containing potential arguments
 * Return: 0
 */
int custom_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->list_alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = custom_strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(start_node_with(info->list_alias, info->argv[i], '='));
	}

	return (0);
}
