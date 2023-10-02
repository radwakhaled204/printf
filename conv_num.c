#include "main.h"

/**
 * co_Int - Converts an argument to a signed int and
 *              stores it to a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @format_flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @length: A length modifier.
 * @out: A buf_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int co_Int(va_list args, buf_t *out,
		unsigned char format_flags, int wid, int prec, unsigned char length)
{
	long int d, copy;
	unsigned int ret = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (length == LONG)
		d = va_arg(args, long int);
	else
		d = va_arg(args, int);
	if (length == SHORT)
		d = (short)d;
	if (SPACE_FLAG == 1 && d >= 0)
		ret += _memcpy(out, &space, 1);
	if (prec <= 0 && MINUS_FLAG == 0)
	{
		if (d == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
				count++;
		}
		count += (d == 0) ? 1 : 0, count += (d < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && d >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && d >= 0) ? 1 : 0;
		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && d >= 0)
			ret += _memcpy(out, &plus, 1);
		if (ZERO_FLAG == 1 && d < 0)
			ret += _memcpy(out, &neg, 1);
		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (wid -= count; wid > 0; wid--)
			ret += _memcpy(out, &pad, 1);
	}
	if (ZERO_FLAG == 0 && d < 0)
		ret += _memcpy(out, &neg, 1);
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		ret += _memcpy(out, &plus, 1);
	if (!(d == 0 && prec == 0))
		ret += convert_sbase(out, d, "0123456789", format_flags, 0, prec);
	ret += print_neg_width(out, ret, format_flags, wid);
	return (ret);
}
/**
 * co_Binary - Converts an unsigned int argument to binary
 * and stores it to a buffer contained in a struct.
 * @params: A va_list pointing to the argument to be converted.
 * @modifiers: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @size: A length modifier.
 * @buffer: A buf_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */

unsigned int co_Binary(va_list params, buf_t *buffer,
		unsigned char modifiers, int width, int precision, unsigned char size)
{
	unsigned int number;

	number = va_arg(params, unsigned int);
	(void)size;
	return (convert_ubase(buffer, number, "01", modifiers, width, precision));
}

/**
 * co_Octal - Converts an unsigned int to octal and
 * stores it to a buffer contained in a struct.
 * @params: A va_list poinitng to the argument to be converted.
 * @format_flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @size: A length modifier.
 * @buffer: A buf_t struct containing a character array.
 * Return: The number of bytes stored to the buffer.
 */

unsigned int co_Octal(va_list params, buf_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char size)
{
	unsigned long int number;
	unsigned int result = 0;
	char zero = '0';


	if (size == LONG)
		number = va_arg(params, unsigned long int);
	else
		number = va_arg(params, unsigned int);

	if (size == SHORT)
		number = (unsigned short)number;

	if (HASH_FLAG == 1 && number != 0)
		result += _memcpy(buffer, &zero, 1);

	if (!(number == 0 && precision == 0))
		result += convert_ubase(buffer, number, "01234567",
				format_flags, width, precision);
	result += print_neg_width(buffer, result, format_flags, width);
	return (result);
}

/**
 * co_Decimal- Converts an unsigned int argument to decimal and
 * stores it to a buffer contained in a struct.
 * @params: A va_list pointing to the argument to be converted.
 * @modifiers: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @size: A length modifier.
 * @buffer: A buf_t struct containing a character array.
 * Return: The number of bytes stored to the buffer
 */

unsigned int co_Decimal(va_list params, buf_t *buffer,
		unsigned char modifiers, int width, int precision, unsigned char size)
{
	unsigned long int number;
	unsigned int result = 0;

	if (size == LONG)
		number = va_arg(params, unsigned long int);
	else
		number = va_arg(params, unsigned int);

	if (size == SHORT)
		number = (unsigned short)number;
	if (!(number == 0 && precision == 0))
		result += convert_ubase(buffer, number, "0123456789",
				modifiers, width, precision);

	result += print_neg_width(buffer, result, modifiers, width);

	return (result);
}
