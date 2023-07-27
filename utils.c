#include "main.h"

/* Function to evaluate if a character is printable */
/**
 * is_printable - Determines if a character is printable
 * @character: Character to be evaluated
 *
 * Return: 1 if character is printable, 0 otherwise
 */
int is_printable(char character)
{
	if (character >= 32 && character < 127)
		return (1);

	return (0);
}

/* Function to append ASCII in hexadecimal code to buffer */
/**
 * append_hexa_code - Appends ASCII in hexadecimal code to buffer
 * @buffer_array: Array of characters
 * @index: Index at which to start appending
 * @ascii_code: ASCII code
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer_array[], int index)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexadecimal format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer_array[index++] = '\\';
	buffer_array[index++] = 'x';

	buffer_array[index++] = map_to[ascii_code / 16];
	buffer_array[index] = map_to[ascii_code % 16];

	return (3);
}

/* Function to verify if a character is a digit */
/**
 * is_digit - Checks if a character is a digit
 * @character: Character to be evaluated
 *
 * Return: 1 if character is a digit, 0 otherwise
 */
int is_digit(char character)
{
	if (character >= '0' && character <= '9')
		return (1);

	return (0);
}

/* Function to cast a number to the specified size */
/**
 * convert_size_number - Casts a number to the specified size
 * @number: Number to be casted
 * @size_specifier: Number indicating the type to be casted
 *
 * Return: Casted value of number
 */
long int convert_size_number(long int number, int size_specifier)
{
	if (size_specifier == SIZE_LONG)
		return (number);
	else if (size_specifier == SIZE_SHORT)
		return ((short)number);

	return ((int)number);
}

/* Function to cast a number to the specified size */
/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @number: Number to be casted
 * @size_specifier: Number indicating the type to be casted
 *
 * Return: Casted value of number
 */
long int convert_size_unsgnd(unsigned long int number, int size_specifier)
{
	if (size_specifier == SIZE_LONG)
		return (number);
	else if (size_specifier == SIZE_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}

