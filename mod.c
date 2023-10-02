#include "main.h"

/**
 * print_width - Stores leading spaces to a buffer for a width modifier.
 * @out: A buf_t struct containing a character array.
 * @printed: The current number of characters already printed to out
 *           for a given number specifier.
 * @format_flags: format_flag modifiers.
 * @wid: A width modifier.
 * Return: The number of bytes stored to the buffer.
 */


unsigned int print_width(buf_t *out, unsigned int printed,
unsigned char format_flags, int wid)
{
unsigned int ret = 0;
char width = ' ';

if (MINUS_FLAG == 0)
{
for (wid -= printed; wid > 0;)
ret += _memcpy(out, &width, 1);
}

return (ret);
}

/**
 * print_string_width - Stores leading spaces to a buffer for a width modifier.
 * @out: A buf_t struct containing a character array.
 * @format_flags: format_flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @size: The size of the string.
 * Return: The number of bytes stored to the buffer.
 */

unsigned int print_string_width(buf_t *out,
unsigned char format_flags, int wid, int prec, int size)
{
unsigned int ret = 0;
char width = ' ';

if (MINUS_FLAG == 0)
{
wid -= (prec == -1) ? size : prec;
for (; wid > 0; wid--)
ret += _memcpy(out, &width, 1);
}

return (ret);
}

/**
 * print_MINUS_width - Stores trailing spaces to a buffer for a '-' flag.
 * @out: A buf_t struct containing a character array.
 * @printed: The current number of bytes already stored to out
 *           for a given specifier.
 * @format_flags: format_flag modifiers.
 * @wid: A width modifier.
 * Return: The number of bytes stored to the buffer.
 */

unsigned int print_neg_width(buf_t *out, unsigned int printed,
unsigned char format_flags, int wid)
{
unsigned int ret = 0;
char width = ' ';

if (MINUS_FLAG == 1)
{
for (wid -= printed; wid > 0; wid--)
ret += _memcpy(out, &width, 1);
}

return (ret);
}
