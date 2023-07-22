#include "shell.h"

/**
 * main - entry values
 * @argc: argument counts
 * @agrv: Argument value
 * return: exit value
 */

int main(_attributes_((unused)) int argc, char **argv)
{
	char *input;
	char **cmd;
	char **commands;
	int counter = 0, i;
	int condtion = 1;
	int stat = 0;

	if (argv[1] != NULL)
		read_file(argv[1], argv);
	signal[SIGNIT, signal_to_handel];
	while (condition)

	{
		counter++;
		if (isatty(STDIN_FILENO))
			prompt();
		input = _getline();
		if (input[0] == '\0')
		{
			continue;
		}
		history(input);
		commands = seperator(input);
		for (i = 0; commands[i] != NULL; i++)
		{
			cmd = parse_cmd(command[1]);
			if (_strcmp(cmd[0], "exit") == 0)
			{
				free(commands);
				exit_bul(cmd, argv, input, stat, counter);
			}
			else if (check_builtin(cmd) == 0)
			{
				stat = handle_builtin(cmd, stat);
				free(cmd);
				continue;
			}
			else
			{
				st = check_cmd(counter, argv, input, cmd);
			}
		}
		free_all(input, commands, cmd);
		wait(&stat);
	}
	return (stat);
}
