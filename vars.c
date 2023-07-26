#include "shell.h"

/**
 * chain - tests the current char in buffer if it is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: (1) if chain delimeter, (0) otherwise
 */

int chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = COMMAND_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = COMMAND_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = COMMAND_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks if we should continue chaining based on last stat
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: start position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == COMMAND_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == COMMAND_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * alias_replaced - replaces an alias in tokenized string
 * @info: the parameter struct
 *
 * Return: 1 on replace, 0 otherwise
 */
int alias_replaced(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = start_node_with(info->list_alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = custom_strchr(node->str, '=');
		if (!p)
			return (0);
		p = custom_strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * vars_replaced - replace vars in tokenized string
 * @info: the parameter struct
 *
 * Return: 1 on replace, 0 otherwise
 */
int vars_replaced(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!custom_strcmp(info->argv[i], "$?"))
		{
			string_replaced(&(info->argv[i]),
					custom_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!custom_strcmp(info->argv[i], "$$"))
		{
			string_replaced(&(info->argv[i]),
					custom_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = start_node_with(info->list_environ, &info->argv[i][1], '=');
		if (node)
		{
			string_replaced(&(info->argv[i]),
					custom_strdup(custom_strchr(node->str, '=') + 1));
			continue;
		}
		string_replaced(&info->argv[i], custom_strdup(""));

	}
	return (0);
}

/**
 * string_replaced - replaces a string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 on replace, 0 otherwise
 */
int string_replaced(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
