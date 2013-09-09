
#include <muskios/kstdio.h>
#include <muskios/kernel.h>
#include <string.h>

void panic(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vpanic(fmt, args);
	va_end(args);
}

void vpanic(const char *fmt, va_list args)
{
	kvprintf(fmt, args);
	halt();
}

void halt(void)
{
	for (;;)
		asm("hlt");
	__builtin_unreachable();
}
