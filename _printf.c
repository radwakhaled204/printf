#include "main.h"

/**
 * flush - Peforms cleanup operations for _printf.
 * @args: A va_list of arguments provided to _printf.
 * @out: A buffer_t struct.
 */
void flush(va_list args, buf_t *out)
{
	va_end(args);
	write(1, out->start, out->length);
	free_buffer(out);
}

/**
 * r_printf - Reads through the format string for _printf.
 * @format: Character string to print - may contain directives.
 * @out: A buf_t struct containing a buffer.
 * @args: A va_list of arguments.
 *
 * Return: The number of characters stored to output.
 * @function int - function.
 */
int r_printf(const char *format, va_list args, buf_t *out)
{
	int i, wid, prec, ret = 0;
	char tmp;
	unsigned char flags, len;
	unsigned int (*f)(va_list, buf_t *, unsigned char, int, int, unsigned char);

	for (i = 0; *(format + i); i++)
	{
		len = 0;
		if (*(format + i) == '%')
		{
			tmp = 0;
			flags = get_flag_value(format + i + 1, &tmp);
			wid = get_width_value(args, format + i + tmp + 1, &tmp);
			prec = get_precision_value(args, format + i + tmp + 1,
					&tmp);
			len = get_length_value(format + i + tmp + 1, &tmp);

			f = handle_specifiers(format + i + tmp + 1);
			if (f != NULL)
			{
				i += tmp + 1;
				ret += f(args, out, flags, wid, prec, len);
				continue;
			}
			else if (*(format + i + tmp + 1) == '\0')
			{
				ret = -1;
				break;
			}
		}
		ret += _memcpy(out, (format + i), 1);
		i += (len != 0) ? 1 : 0;
	}
	flush(args, out);
	return (ret);
}

/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	buf_t *out;
	va_list args;
	int result;

	if (format == NULL)
		return (-1);
	out = init_buffer();
	if (out == NULL)
		return (-1);

	va_start(args, format);

	result = r_printf(format, args, out);

	return (result);
}
