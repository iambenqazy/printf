#include "main.h"

int _printf(const char *format, ...);
int processPrintf(const char *format, va_list args, Buffer *output);
void performCleanup(va_list args, Buffer *output);

/**
 * performCleanup - Peforms cleanup operations for _printf.
 * @output: A buffer_t struct.
 * @args: A va_list of arguments provided to _printf.
 */

void performCleanup(va_list args, Buffer *output)
{
va_end(args);
write(1, output->start, output->len);
freeBuffer(output);
}

/**
 * processPrintf - Check through the format string for _printf.
 * @output: A buffer_t struct containing a buffer.
 * @format: Character string to print - may contain directives.
 * @args: A va_list of arguments.
 *
 * Return: The characters count stored to output.
 */

int processPrintf(const char *format, va_list args, Buffer *output)
{
int ret = 0;
unsigned char flags, length;
unsigned int (*specifierFunc)(va_list, Buffer *,
		unsigned char, int, int, unsigned char);

for (int i = 0; format[i]; i++)
{
length = 0;
if (format[i] == '%')
{
char tmp = 0;
flags = extractFlags(format + i + 1, &tmp);
int width = extractWidth(args, format + i + tmp + 1, &tmp);
int precision = extractPrecision(args, format + i + tmp + 1, &tmp);
length = extractLength(format + i + tmp + 1, &tmp);

specifierFunc = getSpecifierFunction(format + i + tmp + 1);
if (specifierFunc != NULL)
{
i += tmp + 1;
ret += specifierFunc(args, output, flags, width, precision, length);
continue;
}
else if (format[i + tmp + 1] == '\0')
{
ret = -1;
break;
}
}
ret += copyToBuffer(output, (format + i), 1);
i += (length != 0) ? 1 : 0;
}
performCleanup(args, output);
return (ret);
}

int _printf(const char *format, ...)
{
Buffer *output;
va_list args;
int ret;

if (format == NULL)
return (-1);
output = createBuffer();
if (output == NULL)
return (-1);

va_start(args, format);

ret = processPrintf(format, args, output);

return (ret);
}
