#include "main.h"

/**
 * is_cmd - determines if a file is an executable command
 * @infos: the infos struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(infos_t *infos, char *path)
{
	struct stat st;

	(void)infos;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new bufferfer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[WRITE_BUFFER_SIZE];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buffer[k++] = pathstr[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_path - finds this cmd in the PATH string
 * @infos: the infos struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(infos_t *infos, char *pathstr, char *cmd)
{
	int i = 0, curr_position = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(infos, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_position, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(infos, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_position = i;
		}
		i++;
	}
	return (NULL);
}
