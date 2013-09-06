
#ifndef _MUSKIOS_KSTDIO_H_
#define _MUSKIOS_KSTDIO_H_

#include <sys/cdefs.h>
#include <stddef.h>
#include <stdarg.h>

__BEGIN_DECLS

#ifndef EOF
#define EOF (-1)
#endif

// Hooks for the drivers to install.
extern int (*kputchar)(int);
extern int (*kgetchar)(void);

extern int kputs(const char *);
extern int kvprintf(const char *, va_list) __attribute__((format(printf, 1, 0)));
extern int kprintf(const char *, ...) __attribute__((format(printf, 1, 2)));

__END_DECLS

#endif
