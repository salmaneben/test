#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFFER_SIZE 1024

/* Formatting Flags */
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

/* Size Specifiers */
#define SIZE_LONG 2
#define SIZE_SHORT 1

/**
 * struct format - Struct for format specifiers
 *
 * @format: The format specifier.
 * @function: The function associated with the format specifier.
 */
struct format
{
	char format;
	int (*benx)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct format format_t - Typedef for format struct
 *
 * @format: The format specifier.
 * @format_t: The function associated with the format specifier.
 */
typedef struct format format_t;

int _printf(const char *format_string, ...);
int handle_print(const char *format_specifier, int *index,
va_list arg_list, char print_buffer[], int format_flags, int format_width, int format_precision, int format_size);

/****************** FUNCTIONS ******************/

/* Functions to print characters and strings */
int print_char(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);
int print_string(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);
int print_percent(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);

/* Functions to print numbers */
int print_int(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);
int print_binary(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);
int print_unsigned(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);
int print_octal(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);
int print_hexaxx(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_hexa_vor(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);

int print_hexa(va_list types, char map_to[],
char print_buffer[], int format_flags, char flag_char, int format_width, int format_precision, int format_size);

/* Function to print non printable characters */
int print_non_printable(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);

/* Function to print memory address */
int print_pointer(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);

/* Functions to handle other specifiers */
int get_flags(const char *format_string, int *index);
int get_width(const char *format_string, int *index, va_list arg_list);
int get_precision(const char *format_string, int *index, va_list arg_list);
int get_size(const char *format_string, int *index);

/* Function to print string in reverse */
int print_reverse(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);

/* Function to print a string in rot 13 */
int print_rot13string(va_list types, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);

/* Width handler */
int handle_write_char(char character, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);
int write_number(int is_positive, int index, char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);
int write_num(int index, char buffer[], int format_flags, int format_width, int format_precision,
	int length, char padding, char extra_char);
int write_pointer(char print_buffer[], int index, int length,
	int format_width, int format_flags, char padding, char extra_char, int padding_start);

int write_unsgnd(int is_negative, int index,
char print_buffer[],
	int format_flags, int format_width, int format_precision, int format_size);

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */

