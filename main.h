#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

#define SHORT_LENGTH 1
#define LONG_LENGTH 2

typedef struct Buffer {
    char *buffer;
    char *start;
    unsigned int len;
} Buffer;

typedef struct Converter {
    unsigned char specifier;
    unsigned int (*func)(va_list, Buffer *,
        unsigned char, int, int, unsigned char);
} Converter;

typedef struct Flag {
    unsigned char flag;
    unsigned char value;
} Flag;

int custom_printf(const char *format, ...);

unsigned int convert_char(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_string(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_int(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_percent(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_binary(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_unsigned(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_octal(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_hex(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_hex_upper(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_custom_string(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_pointer(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_rot13(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);
unsigned int convert_reverse(va_list args, Buffer *output,
    unsigned char flags, int width, int precision, unsigned char length);

unsigned char extract_flags(const char *flags, char *index);
unsigned char extract_length(const char *modifier, char *index);
int extract_width(va_list args, const char *modifier, char *index);
int extract_precision(va_list args, const char *modifier, char *index);
unsigned int (*get_specifier_function(const char *specifier))(va_list, Buffer *,
    unsigned char, int, int, unsigned char);

unsigned int print_with_width(Buffer *output, unsigned int printed,
    unsigned char flags, int width);
unsigned int print_string_with_width(Buffer *output,
    unsigned char flags, int width, int precision, int size);
unsigned int print_negative_width(Buffer *output, unsigned int printed,
    unsigned char flags, int width);

Buffer *initialize_buffer(void);
void free_buffer(Buffer *output);
unsigned int copy_to_buffer(Buffer *output, const char *src, unsigned int n);
unsigned int convert_signed_base(Buffer *output, long int num, char *base,
    unsigned char flags, int width, int precision);
unsigned int convert_unsigned_base(Buffer *output, unsigned long int num, char *base,
    unsigned char flags, int width, int precision);

#endif /* MAIN_H */
