#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @char_type: char types.
 * @buff_array: Buffer array to handle print
 * @flag_calc:  Calculates active flags.
 * @width_val: get width.
 * @precision_spec: precision specifier
 * @size_spec: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char char_type, char buff_array[],
	int flag_calc, int width_val, int precision_spec, int size_spec)
{
	/* char is stored at left and paddind at buff_array's right */
	int index = 0;
	char padding = ' ';

	UNUSED(precision_spec);
	UNUSED(size_spec);

	if (flag_calc & FLAG_ZERO)
		padding = '0';

	buff_array[index++] = char_type;
	buff_array[index] = '\0';

	if (width_val > 1)
	{
		buff_array[BUFFER_SIZE - 1] = '\0';
		for (index = 0; index < width_val - 1; index++)
			buff_array[BUFFER_SIZE - index - 2] = padding;

		if (flag_calc & FLAG_MINUS)
		{
			return (write(1, &buff_array[0], 1) +
					write(1, &buff_array[BUFFER_SIZE - index - 1], width_val - 1));
		}
		else
		{
			return (write(1, &buff_array[BUFFER_SIZE - index - 1], width_val - 1) +
					write(1, &buff_array[0], 1));
		}
	}

	return (write(1, &buff_array[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_neg: Lista of arguments
 * @index_val: char types.
 * @buff_array: Buffer array to handle print
 * @flag_calc:  Calculates active flags
 * @width_val: get width.
 * @precision_spec: precision specifier
 * @size_spec: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_neg, int index_val, char buff_array[],
	int flag_calc, int width_val, int precision_spec, int size_spec)
{
	int length_val = BUFFER_SIZE - index_val - 1;
	char padding = ' ', extra_char = 0;

	UNUSED(size_spec);

	if ((flag_calc & FLAG_ZERO) && !(flag_calc & FLAG_MINUS))
		padding = '0';
	if (is_neg)
		extra_char = '-';
	else if (flag_calc & FLAG_PLUS)
		extra_char = '+';
	else if (flag_calc & FLAG_SPACE)
		extra_char = ' ';

	return (write_num(index_val, buff_array, flag_calc, width_val, precision_spec,
		length_val, padding, extra_char));
}

/**
 * write_num - Write a number using a bufffer
 * @index_val: Index at which the number starts on the buffer
 * @buff_array: Buffer
 * @flag_calc: Flags
 * @width_val: width
 * @prec_spec: Precision specifier
 * @length_val: Number length
 * @padding: Pading char
 * @extra_char: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int index_val, char buff_array[],
	int flag_calc, int width_val, int prec_spec,
	int length_val, char padding, char extra_char)
{
	int index, padding_start = 1;

	if (prec_spec == 0 && index_val == BUFFER_SIZE - 2 && buff_array[index_val] == '0' && width_val == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec_spec == 0 && index_val == BUFFER_SIZE - 2 && buff_array[index_val] == '0')
		buff_array[index_val] = padding = ' '; /* width_val is displayed with padding ' ' */
	if (prec_spec > 0 && prec_spec < length_val)
		padding = ' ';
	while (prec_spec > length_val)
		buff_array[--index_val] = '0', length_val++;
	if (extra_char != 0)
		length_val++;
	if (width_val > length_val)
	{
		for (index = 1; index < width_val - length_val + 1; index++)
			buff_array[index] = padding;
		buff_array[index] = '\0';
		if (flag_calc & FLAG_MINUS && padding == ' ')/* Asign extra char to left of buff_array */
		{
			if (extra_char)
				buff_array[--index_val] = extra_char;
			return (write(1, &buff_array[index_val], length_val) + write(1, &buff_array[1], index - 1));
		}
		else if (!(flag_calc & FLAG_MINUS) && padding == ' ')/* extra char to left of buff_array */
		{
			if (extra_char)
				buff_array[--index_val] = extra_char;
			return (write(1, &buff_array[1], index - 1) + write(1, &buff_array[index_val], length_val));
		}
		else if (!(flag_calc & FLAG_MINUS) && padding == '0')/* extra char to left of padding */
		{
			if (extra_char)
				buff_array[--padding_start] = extra_char;
			return (write(1, &buff_array[padding_start], index - padding_start) +
					write(1, &buff_array[index_val], length_val - (1 - padding_start)));
		}
	}
	if (extra_char)
		buff_array[--index_val] = extra_char;
	return (write(1, &buff_array[index_val], length_val));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_neg: Number indicating if the num is negative
 * @index_val: Index at which the number starts in the buffer
 * @buff_array: Array of chars
 * @flag_calc: Flags specifiers
 * @width_val: Width specifier
 * @precision_spec: Precision specifier
 * @size_spec: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_neg, int index_val,
	char buff_array[],
	int flag_calc, int width_val, int precision_spec, int size_spec)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length_val = BUFFER_SIZE - index_val - 1, index = 0;
	char padding = ' ';

	UNUSED(is_neg);
	UNUSED(size_spec);

	if (precision_spec == 0 && index_val == BUFFER_SIZE - 2 && buff_array[index_val] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision_spec > 0 && precision_spec < length_val)
		padding = ' ';

	while (precision_spec > length_val)
	{
		buff_array[--index_val] = '0';
		length_val++;
	}

	if ((flag_calc & FLAG_ZERO) && !(flag_calc & FLAG_MINUS))
		padding = '0';

	if (width_val > length_val)
	{
		for (index = 0; index < width_val - length_val; index++)
			buff_array[index] = padding;

		buff_array[index] = '\0';

		if (flag_calc & FLAG_MINUS) /* Asign extra char to left of buff_array [buff_array>padding]*/
		{
			return (write(1, &buff_array[index_val], length_val) + write(1, &buff_array[0], index));
		}
		else /* Asign extra char to left of padding [padding>buff_array]*/
		{
			return (write(1, &buff_array[0], index) + write(1, &buff_array[index_val], length_val));
		}
	}

	return (write(1, &buff_array[index_val], length_val));
}

/**
 * write_pointer - Write a memory address
 * @buff_array: Arrays of chars
 * @index_val: Index at which the number starts in the buffer
 * @length_val: Length of number
 * @width_val: Width specifier
 * @flag_calc: Flags specifier
 * @padding: Char representing the padding
 * @extra_char: Char representing extra char
 * @padding_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buff_array[], int index_val, int length_val,
	int width_val, int flag_calc, char padding, char extra_char, int padding_start)
{
	int index;

	if (width_val > length_val)
	{
		for (index = 3; index < width_val - length_val + 3; index++)
			buff_array[index] = padding;
		buff_array[index] = '\0';
		if (flag_calc & FLAG_MINUS && padding == ' ')/* Asign extra char to left of buff_array */
		{
			buff_array[--index_val] = 'x';
			buff_array[--index_val] = '0';
			if (extra_char)
				buff_array[--index_val] = extra_char;
			return (write(1, &buff_array[index_val], length_val) + write(1, &buff_array[3], index - 3));
		}
		else if (!(flag_calc & FLAG_MINUS) && padding == ' ')/* extra char to left of buff_array */
		{
			buff_array[--index_val] = 'x';
			buff_array[--index_val] = '0';
			if (extra_char)
				buff_array[--index_val] = extra_char;
			return (write(1, &buff_array[3], index - 3) + write(1, &buff_array[index_val], length_val));
		}
		else if (!(flag_calc & FLAG_MINUS) && padding == '0')/* extra char to left of padding */
		{
			if (extra_char)
				buff_array[--padding_start] = extra_char;
			buff_array[1] = '0';
			buff_array[2] = 'x';
			return (write(1, &buff_array[padding_start], index - padding_start) +
					write(1, &buff_array[index_val], length_val - (1 - padding_start) - 2));
		}
	}
	buff_array[--index_val] = 'x';
	buff_array[--index_val] = '0';
	if (extra_char)
		buff_array[--index_val] = extra_char;
	return (write(1, &buff_array[index_val], BUFFER_SIZE - index_val - 1));
}

