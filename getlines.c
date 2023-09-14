#include "main.h"

/**
 * input_buf - buffers chained commands
 * @infos: parameter struct
 * @buffer: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(infos_t *infos, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
		r = getline(buffer, &len_p, stdin);
		r = _getline(infos, buffer, &len_p);

		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			infos->line_count_flag = 1;
			remove_comments(*buffer);
			build_history_list(infos, *buffer, infos->histcount++);
			{
				*len = r;
				infos->cmd_buffer = buffer;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @infos: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(infos_t *infos)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buffer_p = &(infos->arg), *p;

	_putchar(BUFFER_FLUSH);
	r = input_buf(infos, &buffer, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;

		_check_chain(infos, buffer, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (_is_chain(infos, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			infos->cmd_buffer_type = CMD_NORM;
		}

		*buffer_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buffer_p = buffer; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @infos: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(infos_t *infos, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(infos->readfd, buffer, WRITE_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @infos: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(infos_t *infos, char **ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t a = 0, b = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		b = *length;
	if (i == len)
		i = len = 0;

	a = read_buf(infos, buffer, &len);
	if (a == -1 || (a == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, b, b ? b + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (b)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);

	b += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = b;
	*ptr = p;
	return (b);
}

/**
 * _sigintHandler - blocks ctrl-C
 * @num: the signal number
 *
 * Return: void
 */
void _sigintHandler(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}
