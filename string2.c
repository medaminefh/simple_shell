#include "main.h"

/**
 * *_strcat - return the length of a string
 * @dest: is the str
 * @src: is the src
 *
 * Return: return int
 */
char *_strcat(char *dest, char *src)
	{
		char *a = dest;

		while (*dest)
			dest++;
		while (*src)
			*dest++ = *src++;
		*dest = *src;
		return (a);
	}

/**
 * *_strdup - return if two strings are equal
 * @s: is the str1
 *
 * Return: return int
 */
char *_strdup(const char *s)
{

	int i = 0;
	char *r;

	if (s == NULL)
		return (NULL);
	while (*s++)
		i++;
	r = malloc(sizeof(char) * (i + 1));
	if (!r)
		return (NULL);
	for (i++; i--;)
		r[i] = *--s;
	return (r);
}


/**
 * _puts - return if two strings are equal
 * @str1: is the str1
 *
 * Return: return int
 */
void _puts(char *str1)
{

	int i = 0;

	if (!str1)
		return;

	while (str1[i] != '\0')
	{
		_putchar(str1[i]);
		i++;
	}
}

/**
 * _putchar - two strings are equal
 * @s1: is the str1
 *
 * Return: return int
 */

int _putchar(char s1)
{
return (write(1, &s1, 1));
}

/**
 * _strncpy - This will convert ascii number into char
(* a blank line
 * Description: by placing %c instead of %d, the number will be converted)?
(* section header: Section description)*
 * @dest: is a pointer to a string
 * @src: is a pointer to a str
 * @n: is an int
 * Return: just return 0 for ok
 */
char *_strncpy(char *dest, char *src, int n)
{
int a;
for (a = 0; (a < n && src[a] != '\0'); a++)
{
dest[a] = src[a];
}
for ( ; a < n; a++)
{
dest[a] = '\0';
}

return (dest);
}
