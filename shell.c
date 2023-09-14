#include "main.h"

/**
 * main - return the length of a string
 * @argc: is the str
 * @argv: is the array of str
 *
 * Return: return int
 */
int main(int argc, char **argv)
{
	infos_t infos[] = {INIT_INFO};
	int a = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (a)
		: "r" (a));

	if (argc == 2)
	{
		a = open(argv[1], O_RDONLY);
		if (a == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}

		infos->readfd = a;
	}

	populate_env_list(infos);
	read_history(infos);
	shell(infos, argv);
	return (EXIT_SUCCESS);
}
