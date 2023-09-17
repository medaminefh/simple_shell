#include "main.h"

/**
 * get_history_file - gets the history file
 * @infos: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(infos_t *infos)
{
	char *buffer, *dir;

	dir = _getenv(infos, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HISTORY_FILE);
	return (buffer);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @infos: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(infos_t *infos)
{
	ssize_t fd;
	char *filename = get_history_file(infos);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = infos->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @infos: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(infos_t *infos)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL;
	char *filename = get_history_file(infos);

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
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(infos, buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(infos, buffer + last, linecount++);
	free(buffer);
	infos->histcount = linecount;
	while (infos->histcount-- >= HISTORY_MAX)
		delete_node(&(infos->history), 0);
	renumber_history(infos);
	return (infos->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @infos: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(infos_t *infos, char *buffer, int linecount)
{
	list_t *node = NULL;

	if (infos->history)
		node = infos->history;
	add_node_end(&node, buffer, linecount);

	if (!infos->history)
		infos->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @infos: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(infos_t *infos)
{
	list_t *node = infos->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (infos->histcount = i);
}
