#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* MACROS */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define FLUSH_BUFFER -1

#define COMMAND_NORM	0
#define COMMAND_OR		1
#define COMMAND_AND		2
#define COMMAND_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define FILE_HISTORY	".simple_shell_history"
#define MAXIMUM_HISTORY	4096

extern char **environ;

/* info_struct */

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: string generated from getline containing arguements
 * @argv: array of strings generated from arg
 * @path: string path for the current command
 * @argc: the argument count
 * @line_count: error count
 * @error_num: error code for exit(s)
 * @linecount_flag: counts line of input
 * @filename: program filename
 * @list_environ: linked list local copy of environ
 * @environ: cmodified copy of environ from LL env
 * @list_history: history node
 * @list_alias: alias node
 * @environ_changed: changes an environ
 * @status: return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @read_fd: fd from which line input is read
 * @history_count: history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int error_num;
	int linecount_flag;
	char *filename;
	list_t *list_environ;
	list_t *list_history;
	list_t *list_alias;
	char **environ;
	int environ_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int read_fd;
	int history_count;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains builtin strings and related functions
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* PROTOTYPES*/

/* shell_loop */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* parser.c */
int _cmd(info_t *, char *);
char *duplicate_char(char *, int, int);
char *pathfinder(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void custom_put(char *);
int custom_putschar(char);
int custom_put_fd(char c, int fd);
int custom_puts_fd(char *str, int fd);

/*  string.c */
int custom_strlen(char *);
int custom_strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *custom_strcat(char *, char *);

/* string1.c */
char *custom_strcpy(char *, char *);
char *custom_strdup(const char *);
void custom_puts(char *);
int custom_putchar(char);

/* exits.c */
char *custom_strncpy(char *, char *, int);
char *custom_strncat(char *, char *, int);
char *custom_strchr(char *, char);

/* tokenizer.c */
char **strn_tk(char *, char *);
char **str_tk(char *, char);

/* realloc.c */
char *memory_set(char *, char, unsigned int);
void file_free(char **);
void *re_allocate(void *, unsigned int, unsigned int);

/* memory.c */
int buffer_free(void **);

/* atoi.c */
int custom_interactive(info_t *);
int custom_delimeter(char, char *);
int custom_alphabet(int);
int custom_string_to_int(char *);

/* errors1.c */
int string_to_int(char *);
void printerror(info_t *, char *);
int print_dir(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin.c */
int custom_exit(info_t *);
int custom_cd(info_t *);
int custom_help(info_t *);

/* builtin1.c */
int custom_history(info_t *);
int custom_alias(info_t *);

/* getline.c */
ssize_t get_input(info_t *);
int get_line(info_t *, char **, size_t *);
void sign_int_handler(int);

/* getinfo.c */
void info_cleared(info_t *);
void info_set(info_t *, char **);
void info_freed(info_t *, int);

/* environ.c */
char *custom_getenv(info_t *, const char *);
int custom_env(info_t *);
int custom_set_env(info_t *);
int custom_unset_env(info_t *);
int custom_populate_env_list(info_t *);

/* getenv.c */
char **custom_get_environ(info_t *);
int custom_unsetenv(info_t *, char *);
int custom_setenv(info_t *, char *, char *);

/* history.c */
char *history_file(info_t *info);
int save_history(info_t *info);
int load_history(info_t *info);
int history_list(info_t *info, char *buf, int linecount);
int history_numbered(info_t *info);

/* lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *node_end(list_t **, const char *, int);
size_t print_list_string(const list_t *);
int node_at_index_deleted(list_t **, unsigned int);
void list_freed(list_t **);

/* lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t list_print(const list_t *);
list_t *start_node_with(list_t *, char *, char);
ssize_t node_index(list_t *, list_t *);

/* vars.c */
int chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int alias_replaced(info_t *);
int vars_replaced(info_t *);
int string_replaced(char **, char *);

#endif
