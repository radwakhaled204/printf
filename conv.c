#include "main.h"

/**
 * convert_sbase - Converts a signed long to an inputted base and stores
 *                 the result to a buffer contained in a struct.
 * @out_buffer: A buf_t struct containing a character array.
 * @number: A signed long to be converted.
 * @base_string: A pointer to a string containing the base to convert to.
 * @format_flags: Flag modifiers.
 * @min_width: A width modifier.
 * @precision: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_sbase(buf_t *out_buffer, long int number,
		char *base_string, unsigned char format_flags, int min_width, int precision)
{
	int base_size;
	char digit, pad = '0';
	unsigned int num_chars = 1;

	for (base_size = 0; *(base_string + base_size);)
		base_size++;

	if (number >= base_size || number <= -base_size)
		num_chars += convert_sbase(out_buffer, number / base_size, base_string,
				format_flags, min_width - 1, precision - 1);

	else
	{
		for (; precision > 1; precision--, min_width--) /* Handle precision */
			num_chars += _memcpy(out_buffer, &pad, 1);

		if (MINUS_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; min_width > 1; min_width--)
				num_chars += _memcpy(out_buffer, &pad, 1);
		}
	}

	digit = base_string[(number < 0 ? -1 : 1) * (number % base_size)];
	_memcpy(out_buffer, &digit, 1);

	return (num_chars);
}

/**
 * convert_ubase - Converts an unsigned long to an inputted base and
 *                 stores the result to a buffer contained in a struct.
 * @out_buffer: A buf_t struct containing a character array.
 * @number: An unsigned long to be converted.
 * @base_string: A pointer to a string containing the base to convert to.
 * @format_flags: Flag modifiers.
 * @min_width: A width modifier.
 * @precision: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_ubase(buf_t *out_buffer, unsigned long int number,
		char *base_string, unsigned char format_flags, int min_width, int precision)
{
	unsigned int base_size, num_chars = 1;
	char digit, pad = '0', *prefix = "0x";

	for (base_size = 0; *(base_string + base_size);)
		base_size++;

	if (number >= base_size)
		num_chars += convert_ubase(out_buffer, number / base_size, base_string,
				format_flags, min_width - 1, precision - 1);

	else
	{
		if (((format_flags >> 5) & 1) == 1) /* Printing a ptr address */
		{
			min_width -= 2;
			precision -= 2;
		}
		for (; precision > 1; precision--, min_width--) /* Handle precision */
			num_chars += _memcpy(out_buffer, &pad, 1);

		if (MINUS_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; min_width > 1; min_width--)
				num_chars += _memcpy(out_buffer, &pad, 1);
		}
		if (((format_flags >> 5) & 1) == 1) /* Print 0x for ptr address */
			num_chars += _memcpy(out_buffer, prefix, 2);
	}

	digit = base_string[(number % base_size)];
	_memcpy(out_buffer, &digit, 1);

	return (num_chars);
}
