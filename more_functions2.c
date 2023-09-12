#include "main.h"


/**
 * print_d - This will convert ascii number into char
(* a blank line
 * Description: by placing %c instead of %d, the number will be converted)?
(* section header: Section description)*
 * @input: is a string
 * @a: is a cha
 * Return: just return 0 for ok
 */
int print_d(int input, int a)
{
	int i = 0;
	int count = 0;
	int (*__putchar)(char) = _putchar;
	unsigned int _abs_, current;

	if (a == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
	{
		_abs_ = input;
	}
	current = _abs_;
	for (i = 1000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - wr to stderr
 * @s: The characer t
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char s)
{
	int i = 0;
	char buffer[WRITE_BUFFER_SIZE];

	if (s == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (s != BUFFER_FLUSH)
		buffer[i++] = s;
	return (1);
}

/**
 * _putfd - ven fd
 * @s: The  to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char s, int fd)
{
	int i = 0;
	char buffer[WRITE_BUFFER_SIZE];

	if (s == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (s != BUFFER_FLUSH)
		buffer[i++] = s;
	return (1);
}

/**
 *_putsfd - priing
 * @str: the sted
 * @fd: the filwrite to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
