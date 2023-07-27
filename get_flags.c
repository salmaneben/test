#include "main.h"

/* Function to calculate active flags */
/**
 * get_flags - Determines active flags
 * @format_string: Formatted string in which to print the arguments
 * @index: Pointer to the current index in the format string
 * Return: Flags:
 */
int get_flags(const char *format_string, int *index)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int flag_index, current_index;
	int flags = 0;
	const char FLAGS_CHARACTERS[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARRAY[] = {FLAG_MINUS, FLAG_PLUS, FLAG_ZERO, FLAG_HASH, FLAG_SPACE, 0};

	for (current_index = *index + 1; format_string[current_index] != '\0'; current_index++)
	{
		for (flag_index = 0; FLAGS_CHARACTERS[flag_index] != '\0'; flag_index++)
			if (format_string[current_index] == FLAGS_CHARACTERS[flag_index])
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

