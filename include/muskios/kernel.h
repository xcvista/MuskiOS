
#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <sys/cdefs.h>
#include <stdint.h>
#include <stdarg.h>

__BEGIN_DECLS

extern void kmain(int, const char **);

extern void panic(const char *, ...) __attribute__((noreturn));
extern void vpanic(const char *, va_list) __attribute__((noreturn));
extern void halt(void) __attribute__((noreturn));

__END_DECLS

#endif
