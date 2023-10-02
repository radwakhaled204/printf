#include "main.h"

/**
 * get_flag_value - Returns the value for each flag in the format string.
 * @ptr_flag: A pointer to a potential string of flags.
 * @ptr_ft: A pointer to the current index of the format string.
 * Return: If flag characters are found - a bitwise value of the flags.
 * Otherwise - 0.
*/
unsigned char get_flag_value(const char *ptr_flag, char *ptr_ft)
{
	int i, k;
	unsigned char flag_result = 0;
	flags_t flag_list[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', MINUS},
		{0, 0}
	};

	for (i = 0; ptr_flag[i]; i++)
	{
		for (k = 0; flag_list[k].flag != 0; k++)
		{
			if (ptr_flag[i] == flag_list[k].flag)
			{
				(*ptr_ft)++;
				if (flag_result == 0)
					flag_result = flag_list[k].value;
				else
					flag_result |= flag_list[k].value;
				break;
			}
		}
		if (flag_list[k].value == 0)
		break;
	}

	return (flag_result);
}
/**
 * get_length_value - Returns the value for each length
 * modifier in the format string.
 * @ptr_mod: A pointer to a possible length modifier.
 * @ptr_ft: A pointer to the current index of the format string.
 * Return: If a length modifier is found - its corresponding value.
 *  Otherwise - 0.
*/
unsigned char get_length_value(const char *ptr_mod, char *ptr_ft)
{
	if (*ptr_mod == 'h')
	{
		(*ptr_ft)++;
		return (SHORT);
	}

	else if (*ptr_mod == 'l')
	{
		(*ptr_ft)++;
		return (LONG);
	}

	return (0);
}

/**
 * get_width_value - Returns the value for a width modifier
 * in the format string.
 * @args: A va_list of arguments.
 * @ptr_mod: A pointer to a possible width modifier.
 * @ptr_ft: A pointer to the current index of the format string.
 * Return: If a width modifier is found - its value.
 * Otherwise - 0.
*/
int get_width_value(va_list args, const char *ptr_mod, char *ptr_ft)
{
	int wid_value = 0;

	while ((*ptr_mod >= '0' && *ptr_mod <= '9') || (*ptr_mod == '*'))
	{
		(*ptr_ft)++;

		if (*ptr_mod == '*')
		{
			wid_value = va_arg(args, int);
			if (wid_value <= 0)
				return (0);
			return (wid_value);
		}
		wid_value *= 10;
		wid_value += (*ptr_mod - '0');
		ptr_mod++;
	}

	return (wid_value);
}

/**
 * get_precision_value - Returns the value for a precision
 * modifier in the format string.
 * @args: A va_list of arguments.
 * @ptr_mod: A pointer to a possible precision modifier.
 * @ptr_ft: A pointer to the current index of the format string.
 *
 * Return: If a precision modifier is found - its value. 0
 */
int get_precision_value(va_list args, const char *ptr_mod, char *ptr_ft)
{
	int prec_value = 0;

	if (*ptr_mod != '.')
		return (-1);
	ptr_mod++;
	(*ptr_ft)++;
	if ((*ptr_mod <= '0' || *ptr_mod > '9') && *ptr_mod != '*')
	{
		if (*ptr_mod == '0')
			(*ptr_ft)++;
		return (0);
	}
	while ((*ptr_mod >= '0' && *ptr_mod <= '9') ||
			(*ptr_mod == '*'))
	{
		(*ptr_ft)++;

		if (*ptr_mod == '*')
		{
			prec_value = va_arg(args, int);
			if (prec_value <= 0)
				return (0);
			return (prec_value);
		}
		prec_value *= 10;
		prec_value += (*ptr_mod - '0');
		ptr_mod++;
	}
	return (prec_value);
}

/**
 * handle_specifiers - returns a pointer to a function that can convert
 * an argument of a given type to a string and store it in a buffer
 * @int: int
 * @int: int
 * @char: char
 * @char: char
 * Return: If a conversion function is matched - a pointer to the function.
 * Otherwise - NULL.
 */

unsigned int(*handle_specifiers(const char *specifier))(va_list, buf_t *,
		unsigned char, int, int, unsigned char)

{
	int index;

	ca_specifier_t converters[] = {
		{"c", Co_Char},
		{"s", store_string},
		{"d", co_Int},
		{"i", co_Int},
		{"%", Co_Percent},
		{"b", co_Binary},
		{"u", co_Decimal},
		{"o", co_Octal},
		{"x", Co_LoHex},
		{"X", Co_UpHex},
		{"S", co_S},
		{"p", Co_Pointer},
		{"r", co_r},
		{"R", co_R},
		{0, NULL}
	};

	for (index = 0; converters[index].f; index++)
	{
		if (converters[index].specifier[0] == specifier[0])
			return (converters[index].f);
	}

	return (NULL);
}
