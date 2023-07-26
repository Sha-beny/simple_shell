#include "shell.h"

/**
 * custom_exit - exits the shell program
 * @info: struct containing potential arguments
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int custom_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = string_to_int(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			printerror(info, "Illegal number: ");
			custom_puts(info->argv[1]);
			custom_putchar('\n');
			return (1);
		}
		info->error_num = string_to_int(info->argv[1]);
		return (-2);
	}
	info->error_num = -1;
	return (-2);
}

/**
 * custom_cd - changes the directory of the current process
 * @info: struct containing potential arguments
 * Return: 0
 */
int custom_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		custom_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = custom_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = custom_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (custom_strcmp(info->argv[1], "-") == 0)
	{
		if (!custom_getenv(info, "OLDPWD="))
		{
			custom_puts(s);
			custom_putchar('\n');
			return (1);
		}
		custom_puts(custom_getenv(info, "OLDPWD=")), custom_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = custom_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		printerror(info, "can't cd to ");
		custom_puts(info->argv[1]), custom_putchar('\n');
	}
	else
	{
		custom_setenv(info, "OLDPWD", custom_getenv(info, "PWD="));
		custom_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * custom_help - changes the directory of the current process to (man_help)
 * @info: struct containing potential argument
 * Return: 0
 */
int custom_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	custom_puts("help call works. Function not yet implemented \n");
	if (0)
		custom_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
