#include "main.h"

/**
 * _clear_info - initializes info_t struct
 * @infos: struct address
 */
void _clear_info(infos_t *infos)
{
	infos->arg = NULL;
	infos->argv = NULL;
	infos->path = NULL;
	infos->argc = 0;
}

/**
 * _set_info - initializes info_t struct
 * @infos: struct address
 * @av: argument vector
 */
void _set_info(infos_t *infos, char **av)
{
	int i = 0;

	infos->fname = av[0];
	if (infos->arg)
	{
		infos->argv = strtow(infos->arg, " \t");
		if (!infos->argv)
		{

			infos->argv = malloc(sizeof(char *) * 2);
			if (infos->argv)
			{
				infos->argv[0] = _strdup(infos->arg);
				infos->argv[1] = NULL;
			}
		}
		for (i = 0; infos->argv && infos->argv[i]; i++)
			;
		infos->argc = i;

		_replace_alias(infos);
		_replace_vars(infos);
	}
}

/**
 * _free_info - frees info_t struct fields
 * @infos: struct address
 * @all: true if freeing all fields
 */
void _free_info(infos_t *infos, int all)
{
	free_strings(infos->argv);
	infos->argv = NULL;
	infos->path = NULL;
	if (all)
	{
		if (!infos->cmd_buffer)
			free(infos->arg);
		if (infos->env)
			free_list(&(infos->env));
		if (infos->history)
			free_list(&(infos->history));
		if (infos->alias)
			free_list(&(infos->alias));
		free_strings(infos->environ);
			infos->environ = NULL;
		bfree((void **)infos->cmd_buffer);
		if (infos->readfd > 2)
			close(infos->readfd);
		_putchar(BUFFER_FLUSH);
	}
}
