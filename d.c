#include "main.h"

/**
 * _getenv - gets the value of an environ variable
 * @infos: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(infos_t *infos, const char *name)
{
	list_t *n = infos->env;
	char *p;

	while (n)
	{
		p = starts_with(n->str, name);
		if (p && *p)
			return (p);
		n = n->next;
	}
	return (NULL);
}

/**
 * _my_env - prints the current environment
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _my_env(infos_t *infos)
{
	print_list_str(infos->env);
	return (0);
}



/**
 * _my_setenviron - Initialize a new environment variable,
 *             or modify an existing one
 * @infos: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _my_setenviron(infos_t *infos)
{
	if (infos->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infos, infos->argv[1], infos->argv[2]))
		return (0);
	return (1);
}

/**
 * populate_env_list - populates env linked list
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(infos_t *infos)
{
	list_t *n = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&n, environ[i], 0);
	infos->env = n;
	return (0);
}
