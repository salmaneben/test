#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @index: Pointer to the current index in the format string
 * Return: Flags:
 */
int get_flags(const char *format, int *index)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int flag_index, current_index; /* Renamed 'j' to 'flag_index' and 'curr_i' to 'current_index'*/
	int flags = 0;
	const char FLAGS_CHARACTERS[] = {'-', '+', '0', '#', ' ', '\0'}; /* Renamed 'FLAGS_CH' to 'FLAGS_CHARACTERS'*/
	const int FLAGS_ARRAY[] = {FLAG_MINUS, FLAG_PLUS, FLAG_ZERO, FLAG_HASH, FLAG_SPACE, 0}; /* Renamed 'FLAGS_ARR' to 'FLAGS_ARRAY'*/

	for (current_index = *index + 1; format[current_index] != '\0'; current_index++)
	{
		for (flag_index = 0; FLAGS_CHARACTERS[flag_index] != '\0'; flag_index++)
			if (format[current_index] == FLAGS_CHARACTERS[flag_index])
			{
				flags |= FLAGS_ARRAY[flag_index];
				break;
			}

		if (FLAGS_CHARACTERS[flag_index] == 0)
			break;
	}

	*index = current_index - 1;

	return (flags);
}

