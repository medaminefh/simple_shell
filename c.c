#include "main.h"

/**
 * _is_chain - test if current char in buffer is a chain delimeter
 * @infos: the parameter struct
 * @buffer: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int _is_chain(infos_t *infos, char *buffer, size_t *p)
{
	size_t j = *p;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		infos->cmd_buffer_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		infos->cmd_buffer_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		infos->cmd_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * _check_chain - checks we should continue chaining based on last status
 * @infos: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void _check_chain(infos_t *infos, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (infos->cmd_buffer_type == CMD_AND)
	{
		if (infos->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (infos->cmd_buffer_type == CMD_OR)
	{
		if (!infos->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * _replace_alias - replaces an aliases in the tokenized string
 * @infos: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_alias(infos_t *infos)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(infos->alias, infos->argv[0], '=');
		if (!node)
			return (0);
		free(infos->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		infos->argv[0] = p;
	}
	return (1);
}

/**
 * _replace_vars - replaces vars in the tokenized string
 * @infos: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_vars(infos_t *infos)
{
	int i = 0;
	list_t *node;

	for (i = 0; infos->argv[i]; i++)
	{
		if (infos->argv[i][0] != '$' || !infos->argv[i][1])
			continue;

		if (!_strcmp(infos->argv[i], "$?"))
		{
			_replace_string(&(infos->argv[i]),
				_strdup(convert_number(infos->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infos->argv[i], "$$"))
		{
			_replace_string(&(infos->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(infos->env, &infos->argv[i][1], '=');
		if (node)
		{
			_replace_string(&(infos->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		_replace_string(&infos->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * _replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int _replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
