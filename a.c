#include "main.h"

/**
 * _my_exit - exits the shell
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if infos.argv[0] != "exit"
 */
int _my_exit(infos_t *infos)
{
	int exitk;

	if (infos->argv[1])
	{
		exitk = _errtoi(infos->argv[1]);
		if (exitk == -1)
		{
			infos->status = 2;
			printf_error(infos, "Illegal number: ");
			_eputs(infos->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infos->err_num = _errtoi(infos->argv[1]);
		return (-2);
	}
	infos->err_num = -1;
	return (-2);
}

/**
 * _my_cd - changes the current directory of the process
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_cd(infos_t *infos)
{
	char *s;
	char *dirs;
	char buffer[BUFFER_SIZE];
	int chdir_ret;

	s = getcwd(buffer, BUFFER_SIZE);
	if (!s)
		_puts("TODO: >>get failure emsg here<<\n");
	if (!infos->argv[1])
	{
		dirs = _getenv(infos, "HOME=");
		if (!dirs)
			chdir_ret = chdir((dirs = _getenv(infos, "PWD=")) ? dirs : "/");
		else
			chdir_ret = chdir(dirs);
	}
	else if (_strcmp(infos->argv[1], "-") == 0)
	{
		if (!_getenv(infos, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(infos, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dirs = _getenv(infos, "OLDPWD=")) ? dirs : "/");
	}
	else
		chdir_ret = chdir(infos->argv[1]);
	if (chdir_ret == -1)
	{
		printf_error(infos, "can't cd to ");
		_eputs(infos->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(infos, "OLDPWD", _getenv(infos, "PWD="));
		_setenv(infos, "PWD", getcwd(buffer, BUFFER_SIZE));
	}
	return (0);
}

/**
 * _my_help - changes the current directory of the process
 * @infos: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_help(infos_t *infos)
{
	char **args;

	args = infos->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*args);
	return (0);
}
