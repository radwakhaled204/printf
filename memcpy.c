#include "main.h"

/**
 * _memcpy - Copies n bytes from memory area src to
 *           the buffer contained in a buf_t struct.
 * @out: A buf_t struct.
 * @src: A pointer to the memory area to copy.
 * @n: The number of bytes to be copied.
 * Return: The number of bytes copied.
 */


unsigned int _memcpy(buf_t *out, const char *src, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
	{
		*(out->buffer) = *(src + index);
		(out->length)++;

		if (out->length == 1024)
		{
			write(1, out->start, out->length);
			out->buffer = out->start;
			out->length = 0;
		}

		else
			(out->buffer)++;
	}

	return (n);
}

/**
 * free_buffer - Frees a buf_t struct.
 * @out: The buf_t struct to be freed.
 */

void free_buffer(buf_t *out)
{
	free(out->start);
	free(out);
}

/**
 * init_buffer - Initializes a variable of struct type buf_t.
 *
 * Return: A pointer to the initialized buf_t.
 */

buf_t *init_buffer(void)
{
	buf_t *out;

	out = malloc(sizeof(buf_t));
	if (out == NULL)
		return (NULL);

	out->buffer = malloc(sizeof(char) * 1024);
	if (out->buffer == NULL)
	{
		free(out);
		return (NULL);
	}

	out->start = out->buffer;
	out->length = 0;

	return (out);
}
