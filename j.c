#include "main.h"

/**
 * get_hist_file - gets the history file
 * @infos: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_file(infos_t *infos)
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
 * write_hist - creates a file, or appends to an existing file
 * @infos: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_hist(infos_t *infos)
{
	char *filename = get_hist_file(infos);
	ssize_t file_d;
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_d = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_d == -1)
		return (-1);
	for (node = infos->history; node; node = node->next)
	{
		_putsfd(node->str, file_d);
		_putfd('\n', file_d);
	}
	_putfd(BUFFER_FLUSH, file_d);
	close(file_d);
	return (1);
}

/**
 * read_hist - reads history from file
 * @infos: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_hist(infos_t *infos)
{
	ssize_t file_d, rdlen, file_size = 0;
	struct stat st;
	int i, last = 0, line_count = 0;
	char *buffer;
	char *filename = get_hist_file(infos);

	if (!filename)
		return (0);

	file_d = open(filename, O_RDONLY);
	free(filename);
	if (file_d == -1)
		return (0);
	if (!fstat(file_d, &st))
		file_size = st.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	rdlen = read(file_d, buffer, file_size);
	buffer[file_size] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(file_d);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_hist_list(infos, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		build_hist_list(infos, buffer + last, line_count++);
	free(buffer);
	infos->histcount = line_count;
	while (infos->histcount-- >= HISTORY_MAX)
		delete_node(&(infos->history), 0);
	renumber_hist(infos);
	return (infos->histcount);
}

/**
 * build_hist_list - adds entry ist
 * @infos: Structure containing  to maintain
 * @buffer: buff
 * @linecount: the history
 *
 * Return: Always 0
 */
int build_hist_list(infos_t *infos, char *buffer, int linecount)
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
 * renumber_hist - renumbers the history linked list after changes
 * @infos: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_hist(infos_t *infos)
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
