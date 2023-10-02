
#ifndef MAIN_H
#define MAIN_H


#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdarg.h>

/* FLAGS */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define MINUS 16
#define PLUS_FLAG (format_flags & 1)
#define SPACE_FLAG ((format_flags >> 1) & 1)
#define HASH_FLAG ((format_flags >> 2) & 1)
#define ZERO_FLAG ((format_flags >> 3) & 1)
#define MINUS_FLAG ((format_flags >> 4) & 1)

/* LENGTH */
#define SHORT 1
#define LONG 2


/**
 * struct buf - Struct of buf.
 * @buffer: A pointer to data in memory.
 * @start:  A  pointer to the beginning of buffer.
 * @length: The length of the data stored in buffer.
 */

typedef struct buf
{
	char *buffer;
	char *start;
	unsigned int length;
} buf_t;


/**
 * struct ca_specifier - Struct of specifier.
 * @specifier: A  pointer to a specifier.
 * unsigned int (*f)(va_list, buf_t *, unsigned char, int, int, unsigned char):
 *       A function pointer with specific parameters and return type.
 * @f: A pointer to a conversion function corresponding to specifier.
 */

typedef struct ca_specifier
{
	char *specifier;
	unsigned int (*f)(va_list, buf_t *, unsigned char, int, int, unsigned char);
} ca_specifier_t;

/**
 * struct flags - Struct of flags.
 * @flag: A char for flag.
 * @value: value of flag.
 */

typedef struct flags
{
	unsigned char flag;
	int value;
} flags_t;

int _printf(const char *format, ...);
void flush(va_list args, buf_t *out);
int r_printf(const char *format, va_list args, buf_t *out);

/* functions to convert  */

unsigned int Co_Char(va_list arguments, buf_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char size);
unsigned int store_string(va_list args, buf_t *out,
		unsigned char format_flags, int wid, int prec, unsigned char length);
unsigned int co_r(va_list args, buf_t *out,
		unsigned char format_flags, int wid, int prec, unsigned char length);
unsigned int co_R(va_list args, buf_t *out,
		unsigned char format_flags, int wid, int prec, unsigned char length);
unsigned int co_S(va_list args, buf_t *out,
		unsigned char format_flags, int wid, int prec, unsigned char length);
unsigned int Co_Percent(va_list arguments, buf_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char size);
unsigned int Co_Pointer(va_list arguments, buf_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char size);
unsigned int Co_LoHex(va_list arguments, buf_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char size);
unsigned int Co_UpHex(va_list arguments, buf_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char size);
unsigned int co_Int(va_list args, buf_t *out,
		unsigned char format_flags, int wid, int prec, unsigned char length);
unsigned int co_Binary(va_list params, buf_t *buffer,
		unsigned char modifiers, int width, int precision, unsigned char size);
unsigned int co_Octal(va_list params, buf_t *buffer,
		 unsigned char modifiers, int width, int precision, unsigned char size);
unsigned int co_Decimal(va_list params, buf_t *buffer,
		unsigned char modifiers, int width, int precision, unsigned char size);

/* Another Functions */

buf_t *init_buffer(void);
void free_buffer(buf_t *out);
unsigned int _memcpy(buf_t *out, const char *src, unsigned int n);
unsigned int convert_sbase(buf_t *out_buffer, long int number,
		char *base_string, unsigned char format_flags, int min_width, int precision);
unsigned int convert_ubase(buf_t *out_buffer, unsigned long int number,
		char *base_string, unsigned char format_flags, int min_width, int precision);

/* Modifiers */

unsigned int print_width(buf_t *out, unsigned int printed,
		unsigned char format_flags, int wid);
unsigned int print_string_width(buf_t *out,
		unsigned char format_flags, int wid, int prec, int size);
unsigned int print_neg_width(buf_t *out, unsigned int printed,
		unsigned char format_flags, int wid);

/* Handlers */

/**
 * handle_specifiers - handle.
 * @ptr_flag: A pointer to a potential string of flags.
 * @ptr_ft: A pointer to the current index of the format string.
 * Return: If flag characters are found - a bitwise value of the flags.
 */

unsigned char get_flag_value(const char *ptr_flag, char *ptr_ft);
unsigned char get_length_value(const char *ptr_mod, char *ptr_ft);
int get_width_value(va_list args, const char *ptr_mod, char *ptr_ft);
int get_precision_value(va_list args, const char *ptr_mod, char *ptr_ft);
unsigned int(*handle_specifiers(const char *specifier))(va_list, buf_t *,
		unsigned char, int, int, unsigned char);




#endif // MAIN_H_INCLUDED
