
#ifndef _KERNEL_H_
#define _KERNEL_H_

#include <sys/cdefs.h>

__BEGIN_DECLS

extern void kernel_main(void);
extern void hang(void) __attribute__((noreturn));

extern void _init(void);
extern void _fini(void);

__END_DECLS

#endif
