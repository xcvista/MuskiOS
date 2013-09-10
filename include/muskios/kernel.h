
#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <sys/cdefs.h>
#include <stdint.h>
#include <stdarg.h>

__BEGIN_DECLS

extern void kmain(int, const char **);

extern void panic(const char *, ...) __attribute__((noreturn, format(printf, 1, 2)));
extern void vpanic(const char *, va_list) __attribute__((noreturn, format(printf, 1, 0)));
extern void halt(void) __attribute__((noreturn));

#define kpanic(fmt, ...) panic("%s:%d <%s: 0x%x>: PANIC\n" fmt, __FILE__, __LINE__, __PRETTY_FUNCTION__, (size_t)__FUNCTION__, ##__VA_ARGS__)

__END_DECLS

#endif
