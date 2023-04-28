#ifndef SHELL_H_
#define SHELL_H_

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>


#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main functions  */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_mem_size, unsigned int new_mem_size);
char **_strtok(char *line, char *delimit);
char *get_location(char *cmd);
list_t *get_dir_path(char *pth);
int exec_cmd(char **args, char **first);
void free_list(list_t *head);
char *int_to_str(int num);
char *fill_dir_path(char *pth);

/* Input functions */
void partition_line(char **line, ssize_t length);
void var_replacement(char **args, int *exe_opt);
char *get_cmd_args(char *line, int *exe_opt);
int call_cmd_args(char **args, char **frnt, int *exe_opt);
int run_cmd_args(char **args, char **frnt, int *exe_opt);
int handle_cmd_args(int *exe_opt);
int check_cmd_args(char **args);
void free_args_mem(char **args, char **frnt);
char **replace_aliases(char **args);


/* Builtins shellin functions */
int (*get_builtin(char *command))(char **args, char **front);
int shellin_exit(char **args, char **front);
int shellin_print_env(char **args, char __attribute__((__unused__)) **front);
int shellin_set_env(char **args, char __attribute__((__unused__)) **front);
int shellin_del_env(char **args, char __attribute__((__unused__)) **front);
int shellin_cd(char **args, char __attribute__((__unused__)) **front);
int shellin_alias(char **args, char __attribute__((__unused__)) **front);
int shellin_help(char **args, char __attribute__((__unused__)) **front);

/*Help*/
void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_env(void);
void help_help(void);
void help_setenv(void);
void help_unsetenv(void);

/* Environment var functions */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/*Tokenz functions*/
int token_count(char *str, char *delimit);
int token_length(char *str, char *delimit);

/* Error Functions */
int create_custom_stderr(char **args, int err);
char *error_env(char **args);
char *error_alias(char **args);
char *error_exit(char **args);
char *error_cd(char **args);
char *error_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* String functions */
int _strlength(const char *c);
char *_strcat(char *des, const char *sstr);
char *_strncat(char *des, const char *sstr, size_t q);
char *_strcpy(char *des, const char *sstr);
char *_strchar(char *q, char r);
int _strsub(char *c, char *kubali);
int _strcmpr(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t q);

/* Linkedlist  */
alias_t *add_end_alias(alias_t **head, char *name, char *value);
void free_list_alias(alias_t *head);
list_t *add_end_node(list_t **head, char *dir_path);
void free_list(list_t *head);

/*miscellaneous functions*/
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);
ssize_t get_new_length(char *line);
void logic_operator(char *line, ssize_t *new_length);
char *get_env_var_value(char *start, int length);
char *get_pid(void);
int cant_open_err(char *file_pth);
int run_file_commands(char *file_path, int *exe_opt);

#endif
