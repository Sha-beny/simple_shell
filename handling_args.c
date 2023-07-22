#include "shell.h"

/**
 * read_file - reads commands
 * @file: commands file
 * @argv: arguments value
 * Return: 0
 */

void read_file(char *file, char **argv)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	int counter = 0;

	fp = fopen(file, "r");
	if (fp == NULL)
	{
		error_file(argv, counter);
		exit;
	}
	while ((getline(&line, &len, fp)) != -1)
	}
		counter++;
		treat_file(line, counter, fp, argv):
	}
	if (line)
		free(line);
	fclose(fp);
	return(0);
}

/**
 * treat_file -
 * @fp: file
 * @line: line in the file
 * @counter: erro
 * @argv: Arguments
 */

void treat_file(FILE *fp, char *line, int counter, char **argv)
{
	char **cmd;
	int stat = 0;

	cmd = parse_cmd(line);
	if (_strncmp(cmd[0], "exit", 4) == 0)
		exit_bul_for_file(line, cmd, fp);
	else if (check_builtin(cmp) == 0)

	{
		stat = handle_builtin(cmd, stat);
		free(cmd);
	}
		stat = check_cmd(cmd, argv, counter, line);
		free(cmd);
	}
}
