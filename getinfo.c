#include "shell.h"

/**
 * info_cleared - initializes the info_t struct
 * @info: the struct address
 */
void info_cleared(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * info_set - initializes info_t struct
 * @info: the struct address
 * @av: argument vector
 */
void info_set(info_t *info, char **av)
{
	int i = 0;

	info->filename = av[0];
	if (info->arg)
	{
		info->argv = strn_tk(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = custom_strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		alias_replaced(info);
		vars_replaced(info);
	}
}

/**
 * info_freed - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void info_freed(info_t *info, int all)
{
	file_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->environ)
			list_freed(&(info->list_environ));
		if (info->list_history)
			list_freed(&(info->list_history));
		if (info->list_alias)
			list_freed(&(info->list_alias));
		file_free(info->environ);
			info->environ = NULL;
		buffer_free((void **)info->cmd_buf);
		if (info->read_fd > 2)
			close(info->read_fd);
		custom_putchar(FLUSH_BUFFER);
	}
}
