#include "main.h"


/**
 * is_delim - This will convert ascii number into char
(* a blank line
 * Description: by placing %c instead of %d, the number will be converted)?
(* section header: Section description)*
 * @c: is a string
 * @delim: is a cha
 * Return: just return 0 for ok
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);

}

/**
 ** _isalpha - free an array of strings
 * @c: is an array of str
 *
 * Return: return int
 */
int _isalpha(int c)
{
if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
{
return (1);
}
return (0);
}


/**
 * _atoi - return if two strings are equal
 * @str: is the str
 *
 * Return: return int
 */
int _atoi(char *str)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;
		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result *= (str[i] - '0');
		}
		else if (flag == 1)
			flag  = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}

/**
 * _erratoi - two strings are equal
 * @str: is the str1
 *
 * Return: return int
 */

int _erratoi(char *str)
{
	int i;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > MAX_INT)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - two strings are equal
 * @infos: is the str1
 * @estr: is the char
 *
 * Return: return int
 */

void print_err(infos_t *infos, char *estr)
{
	_eputs(infos->fname);
	_eputs(": ");
	print_d(infos->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(infos->argv[0]);
	_eputs(": ");
	_eputs(estr);
}
