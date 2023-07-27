#include "shell.h"

/**
 * hsh - our main shell loop
 * @info: parameter & return info struct
 * @av: argument vector from main()
 *
 * Return: success(0), error(1), or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		info_cleared(info);
		if (custom_interactive(info))
			custom_puts("$ ");
		custom_putchar(FLUSH_BUFFER);
		r = get_input(info);
		if (r != -1)
		{
			info_set(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (custom_interactive(info))
			custom_putchar('\n');
		info_freed(info, 0);
	}
	save_history(info);
	info_freed(info, 1);
	if (!custom_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->error_num == -1)
			exit(info->status);
		exit(info->error_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: parameter & return info struct
 *
 * Return: (-1) if builtin not found,
 * (0) if builtin executed successfully,
 * (1) if builtin found but not successful,
 * (2) if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", custom_exit},
		{"env", custom_env},
		{"help", custom_help},
		{"history", custom_history},
		{"setenv", custom_set_env},
		{"unsetenv", custom_unset_env},
		{"cd", custom_cd},
		{"alias", custom_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (custom_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - find a command in PATH
 * @info: parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!custom_delimeter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = pathfinder(info, custom_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((custom_interactive(info) || custom_getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && _cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printerror(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an executable thread to run cmd
 * @info: parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, custom_get_environ(info)) == -1)
		{
			info_freed(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printerror(info, "Permission denied\n");
		}
	}
	}
