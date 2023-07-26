#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

/* Buffer size */
#define BUFF_SIZE 1024
#define UNUSED(x) (void)(x)

/* Flags */
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_SPACE 16

/* Sizes */
#define SIZE_LONG 2
#define SIZE_SHORT 1

/* Format struct and associated function */
typedef struct format
{
    char fmt;
    int (*fn)(va_list, char[], int, int, int, int);
} format_t;

/* Main function prototype */
int _printf(const char *format, ...);

/* Function prototypes for handling print */
int handle_print(const char *fmt, int *i, va_list list, char buffer[], int flags, int width, int precision, int size);

/* Function prototypes for printing characters, strings, and percent */
int print_character(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Function prototypes for printing numbers */
int print_integer(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_hexa(va_list types, char map_to[], char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Function prototypes for non printable characters and memory address */
int print_non_printable(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_pointer(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Function prototypes for handling other specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/* Function prototypes for printing string in reverse and rot13 */
int print_reverse(va_list types, char buffer[], int flags, int width, int precision, int size);
int print_rot13(va_list types, char buffer[], int flags, int width, int precision, int size);

/* Function prototypes for width handler */
int handle_write_character(char c, char buffer[], int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[], int flags, int width, int precision, int size);
int write_num(int ind, char bff[], int flags, int width, int precision, int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start);
int write_unsigned(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size);

/* Function prototypes for utilities */
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);
long int convert_size_number(long int num, int size);
unsigned long int convert_size_unsigned(unsigned long int num, int size);

#endif /* MAIN_H */

