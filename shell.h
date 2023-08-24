/**
 * SHELL.H
 * Authour: OBIAKOR LUCY(lucyobiakor@gmail.com)
 * NUATIN AYOOLA
 */

#ifndef SHELL_H
#define SHELL_H

/******HEADER FILES******/
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>

/****** for read/write buffers ******/
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/****** for command chaining ******/
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/****** for convert_number() ******/
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/****** 1 if using system getline() ******/
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


/**
 * struct liststr - singly linked list function.
 * @num: the number of the field.
 * @str: a string found.
 * @next: pointing to the next node.
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * allows uniform prototype for function pointer struct.
 * struct passinfo - containing pseudo-arguements to pass into a function,
 * @argc: the argument counting
 * @line_count: the error counting
 * @err_num: the error code for exit()s
 * @linecount_flag: if on counting this line of input.
 * @environ: custom modified copying of environ from LL env.
 * @history: the history node.
 * @alias: the alias node.
 * @arg: a string generated from getline contains arguements.
 * @argv:an array of strings generating from arg
 * @path: a string path for the current command.
 * @fname: the program filename.
 * @env: linked list local copying of environ.
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line inputs.
 * @histcount: the history line number counting.
 * @env_changed: on if environ was chaning.
 * @status: the return status of the last exec'd commands.
 * @cmd_buf: address of pointer to cmd_buf, on if chained.
 */
typedef struct passinfo
{
	int argc;
	unsigned int line_count;
	char **argv;
	char *path;
	int env_changed;
	int status;
	char *arg;
	char *fname;
	list_t *env;
	list_t *history;
	int err_num;
	int linecount_flag;
	list_t *alias;
	char **environ;

	int readfd;
	char **cmd_buf; /**pointer to cmd ;chain buffer,for memory mangement**/
	int histcount;
	int cmd_buf_type; /****** CMD_type ||, &&, ; ******/
} info_t;

#define INFO_INIT
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
 * struct builtin - containing a builtin string and relating function
 * @type: the builtin commanding flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/****** _shloop.c ******/
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int hsh(info_t *, char **);

/****** _parser.c ******/
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);

/****** loophsh.c ******/
int loophsh(char **);

/****** _errors.c ******/
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _eputchar(char);
void _eputs(char *);

/****** _string.c ******/
char *_strcat(char *, char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
int _strlen(char *);

/****** _string1.c ******/
int _putchar(char);
char *_strdup(const char *);
void _puts(const char *str);
char *_strcpy(char *dest, const char *src);

/****** _exits.c ******/
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);

/****** _tokenizer.c ******/
char **tokenize_string(char *str, char *delim);
//char **strtow(char *, char *);
//char **strtow2(char *, char);

/****** _realloc.c ******/
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);

/****** _errors1.c ******/
int print_d(int, int);
char *convert_number(long int, int, int);
void print_error(info_t *, char *);
void remove_comments(char *);
int _erratoi(char *);

/****** _atoi.c ******/
int _atoi(char *);
int is_delim(char, char *);
int interactive(info_t *);
int _isalpha(int);

/****** _builtin1.c ******/
int _myalias(info_t *);
int _myhistory(info_t *);

/****** _memory.c ******/
int bfree(void **);

/****** _getinfo.c ******/
void set_info(info_t *, char **);
void clear_info(info_t *);
void free_info(info_t *, int);

/****** _builtin.c ******/
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/****** _environ.c ******/
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
char *_getenv(info_t *, const char *);
int populate_env_list(info_t *);
int _myenv(info_t *);

/****** _getline.c ******/
int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);

/****** _lists.c ******/
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
list_t *add_node(list_t **, const char *, int);

/****** _history.c ******/
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int write_history(info_t *info);
int renumber_history(info_t *info);
char *get_history_file(info_t *info);

/****** _getenv.c ******/
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

/****** _lists1.c ******/
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
size_t list_len(const list_t *);

/****** _vars.c ******/
int replace_string(char **, char *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int is_chain(info_t *, char *, size_t *);
int replace_string(char **, char *);

#endif/***** _SHELL_H_ *****/
