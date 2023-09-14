#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

/* for read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1
#define MAX_INT 4000
/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE	"._history"

extern char **environ;

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
 *struct passinfo - contains pseudo-arguements to pass into a function,
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
typedef struct passinfo
{
	char **argv;
	char *arg;
	int argc;
	unsigned int line_count;
	int err_num;
	char *path;
	int line_count_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buffer_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} infos_t;

#define INIT_INFO \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

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


char *_getenv(infos_t *, const char *);
int _my_env(infos_t *);
int _my_setenv(infos_t *);
int _my_unsetenv(infos_t *);
int populate_env_list(infos_t *);

/* env2.c module */
char **get_environ(infos_t *);
int _unsetenv(infos_t *, char *);
int _set_env(infos_t *, char *, char *);

int _is_chain(infos_t *, char *, size_t *);
void _check_chain(infos_t *, char *, size_t *, size_t, size_t);
int _replace_alias(infos_t *);
int _replace_vars(infos_t *);
int _replace_string(char **, char *);

/* hsh.c */
int shell(infos_t *, char **);
int find_builtin(infos_t *);
void find_cmd(infos_t *);
void fork_cmd(infos_t *);

/* path.c */
int is_cmd(infos_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(infos_t *, char *, char *);

ssize_t get_input(infos_t *);
int _getline(infos_t *, char **, size_t *);
void _sigintHandler(int);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtow2(char *, char);

char **strtow(char *, char *);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int bfree(void **);

int interactive(infos_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
void print_error(infos_t *, char *);
int print_d(int, int);

/* builtin_emulators.c */
int _my_help(infos_t *);
int _my_exit(infos_t *);
int _my_cd(infos_t *);

ssize_t get_input(infos_t *);
int _getline(infos_t *, char **, size_t *);
void sigintHandler(int);

/* info.c module */
void _clear_info(infos_t *);
void _free_info(infos_t *, int);
void _set_info(infos_t *, char **);


list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
size_t print_list_str(const list_t *);
void free_list(list_t **);

/* liststr2.c module */
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
size_t list_len(const list_t *);
ssize_t get_node_index(list_t *, list_t *);

char *get_history_file(infos_t *info);
int write_history(infos_t *info);
int read_history(infos_t *info);
int build_history_list(infos_t *info, char *, int);
int renumber_history(infos_t *info);

#endif
