#include "shell.h"

/**
 * history_file - gets the history of a file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *history_file(info_t *info)
{
	char *buf, *dir;

	dir = custom_getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (custom_strlen(dir) + custom_strlen(FILE_HISTORY) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	custom_strcpy(buf, dir);
	custom_strcat(buf, "/");
	custom_strcat(buf, FILE_HISTORY);
	return (buf);
}

/**
 * save_history - creates a file or make appends to an existing one
 * @info: the parameter struct
 *
 * Return: success(1), else -1
 */
int save_history(info_t *info)
{
	ssize_t fd;
	char *filename = history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->list_history; node; node = node->next)
	{
		custom_puts_fd(node->str, fd);
		custom_put_fd('\n', fd);
	}
	custom_put_fd(FLUSH_BUFFER, fd);
	close(fd);
	return (1);
}

/**
 * load_history - reads history from a file
 * @info: the parameter struct
 *
 * Return: (history_count) on success, 0 otherwise
 */
int load_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		history_list(info, buf + last, linecount++);
	free(buf);
	info->history_count = linecount;
	while (info->history_count-- >= MAXIMUM_HISTORY)
		node_at_index_deleted(&(info->list_history), 0);
	history_numbered(info);
	return (info->history_count);
}

/**
 * history_list - adds entries to a history linked list
 * @info: struct containing potential arguments
 * @buf: buffer
 * @linecount: the history linecount, history_count
 *
 * Return: 0
 */
int history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->list_history)
		node = info->list_history;
	node_end(&node, buf, linecount);

	if (!info->list_history)
		info->list_history = node;
	return (0);
}

/**
 * history_numbered - renumber the history linked list after changes
 * @info: struct containing potential arguments
 *
 * Return: the new history_count
 */
int history_numbered(info_t *info)
{
	list_t *node = info->list_history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->history_count = i);
}
