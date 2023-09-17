#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

/* for command chaining */
#define SHELL_NORM 0
#define SHELL_OR 1
#define SHELL_AND 2
#define SHELL_CHAIN 3

/* for read/write buffers */
#define BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* for convert_number() */
#define CONVERT_LOWER 1
#define CONVERT_UNS 2

#define HISTORY_FILE	"._history"
#define HISTORY_MAX	4096

extern char **environ;



/**
 * struct lista - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct lista
{
	int num;
	char *str;
	struct lista *next;
} list_t;

#define INIT_INFORMATIONS \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct passinginfos - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@line_count_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buffer: address of pointer to cmd_buf, on if chaining
 *@cmd_buffer_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinginfos
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int line_count_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buffer;
	int cmd_buffer_type;
	int readfd;
	int histcount;
} infos_t;



/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(infos_t *);
} builtin_table;


/* hsh.c */
int shell(infos_t *, char **);
int find_builtin(infos_t *);
void find_command(infos_t *);
void fork_shell(infos_t *);

/* path.c */
int is_command(infos_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(infos_t *, char *, char *);

/* err_string_functions.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_functions2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* env.c module */
char *_getenv(infos_t *, const char *);
int _my_env(infos_t *);
int _my_setenviron(infos_t *);
int _my_unsetenv(infos_t *);
int populate_env(infos_t *);

/* string_functions3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* string_functions4.c */
char **strtow(char *, char *);

/* memory_functions */
char *_memset(char *, char, unsigned int);
void free_strings(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int bfree(void **);

/* info.c module */
void _clear_info(infos_t *);
void _set_info(infos_t *, char **);
void _free_info(infos_t *, int);


/* more_functions.c */
int is_interactive(infos_t *);
int is_del(char, char *);
int _isalpha(int);
int _atoi(char *);

/* more_functions2.c */
int _errtoi(char *);
void printf_error(infos_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin_emulators.c */
int _my_exit(infos_t *);
int _my_cd(infos_t *);

/* builtin_emulators2.c */
int _my_hist(infos_t *);

/* getline.c module */
ssize_t get_input(infos_t *);
int _getline(infos_t *, char **, size_t *);
void _sigintHandler(int);

/* env2.c module */
char **get_env(infos_t *);
int _unsetenv(infos_t *, char *);
int _setenv(infos_t *, char *, char *);

/* file_io_functions.c */
char *get_hist_file(infos_t *);
int write_hist(infos_t *);
int read_hist(infos_t *);
int build_hist_list(infos_t *, char *, int);
int renumber_hist(infos_t *);

/* liststr.c module */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node(list_t **, unsigned int);
void free_list(list_t **);

/* liststr2.c module */
size_t list_len(const list_t *);
char **list_to_str(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* chain.c */
int _is_chain(infos_t *, char *, size_t *);
void _check_chain(infos_t *, char *, size_t *, size_t, size_t);
int _replace_alias(infos_t *);
int _replace_vars(infos_t *);
int _replace_string(char **, char *);

#endif
