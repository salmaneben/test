#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @character: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char character, char buffer[],
	int flags, int width, int precision, int size)
{
	int index = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & FLAG_ZERO)
		padding = '0';

	buffer[index++] = character;
	buffer[index] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (index = 0; index < width - 1; index++)
			buffer[BUFF_SIZE - index - 2] = padding;

		if (flags & FLAG_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - index - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - index - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @index: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char padding = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & FLAG_PLUS)
		extra_ch = '+';
	else if (flags & FLAG_SPACE)
		extra_ch = ' ';

	return (write_num(index, buffer, flags, width, precision,
		length, padding, extra_ch));
}

/**
 * write_num - Write a number using a bufffer
 * @index: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padding: Padding char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int index, char buffer[],
	int flags, int width, int prec,
	int length, char padding, char extra_c)
{
	int i, padding_start = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = padding = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padding = ' ';
	while (prec > length)
		buffer[--index] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padding;

		buffer[i] = '\0';
		if (flags & FLAG_MINUS && padding == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & FLAG_MINUS) && padding == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & FLAG_MINUS) && padding == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padding_start] = extra_c;
			return (write(1, &buffer[padding_start], i - padding_start) +
				write(1, &buffer[index], length - (1 - padding_start)));
		}
	}
	if (extra_c)
		buffer[--index] = extra_c;
	return (write(1, &buffer[index], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1, i = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding = '0';

	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padding;

		buffer[i] = '\0';
		if (flags & FLAG_MINUS)
			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		else
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
	}

	return (write(1, &buffer[index], length));
}

